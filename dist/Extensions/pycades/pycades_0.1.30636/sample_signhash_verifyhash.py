import pycades

store = pycades.Store()
store.Open(pycades.CADESCOM_CONTAINER_STORE, pycades.CAPICOM_MY_STORE,
           pycades.CAPICOM_STORE_OPEN_MAXIMUM_ALLOWED)
certs = store.Certificates
assert(certs.Count != 0), "Certificates with private key not found"

signer = pycades.Signer()
signer.Certificate = certs.Item(1)
signer.CheckCertificate = True

hashedData = pycades.HashedData()
hashedData.Algorithm = pycades.CADESCOM_HASH_ALGORITHM_CP_GOST_3411_2012_256
hashedData.Hash("test data")

signedData = pycades.SignedData()
signature = signedData.SignHash(hashedData, signer, pycades.CADESCOM_CADES_BES)
print("--Signature--")
print(signature)
print("----")

_signedData = pycades.SignedData()
_signedData.VerifyHash(hashedData, signature, pycades.CADESCOM_CADES_BES)
print("Verified successfully")
