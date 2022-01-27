#include "PyCadesCertificateStatus.h"
#include "PyCadesCertificates.h"
#include "PyCadesOID.h"
#include "PyCadesEKU.h"

using namespace CryptoPro::PKI::CAdES;

static void CertificateStatus_dealloc(CertificateStatus *self)
{
    Py_TYPE(self)->tp_free((PyObject *)self);
}

static PyObject *CertificateStatus_new(PyTypeObject *type, PyObject *args, PyObject *kwds)
{
    CertificateStatus *self;
    self = (CertificateStatus *)type->tp_alloc(type, 0);
    if (self != NULL)
    {
        self->m_pCppCadesImpl = boost::shared_ptr<CPPCadesCPCertificateStatusObject>(new CPPCadesCPCertificateStatusObject());
    }
    return (PyObject *)self;
}

static PyObject *CertificateStatus_getResult(CertificateStatus *self)
{
    BOOL bResult = 0;
    HR_METHOD_ERRORCHECK_RETURN(self->m_pCppCadesImpl->get_Result(&bResult));
    return bResult ? Py_True : Py_False;
}

static PyGetSetDef CertificateStatus_getset[] = {
    {"Result", (getter)CertificateStatus_getResult, NULL, "Result", NULL},
    {NULL} /* Sentinel */
};

static PyMethodDef CertificateStatus_methods[] = {
    {NULL} /* Sentinel */
};

PyTypeObject CertificateStatusType = {
    PyVarObject_HEAD_INIT(NULL, 0) "pycades.CertificateStatus", /* tp_name */
    sizeof(CertificateStatus),                                  /* tp_basicsize */
    0,                                                          /* tp_itemsize */
    (destructor)CertificateStatus_dealloc,                      /* tp_dealloc */
    0,                                                          /* tp_print */
    0,                                                          /* tp_getattr */
    0,                                                          /* tp_setattr */
    0,                                                          /* tp_compare */
    0,                                                          /* tp_repr */
    0,                                                          /* tp_as_number */
    0,                                                          /* tp_as_sequence */
    0,                                                          /* tp_as_mapping */
    0,                                                          /* tp_hash */
    0,                                                          /* tp_call */
    0,                                                          /* tp_str */
    0,                                                          /* tp_getattro */
    0,                                                          /* tp_setattro */
    0,                                                          /* tp_as_buffer */
    Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,                   /* tp_flags */
    "CertificateStatus object",                                 /* tp_doc */
    0,                                                          /* tp_traverse */
    0,                                                          /* tp_clear */
    0,                                                          /* tp_richcompare */
    0,                                                          /* tp_weaklistoffset */
    0,                                                          /* tp_iter */
    0,                                                          /* tp_iternext */
    CertificateStatus_methods,                                  /* tp_methods */
    0,                                                          /* tp_members */
    CertificateStatus_getset,                                   /* tp_getset */
    0,                                                          /* tp_base */
    0,                                                          /* tp_dict */
    0,                                                          /* tp_descr_get */
    0,                                                          /* tp_descr_set */
    0,                                                          /* tp_dictoffset */
    0,                                                          /* tp_init */
    0,                                                          /* tp_alloc */
    CertificateStatus_new,                                      /* tp_new */
};
