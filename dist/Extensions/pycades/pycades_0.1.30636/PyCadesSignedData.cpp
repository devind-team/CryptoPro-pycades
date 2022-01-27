#include "PyCadesSignedData.h"
#include "PyCadesSigner.h"
#include "PyCadesSigners.h"
#include "PyCadesCertificates.h"
#include "PyCadesHashedData.h"
#include "PyCadesStore.h"

#include <iostream>
#include <fstream>
using namespace CryptoPro::PKI::CAdES;

static void SignedData_dealloc(SignedData *self)
{
    Py_TYPE(self)->tp_free((PyObject *)self);
}

static PyObject *SignedData_new(PyTypeObject *type, PyObject *args, PyObject *kwds)
{
    SignedData *self;
    self = (SignedData *)type->tp_alloc(type, 0);
    if (self != NULL)
    {
        self->m_pCppCadesImpl = new CPPCadesSignedDataObject();
    }
    return (PyObject *)self;
}

static PyObject *SignedData_SignCades(SignedData *self, PyObject *args)
{
    PyObject *pPySigner = NULL;
    long lCadesType = CADESCOM_CADES_DEFAULT;
    long lEncodingType = CAPICOM_ENCODE_BASE64;
    int bDetached = 0;
    if (!PyArg_ParseTuple(args, "|O!lil", &SignerType, &pPySigner, &lCadesType, &bDetached, &lEncodingType))
    {
        return NULL;
    }

    CAPICOM_ENCODING_TYPE EncodingType = (CAPICOM_ENCODING_TYPE)lEncodingType;
    CADESCOM_CADES_TYPE CadesType = (CADESCOM_CADES_TYPE)lCadesType;

    boost::shared_ptr<CryptoPro::PKI::CAdES::CPPCadesCPSignerObject> pSignerCppCadesImpl;
    if (pPySigner)
    {
        Signer *pSigner = (Signer *)pPySigner;
        pSignerCppCadesImpl = pSigner->m_pCppCadesImpl;
    }

    CryptoPro::CBlob blobSignedMessage;
    HR_METHOD_ERRORCHECK_RETURN(self->m_pCppCadesImpl->SignCades(
        pSignerCppCadesImpl, CadesType, bDetached, EncodingType, &blobSignedMessage));

    CAtlString sSignedMessage = CAtlString((const char *)blobSignedMessage.pbData(), blobSignedMessage.cbData());
    return EncodingType == CAPICOM_ENCODE_BINARY ? 
        PyBytes_FromStringAndSize((const char *)blobSignedMessage.pbData(), blobSignedMessage.cbData()) : 
        Py_BuildValue("s", sSignedMessage.GetString());
}

static PyObject *SignedData_SignHash(SignedData *self, PyObject *args)
{
    PyObject *pPySigner = NULL;
    PyObject *pPyHashedData = NULL;
    long lCadesType = CADESCOM_CADES_DEFAULT;
    long lEncodingType = CAPICOM_ENCODE_BASE64;
    if (!PyArg_ParseTuple(args, "O!|O!ll", &HashedDataType, &pPyHashedData, &SignerType, &pPySigner, &lCadesType, &lEncodingType))
    {
        return NULL;
    }

    CADESCOM_CADES_TYPE CadesType = (CADESCOM_CADES_TYPE)lCadesType;
    CAPICOM_ENCODING_TYPE EncodingType = (CAPICOM_ENCODING_TYPE)lEncodingType;

    Signer *pSigner = (Signer *)pPySigner;
    HashedData *pHashedData = (HashedData *)pPyHashedData;

    CryptoPro::CBlob blobValue;
    HR_METHOD_ERRORCHECK_RETURN(self->m_pCppCadesImpl->SignHash(
        pSigner->m_pCppCadesImpl, pHashedData->m_pCppCadesImpl, CadesType, EncodingType, &blobValue));

    CAtlString sValue = CAtlString((const char *)blobValue.pbData(), blobValue.cbData());
    return EncodingType == CAPICOM_ENCODE_BINARY ? 
        PyBytes_FromStringAndSize((const char *)blobValue.pbData(), blobValue.cbData()) : 
        Py_BuildValue("s", sValue.GetString());
}

static PyObject *SignedData_CoSignHash(SignedData *self, PyObject *args)
{
    PyObject *pPySigner = NULL;
    PyObject *pPyHashedData = NULL;
    long lCadesType = CADESCOM_CADES_DEFAULT;
    long lEncodingType = CAPICOM_ENCODE_BASE64;
    if (!PyArg_ParseTuple(args, "O!|O!ll", &HashedDataType, &pPyHashedData, &SignerType, &pPySigner, &lCadesType, &lEncodingType))
    {
        return NULL;
    }

    CADESCOM_CADES_TYPE CadesType = (CADESCOM_CADES_TYPE)lCadesType;
    CAPICOM_ENCODING_TYPE EncodingType = (CAPICOM_ENCODING_TYPE)lEncodingType;

    Signer *pSigner = (Signer *)pPySigner;
    HashedData *pHashedData = (HashedData *)pPyHashedData;

    CryptoPro::CBlob blobValue;
    HR_METHOD_ERRORCHECK_RETURN(self->m_pCppCadesImpl->CoSignHash(pSigner->m_pCppCadesImpl, pHashedData->m_pCppCadesImpl, CadesType, EncodingType, &blobValue));

    CAtlString sValue = CAtlString((const char *)blobValue.pbData(), blobValue.cbData());
    return EncodingType == CAPICOM_ENCODE_BINARY ? 
        PyBytes_FromStringAndSize((const char *)blobValue.pbData(), blobValue.cbData()) : 
        Py_BuildValue("s", sValue.GetString());
}

static PyObject *SignedData_Sign(SignedData *self, PyObject *args)
{
    PyObject *pPySigner = NULL;
    int bDetached = 0;
    long lEncodingType = CAPICOM_ENCODE_BASE64;
    if (!PyArg_ParseTuple(args, "|O!il", &SignerType, &pPySigner, &bDetached, &lEncodingType))
    {
        return NULL;
    }

    CAPICOM_ENCODING_TYPE EncodingType = (CAPICOM_ENCODING_TYPE)lEncodingType;
    Signer *pSigner = (Signer *)pPySigner;
    CryptoPro::CBlob blobValue;
    HR_METHOD_ERRORCHECK_RETURN(self->m_pCppCadesImpl->Sign(pSigner->m_pCppCadesImpl, bDetached, EncodingType, &blobValue));

    CAtlString sValue = CAtlString((const char *)blobValue.pbData(), blobValue.cbData());
    return EncodingType == CAPICOM_ENCODE_BINARY ? 
        PyBytes_FromStringAndSize((const char *)blobValue.pbData(), blobValue.cbData()) : 
        Py_BuildValue("s", sValue.GetString());
}

static PyObject *SignedData_CoSign(SignedData *self, PyObject *args)
{
    PyObject *pPySigner = NULL;
    long lEncodingType = CAPICOM_ENCODE_BASE64;
    if (!PyArg_ParseTuple(args, "|O!l", &SignerType, &pPySigner, &lEncodingType))
    {
        return NULL;
    }

    CAPICOM_ENCODING_TYPE EncodingType = (CAPICOM_ENCODING_TYPE)lEncodingType;
    Signer *pSigner = (Signer *)pPySigner;
    CryptoPro::CBlob blobValue;
    HR_METHOD_ERRORCHECK_RETURN(self->m_pCppCadesImpl->CoSign(pSigner->m_pCppCadesImpl, EncodingType, &blobValue));

    CAtlString sValue = CAtlString((const char *)blobValue.pbData(), blobValue.cbData());
    return EncodingType == CAPICOM_ENCODE_BINARY ? 
        PyBytes_FromStringAndSize((const char *)blobValue.pbData(), blobValue.cbData()) : 
        Py_BuildValue("s", sValue.GetString());
}

static PyObject *SignedData_CoSignCades(SignedData *self, PyObject *args)
{
    PyObject *pPySigner = NULL;
    long lCadesType = CADESCOM_CADES_DEFAULT;
    long lEncodingType = CAPICOM_ENCODE_BASE64;
    if (!PyArg_ParseTuple(args, "|O!ll", &SignerType, &pPySigner, &lCadesType, &lEncodingType))
    {
        return NULL;
    }

    CADESCOM_CADES_TYPE CadesType = (CADESCOM_CADES_TYPE)lCadesType;
    CAPICOM_ENCODING_TYPE EncodingType = (CAPICOM_ENCODING_TYPE)lEncodingType;
    CryptoPro::CBlob blobValue;
    Signer *pSigner = (Signer *)pPySigner;
    HR_METHOD_ERRORCHECK_RETURN(self->m_pCppCadesImpl->CoSignCades(pSigner->m_pCppCadesImpl, CadesType, EncodingType, &blobValue));

    CAtlString sValue = CAtlString((const char *)blobValue.pbData(), blobValue.cbData());
    return EncodingType == CAPICOM_ENCODE_BINARY ? 
        PyBytes_FromStringAndSize((const char *)blobValue.pbData(), blobValue.cbData()) : 
        Py_BuildValue("s", sValue.GetString());
}

static PyObject *SignedData_EnhanceCades(SignedData *self, PyObject *args)
{
    long lCadesType = CADESCOM_CADES_DEFAULT;
    char *szTSAAddress = "";
    long lEncodingType = CAPICOM_ENCODE_BASE64;
    CryptoPro::CBlob blobValue;

    if (!PyArg_ParseTuple(args, "|lsl", &lCadesType, &szTSAAddress, &lEncodingType))
    {
        return NULL;
    }

    CADESCOM_CADES_TYPE CadesType = (CADESCOM_CADES_TYPE)lCadesType;
    CAPICOM_ENCODING_TYPE EncodingType = (CAPICOM_ENCODING_TYPE)lEncodingType;

    HR_METHOD_ERRORCHECK_RETURN(self->m_pCppCadesImpl->EnhanceCades(CadesType, CAtlString(szTSAAddress), EncodingType, &blobValue));

    CAtlString sValue = CAtlString((const char *)blobValue.pbData(), blobValue.cbData());
    return EncodingType == CAPICOM_ENCODE_BINARY ? 
        PyBytes_FromStringAndSize((const char *)blobValue.pbData(), blobValue.cbData()) : 
        Py_BuildValue("s", sValue.GetString());
}

static PyObject *SignedData_Verify(SignedData *self, PyObject *args)
{
    char *szSignedMessage = "";
    int bDetached = 0;
    long lVerifyFlag = 0;
    if (!PyArg_ParseTuple(args, "s|il", &szSignedMessage, &bDetached, &lVerifyFlag))
    {
        return NULL;
    }

    CAPICOM_SIGNED_DATA_VERIFY_FLAG VerifyFlag = (CAPICOM_SIGNED_DATA_VERIFY_FLAG)lVerifyFlag;

    CryptoPro::CBlob blobSignedMessage;
    blobSignedMessage.assign((unsigned char *)szSignedMessage, strlen((const char *)szSignedMessage));

    HR_METHOD_ERRORCHECK_RETURN(self->m_pCppCadesImpl->Verify(blobSignedMessage, bDetached, VerifyFlag));
    Py_RETURN_NONE;
}

static PyObject *SignedData_VerifyCades(SignedData *self, PyObject *args)
{
    char *szSignedMessage = "";
    long lCadesType = CADESCOM_CADES_DEFAULT;
    int bDetached = 0;
    if (!PyArg_ParseTuple(args, "s|li", &szSignedMessage, &lCadesType, &bDetached))
    {
        return NULL;
    }

    CADESCOM_CADES_TYPE CadesType = (CADESCOM_CADES_TYPE)lCadesType;
    CryptoPro::CBlob blobSignedMessage;
    blobSignedMessage.assign((unsigned char *)szSignedMessage, strlen((const char *)szSignedMessage));

    HR_METHOD_ERRORCHECK_RETURN(self->m_pCppCadesImpl->VerifyCades(blobSignedMessage, CadesType, bDetached));
    Py_RETURN_NONE;
}

static PyObject *SignedData_VerifyHash(SignedData *self, PyObject *args)
{
    PyObject *pPyHashedData = NULL;
    char *szSignedMessage = "";
    long lCadesType = CADESCOM_CADES_DEFAULT;
    if (!PyArg_ParseTuple(args, "O!sl", &HashedDataType, &pPyHashedData, &szSignedMessage, &lCadesType))
    {
        return NULL;
    }

    CADESCOM_CADES_TYPE CadesType = (CADESCOM_CADES_TYPE)lCadesType;
    CryptoPro::CBlob blobSignedMessage;
    blobSignedMessage.assign((unsigned char *)szSignedMessage, strlen((const char *)szSignedMessage));

    HashedData *pHashedData = (HashedData *)pPyHashedData;
    HR_METHOD_ERRORCHECK_RETURN(self->m_pCppCadesImpl->VerifyHash(pHashedData->m_pCppCadesImpl, blobSignedMessage, CadesType));
    Py_RETURN_NONE;
}

static int SignedData_setContentEncoding(SignedData *self, PyObject *value)
{
    long lType = 0;
    if (!PyArg_Parse(value, "l", &lType))
    {
        return -1;
    }
    CADESCOM_CONTENT_ENCODING_TYPE Type = (CADESCOM_CONTENT_ENCODING_TYPE)lType;
    HR_SETTER_ERRORCHECK_RETURN(self->m_pCppCadesImpl->put_ContentEncoding(Type));
    return 0;
}

static PyObject *SignedData_getContentEncoding(SignedData *self)
{
    CADESCOM_CONTENT_ENCODING_TYPE type;
    HR_METHOD_ERRORCHECK_RETURN(self->m_pCppCadesImpl->get_ContentEncoding(&type));
    return Py_BuildValue("l", type);
}

static int SignedData_setContent(SignedData *self, PyObject *value)
{
    char *szVal = "";
    if (!PyArg_Parse(value, "s", &szVal))
    {
        return -1;
    }
    HR_SETTER_ERRORCHECK_RETURN(self->m_pCppCadesImpl->put_Content(szVal, strlen((const char *)szVal)));
    return 0;
}

static PyObject *SignedData_getContent(SignedData *self)
{
    CStringBlob strBlobValue;
    HR_METHOD_ERRORCHECK_RETURN(self->m_pCppCadesImpl->get_Content(strBlobValue));
    CAtlString sValue = CAtlString((const char *)strBlobValue.GetString(), strBlobValue.GetLength());
    return Py_BuildValue("s", sValue.GetString());
}

static PyObject *SignedData_getSigners(SignedData *self)
{
    PyObject *pPySigners = PyObject_CallObject((PyObject *)&SignersType, NULL);
    Signers *pSigners = (Signers *)pPySigners;
    HR_METHOD_ERRORCHECK_RETURN(self->m_pCppCadesImpl->get_Signers(pSigners->m_pCppCadesImpl));
    return Py_BuildValue("O", pSigners);
}

static PyObject *SignedData_getCertificates(SignedData *self)
{
    boost::shared_ptr<CPPCadesCPCertificatesObject> pCPPCadesCPCerts;
    HR_METHOD_ERRORCHECK_RETURN(self->m_pCppCadesImpl->get_Certificates(pCPPCadesCPCerts));
    PyObject *pPyCertificates = PyObject_CallObject((PyObject *)&CertificatesType, NULL);
    Certificates *pCertificates = (Certificates *)pPyCertificates;
    pCertificates->m_pCppCadesImpl = pCPPCadesCPCerts;
    return Py_BuildValue("O", pCertificates);
}

static PyObject *SignedData_AdditionalStore(SignedData *self, PyObject *args)
{
    PyObject *pPyStore = NULL;
    if (!PyArg_ParseTuple(args, "O!", &StoreType, &pPyStore))
    {
        return NULL;
    }
    Store *pStore = (Store *)pPyStore;
    HR_METHOD_ERRORCHECK_RETURN(self->m_pCppCadesImpl->AdditionalStore(pStore->m_pCppCadesImpl));
    Py_RETURN_NONE;
}

static PyGetSetDef SignedData_getset[] = {
    {"ContentEncoding", (getter)SignedData_getContentEncoding, (setter)SignedData_setContentEncoding, "ContentEncoding", NULL},
    {"Content", (getter)SignedData_getContent, (setter)SignedData_setContent, "Content", NULL},
    {"Signers", (getter)SignedData_getSigners, NULL, "Signers", NULL},
    {"Certificates", (getter)SignedData_getCertificates, NULL, "Certificates", NULL},
    {NULL} /* Sentinel */
};

static PyMethodDef SignedData_methods[] = {
    {"SignCades", (PyCFunction)SignedData_SignCades, METH_VARARGS, "SignCades"},
    {"SignHash", (PyCFunction)SignedData_SignHash, METH_VARARGS, "SignHash"},
    {"CoSignHash", (PyCFunction)SignedData_CoSignHash, METH_VARARGS, "CoSignHash"},
    {"Sign", (PyCFunction)SignedData_Sign, METH_VARARGS, "Sign"},
    {"CoSign", (PyCFunction)SignedData_CoSign, METH_VARARGS, "CoSign"},
    {"CoSignCades", (PyCFunction)SignedData_CoSignCades, METH_VARARGS, "CoSignCades"},
    {"EnhanceCades", (PyCFunction)SignedData_EnhanceCades, METH_VARARGS, "EnhanceCades"},
    {"Verify", (PyCFunction)SignedData_Verify, METH_VARARGS, "Verify"},
    {"VerifyCades", (PyCFunction)SignedData_VerifyCades, METH_VARARGS, "VerifyCades"},
    {"VerifyHash", (PyCFunction)SignedData_VerifyHash, METH_VARARGS, "VerifyHash"},
    {"AdditionalStore", (PyCFunction)SignedData_AdditionalStore, METH_VARARGS, "AdditionalStore"},
    {NULL} /* Sentinel */
};

PyTypeObject SignedDataType = {
    PyVarObject_HEAD_INIT(NULL, 0) "pycades.SignedData", /* tp_name */
    sizeof(SignedData),                                  /* tp_basicsize */
    0,                                                   /* tp_itemsize */
    (destructor)SignedData_dealloc,                      /* tp_dealloc */
    0,                                                   /* tp_print */
    0,                                                   /* tp_getattr */
    0,                                                   /* tp_setattr */
    0,                                                   /* tp_compare */
    0,                                                   /* tp_repr */
    0,                                                   /* tp_as_number */
    0,                                                   /* tp_as_sequence */
    0,                                                   /* tp_as_mapping */
    0,                                                   /* tp_hash */
    0,                                                   /* tp_call */
    0,                                                   /* tp_str */
    0,                                                   /* tp_getattro */
    0,                                                   /* tp_setattro */
    0,                                                   /* tp_as_buffer */
    Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,            /* tp_flags */
    "SignedData object",                                 /* tp_doc */
    0,                                                   /* tp_traverse */
    0,                                                   /* tp_clear */
    0,                                                   /* tp_richcompare */
    0,                                                   /* tp_weaklistoffset */
    0,                                                   /* tp_iter */
    0,                                                   /* tp_iternext */
    SignedData_methods,                                  /* tp_methods */
    0,                                                   /* tp_members */
    SignedData_getset,                                   /* tp_getset */
    0,                                                   /* tp_base */
    0,                                                   /* tp_dict */
    0,                                                   /* tp_descr_get */
    0,                                                   /* tp_descr_set */
    0,                                                   /* tp_dictoffset */
    0,                                                   /* tp_init */
    0,                                                   /* tp_alloc */
    SignedData_new,                                      /* tp_new */
};
