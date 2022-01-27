#include "PyCadesPrivateKey.h"

using namespace CryptoPro::PKI::CAdES;

static void PrivateKey_dealloc(PrivateKey *self)
{
    Py_TYPE(self)->tp_free((PyObject *)self);
}

static PyObject *PrivateKey_new(PyTypeObject *type, PyObject *args, PyObject *kwds)
{
    PrivateKey *self;
    self = (PrivateKey *)type->tp_alloc(type, 0);
    if (self != NULL)
    {
        self->m_pCppCadesImpl = boost::shared_ptr<CPPCadesCPPrivateKeyObject>(new CPPCadesCPPrivateKeyObject());
    }
    return (PyObject *)self;
}

static PyObject *PrivateKey_getContainerName(PrivateKey *self)
{
    CAtlString sContName;
    HR_METHOD_ERRORCHECK_RETURN(self->m_pCppCadesImpl->get_ContainerName(sContName));
    return Py_BuildValue("s", sContName.GetString());
}

static PyObject *PrivateKey_getUniqueContainerName(PrivateKey *self)
{
    CAtlString sUniqueContName;
    HR_METHOD_ERRORCHECK_RETURN(self->m_pCppCadesImpl->get_UniqueContainerName(sUniqueContName));
    return Py_BuildValue("s", sUniqueContName.GetString());
}

static PyObject *PrivateKey_getProviderName(PrivateKey *self)
{
    CAtlString sProvName;
    HR_METHOD_ERRORCHECK_RETURN(self->m_pCppCadesImpl->get_ProviderName(sProvName));
    return Py_BuildValue("s", sProvName.GetString());
}

static PyObject *PrivateKey_getProviderType(PrivateKey *self)
{
    CAPICOM_PROV_TYPE Type;
    HR_METHOD_ERRORCHECK_RETURN(self->m_pCppCadesImpl->get_ProviderType(&Type));
    return Py_BuildValue("l", (long)Type);
}

static PyObject *PrivateKey_getKeySpec(PrivateKey *self)
{
    CAPICOM_KEY_SPEC spec;
    HR_METHOD_ERRORCHECK_RETURN(self->m_pCppCadesImpl->get_KeySpec(&spec));
    return Py_BuildValue("l", (long)spec);
}

static PyObject *PrivateKey_ChangePin(PrivateKey *self, PyObject *args)
{
    HR_METHOD_ERRORCHECK_RETURN(self->m_pCppCadesImpl->ChangePin());
    Py_RETURN_NONE;
}

static int PrivateKey_setCachePin(PrivateKey *self, PyObject *value)
{
    int bCachePin = 0;
    if (!PyArg_Parse(value, "i", &bCachePin))
    {
        return -1;
    }
    HR_SETTER_ERRORCHECK_RETURN(self->m_pCppCadesImpl->set_CachePin(bCachePin));
    return 0;
}

static int PrivateKey_setKeyPin(PrivateKey *self, PyObject *value)
{
    char *szKeyPin = "";
    if (!PyArg_Parse(value, "s", &szKeyPin))
    {
        return -1;
    }
    CAtlString sKeyPin = CAtlString(szKeyPin);
    HR_SETTER_ERRORCHECK_RETURN(self->m_pCppCadesImpl->set_KeyPin(sKeyPin));
    return 0;
}

static PyGetSetDef PrivateKey_getset[] = {
    {"ContainerName", (getter)PrivateKey_getContainerName, NULL, "ContainerName", NULL},
    {"UniqueContainerName", (getter)PrivateKey_getUniqueContainerName, NULL, "UniqueContainerName", NULL},
    {"ProviderName", (getter)PrivateKey_getProviderName, NULL, "ProviderName", NULL},
    {"ProviderType", (getter)PrivateKey_getProviderType, NULL, "ProviderType", NULL},
    {"KeySpec", (getter)PrivateKey_getKeySpec, NULL, "KeySpec", NULL},
    {"CachePin", NULL, (setter)PrivateKey_setCachePin, "CachePin", NULL},
    {"KeyPin", NULL, (setter)PrivateKey_setKeyPin, "KeyPin", NULL},
    {NULL} /* Sentinel */
};

static PyMethodDef PrivateKey_methods[] = {
    {"ChangePin", (PyCFunction)PrivateKey_ChangePin, METH_NOARGS, "ChangePin"},
    {NULL} /* Sentinel */
};

PyTypeObject PrivateKeyType = {
    PyVarObject_HEAD_INIT(NULL, 0) "pycades.PrivateKey", /* tp_name */
    sizeof(PrivateKey),                                  /* tp_basicsize */
    0,                                                   /* tp_itemsize */
    (destructor)PrivateKey_dealloc,                      /* tp_dealloc */
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
    "PrivateKey object",                                 /* tp_doc */
    0,                                                   /* tp_traverse */
    0,                                                   /* tp_clear */
    0,                                                   /* tp_richcompare */
    0,                                                   /* tp_weaklistoffset */
    0,                                                   /* tp_iter */
    0,                                                   /* tp_iternext */
    PrivateKey_methods,                                  /* tp_methods */
    0,                                                   /* tp_members */
    PrivateKey_getset,                                   /* tp_getset */
    0,                                                   /* tp_base */
    0,                                                   /* tp_dict */
    0,                                                   /* tp_descr_get */
    0,                                                   /* tp_descr_set */
    0,                                                   /* tp_dictoffset */
    0,                                                   /* tp_init */
    0,                                                   /* tp_alloc */
    PrivateKey_new,                                      /* tp_new */
};
