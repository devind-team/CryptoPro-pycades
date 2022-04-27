import requests
import os
import json
import base64

SETTINGS_SERTIFICATE = {
    # specify the serial number of the license
    'SERIAL_NUMBER_LICENSE': '',
    # specify the path to the root certificate with the extension (p7b)
    'root_certificate': os.path.join('./', 'certificates', 'filename.p7b'),
    # specify the path to the user certificate (archive)
    'user_certificate': os.path.join('./', 'certificates', 'bundle-no-pin.zip')
}
URL = 'http://localhost:8001'  # localhost:8095'


def installation_license():
    """Installing the serial number of the license"""
    url_license = f'{URL}/license?serial_number='
    response = requests.post(f"{url_license}{SETTINGS_SERTIFICATE['SERIAL_NUMBER_LICENSE']}")
    return response


def installation_certificates_root(file):
    """Installing a root certificate"""
    url_root = f'{URL}/certificate/root'
    files = {
        'file': open(file, 'rb'),
        'Accept': 'application/json',
        'Content-Type': 'multipart/form-data'
    }
    response = requests.post(url_root, files=files)
    return response


def installation_certificates_user(file):
    """Installing a user certificate"""
    url_user = f'{URL}/certificate/user'
    files = {
        'file': open(file, 'rb'),
        'Accept': 'application/json',
        'Content-Type': 'multipart/form-data'
    }
    response = requests.post(url_user, files=files)
    return response


def document_signing(dir_no_signed, dir_signed: str):
    """Document signing"""
    url_sign = f'{URL}/signer'
    files = {
        'file': open(dir_no_signed, 'rb'),
        'Accept': 'application/json',
        'Content-Type': 'multipart/form-data'
    }
    response = requests.post(url_sign, files=files)
    with open(os.path.join(dir_signed, json.loads(response.text)['filename']), 'w') as new_file:
        new_file.write(json.loads(response.text)['signedContent'])
    # new_file = open(os.path.join(dir_signed, json.loads(response.text)['filename']), 'w')
    # new_file.write(json.loads(response.text)['signedContent'])
    # new_file.close()


def decryption_signed_document(dir_signed, dir_unsigned: str):
    """Getting the source file"""
    url_unsign = f'{URL}/unsigner'
    files = {
        'file': open(dir_signed, 'rb'),
        'Accept': 'application/json',
        'Content-Type': 'multipart/form-data'
    }
    response = requests.post(url_unsign, files=files)
    with open(os.path.join(dir_unsigned, json.loads(response.text)['filename']), 'wb') as new_file:
        new_file.write(base64.b64decode(json.loads(response.text)['unsignedContent']))
    # new_file = open(os.path.join(dir_unsigned, json.loads(response.text)['filename']), 'wb')
    # new_file.write(base64.b64decode(json.loads(response.text)['unsignedContent']))
    # new_file.close()


def signature_verification(original_file, signed_file: str):
    """Verification of a signed document"""
    url_verify = f'{URL}/verify'
    files = {
        'original_file': open(original_file, 'rb'),
        'signed_file': open(signed_file, 'rb'),
        'Accept': 'application/json',
        'Content-Type': 'multipart/form-data'
    }
    response = requests.post(url_verify, files=files)
    print(json.loads(response.text)['verifyContent'])


installation_license()
installation_certificates_root(SETTINGS_SERTIFICATE['root_certificate'])
installation_certificates_user(SETTINGS_SERTIFICATE['user_certificate'])


no_signed_dir = os.path.join('./', 'no_signed')
signed_dir = os.path.join('./', 'signed')
list_name_no_signed_files = os.listdir(no_signed_dir)

for name_file in list_name_no_signed_files:
    document_signing(os.path.join(no_signed_dir, name_file), signed_dir)

list_name_signed_files = os.listdir(signed_dir)

list_name_no_signed_files.sort()
list_name_signed_files.sort()

for name_file in list_name_no_signed_files:
    signature_verification(os.path.join(no_signed_dir, name_file), os.path.join(signed_dir, f'{name_file}.sig'))

unsigned_dir = os.path.join('./', 'unsigned')
for name_file in list_name_signed_files:
    decryption_signed_document(os.path.join(signed_dir, name_file), unsigned_dir)
