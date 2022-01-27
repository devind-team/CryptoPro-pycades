#include "PyCadesHashedData.h"

using namespace CryptoPro::PKI::CAdES;

static void HashedData_dealloc(HashedData *self)
{
    Py_TYPE(self)->tp_free((PyObject *)self);
}

static PyObject *HashedData_new(PyTypeObject *type, PyObject *args, PyObject *kwds)
{
    HashedData *self;
    self = (HashedData *)type->tp_alloc(type, 0);
    if (self != NULL)
    {
        self->m_pCppCadesImpl = boost::shared_ptr<CPPCadesCPHashedDataObject>(new CPPCadesCPHashedDataObject());
    }
    return (PyObject *)self;
}

static PyObject *HashedData_Hash(HashedData *self, PyObject *args)
{
    char *szValue = "";
    if (!PyArg_ParseTuple(args, "s", &szValue))
    {
        return NULL;
    }
    CAtlString sValue = CAtlString(szValue);
    HR_METHOD_ERRORCHECK_RETURN(self->m_pCppCadesImpl->put_Hash(sValue.GetString(), sValue.GetLength()));
    Py_RETURN_NONE;
}

static PyObject *HashedData_setHashValue(HashedData *self, PyObject *args)
{
    char *szValue = "";
    if (!PyArg_ParseTuple(args, "s", &szValue))
    {
        return NULL;
    }
    CAtlString sValue(szValue);
    HR_METHOD_ERRORCHECK_RETURN(self->m_pCppCadesImpl->put_HashValue(sValue));
    Py_RETURN_NONE;
}

static PyObject *HashedData_getValue(HashedData *self)
{
    CAtlString sValue;
    HR_METHOD_ERRORCHECK_RETURN(self->m_pCppCadesImpl->get_Value(sValue));
    return Py_BuildValue("s", sValue.GetString());
}

static PyObject *HashedData_getKey(HashedData *self)
{
    CAtlString sKey;
    HR_METHOD_ERRORCHECK_RETURN(self->m_pCppCadesImpl->get_Key(sKey));
    return Py_BuildValue("s", sKey.GetString());
}

static int HashedData_setKey(HashedData *self, PyObject *value)
{
    char *szKey = "";
    if (!PyArg_Parse(value, "s", &szKey))
    {
        return -1;
    }
    CAtlString sKey = CAtlString(szKey);
    HR_SETTER_ERRORCHECK_RETURN(self->m_pCppCadesImpl->put_Key(sKey));
    return 0;
}

static PyObject *HashedData_getAlgorithm(HashedData *self)
{
    CAPICOM_HASH_ALGORITHM Algorithm;
    HR_METHOD_ERRORCHECK_RETURN(self->m_pCppCadesImpl->get_Algorithm(&Algorithm));
    return Py_BuildValue("l", Algorithm);
}

static int HashedData_setAlgorithm(HashedData *self, PyObject *value)
{
    long lAlgorithm = 0;
    if (!PyArg_Parse(value, "l", &lAlgorithm))
    {
        return -1;
    }
    CAPICOM_HASH_ALGORITHM Algorithm = (CAPICOM_HASH_ALGORITHM)lAlgorithm;
    HR_SETTER_ERRORCHECK_RETURN(self->m_pCppCadesImpl->put_Algorithm(Algorithm));
    return 0;
}

static PyObject *HashedData_getDataEncoding(HashedData *self)
{
    CADESCOM_CONTENT_ENCODING_TYPE Type;
    HR_METHOD_ERRORCHECK_RETURN(self->m_pCppCadesImpl->get_DataEncoding(&Type));
    return Py_BuildValue("l", Type);
}

static int HashedData_setDataEncoding(HashedData *self, PyObject *value)
{
    long lType = 0;
    if (!PyArg_Parse(value, "l", &lType))
    {
        return -1;
    }
    CADESCOM_CONTENT_ENCODING_TYPE Type = (CADESCOM_CONTENT_ENCODING_TYPE)lType;
    HR_SETTER_ERRORCHECK_RETURN(self->m_pCppCadesImpl->put_DataEncoding(Type));
    return 0;
}

static PyGetSetDef HashedData_getset[] = {
    {"Key", (getter)HashedData_getKey, (setter)HashedData_setKey, "Key", NULL},
    {"Algorithm", (getter)HashedData_getAlgorithm, (setter)HashedData_setAlgorithm, "Algorithm", NULL},
    {"DataEncoding", (getter)HashedData_getDataEncoding, (setter)HashedData_setDataEncoding, "DataEncoding", NULL},
    {"Value", (getter)HashedData_getValue, NULL, "Key", NULL},
    {NULL} /* Sentinel */
};

static PyMethodDef HashedData_methods[] = {
    {"Hash", (PyCFunction)HashedData_Hash, METH_VARARGS, "Hash"},
    {"SetHashValue", (PyCFunction)HashedData_setHashValue, METH_VARARGS, "SetHashValue"},
    {NULL} /* Sentinel */
};

PyTypeObject HashedDataType = {
    PyVarObject_HEAD_INIT(NULL, 0) "pycades.HashedData", /* tp_name */
    sizeof(HashedData),                                  /* tp_basicsize */
    0,                                                   /* tp_itemsize */
    (destructor)HashedData_dealloc,                      /* tp_dealloc */
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
    "HashedData object",                                 /* tp_doc */
    0,                                                   /* tp_traverse */
    0,                                                   /* tp_clear */
    0,                                                   /* tp_richcompare */
    0,                                                   /* tp_weaklistoffset */
    0,                                                   /* tp_iter */
    0,                                                   /* tp_iternext */
    HashedData_methods,                                  /* tp_methods */
    0,                                                   /* tp_members */
    HashedData_getset,                                   /* tp_getset */
    0,                                                   /* tp_base */
    0,                                                   /* tp_dict */
    0,                                                   /* tp_descr_get */
    0,                                                   /* tp_descr_set */
    0,                                                   /* tp_dictoffset */
    0,                                                   /* tp_init */
    0,                                                   /* tp_alloc */
    HashedData_new,                                      /* tp_new */
};
