import requests
import docker
import os
import json
import base64

SETTINGS_SERTIFICATE = {
    'SERIAL_NUMBER_LICENSE': '4040M-Y0000-010H9-V526R-78PER',
    'root_certificate': os.path.join('./', 'certificates', 'fedulovAs.p7b'),
    'user_certificate': os.path.join('./', 'certificates', 'bundle-no-pin.zip')
}

REST_URI = 'http://172.17.0.1:8095'  # localhost:8095'


def installation_certificates():
    """Установка сертификатов"""

    client = docker.from_env()
    id_container = client.containers.list(filters={'name': 'cryptopro'})[0].attrs['Id']
    container = client.containers.get(id_container)
    container.exec_run(cmd=f"cpconfig -license -set {SETTINGS_SERTIFICATE['SERIAL_NUMBER_LICENSE']}",
                       stdin=True)
    # ПЕРЕДЕЛАТЬ НА НОРМАЛЬНОЕ А НЕ ЧЕРЕЗ БАШ
    command_root_certificate = f"cat {SETTINGS_SERTIFICATE['root_certificate']} | docker exec -i cryptopro /scripts/root"
    os.system(command_root_certificate)
    command_user_certificate = f"cat {SETTINGS_SERTIFICATE['user_certificate']} | docker exec -i cryptopro /scripts/my"
    os.system(command_user_certificate)

    container.exec_run(cmd='certmgr -list',
                       stdin=True)


def http_certificates():
    """Все установленные сертификаты пользователя"""

    url_certificates = f'{REST_URI}/certificates'
    hash_certificates = json.loads(requests.get(url_certificates).text)['certificates'][0]['thumbprint']
    return hash_certificates


def http_sign(file_name, dir_no_signed, dir_signed: str):
    """Подписание документов"""

    url_sign = f'{REST_URI}/sign?find_type=sha1&query={HASH}'
    headers = {'Content-Type': 'x-www-form-urlencoded'}
    files = open(os.path.join(dir_no_signed, file_name), 'rb')
    response = requests.post(url_sign, headers=headers, data=files)
    new_file = open(os.path.join(dir_signed, f"{file_name}.sig"), 'w')
    new_file.write(json.loads(response.text)['signedContent'])
    new_file.close()


def http_verify(file_name, dir_path: str):
    """Проверка подписанного документа"""

    url_verify = f'{REST_URI}/verify'
    headers = {'Content-Type': 'x-www-form-urlencoded'}
    files = open(os.path.join(dir_path, f'{file_name}'), 'rb')
    response = requests.post(url_verify, headers=headers, data=files)
    print(response.json())


def http_unsign(file_name, dir_signed, dir_unsigned: str):
    """Получение исходного файла без подписей"""

    url_unsign = f'{REST_URI}/unsign'
    headers = {'Content-Type': 'x-www-form-urlencoded'}
    files_sig = open(os.path.join(dir_signed, file_name), 'rb')
    response = requests.post(url_unsign, headers=headers, data=files_sig)
    new_file = open(os.path.join(dir_unsigned, f"{file_name}.origin"), 'wb')
    new_file.write(base64.b64decode(json.loads(response.text)['content']))
    new_file.close()


installation_certificates()
HASH = http_certificates()

no_signed_dir = os.path.join('./', 'no_signed')
# no_signed_dir = os.path.join('./', 'test', 'anon', 'syllabus')
signed_dir = os.path.join('./', 'signed')
list_name_files = os.listdir(no_signed_dir)

for name_file in list_name_files:
    http_sign(name_file, no_signed_dir, signed_dir)

list_name_files = os.listdir(signed_dir)

for name_file in list_name_files:
    http_verify(name_file, signed_dir)

unsigned_dir = os.path.join('./', 'unsigned')
for name_file in list_name_files:
    http_unsign(name_file, signed_dir, unsigned_dir)



