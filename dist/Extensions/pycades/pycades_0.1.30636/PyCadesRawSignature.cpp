#include "PyCadesRawSignature.h"
#include "PyCadesCertificate.h"
#include "PyCadesHashedData.h"

using namespace CryptoPro::PKI::CAdES;

static void RawSignature_dealloc(RawSignature *self)
{
    Py_TYPE(self)->tp_free((PyObject *)self);
}

static PyObject *RawSignature_new(PyTypeObject *type, PyObject *args, PyObject *kwds)
{
    RawSignature *self;
    self = (RawSignature *)type->tp_alloc(type, 0);
    if (self != NULL)
    {
        self->m_pCppCadesImpl = boost::shared_ptr<CPPCadesRawSignatureObject>(new CPPCadesRawSignatureObject());
    }
    return (PyObject *)self;
}

static PyObject *RawSignature_SignHash(RawSignature *self, PyObject *args)
{
    PyObject *pPyHashedData = NULL;
    PyObject *pPyCert = NULL;
    CAtlString sSignature;

    if (!PyArg_ParseTuple(args, "O!O!", &HashedDataType, &pPyHashedData, &CertificateType, &pPyCert))
    {
        return NULL;
    }

    HashedData *pHashedData = (HashedData *)pPyHashedData;
    Certificate *pCert = (Certificate *)pPyCert;

    HR_METHOD_ERRORCHECK_RETURN(self->m_pCppCadesImpl->SignHash(pHashedData->m_pCppCadesImpl, pCert->m_pCppCadesImpl, sSignature));
    return Py_BuildValue("s", sSignature.GetString());
}

static PyObject *RawSignature_VerifyHash(RawSignature *self, PyObject *args)
{
    PyObject *pPyHashedData = NULL;
    PyObject *pPyCert = NULL;
    char *szSignature = "";

    if (!PyArg_ParseTuple(args, "O!O!s", &HashedDataType, &pPyHashedData, &CertificateType, &pPyCert, &szSignature))
    {
        return NULL;
    }

    HashedData *pHashedData = (HashedData *)pPyHashedData;
    Certificate *pCertificate = (Certificate *)pPyCert;
    CAtlString sSignature(szSignature);

    HR_METHOD_ERRORCHECK_RETURN(self->m_pCppCadesImpl->VerifyHash(pHashedData->m_pCppCadesImpl, sSignature, pCertificate->m_pCppCadesImpl));
    Py_RETURN_NONE;
}

static PyGetSetDef RawSignature_getset[] = {
    {NULL} /* Sentinel */
};

static PyMethodDef RawSignature_methods[] = {
    {"SignHash", (PyCFunction)RawSignature_SignHash, METH_VARARGS, "SignHash"},
    {"VerifyHash", (PyCFunction)RawSignature_VerifyHash, METH_VARARGS, "VerifyHash"},
    {NULL} /* Sentinel */
};

PyTypeObject RawSignatureType = {
    PyVarObject_HEAD_INIT(NULL, 0) "pycades.RawSignature", /* tp_name */
    sizeof(RawSignature),                                  /* tp_basicsize */
    0,                                                     /* tp_itemsize */
    (destructor)RawSignature_dealloc,                      /* tp_dealloc */
    0,                                                     /* tp_print */
    0,                                                     /* tp_getattr */
    0,                                                     /* tp_setattr */
    0,                                                     /* tp_compare */
    0,                                                     /* tp_repr */
    0,                                                     /* tp_as_number */
    0,                                                     /* tp_as_sequence */
    0,                                                     /* tp_as_mapping */
    0,                                                     /* tp_hash */
    0,                                                     /* tp_call */
    0,                                                     /* tp_str */
    0,                                                     /* tp_getattro */
    0,                                                     /* tp_setattro */
    0,                                                     /* tp_as_buffer */
    Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,              /* tp_flags */
    "RawSignature object",                                 /* tp_doc */
    0,                                                     /* tp_traverse */
    0,                                                     /* tp_clear */
    0,                                                     /* tp_richcompare */
    0,                                                     /* tp_weaklistoffset */
    0,                                                     /* tp_iter */
    0,                                                     /* tp_iternext */
    RawSignature_methods,                                  /* tp_methods */
    0,                                                     /* tp_members */
    RawSignature_getset,                                   /* tp_getset */
    0,                                                     /* tp_base */
    0,                                                     /* tp_dict */
    0,                                                     /* tp_descr_get */
    0,                                                     /* tp_descr_set */
    0,                                                     /* tp_dictoffset */
    0,                                                     /* tp_init */
    0,                                                     /* tp_alloc */
    RawSignature_new,                                      /* tp_new */
};
