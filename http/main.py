import os
import shutil
import pycades
import base64
from fastapi import \
    FastAPI,\
    File,\
    UploadFile
from fastapi.responses import JSONResponse

app = FastAPI()

"""General signature data"""
store = pycades.Store()
store.Open(pycades.CADESCOM_CONTAINER_STORE, pycades.CAPICOM_MY_STORE, pycades.CAPICOM_STORE_OPEN_MAXIMUM_ALLOWED)
certs = store.Certificates
assert (certs.Count != 0), "Certificates with private key not found"

signer = pycades.Signer()
signer.Certificate = certs.Item(1)
signer.CheckCertificate = True


@app.get('/')
async def main_page():
    docs = 'http://127.0.0.1:8000/docs#/'
    return f'Link to go to interactive API documents {docs}'


@app.get('/certificate')
async def data_certificates():
    ret = []
    for i in range(1, certs.Count+1):
        cert = certs.Item(i)
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
    return JSONResponse(content=ret)


@app.post('/certificate/root')
async def root_certificates(file: UploadFile = File(...)):
    # root_certificate = os.path.join('certificate', 'root', file.filename)
    # with open(root_certificate, 'wb') as buffer:
    #    shutil.copyfileobj(file.file, buffer)
    t = await file.read()
    os.system(f'{t} | /scripts/root')
    return JSONResponse(content={'status': 'Installing a root certificate'})


@app.post('/certificate/user')
async def user_certificates(file: UploadFile = File(...)):
    user_certificate = os.path.join('./', 'certificate', 'user', file.filename)
    with open(user_certificate, 'wb') as buffer:
        content = await file.read()
        buffer.write(content)
        buffer.close()
    os.system(f'cat {user_certificate} | /scripts/my')
    return JSONResponse(content={'status': 'Installing a user certificate'})


@app.post('/license')
async def license_number(serial_number: str):
    os.system(f'cpconfig -license -set {serial_number}')
    return JSONResponse(content={'status': 'Installing a serial number license'})


@app.post('/signer')
async def signer_file(file: UploadFile = File(...)):
    signed_data = pycades.SignedData()
    signed_data.Content = base64.b64encode(await file.read()).decode()
    signature = signed_data.SignCades(signer, pycades.CADESCOM_CADES_BES)
    return JSONResponse(content={'signedContent': signature,
                                 'filename': f'{file.filename}.sig'
                                 })





@app.post('/verify')
async def verified_file(file, file_signer: UploadFile = File(...)):
    return {'verify'}
