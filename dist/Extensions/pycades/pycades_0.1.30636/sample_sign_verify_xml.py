import pycades

store = pycades.Store()
store.Open(pycades.CADESCOM_CONTAINER_STORE, pycades.CAPICOM_MY_STORE,
           pycades.CAPICOM_STORE_OPEN_MAXIMUM_ALLOWED)
certs = store.Certificates
assert(certs.Count != 0), "Certificates with private key not found"

signer = pycades.Signer()
signer.Certificate = certs.Item(1)

content_to_sign = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>"
content_to_sign += "<!-- "
content_to_sign += "XML Security Library example: Original XML doc file for sign2 example. "
content_to_sign += "-->"
content_to_sign += "<Envelope xmlns=\"urn:envelope\">"
content_to_sign += "  <Data>"
content_to_sign += "	Hello, World!"
content_to_sign += "  </Data>"
content_to_sign += "  <Node xml:id=\"nodeID\">"
content_to_sign += "	Hello, Node!"
content_to_sign += "  </Node>" + " " + "</Envelope>"

signedXML = pycades.SignedXML()
signedXML.Content = content_to_sign
signedXML.SignatureType = pycades.CADESCOM_XML_SIGNATURE_TYPE_ENVELOPED | pycades.CADESCOM_XADES_BES
signature = signedXML.Sign(signer)
print("--Signature--")
print(signature)
print("----")

signedXML.Content = ""
signedXML.Verify(signature)
assert(signature == signedXML.Content), "Incorrect value of SignedXML.Verify result"
print("Verified successfully")