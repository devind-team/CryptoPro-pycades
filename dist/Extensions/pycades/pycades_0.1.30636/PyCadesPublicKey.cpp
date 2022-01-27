#include "PyCadesPublicKey.h"
#include "PyCadesEncodedData.h"
#include "PyCadesOID.h"

using namespace CryptoPro::PKI::CAdES;

static void PublicKey_dealloc(PublicKey *self)
{
    Py_TYPE(self)->tp_free((PyObject *)self);
}

static PyObject *PublicKey_new(PyTypeObject *type, PyObject *args, PyObject *kwds)
{
    PublicKey *self;
    self = (PublicKey *)type->tp_alloc(type, 0);
    if (self != NULL)
    {
        self->m_pCppCadesImpl = boost::shared_ptr<CPPCadesCPPublicKeyObject>(new CPPCadesCPPublicKeyObject());
    }
    return (PyObject *)self;
}

static PyObject *PublicKey_getAlgorithm(PublicKey *self)
{
    PyObject *pPyOID = PyObject_CallObject((PyObject *)&OIDType, NULL);
    OID *pOID = (OID *)pPyOID;
    pOID->m_pCppCadesImpl = boost::shared_ptr<CPPCadesCPOIDObject>(new CPPCadesCPOIDObject());
    HR_METHOD_ERRORCHECK_RETURN(self->m_pCppCadesImpl->get_Algorithm(pOID->m_pCppCadesImpl));
    return Py_BuildValue("O", pOID);
}

static PyObject *PublicKey_getLength(PublicKey *self)
{
    DWORD dwLen = 0;
    HR_METHOD_ERRORCHECK_RETURN(self->m_pCppCadesImpl->get_Length(&dwLen));
    return Py_BuildValue("l", dwLen);
}

static PyObject *PublicKey_getEncodedKey(PublicKey *self)
{
    PyObject *pPyEncodedData = PyObject_CallObject((PyObject *)&EncodedDataType, NULL);
    EncodedData *pEncodedData = (EncodedData *)pPyEncodedData;
    HR_METHOD_ERRORCHECK_RETURN(self->m_pCppCadesImpl->get_EncodedKey(pEncodedData->m_pCppCadesImpl));
    return Py_BuildValue("O", pEncodedData);
}

static PyObject *PublicKey_getEncodedParameters(PublicKey *self)
{
    PyObject *pPyEncodedData = PyObject_CallObject((PyObject *)&EncodedDataType, NULL);
    EncodedData *pEncodedData = (EncodedData *)pPyEncodedData;
    HR_METHOD_ERRORCHECK_RETURN(self->m_pCppCadesImpl->get_EncodedParameters(pEncodedData->m_pCppCadesImpl));
    return Py_BuildValue("O", pEncodedData);
}

static PyGetSetDef PublicKey_getset[] = {
    {"Algorithm", (getter)PublicKey_getAlgorithm, NULL, "Algorithm", NULL},
    {"Length", (getter)PublicKey_getLength, NULL, "Length", NULL},
    {"EncodedKey", (getter)PublicKey_getEncodedKey, NULL, "EncodedKey", NULL},
    {"EncodedParameters", (getter)PublicKey_getEncodedParameters, NULL, "EncodedParameters", NULL},
    {NULL} /* Sentinel */
};

static PyMethodDef PublicKey_methods[] = {
    {NULL} /* Sentinel */
};

PyTypeObject PublicKeyType = {
    PyVarObject_HEAD_INIT(NULL, 0) "pycades.PublicKey", /* tp_name */
    sizeof(PublicKey),                                  /* tp_basicsize */
    0,                                                  /* tp_itemsize */
    (destructor)PublicKey_dealloc,                      /* tp_dealloc */
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
    "PublicKey object",                                 /* tp_doc */
    0,                                                  /* tp_traverse */
    0,                                                  /* tp_clear */
    0,                                                  /* tp_richcompare */
    0,                                                  /* tp_weaklistoffset */
    0,                                                  /* tp_iter */
    0,                                                  /* tp_iternext */
    PublicKey_methods,                                  /* tp_methods */
    0,                                                  /* tp_members */
    PublicKey_getset,                                   /* tp_getset */
    0,                                                  /* tp_base */
    0,                                                  /* tp_dict */
    0,                                                  /* tp_descr_get */
    0,                                                  /* tp_descr_set */
    0,                                                  /* tp_dictoffset */
    0,                                                  /* tp_init */
    0,                                                  /* tp_alloc */
    PublicKey_new,                                      /* tp_new */
};
