#include <Python.h>
#include "PyCadesAbout.h"
#include "PyCadesAlgorithm.h"
#include "PyCadesAttribute.h"
#include "PyCadesAttributes.h"
#include "PyCadesBasicConstraints.h"
#include "PyCadesBlobs.h"
#include "PyCadesCertificate.h"
#include "PyCadesCertificates.h"
#include "PyCadesCertificateStatus.h"
#include "PyCadesCRL.h"
#include "PyCadesEncodedData.h"
#include "PyCadesEnvelopedData.h"
#include "PyCadesEKU.h"
#include "PyCadesEKUs.h"
#include "PyCadesExtendedKeyUsage.h"
#include "PyCadesHashedData.h"
#include "PyCadesKeyUsage.h"
#include "PyCadesOID.h"
#include "PyCadesPrivateKey.h"
#include "PyCadesPublicKey.h"
#include "PyCadesRawSignature.h"
#include "PyCadesRecipients.h"
#include "PyCadesSignatureStatus.h"
#include "PyCadesSignedData.h"
#include "PyCadesSignedXML.h"
#include "PyCadesSigner.h"
#include "PyCadesSigners.h"
#include "PyCadesStore.h"
#include "PyCadesSymmetricAlgorithm.h"
#include "PyCadesVersion.h"

#define PYCADES_VERSION "0.1.30636"
static PyObject * pycades_ModuleVersion(PyObject *self, PyObject *args)
{
    return Py_BuildValue("s", PYCADES_VERSION);
}

static PyMethodDef pycadesMethods[] = {
    {"ModuleVersion", pycades_ModuleVersion, METH_NOARGS, "pycades module version"},
    {NULL, NULL, 0, NULL}};

PyMODINIT_FUNC PyInit_pycades(void) {
    static struct PyModuleDef moduledef = {
        PyModuleDef_HEAD_INIT,
        "pycades",
        "pycades",
        -1,
        pycadesMethods,
        NULL,
        NULL,
        NULL,
        NULL
    };

    PyObject *module = PyModule_Create(&moduledef);
    if (!module){
        PyErr_SetString(PyExc_RuntimeError, "Cannot create pycades object");
        return NULL;
    }

    if (PyType_Ready (&AboutType) < 0){
        PyErr_SetString(PyExc_RuntimeError, "Cannot create About object");
        return NULL;
    }
    Py_INCREF(&AboutType);
    PyModule_AddObject(module, "About", (PyObject *)&AboutType);

    if (PyType_Ready (&AlgorithmType) < 0){
        PyErr_SetString(PyExc_RuntimeError, "Cannot create Algorithm object");
        return NULL;
    }
    Py_INCREF(&AlgorithmType);

    if (PyType_Ready (&AttributeType) < 0){
        PyErr_SetString(PyExc_RuntimeError, "Cannot create Attribute object");
        return NULL;
    }
    Py_INCREF(&AttributeType);
    PyModule_AddObject(module, "Attribute", (PyObject *)&AttributeType);

    if (PyType_Ready (&AttributesType) < 0){
        PyErr_SetString(PyExc_RuntimeError, "Cannot create Attributes object");
        return NULL;
    }
    Py_INCREF(&AttributesType);

    if (PyType_Ready (&BasicConstraintsType) < 0){
        PyErr_SetString(PyExc_RuntimeError, "Cannot create BasicConstraints object");
        return NULL;
    }
    Py_INCREF(&BasicConstraintsType);

    if (PyType_Ready (&BlobsType) < 0){
        PyErr_SetString(PyExc_RuntimeError, "Cannot create Blobs object");
        return NULL;
    }
    Py_INCREF(&BlobsType);

    if (PyType_Ready (&CertificateType) < 0){
        PyErr_SetString(PyExc_RuntimeError, "Cannot create Certificate object");
        return NULL;
    }
    Py_INCREF(&CertificateType);
    PyModule_AddObject(module, "Certificate", (PyObject *)&CertificateType);

    if (PyType_Ready (&CertificatesType) < 0){
        PyErr_SetString(PyExc_RuntimeError, "Cannot create Certificates object");
        return NULL;
    }
    Py_INCREF(&CertificatesType);

    if (PyType_Ready (&CertificateStatusType) < 0){
        PyErr_SetString(PyExc_RuntimeError, "Cannot create CertificateStatus object");
        return NULL;
    }
    Py_INCREF(&CertificateStatusType);

    if (PyType_Ready (&CRLType) < 0){
        PyErr_SetString(PyExc_RuntimeError, "Cannot create CRL object");
        return NULL;
    }
    Py_INCREF(&CRLType);
    PyModule_AddObject(module, "CRL", (PyObject *)&CRLType);

    if (PyType_Ready (&EncodedDataType) < 0){
        PyErr_SetString(PyExc_RuntimeError, "Cannot create EncodedData object");
        return NULL;
    }
    Py_INCREF(&EncodedDataType);

    if (PyType_Ready (&EnvelopedDataType) < 0){
        PyErr_SetString(PyExc_RuntimeError, "Cannot create EnvelopedData object");
        return NULL;
    }
    Py_INCREF(&EnvelopedDataType);
    PyModule_AddObject(module, "EnvelopedData", (PyObject *)&EnvelopedDataType);

    if (PyType_Ready (&ExtendedKeyUsageType) < 0){
        PyErr_SetString(PyExc_RuntimeError, "Cannot create ExtendedKeyUsage object");
        return NULL;
    }
    Py_INCREF(&ExtendedKeyUsageType);

    if (PyType_Ready (&EKUType) < 0){
        PyErr_SetString(PyExc_RuntimeError, "Cannot create EKU object");
        return NULL;
    }
    Py_INCREF(&EKUType);

    if (PyType_Ready (&EKUsType) < 0){
        PyErr_SetString(PyExc_RuntimeError, "Cannot create EKUs object");
        return NULL;
    }
    Py_INCREF(&EKUsType);

    if (PyType_Ready (&HashedDataType) < 0){
        PyErr_SetString(PyExc_RuntimeError, "Cannot create HashedData object");
        return NULL;
    }
    Py_INCREF(&HashedDataType);
    PyModule_AddObject(module, "HashedData", (PyObject *)&HashedDataType);

    if (PyType_Ready (&KeyUsageType) < 0){
        PyErr_SetString(PyExc_RuntimeError, "Cannot create KeyUsage object");
        return NULL;
    }
    Py_INCREF(&KeyUsageType);

    if (PyType_Ready (&OIDType) < 0){
        PyErr_SetString(PyExc_RuntimeError, "Cannot create OID object");
        return NULL;
    }
    Py_INCREF(&OIDType);

    if (PyType_Ready (&PrivateKeyType) < 0){
        PyErr_SetString(PyExc_RuntimeError, "Cannot create PrivateKey object");
        return NULL;
    }
    Py_INCREF(&PrivateKeyType);

    if (PyType_Ready (&PublicKeyType) < 0){
        PyErr_SetString(PyExc_RuntimeError, "Cannot create PublicKey object");
        return NULL;
    }
    Py_INCREF(&PublicKeyType);

    if (PyType_Ready (&RawSignatureType) < 0){
        PyErr_SetString(PyExc_RuntimeError, "Cannot create RawSignature object");
        return NULL;
    }
    Py_INCREF(&RawSignatureType);
    PyModule_AddObject(module, "RawSignature", (PyObject *)&RawSignatureType);

    if (PyType_Ready (&RecipientsType) < 0){
        PyErr_SetString(PyExc_RuntimeError, "Cannot create Recipients object");
        return NULL;
    }
    Py_INCREF(&RecipientsType);

    if (PyType_Ready (&SignatureStatusType) < 0){
        PyErr_SetString(PyExc_RuntimeError, "Cannot create SignatureStatus object");
        return NULL;
    }
    Py_INCREF(&SignatureStatusType);

    if (PyType_Ready (&SignedDataType) < 0){
        PyErr_SetString(PyExc_RuntimeError, "Cannot create SignedData object");
        return NULL;
    }
    Py_INCREF(&SignedDataType);
    PyModule_AddObject(module, "SignedData", (PyObject *)&SignedDataType);

    if (PyType_Ready (&SignedXMLType) < 0){
        PyErr_SetString(PyExc_RuntimeError, "Cannot create SignedXML object");
        return NULL;
    }
    Py_INCREF(&SignedXMLType);
    PyModule_AddObject(module, "SignedXML", (PyObject *)&SignedXMLType);

    if (PyType_Ready (&SignerType) < 0){
        PyErr_SetString(PyExc_RuntimeError, "Cannot create Signer object");
        return NULL;
    }
    Py_INCREF(&SignerType);
    PyModule_AddObject(module, "Signer", (PyObject *)&SignerType);

    if (PyType_Ready (&SignersType) < 0){
        PyErr_SetString(PyExc_RuntimeError, "Cannot create Signers object");
        return NULL;
    }
    Py_INCREF(&SignersType);

    if (PyType_Ready (&StoreType) < 0){
        PyErr_SetString(PyExc_RuntimeError, "Cannot create Store object");
        return NULL;
    }
    Py_INCREF(&StoreType);
    PyModule_AddObject(module, "Store", (PyObject *)&StoreType);

    if (PyType_Ready (&SymmetricAlgorithmType) < 0){
        PyErr_SetString(PyExc_RuntimeError, "Cannot create SymmetricAlgorithm object");
        return NULL;
    }
    Py_INCREF(&SymmetricAlgorithmType);
    PyModule_AddObject(module, "SymmetricAlgorithm", (PyObject *)&SymmetricAlgorithmType);

    if (PyType_Ready (&VersionType) < 0){
        PyErr_SetString(PyExc_RuntimeError, "Cannot create Version object");
        return NULL;
    }
    Py_INCREF(&VersionType);


    PyModule_AddIntConstant(module, "CADESCOM_STRING_TO_UCS2LE", 0);
    PyModule_AddIntConstant(module, "CADESCOM_BASE64_TO_BINARY", 1);
    PyModule_AddIntConstant(module, "CAPICOM_LOCAL_MACHINE_STORE", 1);
    PyModule_AddIntConstant(module, "CAPICOM_CURRENT_USER_STORE", 2);
    PyModule_AddIntConstant(module, "CADESCOM_MEMORY_STORE", 0);
    PyModule_AddIntConstant(module, "CADESCOM_LOCAL_MACHINE_STORE", 1);
    PyModule_AddIntConstant(module, "CADESCOM_CURRENT_USER_STORE", 2);
    PyModule_AddIntConstant(module, "CADESCOM_CONTAINER_STORE", 100);
    PyModule_AddIntConstant(module, "CAPICOM_STORE_OPEN_MAXIMUM_ALLOWED", 2);
    PyModule_AddIntConstant(module, "CADESCOM_XML_SIGNATURE_TYPE_ENVELOPED", 0);
    PyModule_AddIntConstant(module, "CADESCOM_XML_SIGNATURE_TYPE_ENVELOPING", 1);
    PyModule_AddIntConstant(module, "CADESCOM_XML_SIGNATURE_TYPE_TEMPLATE", 2);
    PyModule_AddIntConstant(module, "CADESCOM_CADES_DEFAULT", 0);
    PyModule_AddIntConstant(module, "CADESCOM_CADES_BES", 1);
    PyModule_AddIntConstant(module, "CADESCOM_CADES_T", 0x5);
    PyModule_AddIntConstant(module, "CADESCOM_CADES_X_LONG_TYPE_1", 0x5d);
    PyModule_AddIntConstant(module, "CADESCOM_PKCS7_TYPE", 0xffff);
    PyModule_AddIntConstant(module, "CADESCOM_ENCODE_BASE64", 0);
    PyModule_AddIntConstant(module, "CADESCOM_ENCODE_BINARY", 1);
    PyModule_AddIntConstant(module, "CADESCOM_XADES_DEFAULT", 0x00000010);
    PyModule_AddIntConstant(module, "CADESCOM_XADES_BES", 0x00000020);
    PyModule_AddIntConstant(module, "CADESCOM_XADES_T", 0x00000050);
    PyModule_AddIntConstant(module, "CADESCOM_XADES_X_LONG_TYPE_1", 0x000005d0);
    PyModule_AddIntConstant(module, "CADESCOM_XADES_A", 0x000007d0);
    PyModule_AddIntConstant(module, "CADESCOM_XMLDSIG_TYPE", 0);
    PyModule_AddIntConstant(module, "CAPICOM_CERTIFICATE_INCLUDE_WHOLE_CHAIN", 1);
    PyModule_AddIntConstant(module, "CAPICOM_CERTIFICATE_INCLUDE_END_ENTITY_ONLY", 2);
    PyModule_AddIntConstant(module, "CAPICOM_CERTIFICATE_INCLUDE_CHAIN_EXCEPT_ROOT", 0);
    PyModule_AddIntConstant(module, "CAPICOM_CERTIFICATE_INCLUDE_WHOLE_CHAIN", 1);
    PyModule_AddIntConstant(module, "CAPICOM_CERT_INFO_SUBJECT_SIMPLE_NAME", 0);
    PyModule_AddIntConstant(module, "CAPICOM_CERT_INFO_ISSUER_SIMPLE_NAME", 1);
    PyModule_AddIntConstant(module, "CAPICOM_CERTIFICATE_FIND_SHA1_HASH", 0);
    PyModule_AddIntConstant(module, "CAPICOM_CERTIFICATE_FIND_SUBJECT_NAME", 1);
    PyModule_AddIntConstant(module, "CAPICOM_CERTIFICATE_FIND_ISSUER_NAME", 2);
    PyModule_AddIntConstant(module, "CAPICOM_CERTIFICATE_FIND_ROOT_NAME", 3);
    PyModule_AddIntConstant(module, "CAPICOM_CERTIFICATE_FIND_TEMPLATE_NAME", 4);
    PyModule_AddIntConstant(module, "CAPICOM_CERTIFICATE_FIND_EXTENSION", 5);
    PyModule_AddIntConstant(module, "CAPICOM_CERTIFICATE_FIND_EXTENDED_PROPERTY", 6);
    PyModule_AddIntConstant(module, "CAPICOM_CERTIFICATE_FIND_APPLICATION_POLICY", 7);
    PyModule_AddIntConstant(module, "CAPICOM_CERTIFICATE_FIND_CERTIFICATE_POLICY", 8);
    PyModule_AddIntConstant(module, "CAPICOM_CERTIFICATE_FIND_TIME_VALID", 9);
    PyModule_AddIntConstant(module, "CAPICOM_CERTIFICATE_FIND_TIME_NOT_YET_VALID", 10);
    PyModule_AddIntConstant(module, "CAPICOM_CERTIFICATE_FIND_TIME_EXPIRED", 11);
    PyModule_AddIntConstant(module, "CAPICOM_CERTIFICATE_FIND_KEY_USAGE", 12);
    PyModule_AddIntConstant(module, "CAPICOM_DIGITAL_SIGNATURE_KEY_USAGE", 128);
    PyModule_AddIntConstant(module, "CAPICOM_PROPID_ENHKEY_USAGE", 9);
    PyModule_AddIntConstant(module, "CAPICOM_OID_OTHER", 0);
    PyModule_AddIntConstant(module, "CAPICOM_OID_KEY_USAGE_EXTENSION", 10);
    PyModule_AddIntConstant(module, "CAPICOM_ENCODE_BINARY", 1);
    PyModule_AddIntConstant(module, "CAPICOM_ENCODE_ANY", 0xffffffff);
    PyModule_AddIntConstant(module, "CAPICOM_EKU_OTHER", 0);
    PyModule_AddIntConstant(module, "CAPICOM_EKU_SERVER_AUTH", 1);
    PyModule_AddIntConstant(module, "CAPICOM_EKU_CLIENT_AUTH", 2);
    PyModule_AddIntConstant(module, "CAPICOM_EKU_CODE_SIGNING", 3);
    PyModule_AddIntConstant(module, "CAPICOM_EKU_EMAIL_PROTECTION", 4);
    PyModule_AddIntConstant(module, "CAPICOM_EKU_SMARTCARD_LOGON", 5);
    PyModule_AddIntConstant(module, "CAPICOM_AUTHENTICATED_ATTRIBUTE_SIGNING_TIME", 0);
    PyModule_AddIntConstant(module, "CAPICOM_AUTHENTICATED_ATTRIBUTE_DOCUMENT_NAME", 1);
    PyModule_AddIntConstant(module, "CAPICOM_AUTHENTICATED_ATTRIBUTE_DOCUMENT_DESCRIPTION", 2);
    PyModule_AddIntConstant(module, "CADESCOM_AUTHENTICATED_ATTRIBUTE_SIGNING_TIME", 0);
    PyModule_AddIntConstant(module, "CADESCOM_AUTHENTICATED_ATTRIBUTE_DOCUMENT_NAME", 1);
    PyModule_AddIntConstant(module, "CADESCOM_AUTHENTICATED_ATTRIBUTE_DOCUMENT_DESCRIPTION", 2);
    PyModule_AddIntConstant(module, "CADESCOM_ATTRIBUTE_OTHER", -1);
    PyModule_AddIntConstant(module, "CADESCOM_DISPLAY_DATA_NONE", 0);
    PyModule_AddIntConstant(module, "CADESCOM_DISPLAY_DATA_CONTENT", 1);
    PyModule_AddIntConstant(module, "CADESCOM_DISPLAY_DATA_ATTRIBUTE", 2);
    PyModule_AddIntConstant(module, "CADESCOM_ENCRYPTION_ALGORITHM_RC2", 0);
    PyModule_AddIntConstant(module, "CADESCOM_ENCRYPTION_ALGORITHM_RC4", 1);
    PyModule_AddIntConstant(module, "CADESCOM_ENCRYPTION_ALGORITHM_DES", 2);
    PyModule_AddIntConstant(module, "CADESCOM_ENCRYPTION_ALGORITHM_3DES", 3);
    PyModule_AddIntConstant(module, "CADESCOM_ENCRYPTION_ALGORITHM_AES", 4);
    PyModule_AddIntConstant(module, "CADESCOM_ENCRYPTION_ALGORITHM_GOST_28147_89", 25);
    PyModule_AddIntConstant(module, "CADESCOM_HASH_ALGORITHM_SHA1", 0);
    PyModule_AddIntConstant(module, "CADESCOM_HASH_ALGORITHM_MD2", 1);
    PyModule_AddIntConstant(module, "CADESCOM_HASH_ALGORITHM_MD4", 2);
    PyModule_AddIntConstant(module, "CADESCOM_HASH_ALGORITHM_MD5", 3);
    PyModule_AddIntConstant(module, "CADESCOM_HASH_ALGORITHM_SHA_256", 4);
    PyModule_AddIntConstant(module, "CADESCOM_HASH_ALGORITHM_SHA_384", 5);
    PyModule_AddIntConstant(module, "CADESCOM_HASH_ALGORITHM_SHA_512", 6);
    PyModule_AddIntConstant(module, "CADESCOM_HASH_ALGORITHM_CP_GOST_3411", 100);
    PyModule_AddIntConstant(module, "CADESCOM_HASH_ALGORITHM_CP_GOST_3411_2012_256", 101);
    PyModule_AddIntConstant(module, "CADESCOM_HASH_ALGORITHM_CP_GOST_3411_2012_512", 102);
    PyModule_AddIntConstant(module, "CADESCOM_HASH_ALGORITHM_CP_GOST_3411_HMAC", 110);
    PyModule_AddIntConstant(module, "CADESCOM_HASH_ALGORITHM_CP_GOST_3411_2012_256_HMAC", 111);
    PyModule_AddIntConstant(module, "CADESCOM_HASH_ALGORITHM_CP_GOST_3411_2012_512_HMAC", 112);
    PyModule_AddIntConstant(module, "CADESCOM_AllowNone", 0x00);
    PyModule_AddIntConstant(module, "CADESCOM_AllowNoOutstandingRequest", 0x01);
    PyModule_AddIntConstant(module, "CADESCOM_AllowUntrustedCertificate", 0x02);
    PyModule_AddIntConstant(module, "CADESCOM_AllowUntrustedRoot", 0x04);
    PyModule_AddIntConstant(module, "CADESCOM_SkipInstallToStore", 0x10000000);
    PyModule_AddIntConstant(module, "ENABLE_CARRIER_TYPE_CSP", 0x01);
    PyModule_AddIntConstant(module, "ENABLE_CARRIER_TYPE_FKC_NO_SM", 0x02);
    PyModule_AddIntConstant(module, "ENABLE_CARRIER_TYPE_FKC_SM", 0x04);
    PyModule_AddIntConstant(module, "ENABLE_ANY_CARRIER_TYPE", 0x07);
    PyModule_AddIntConstant(module, "DISABLE_EVERY_CARRIER_OPERATION", 0x00);
    PyModule_AddIntConstant(module, "ENABLE_CARRIER_OPEN_ENUM", 0x01);
    PyModule_AddIntConstant(module, "ENABLE_CARRIER_CREATE", 0x02);
    PyModule_AddIntConstant(module, "ENABLE_ANY_OPERATION", 0x03);
    PyModule_AddIntConstant(module, "MEDIA_TYPE_REGISTRY", 0x00000001);
    PyModule_AddIntConstant(module, "MEDIA_TYPE_HDIMAGE", 0x00000002);
    PyModule_AddIntConstant(module, "MEDIA_TYPE_CLOUD", 0x00000004);
    PyModule_AddIntConstant(module, "MEDIA_TYPE_SCARD", 0x00000008);
    PyModule_AddIntConstant(module, "XCN_CRYPT_STRING_BASE64HEADER", 0);
    PyModule_AddIntConstant(module, "AT_KEYEXCHANGE", 1);
    PyModule_AddIntConstant(module, "AT_SIGNATURE", 2);
    PyModule_AddIntConstant(module, "CAPICOM_ENCODE_BASE64", 0);
    PyModule_AddIntConstant(module, "CADESCOM_ENCODE_ANY", -1);
    PyModule_AddIntConstant(module, "CAPICOM_OID_OTHER", 0);
    PyModule_AddIntConstant(module, "CAPICOM_EKU_OTHER", 0);
    PyModule_AddIntConstant(module, "CAPICOM_EKU_SERVER_AUTH", 1);
    PyModule_AddIntConstant(module, "CAPICOM_EKU_CLIENT_AUTH", 2);
    PyModule_AddIntConstant(module, "CAPICOM_EKU_CODE_SIGNING", 3);
    PyModule_AddIntConstant(module, "CAPICOM_EKU_EMAIL_PROTECTION", 4);
    PyModule_AddIntConstant(module, "CAPICOM_EKU_SMARTCARD_LOGON", 5);
    PyModule_AddIntConstant(module, "CAPICOM_EKU_ENCRYPTING_FILE_SYSTEM", 6);
    PyModule_AddIntConstant(module, "CAPICOM_CERT_INFO_ISSUER_SIMPLE_NAME", 1);
    PyModule_AddIntConstant(module, "CAPICOM_CERT_INFO_SUBJECT_EMAIL_NAME", 2);
    PyModule_AddIntConstant(module, "CAPICOM_CERT_INFO_ISSUER_EMAIL_NAME", 3);
    PyModule_AddIntConstant(module, "CAPICOM_CERT_INFO_SUBJECT_UPN", 4);
    PyModule_AddIntConstant(module, "CAPICOM_CERT_INFO_ISSUER_UPN", 5);
    PyModule_AddIntConstant(module, "CAPICOM_CERT_INFO_SUBJECT_DNS_NAME", 6);
    PyModule_AddIntConstant(module, "CAPICOM_CERT_INFO_ISSUER_DNS_NAME", 7);
    PyModule_AddIntConstant(module, "CAPICOM_PROPID_KEY_PROV_INFO", 2);
    PyModule_AddIntConstant(module, "CAPICOM_ENCRYPTION_KEY_LENGTH_MAXIMUM", 0);
    PyModule_AddIntConstant(module, "CAPICOM_ENCRYPTION_KEY_LENGTH_40_BITS", 1);
    PyModule_AddIntConstant(module, "CAPICOM_ENCRYPTION_KEY_LENGTH_56_BITS", 2);
    PyModule_AddIntConstant(module, "CAPICOM_ENCRYPTION_KEY_LENGTH_128_BITS", 3);
    PyModule_AddIntConstant(module, "CAPICOM_ENCRYPTION_KEY_LENGTH_192_BITS", 4);
    PyModule_AddIntConstant(module, "CAPICOM_ENCRYPTION_KEY_LENGTH_256_BITS", 5);
    PyModule_AddIntConstant(module, "CAPICOM_DATA_ENCIPHERMENT_KEY_USAGE", 16);
    PyModule_AddIntConstant(module, "CAPICOM_DIGITAL_SIGNATURE_KEY_USAGE", 128);
    PyModule_AddIntConstant(module, "CAPICOM_CERT_INFO_SUBJECT_SIMPLE_NAME", 0);
    PyModule_AddIntConstant(module, "CAPICOM_CERTIFICATE_FIND_KEY_USAGE", 12);

    PyModule_AddStringConstant(module, "CAPICOM_MY_STORE", "My");
    PyModule_AddStringConstant(module, "CAPICOM_CA_STORE", "CA");
    PyModule_AddStringConstant(module, "CAPICOM_ROOT_STORE", "Root");
    PyModule_AddStringConstant(module, "CAPICOM_OTHER_STORE", "AddressBook");
    PyModule_AddStringConstant(module, "XmlDsigGost3410UrlObsolete", "http://www.w3.org/2001/04/xmldsig-more#gostr34102001-gostr3411");
    PyModule_AddStringConstant(module, "XmlDsigGost3411UrlObsolete", "http://www.w3.org/2001/04/xmldsig-more#gostr3411");
    PyModule_AddStringConstant(module, "XmlDsigGost3410Url", "urn:ietf:params:xml:ns:cpxmlsec:algorithms:gostr34102001-gostr3411");
    PyModule_AddStringConstant(module, "XmlDsigGost3411Url", "urn:ietf:params:xml:ns:cpxmlsec:algorithms:gostr3411");
    PyModule_AddStringConstant(module, "XmlDsigGost3410Url2012256", "urn:ietf:params:xml:ns:cpxmlsec:algorithms:gostr34102012-gostr34112012-256");
    PyModule_AddStringConstant(module, "XmlDsigGost3411Url2012256", "urn:ietf:params:xml:ns:cpxmlsec:algorithms:gostr34112012-256");
    PyModule_AddStringConstant(module, "XmlDsigGost3410Url2012512", "urn:ietf:params:xml:ns:cpxmlsec:algorithms:gostr34102012-gostr34112012-512");
    PyModule_AddStringConstant(module, "XmlDsigGost3411Url2012512", "urn:ietf:params:xml:ns:cpxmlsec:algorithms:gostr34112012-512");

    return module;
}

