import os, json, shutil
from typing import Optional
from fastapi import \
    FastAPI,\
    Request,\
    File,\
    UploadFile, Path, Query


app = FastAPI()


@app.post('/certificate/root/{name}')
async def certificates_root(name: str, file: UploadFile = File(...)):
    root_certificate = os.path.join('certificate', 'root', f'{name}')
    with open(root_certificate, 'wb') as buffer:
        shutil.copyfileobj(file.file, buffer)
    os.system(f'cat {root_certificate} | /scripts/root | touch 1.txt')


@app.post('/certificate/user/{name}')
async def certificates_root(name: str, file: UploadFile = File(...)):
    user_certificate = os.path.join('./', 'certificate', 'user', f'{name}')
    with open(user_certificate, 'wb') as buffer:
        content = await file.read()
        buffer.write(content)
        buffer.close()
    os.system(f'cat {user_certificate} | /scripts/my')


@app.get('/')
async def root():
    t = 'Hi'
    return t


@app.get('/license/{serial_number}')
async def certificates(serial_number: str):
    os.system(f'cpconfig -license -set {serial_number}')


@app.post('/signer')
async def certificates():
    return {'signer'}


@app.post('/verify')
async def certificates():
    return {'verify'}

