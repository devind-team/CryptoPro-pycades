#include "PyCadesSignatureStatus.h"

using namespace CryptoPro::PKI::CAdES;

static void SignatureStatus_dealloc(SignatureStatus *self)
{
    Py_TYPE(self)->tp_free((PyObject *)self);
}

static PyObject *SignatureStatus_new(PyTypeObject *type, PyObject *args, PyObject *kwds)
{
    SignatureStatus *self;
    self = (SignatureStatus *)type->tp_alloc(type, 0);
    if (self != NULL)
    {
        self->m_pCppCadesImpl = boost::shared_ptr<CPPCadesSignatureStatusObject>(new CPPCadesSignatureStatusObject());
    }
    return (PyObject *)self;
}

static PyObject *SignatureStatus_getIsValid(SignatureStatus *self)
{
    bool bIsValid = false;
    HR_METHOD_ERRORCHECK_RETURN(self->m_pCppCadesImpl->IsValid(bIsValid));
    return bIsValid ? Py_True : Py_False;
}

static PyGetSetDef SignatureStatus_getset[] = {
    {"IsValid", (getter)SignatureStatus_getIsValid, NULL, "IsValid", NULL},
    {NULL} /* Sentinel */
};

static PyMethodDef SignatureStatus_methods[] = {
    {NULL} /* Sentinel */
};

PyTypeObject SignatureStatusType = {
    PyVarObject_HEAD_INIT(NULL, 0) "pycades.SignatureStatus", /* tp_name */
    sizeof(SignatureStatus),                                  /* tp_basicsize */
    0,                                                        /* tp_itemsize */
    (destructor)SignatureStatus_dealloc,                      /* tp_dealloc */
    0,                                                        /* tp_print */
    0,                                                        /* tp_getattr */
    0,                                                        /* tp_setattr */
    0,                                                        /* tp_compare */
    0,                                                        /* tp_repr */
    0,                                                        /* tp_as_number */
    0,                                                        /* tp_as_sequence */
    0,                                                        /* tp_as_mapping */
    0,                                                        /* tp_hash */
    0,                                                        /* tp_call */
    0,                                                        /* tp_str */
    0,                                                        /* tp_getattro */
    0,                                                        /* tp_setattro */
    0,                                                        /* tp_as_buffer */
    Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,                 /* tp_flags */
    "SignatureStatus object",                                 /* tp_doc */
    0,                                                        /* tp_traverse */
    0,                                                        /* tp_clear */
    0,                                                        /* tp_richcompare */
    0,                                                        /* tp_weaklistoffset */
    0,                                                        /* tp_iter */
    0,                                                        /* tp_iternext */
    SignatureStatus_methods,                                  /* tp_methods */
    0,                                                        /* tp_members */
    SignatureStatus_getset,                                   /* tp_getset */
    0,                                                        /* tp_base */
    0,                                                        /* tp_dict */
    0,                                                        /* tp_descr_get */
    0,                                                        /* tp_descr_set */
    0,                                                        /* tp_dictoffset */
    0,                                                        /* tp_init */
    0,                                                        /* tp_alloc */
    SignatureStatus_new,                                      /* tp_new */
};
