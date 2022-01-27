import pycades

store = pycades.Store()
store.Open(pycades.CADESCOM_CONTAINER_STORE, pycades.CAPICOM_MY_STORE,
           pycades.CAPICOM_STORE_OPEN_MAXIMUM_ALLOWED)
certs = store.Certificates
assert(certs.Count != 0), "Certificates with private key not found"

cert = certs.Item(1)
envelopedData = pycades.EnvelopedData()
envelopedData.Content = "Message to encrypt с русскими буквами"
envelopedData.Recipients.Add(cert)
encryptedMessage = envelopedData.Encrypt(pycades.CADESCOM_ENCODE_BASE64)
print("--Encrypted Message--")
print(encryptedMessage)
print("----")

envelopedData2 = pycades.EnvelopedData()
envelopedData2.Decrypt(encryptedMessage)
content = envelopedData2.Content
assert(content == "Message to encrypt с русскими буквами"), "Incorrect value of EnvelopedData.Decrypt result"
print("Decrypted successfully")