import os, requests

URL = 'http://127.0.0.1:8000/files/'
# URL = 'http://127.0.0.1:8000/certificate/root'

file_name = 'test.pdf'
file = os.path.join('./', 'example_http', file_name)

files = {
    'file': open(file, 'rb'),
    # 'type': 'application/pdf',
    'Accept': 'application/json',
    'Content-Type': 'multipart/form-data'
}

response = requests.post(URL, files=files)
