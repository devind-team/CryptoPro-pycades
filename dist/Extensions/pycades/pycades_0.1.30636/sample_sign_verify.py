import pycades

store = pycades.Store()
store.Open(pycades.CADESCOM_CONTAINER_STORE, pycades.CAPICOM_MY_STORE,
           pycades.CAPICOM_STORE_OPEN_MAXIMUM_ALLOWED)
certs = store.Certificates
assert(certs.Count != 0), "Certificates with private key not found"

signer = pycades.Signer()
signer.Certificate = certs.Item(1)
signer.CheckCertificate = True

signedData = pycades.SignedData()
signedData.Content = "Test content to be signed"
signature = signedData.SignCades(signer, pycades.CADESCOM_CADES_BES)
print("--Signature--")
print(signature)
print("----")

_signedData = pycades.SignedData()
_signedData.VerifyCades(signature, pycades.CADESCOM_CADES_BES)
print("Verified successfully")
