import os
import shutil
import pycades
import base64
import json
import filecmp
from fastapi import \
    FastAPI,\
    File,\
    UploadFile
from fastapi.responses import \
    JSONResponse, \
    RedirectResponse

app = FastAPI()


async def store_data():
    store = pycades.Store()
    store.Open(pycades.CADESCOM_CONTAINER_STORE, pycades.CAPICOM_MY_STORE, pycades.CAPICOM_STORE_OPEN_MAXIMUM_ALLOWED)
    certs = store.Certificates
    assert (certs.Count != 0), "Certificates with private key not found"
    return certs


async def signature_data():
    certificate = await store_data()
    signer = pycades.Signer()
    signer.Certificate = certificate.Item(1)
    signer.CheckCertificate = True
    return signer


async def write_file(save_file, data_file):
    with open(save_file, 'wb') as buffer:
        shutil.copyfileobj(data_file.file, buffer)


@app.get('/')
async def redirect_page_docs():
    return RedirectResponse('/docs#/')


@app.get('/certificate')
async def data_certificates():
    certificate = await store_data()
    ret = []
    for i in range(1, certificate.Count+1):
        cert = certificate.Item(i)
        issuer = cert.IssuerName.split(',')
        subject = cert.SubjectName.split(',')
        cert_info = {
            'privateKey': {
                'providerName': cert.PrivateKey.ProviderName,
                'uniqueContainerName': cert.PrivateKey.UniqueContainerName,
                'containerName': cert.PrivateKey.ContainerName,
            },
            'algorithm': {
                'name': cert.PublicKey().Algorithm.FriendlyName,
                'val': cert.PublicKey().Algorithm.Value,
            },
            'valid': {
                'from': cert.ValidFromDate,
                'to': cert.ValidToDate,
            },
            'issuer': {
                'C': issuer[8],
                'L': issuer[6],
                'O': issuer[1],
                'CN': issuer[0],
            },
            'subject': {
                'C': subject[4],
                'L': subject[6],
                'O': subject[7],
                'CN': subject[8],
            },
            'thumbprint': cert.Thumbprint,
            'serialNumber': cert.SerialNumber,
            'hasPrivateKey': cert.HasPrivateKey()
        }
        ret.append(cert_info)
    return JSONResponse(content={'certificate': ret})


@app.post('/certificate/root')
async def root_certificates(file: UploadFile = File(...)):
    root_certificate = os.path.join('./', 'tmp', file.filename)
    await write_file(root_certificate, file)
    os.system(f'cat {root_certificate}  | /scripts/root')
    os.remove(root_certificate)
    return JSONResponse(content={'status': 'Root certificate installed'})


@app.post('/certificate/user')
async def user_certificates(file: UploadFile = File(...)):
    user_certificate = os.path.join('./', 'tmp', file.filename)
    await write_file(user_certificate, file)
    os.system(f'cat {user_certificate} | /scripts/my')
    os.remove(user_certificate)
    return JSONResponse(content={'status': 'User certificate installed'})


@app.post('/license')
async def license_number(serial_number: str):
    os.system(f'cpconfig -license -set {serial_number}')
    return JSONResponse(content={'statusLicense': 'Serial number license installed'})


@app.post('/signer')
async def signer_file(file: UploadFile = File(...)):
    signed_data = pycades.SignedData()
    signed_data.Content = base64.b64encode(await file.read()).decode()
    signature = signed_data.SignCades(await signature_data(), pycades.CADESCOM_CADES_BES)
    return JSONResponse(content={'signedContent': signature,
                                 'filename': f'{file.filename}.sig'
                                 })


@app.post('/unsigner')
async def unsigner_file(file: UploadFile = File(...)):
    _signedData = pycades.SignedData()
    _signedData.VerifyCades((await file.read()).decode(), pycades.CADESCOM_CADES_BES)
    return JSONResponse(content={'unsignedContent': _signedData.Content,
                                 'filename': f"{file.filename.replace('.sig', '')}"
                                 })


@app.post('/verify')
async def verified_file(original_file: UploadFile = File(...), signed_file: UploadFile = File(...)):
    tmp_original = os.path.join('tmp', original_file.filename)
    tmp_signed = os.path.join('tmp', signed_file.filename)
    await write_file(tmp_original, original_file)
    with open(tmp_signed, 'wb') as buffer:
        buffer.write(base64.b64decode(json.loads((await unsigner_file(signed_file)).body)['unsignedContent']))
        buffer.close()
    if filecmp.cmp(tmp_original, tmp_signed):
        subject_name = (await signature_data()).Certificate.SubjectName
    else:
        subject_name = 'Error (Maybe the file is signed with a different signature)'
    os.remove(tmp_original)
    os.remove(tmp_signed)
    return JSONResponse(content={'verifyContent': subject_name})
