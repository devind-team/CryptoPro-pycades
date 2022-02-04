import docker
import os
from time import sleep

# SERIAL_NUMBER_LICENSE = '4040M-Y0000-010H9-V526R-78PER'
# root_certificate = os.path.join('./', 'certificates', 'fedulovAs.p7b')
# user_certificate = os.path.join('./', 'certificates', 'bundle-no-pin.zip')

SERIAL_NUMBER_LICENSE = '4040M-Y0000-010H9-V526R-78PER'
root_certificate = os.path.join('./', 'certificates', 'dushanbe', 'cert.p7b')
user_certificate = os.path.join('./', 'certificates', 'dushanbe', 'bundle-no-pin.zip')

client = docker.from_env()

'''
client.containers.run(image='required/cryptopro',
                      auto_remove=True,
                      name='cryptopro_4',
                      ports={'80/tcp': '8095'}
                      )
'''

id_container = client.containers.list(filters={'name': 'cryptopro'})[0].attrs['Id']
container = client.containers.get(id_container)

container.exec_run(cmd=f'cpconfig -license -set {SERIAL_NUMBER_LICENSE}',
                   stdin=True)

# ПЕРЕДЕЛАТЬ НА НОРМАЛЬНОЕ А НЕ ЧЕРЕЗ БАШ
command_root_certificate = f'cat {root_certificate} | docker exec -i cryptopro /scripts/root'
os.system(command_root_certificate)
command_user_certificate = f'cat {user_certificate} | docker exec -i cryptopro /scripts/my'
os.system(command_user_certificate)

container.exec_run(cmd='certmgr -list',
                   stdin=True)

# ДОГАДАТЬСЯ КАК ИЗВЛЕЧЬ ХЕШ

HASH = 'baabcc6b59c42948ce65ba7bed4dd614ee0429c6'

no_signed_dir = os.path.join('./', 'no_signed')
# no_signed_dir = os.path.join('./', 'test', 'anon', 'syllabus')
signed_dir = os.path.join('./', 'signed')
list_files = os.listdir(no_signed_dir)

for file_name in list_files:
    command = f'cat "{no_signed_dir}/{file_name}" | docker exec -i cryptopro /scripts/sign {HASH} > "{signed_dir}/' \
              f'{file_name}.sig"'
    os.system(command)
    command_2 = f'cat "{signed_dir}/{file_name}.sig" | docker exec -i cryptopro scripts/verify'
    os.system(command_2)

# ОБРАТНЫЙ ПЕРЕВОД
unsigned_dir = os.path.join('./', 'unsigned')
list_files = os.listdir(signed_dir)

for file_name in list_files:
    command = f'cat "{signed_dir}/{file_name}" | docker exec -i cryptopro /scripts/unsign {HASH} > "{unsigned_dir}/' \
              f'{file_name}.origin"'
    os.system(command)

