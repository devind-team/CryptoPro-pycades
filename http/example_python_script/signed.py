import os

# нужно придумать как его получить
# HASH = os.system("`docker exec -i cryptopro certmgr -list | grep 'SHA1 Hash           :' | awk '{print $4}'`")

# 09.03.03_ПИ_ПИЭ_Б1.О.11_Операционные_системы_з_2020.pdf
# ABbzo_220920211230Анн_11.03.04_ЭиНЭ_ПЭ_Б1.О.17_Инженерная и компьютерная графика_о_2019.pdf

HASH = 'baabcc6b59c42948ce65ba7bed4dd614ee0429c6'

no_signed_dir = os.path.join('./', 'no_signed')
# no_signed_dir = os.path.join('./', 'test', 'anon', 'syllabus')
signed_dir = os.path.join('./', 'signed')
list_files = os.listdir(no_signed_dir)

for file_name in list_files:
    # command = f'cat "{no_signed_dir}/{file_name}" | docker exec -i cryptopro /scripts/sign {HASH} > "{signed_dir}/' \
    #          f'{file_name}.sig"'
    # os.system(command)
    command_2 = f'cat "{signed_dir}/{file_name}.sig" | docker exec -i cryptopro scripts/verify'
    os.system(command_2)



