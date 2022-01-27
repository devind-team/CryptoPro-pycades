#include "PyCadesSignedXML.h"
#include "PyCadesSigner.h"
#include "PyCadesSigners.h"

using namespace CryptoPro::PKI::CAdES;

static void SignedXML_dealloc(SignedXML *self)
{
    Py_TYPE(self)->tp_free((PyObject *)self);
}

static PyObject *SignedXML_new(PyTypeObject *type, PyObject *args, PyObject *kwds)
{
    SignedXML *self;
    self = (SignedXML *)type->tp_alloc(type, 0);
    if (self != NULL)
    {
        self->m_pCppCadesImpl = boost::shared_ptr<CPPCadesSignedXMLObject>(new CPPCadesSignedXMLObject());
    }
    return (PyObject *)self;
}

static int SignedXML_setContent(SignedXML *self, PyObject *value)
{
    char *szContent = NULL;
    if (!PyArg_Parse(value, "s", &szContent))
    {
        return -1;
    }
    CStringBlob strBlobContent(szContent);
    HR_SETTER_ERRORCHECK_RETURN(self->m_pCppCadesImpl->put_Content(strBlobContent));
    return 0;
}

static PyObject *SignedXML_getContent(SignedXML *self)
{
    CStringBlob strBlobContent;
    HR_METHOD_ERRORCHECK_RETURN(self->m_pCppCadesImpl->get_Content(strBlobContent));
    DWORD dwContentLen = strBlobContent.GetLength();
    char* szContent = (char *)calloc(dwContentLen, sizeof(char));
    if (!szContent)
    {
        PyErr_NoMemory();
        return NULL;
    }
    memcpy(szContent, strBlobContent, dwContentLen);
    PyObject *pPyResult = Py_BuildValue("s", szContent);
    free(szContent);

    return pPyResult;
}

static int SignedXML_setSignatureType(SignedXML *self, PyObject *value)
{
    long lType;
    if (!PyArg_Parse(value, "l", &lType))
    {
        return -1;
    }
    CADESCOM_XML_SIGNATURE_TYPE Type = (CADESCOM_XML_SIGNATURE_TYPE)lType;
    HR_SETTER_ERRORCHECK_RETURN(self->m_pCppCadesImpl->put_SignatureType(Type));
    return 0;
}

static int SignedXML_setDigestMethod(SignedXML *self, PyObject *value)
{
    char *szDigestMethod = "";
    if (!PyArg_Parse(value, "s", &szDigestMethod))
    {
        return -1;
    }
    CStringBlob strBlobMethod(szDigestMethod);
    HR_SETTER_ERRORCHECK_RETURN(self->m_pCppCadesImpl->put_DigestMethod(strBlobMethod));
    return 0;
}

static int SignedXML_setSignatureMethod(SignedXML *self, PyObject *value)
{
    char *szSignatureMethod;
    if (!PyArg_Parse(value, "s", &szSignatureMethod))
    {
        return -1;
    }
    CStringBlob strBlobMethod(szSignatureMethod);
    HR_SETTER_ERRORCHECK_RETURN(self->m_pCppCadesImpl->put_SignatureMethod(strBlobMethod));
    return 0;
}

static PyObject *SignedXML_getSigners(SignedXML *self)
{
    PyObject *pPySigners = PyObject_CallObject((PyObject *)&SignersType, NULL);
    Signers *pSigners = (Signers *)pPySigners;
    HR_METHOD_ERRORCHECK_RETURN(self->m_pCppCadesImpl->get_Signers(pSigners->m_pCppCadesImpl));
    return Py_BuildValue("O", pSigners);
}

static PyObject *SignedXML_Sign(SignedXML *self, PyObject *args)
{
    PyObject *pPySigner = NULL;
    char *szXPath = "";
    if (!PyArg_ParseTuple(args, "O!|s", &SignerType, &pPySigner, &szXPath))
    {
        return NULL;
    }

    Signer *pSigner = (Signer *)pPySigner;
    CStringBlob strBlobXPath(szXPath);
    CStringBlob strBlobResult;
    HR_METHOD_ERRORCHECK_RETURN(self->m_pCppCadesImpl->Sign(pSigner->m_pCppCadesImpl, strBlobXPath, strBlobResult));

    DWORD dwResultLen = strBlobResult.GetLength();
    char *szResult = (char *)calloc(dwResultLen, sizeof(char));
    if (!szResult)
    {
        PyErr_NoMemory();
        return NULL;
    }
    memcpy(szResult, strBlobResult.GetBuffer(), dwResultLen);

    // По умолчанию python использует кодировку utf-8, в которой 0x0A (new line) считается continuation byte.
    // Если этот символ последний в строке, то декодер ломается с ошибкой Invalid continuation byte
    if (szResult[dwResultLen - 1] == 0x0A)
        szResult[dwResultLen - 1] = '\0';

    PyObject *pPyResult = Py_BuildValue("s", szResult);
    free(szResult);

    return pPyResult;
}

static PyObject *SignedXML_Verify(SignedXML *self, PyObject *args)
{
    const char *szSignedMessage = "";
    const char *szXPath = "";

    if (!PyArg_ParseTuple(args, "s|s", &szSignedMessage, &szXPath))
    {
        return NULL;
    }

    CStringBlob strBlobMessage(szSignedMessage, strlen(szSignedMessage));
    CStringBlob strBlobXPath(szXPath, strlen(szXPath));
    HR_METHOD_ERRORCHECK_RETURN(self->m_pCppCadesImpl->Verify(strBlobMessage, strBlobXPath));
    Py_RETURN_NONE;
}

static PyGetSetDef SignedXML_getset[] = {
    {"Content", (getter)SignedXML_getContent, (setter)SignedXML_setContent, "Content", NULL},
    {"SignatureType", NULL, (setter)SignedXML_setSignatureType, "SignatureType", NULL},
    {"DigestMethod", NULL, (setter)SignedXML_setDigestMethod, "DigestMethod", NULL},
    {"SignatureMethod", NULL, (setter)SignedXML_setSignatureMethod, "SignatureMethod", NULL},
    {"Signers", (getter)SignedXML_getSigners, NULL, "Signers", NULL},
    {NULL} /* Sentinel */
};

static PyMethodDef SignedXML_methods[] = {
    {"Sign", (PyCFunction)SignedXML_Sign, METH_VARARGS, "Sign"},
    {"Verify", (PyCFunction)SignedXML_Verify, METH_VARARGS, "Verify"},
    {NULL} /* Sentinel */
};

PyTypeObject SignedXMLType = {
    PyVarObject_HEAD_INIT(NULL, 0) "pycades.SignedXML", /* tp_name */
    sizeof(SignedXML),                                  /* tp_basicsize */
    0,                                                  /* tp_itemsize */
    (destructor)SignedXML_dealloc,                      /* tp_dealloc */
    0,                                                  /* tp_print */
    0,                                                  /* tp_getattr */
    0,                                                  /* tp_setattr */
    0,                                                  /* tp_compare */
    0,                                                  /* tp_repr */
    0,                                                  /* tp_as_number */
    0,                                                  /* tp_as_sequence */
    0,                                                  /* tp_as_mapping */
    0,                                                  /* tp_hash */
    0,                                                  /* tp_call */
    0,                                                  /* tp_str */
    0,                                                  /* tp_getattro */
    0,                                                  /* tp_setattro */
    0,                                                  /* tp_as_buffer */
    Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,           /* tp_flags */
    "SignedXML object",                                 /* tp_doc */
    0,                                                  /* tp_traverse */
    0,                                                  /* tp_clear */
    0,                                                  /* tp_richcompare */
    0,                                                  /* tp_weaklistoffset */
    0,                                                  /* tp_iter */
    0,                                                  /* tp_iternext */
    SignedXML_methods,                                  /* tp_methods */
    0,                                                  /* tp_members */
    SignedXML_getset,                                   /* tp_getset */
    0,                                                  /* tp_base */
    0,                                                  /* tp_dict */
    0,                                                  /* tp_descr_get */
    0,                                                  /* tp_descr_set */
    0,                                                  /* tp_dictoffset */
    0,                                                  /* tp_init */
    0,                                                  /* tp_alloc */
    SignedXML_new,                                      /* tp_new */
};
