import os, json, shutil
from typing import Optional
from fastapi import \
    FastAPI,\
    Request,\
    File,\
    UploadFile, Header
from pydantic import BaseModel


class Item(BaseModel):
    name: str
    description: Optional[str] = None
    price: float
    tax: Optional[float] = None


app = FastAPI()


@app.post('/items/')
async def create_item(item: Item):
    return item


@app.post('/files/')
async def create_file(file: bytes = File(...)):
    return {'file_size': print(file)}


@app.post("/uploadfile/")
async def create_upload_file(file: UploadFile = File(...)):
    contents = await file.read()

    return {'file_size': file.filename}


@app.get('/')
async def root():
    t = 'Hi'
    return t


@app.post('/certificate/root')
async def certificates_root(file: UploadFile = File(...)):
    root_certificate = os.path.join('certificate', 'root', file.filename)
    with open(root_certificate, 'wb') as buffer:
        shutil.copyfileobj(file.file, buffer)
    os.system(f'cat {root_certificate} | /scripts/root')
    return {'status': 'Root certificate set'}


@app.post('/certificate/user')
async def certificates_root(file: UploadFile = File(...)):
    user_certificate = os.path.join('./', 'certificate', 'user', file.filename)
    with open(user_certificate, 'wb') as buffer:
        content = await file.read()
        buffer.write(content)
        buffer.close()
    os.system(f'cat {user_certificate} | /scripts/my')
    return {'status': 'Root certificate set'}


@app.post('/license')
async def certificates(serial_number: str):
    os.system(f'cpconfig -license -set {serial_number}')
    return {'status': 'Serial number license set'}


@app.post('/signer')
async def certificates():
    return {'signer'}


@app.post('/verify')
async def certificates():
    return {'verify'}

