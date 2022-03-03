import pycades


async def store_data():
    store = pycades.Store()
    store.Open(pycades.CADESCOM_CONTAINER_STORE, pycades.CAPICOM_MY_STORE, pycades.CAPICOM_STORE_OPEN_MAXIMUM_ALLOWED)
    certs = store.Certificates
    assert (certs.Count != 0), "Certificates with private key not found"
    return certs


async def signature_data():
    certificate = await store_data()
    signer = pycades.Signer()
    signer.Certificate = certificate.Item(1)
    signer.CheckCertificate = True
    return signer


async def signature_data_pin(pin: str):
    certificate = await store_data()
    signer = pycades.Signer()
    signer.Certificate = certificate.Item(1)
    signer.CheckCertificate = True
    signer.KeyPin = pin
    return signer
