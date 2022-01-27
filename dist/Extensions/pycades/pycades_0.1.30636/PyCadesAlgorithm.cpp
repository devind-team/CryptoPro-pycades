#include "PyCadesAlgorithm.h"

using namespace CryptoPro::PKI::CAdES;

static void Algorithm_dealloc(Algorithm *self)
{
    Py_TYPE(self)->tp_free((PyObject *)self);
}

static PyObject *Algorithm_new(PyTypeObject *type, PyObject *args, PyObject *kwds)
{
    Algorithm *self;
    self = (Algorithm *)type->tp_alloc(type, 0);
    if (self != NULL)
    {
        self->m_pCppCadesImpl = boost::shared_ptr<CPPCadesCPAlgorithmObject>(new CPPCadesCPAlgorithmObject());
    }
    return (PyObject *)self;
}

static PyObject *Algorithm_getName(Algorithm *self)
{
    CADESCOM_ENCRYPTION_ALGORITHM Name;
    HR_METHOD_ERRORCHECK_RETURN(self->m_pCppCadesImpl->get_Name(&Name));
    return Py_BuildValue("l", Name);
}

static int Algorithm_setName(Algorithm *self, PyObject *value)
{
    long lName = 0;
    if (!PyArg_Parse(value, "l", &lName))
    {
        return -1;
    }
    CADESCOM_ENCRYPTION_ALGORITHM Name = (CADESCOM_ENCRYPTION_ALGORITHM)lName;
    HR_SETTER_ERRORCHECK_RETURN(self->m_pCppCadesImpl->put_Name(Name));
    return 0;
}

static PyObject *Algorithm_getKeyLength(Algorithm *self)
{
    CAPICOM_ENCRYPTION_KEY_LENGTH Len;
    HR_METHOD_ERRORCHECK_RETURN(self->m_pCppCadesImpl->get_KeyLength(&Len));
    return Py_BuildValue("l", Len);
}

static int Algorithm_setKeyLength(Algorithm *self, PyObject *value)
{
    long lLen = 0;
    if (!PyArg_Parse(value, "l", &lLen))
    {
        return -1;
    }
    CAPICOM_ENCRYPTION_KEY_LENGTH Len = (CAPICOM_ENCRYPTION_KEY_LENGTH)lLen;
    HR_SETTER_ERRORCHECK_RETURN(self->m_pCppCadesImpl->put_KeyLength(Len));
    return 0;
}

static PyGetSetDef Algorithm_getset[] = {
    {"Name", (getter)Algorithm_getName, (setter)Algorithm_setName, "Name", NULL},
    {"KeyLength", (getter)Algorithm_getKeyLength, (setter)Algorithm_setKeyLength, "KeyLength", NULL},
    {NULL} /* Sentinel */
};

static PyMethodDef Algorithm_methods[] = {
    {NULL} /* Sentinel */
};

PyTypeObject AlgorithmType = {
    PyVarObject_HEAD_INIT(NULL, 0) "pycades.Algorithm", /* tp_name */
    sizeof(Algorithm),                                  /* tp_basicsize */
    0,                                                  /* tp_itemsize */
    (destructor)Algorithm_dealloc,                      /* tp_dealloc */
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
    "Algorithm object",                                 /* tp_doc */
    0,                                                  /* tp_traverse */
    0,                                                  /* tp_clear */
    0,                                                  /* tp_richcompare */
    0,                                                  /* tp_weaklistoffset */
    0,                                                  /* tp_iter */
    0,                                                  /* tp_iternext */
    Algorithm_methods,                                  /* tp_methods */
    0,                                                  /* tp_members */
    Algorithm_getset,                                   /* tp_getset */
    0,                                                  /* tp_base */
    0,                                                  /* tp_dict */
    0,                                                  /* tp_descr_get */
    0,                                                  /* tp_descr_set */
    0,                                                  /* tp_dictoffset */
    0,                                                  /* tp_init */
    0,                                                  /* tp_alloc */
    Algorithm_new,                                      /* tp_new */
};
