#include "PyCadesKeyUsage.h"

using namespace CryptoPro::PKI::CAdES;

static void KeyUsage_dealloc(KeyUsage *self)
{
    Py_TYPE(self)->tp_free((PyObject *)self);
}

static PyObject *KeyUsage_new(PyTypeObject *type, PyObject *args, PyObject *kwds)
{
    KeyUsage *self;
    self = (KeyUsage *)type->tp_alloc(type, 0);
    if (self != NULL)
    {
        self->m_pCppCadesImpl = boost::shared_ptr<CPPCadesCPKeyUsageObject>(new CPPCadesCPKeyUsageObject());
    }
    return (PyObject *)self;
}

static PyObject *KeyUsage_getIsPresent(KeyUsage *self)
{
    BOOL val = 0;
    HR_METHOD_ERRORCHECK_RETURN(self->m_pCppCadesImpl->get_IsPresent(&val));
    return val ? Py_True : Py_False;
}

static PyObject *KeyUsage_getIsCritical(KeyUsage *self)
{
    BOOL val = 0;
    HR_METHOD_ERRORCHECK_RETURN(self->m_pCppCadesImpl->get_IsCritical(&val));
    return val ? Py_True : Py_False;
}

static PyObject *KeyUsage_getIsDigitalSignatureEnabled(KeyUsage *self)
{
    BOOL val = 0;
    HR_METHOD_ERRORCHECK_RETURN(self->m_pCppCadesImpl->get_IsDigitalSignatureEnabled(&val));
    return val ? Py_True : Py_False;
}

static PyObject *KeyUsage_getIsNonRepudiationEnabled(KeyUsage *self)
{
    BOOL val = 0;
    HR_METHOD_ERRORCHECK_RETURN(self->m_pCppCadesImpl->get_IsNonRepudiationEnabled(&val));
    return val ? Py_True : Py_False;
}

static PyObject *KeyUsage_getIsKeyEnciphermentEnabled(KeyUsage *self)
{
    BOOL val = 0;
    HR_METHOD_ERRORCHECK_RETURN(self->m_pCppCadesImpl->get_IsKeyEnciphermentEnabled(&val));
    return val ? Py_True : Py_False;
}

static PyObject *KeyUsage_getIsDataEnciphermentEnabled(KeyUsage *self)
{
    BOOL val = 0;
    HR_METHOD_ERRORCHECK_RETURN(self->m_pCppCadesImpl->get_IsDataEnciphermentEnabled(&val));
    return val ? Py_True : Py_False;
}

static PyObject *KeyUsage_getIsKeyAgreementEnabled(KeyUsage *self)
{
    BOOL val = 0;
    HR_METHOD_ERRORCHECK_RETURN(self->m_pCppCadesImpl->get_IsKeyAgreementEnabled(&val));
    return val ? Py_True : Py_False;
}

static PyObject *KeyUsage_getIsKeyCertSignEnabled(KeyUsage *self)
{
    BOOL val = 0;
    HR_METHOD_ERRORCHECK_RETURN(self->m_pCppCadesImpl->get_IsKeyCertSignEnabled(&val));
    return val ? Py_True : Py_False;
}

static PyObject *KeyUsage_getIsCRLSignEnabled(KeyUsage *self)
{
    BOOL val = 0;
    HR_METHOD_ERRORCHECK_RETURN(self->m_pCppCadesImpl->get_IsCRLSignEnabled(&val));
    return val ? Py_True : Py_False;
}

static PyObject *KeyUsage_getIsEncipherOnlyEnabled(KeyUsage *self)
{
    BOOL val = 0;
    HR_METHOD_ERRORCHECK_RETURN(self->m_pCppCadesImpl->get_IsEncipherOnlyEnabled(&val));
    return val ? Py_True : Py_False;
}

static PyObject *KeyUsage_getIsDecipherOnlyEnabled(KeyUsage *self)
{
    BOOL val = 0;
    HR_METHOD_ERRORCHECK_RETURN(self->m_pCppCadesImpl->get_IsDecipherOnlyEnabled(&val));
    return val ? Py_True : Py_False;
}

static PyGetSetDef KeyUsage_getset[] = {
    {"IsPresent", (getter)KeyUsage_getIsPresent, NULL, "IsPresent", NULL},
    {"IsCritical", (getter)KeyUsage_getIsCritical, NULL, "IsCritical", NULL},
    {"IsDigitalSignatureEnabled", (getter)KeyUsage_getIsDigitalSignatureEnabled, NULL, "IsDigitalSignatureEnabled", NULL},
    {"IsNonRepudiationEnabled", (getter)KeyUsage_getIsNonRepudiationEnabled, NULL, "IsNonRepudiationEnabled", NULL},
    {"IsKeyEnciphermentEnabled", (getter)KeyUsage_getIsKeyEnciphermentEnabled, NULL, "IsKeyEnciphermentEnabled", NULL},
    {"IsKeyAgreementEnabled", (getter)KeyUsage_getIsKeyAgreementEnabled, NULL, "IsKeyAgreementEnabled", NULL},
    {"IsKeyCertSignEnabled", (getter)KeyUsage_getIsKeyCertSignEnabled, NULL, "IsKeyCertSignEnabled", NULL},
    {"IsDataEnciphermentEnabled", (getter)KeyUsage_getIsDataEnciphermentEnabled, NULL, "IsDataEnciphermentEnabled", NULL},
    {"IsCRLSignEnabled", (getter)KeyUsage_getIsCRLSignEnabled, NULL, "IsCRLSignEnabled", NULL},
    {"IsEncipherOnlyEnabled", (getter)KeyUsage_getIsEncipherOnlyEnabled, NULL, "IsEncipherOnlyEnabled", NULL},
    {"IsDecipherOnlyEnabled", (getter)KeyUsage_getIsDecipherOnlyEnabled, NULL, "IsDecipherOnlyEnabled", NULL},
    {NULL} /* Sentinel */
};

static PyMethodDef KeyUsage_methods[] = {
    {NULL} /* Sentinel */
};

PyTypeObject KeyUsageType = {
    PyVarObject_HEAD_INIT(NULL, 0) "pycades.KeyUsage", /* tp_name */
    sizeof(KeyUsage),                                  /* tp_basicsize */
    0,                                                 /* tp_itemsize */
    (destructor)KeyUsage_dealloc,                      /* tp_dealloc */
    0,                                                 /* tp_print */
    0,                                                 /* tp_getattr */
    0,                                                 /* tp_setattr */
    0,                                                 /* tp_compare */
    0,                                                 /* tp_repr */
    0,                                                 /* tp_as_number */
    0,                                                 /* tp_as_sequence */
    0,                                                 /* tp_as_mapping */
    0,                                                 /* tp_hash */
    0,                                                 /* tp_call */
    0,                                                 /* tp_str */
    0,                                                 /* tp_getattro */
    0,                                                 /* tp_setattro */
    0,                                                 /* tp_as_buffer */
    Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,          /* tp_flags */
    "KeyUsage object",                                 /* tp_doc */
    0,                                                 /* tp_traverse */
    0,                                                 /* tp_clear */
    0,                                                 /* tp_richcompare */
    0,                                                 /* tp_weaklistoffset */
    0,                                                 /* tp_iter */
    0,                                                 /* tp_iternext */
    KeyUsage_methods,                                  /* tp_methods */
    0,                                                 /* tp_members */
    KeyUsage_getset,                                   /* tp_getset */
    0,                                                 /* tp_base */
    0,                                                 /* tp_dict */
    0,                                                 /* tp_descr_get */
    0,                                                 /* tp_descr_set */
    0,                                                 /* tp_dictoffset */
    0,                                                 /* tp_init */
    0,                                                 /* tp_alloc */
    KeyUsage_new,                                      /* tp_new */
};
