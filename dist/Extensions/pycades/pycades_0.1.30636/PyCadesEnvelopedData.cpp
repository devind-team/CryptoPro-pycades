#include "PyCadesEnvelopedData.h"
#include "PyCadesRecipients.h"
#include "PyCadesAlgorithm.h"

using namespace CryptoPro::PKI::CAdES;

static void EnvelopedData_dealloc(EnvelopedData *self)
{
    Py_TYPE(self)->tp_free((PyObject *)self);
}

static PyObject *EnvelopedData_new(PyTypeObject *type, PyObject *args, PyObject *kwds)
{
    EnvelopedData *self;
    self = (EnvelopedData *)type->tp_alloc(type, 0);
    if (self != NULL)
    {
        self->m_pCppCadesImpl = new CPPCadesCPEnvelopedDataObject();
    }
    return (PyObject *)self;
}

static PyObject *EnvelopedData_getContent(EnvelopedData *self)
{
    CStringBlob blobContent;
    HR_METHOD_ERRORCHECK_RETURN(self->m_pCppCadesImpl->get_Content(blobContent));
    return Py_BuildValue("s", blobContent.GetString());
}

static int EnvelopedData_setContent(EnvelopedData *self, PyObject *value)
{
    char *szContent = "";
    if (!PyArg_Parse(value, "s", &szContent))
    {
        return -1;
    }
    CAtlString sContent = CAtlString(szContent);
    HR_SETTER_ERRORCHECK_RETURN(self->m_pCppCadesImpl->put_Content(sContent.GetString(), sContent.GetLength()));
    return 0;
}

static PyObject *EnvelopedData_getContentEncoding(EnvelopedData *self)
{
    CADESCOM_CONTENT_ENCODING_TYPE ContentEncoding;
    HR_METHOD_ERRORCHECK_RETURN(self->m_pCppCadesImpl->get_ContentEncoding(&ContentEncoding));
    return Py_BuildValue("l", ContentEncoding);
}

static int EnvelopedData_setContentEncoding(EnvelopedData *self, PyObject *value)
{
    long ContentEncoding = 0;
    if (!PyArg_Parse(value, "l", &ContentEncoding))
    {
        return -1;
    }
    HR_SETTER_ERRORCHECK_RETURN(self->m_pCppCadesImpl->put_ContentEncoding((CADESCOM_CONTENT_ENCODING_TYPE)ContentEncoding));
    return 0;
}

static PyObject *EnvelopedData_getRecipients(EnvelopedData *self)
{
    PyObject *pPyRecipients = PyObject_CallObject((PyObject *)&RecipientsType, NULL);
    Recipients *pRecipients = (Recipients *)pPyRecipients;
    HR_METHOD_ERRORCHECK_RETURN(self->m_pCppCadesImpl->get_Recipients(pRecipients->m_pCppCadesImpl));
    return Py_BuildValue("O", pRecipients);
}

static PyObject *EnvelopedData_getAlgorithm(EnvelopedData *self)
{
    PyObject *pPyAlgorithmType = PyObject_CallObject((PyObject *)&AlgorithmType, NULL);
    Algorithm *pAlgorithm = (Algorithm *)pPyAlgorithmType;
    HR_METHOD_ERRORCHECK_RETURN(self->m_pCppCadesImpl->get_Algorithm(pAlgorithm->m_pCppCadesImpl));
    return Py_BuildValue("O", pAlgorithm);
}

static PyObject *EnvelopedData_Encrypt(EnvelopedData *self, PyObject *args)
{
    long lEncodingType = 0;
    if (!PyArg_ParseTuple(args, "|l", &lEncodingType))
    {
        return NULL;
    }

    CAPICOM_ENCODING_TYPE EncodingType = (CAPICOM_ENCODING_TYPE)lEncodingType;
    CryptoPro::CBlob blobData;
    HR_METHOD_ERRORCHECK_RETURN(self->m_pCppCadesImpl->Encrypt(EncodingType, blobData));
    CAtlString sData = CAtlString((const char *)blobData.pbData(), blobData.cbData());
    return Py_BuildValue("s", sData.GetString());
}

static PyObject *EnvelopedData_Decrypt(EnvelopedData *self, PyObject *args)
{
    char *szData = "";
    if (!PyArg_ParseTuple(args, "s", &szData))
    {
        return NULL;
    }
    CryptoPro::CBlob blobData;
    blobData.assign((unsigned char *)szData, strlen((const char *)szData));
    HR_METHOD_ERRORCHECK_RETURN(self->m_pCppCadesImpl->Decrypt(blobData));
    Py_RETURN_NONE;
}

static PyObject *EnvelopedData_StreamEncrypt(EnvelopedData *self, PyObject *args)
{
    char *szData = "";
    int bIsFinal = 0;
    if (!PyArg_ParseTuple(args, "si", &szData, &bIsFinal))
    {
        return NULL;
    }

    CAtlString sData = CAtlString(CA2CT(CAtlStringA(szData), CP_UTF8));
    CryptoPro::CBlob blobResult;
    HR_METHOD_ERRORCHECK_RETURN(self->m_pCppCadesImpl->StreamEncrypt(
            sData.GetString(), sData.GetLength(), bIsFinal, blobResult));

    CAtlString sResult;
    if (blobResult.cbData())
    {
        sResult = CAtlString((const char *)blobResult.pbData(), blobResult.cbData());
    }
    return Py_BuildValue("s", sResult.GetString());
}

static PyObject *EnvelopedData_StreamDecrypt(EnvelopedData *self, PyObject *args)
{
    char *szData = "";
    int bIsFinal = 0;
    if (!PyArg_ParseTuple(args, "si", &szData, &bIsFinal))
    {
        return NULL;
    }

    CAtlString sData = CAtlString(CA2CT(CAtlStringA(szData), CP_UTF8));
    CryptoPro::CBlob blobResult;
    HR_METHOD_ERRORCHECK_RETURN(self->m_pCppCadesImpl->StreamDecrypt(
            sData.GetString(), sData.GetLength(), bIsFinal, blobResult));

    CAtlString sResult;
    if (blobResult.cbData())
    {
        sResult = CAtlString((const char *)blobResult.pbData(), blobResult.cbData());
    }
    return Py_BuildValue("s", sResult.GetString());
}

static PyGetSetDef EnvelopedData_getset[] = {
    {"Content", (getter)EnvelopedData_getContent, (setter)EnvelopedData_setContent, "Content", NULL},
    {"ContentEncoding", (getter)EnvelopedData_getContentEncoding, (setter)EnvelopedData_setContentEncoding, "ContentEncoding", NULL},
    {"Recipients", (getter)EnvelopedData_getRecipients, NULL, "Recipients", NULL},
    {"Algorithm", (getter)EnvelopedData_getAlgorithm, NULL, "Algorithm", NULL},
    {NULL} /* Sentinel */
};

static PyMethodDef EnvelopedData_methods[] = {
    {"Encrypt", (PyCFunction)EnvelopedData_Encrypt, METH_VARARGS, "Encrypt"},
    {"Decrypt", (PyCFunction)EnvelopedData_Decrypt, METH_VARARGS, "Decrypt"},
    {"StreamEncrypt", (PyCFunction)EnvelopedData_StreamEncrypt, METH_VARARGS, "StreamEncrypt"},
    {"StreamDecrypt", (PyCFunction)EnvelopedData_StreamDecrypt, METH_VARARGS, "StreamDecrypt"},
    {NULL} /* Sentinel */
};

PyTypeObject EnvelopedDataType = {
    PyVarObject_HEAD_INIT(NULL, 0) "pycades.EnvelopedData", /* tp_name */
    sizeof(EnvelopedData),                                  /* tp_basicsize */
    0,                                                      /* tp_itemsize */
    (destructor)EnvelopedData_dealloc,                      /* tp_dealloc */
    0,                                                      /* tp_print */
    0,                                                      /* tp_getattr */
    0,                                                      /* tp_setattr */
    0,                                                      /* tp_compare */
    0,                                                      /* tp_repr */
    0,                                                      /* tp_as_number */
    0,                                                      /* tp_as_sequence */
    0,                                                      /* tp_as_mapping */
    0,                                                      /* tp_hash */
    0,                                                      /* tp_call */
    0,                                                      /* tp_str */
    0,                                                      /* tp_getattro */
    0,                                                      /* tp_setattro */
    0,                                                      /* tp_as_buffer */
    Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,               /* tp_flags */
    "EnvelopedData object",                                 /* tp_doc */
    0,                                                      /* tp_traverse */
    0,                                                      /* tp_clear */
    0,                                                      /* tp_richcompare */
    0,                                                      /* tp_weaklistoffset */
    0,                                                      /* tp_iter */
    0,                                                      /* tp_iternext */
    EnvelopedData_methods,                                  /* tp_methods */
    0,                                                      /* tp_members */
    EnvelopedData_getset,                                   /* tp_getset */
    0,                                                      /* tp_base */
    0,                                                      /* tp_dict */
    0,                                                      /* tp_descr_get */
    0,                                                      /* tp_descr_set */
    0,                                                      /* tp_dictoffset */
    0,                                                      /* tp_init */
    0,                                                      /* tp_alloc */
    EnvelopedData_new,                                      /* tp_new */
};
