#include "PyCadesEncodedData.h"

using namespace CryptoPro::PKI::CAdES;

static void EncodedData_dealloc(EncodedData *self)
{
    Py_TYPE(self)->tp_free((PyObject *)self);
}

static PyObject *EncodedData_new(PyTypeObject *type, PyObject *args, PyObject *kwds)
{
    EncodedData *self;
    self = (EncodedData *)type->tp_alloc(type, 0);
    if (self != NULL)
    {
        self->m_pCppCadesImpl = boost::shared_ptr<CPPCadesCPEncodedDataObject>(new CPPCadesCPEncodedDataObject());
    }
    return (PyObject *)self;
}

static PyObject *EncodedData_Format(EncodedData *self, PyObject *args)
{
    int bMultiLine = 0;
    if (!PyArg_ParseTuple(args, "|i", &bMultiLine))
    {
        return NULL;
    }
    CAtlStringW sValue;
    HR_METHOD_ERRORCHECK_RETURN(self->m_pCppCadesImpl->Format(bMultiLine, sValue));
    return Py_BuildValue("s", sValue.GetString());
}

static PyObject *EncodedData_getValue(EncodedData *self, PyObject *args)
{
    long lType = 0;
    if (!PyArg_ParseTuple(args, "|l", &lType))
    {
        return NULL;
    }
    CAPICOM_ENCODING_TYPE Type = (CAPICOM_ENCODING_TYPE)lType;
    CryptoPro::CBlob data;
    HR_METHOD_ERRORCHECK_RETURN(self->m_pCppCadesImpl->get_Value(Type, data));
    CAtlString sValue = CAtlString((const char *)data.pbData(), data.cbData());
    return Type == CAPICOM_ENCODE_BINARY ? 
            PyBytes_FromStringAndSize((const char *)data.pbData(), data.cbData()) : 
            Py_BuildValue("s", sValue.GetString());
}

static PyGetSetDef EncodedData_getset[] = {
    {NULL} /* Sentinel */
};

static PyMethodDef EncodedData_methods[] = {
    {"Value", (PyCFunction)EncodedData_getValue, METH_VARARGS, "Value"},
    {"Format", (PyCFunction)EncodedData_Format, METH_VARARGS, "Format"},
    {NULL} /* Sentinel */
};

PyTypeObject EncodedDataType = {
    PyVarObject_HEAD_INIT(NULL, 0) "pycades.EncodedData", /* tp_name */
    sizeof(EncodedData),                                  /* tp_basicsize */
    0,                                                    /* tp_itemsize */
    (destructor)EncodedData_dealloc,                      /* tp_dealloc */
    0,                                                    /* tp_print */
    0,                                                    /* tp_getattr */
    0,                                                    /* tp_setattr */
    0,                                                    /* tp_compare */
    0,                                                    /* tp_repr */
    0,                                                    /* tp_as_number */
    0,                                                    /* tp_as_sequence */
    0,                                                    /* tp_as_mapping */
    0,                                                    /* tp_hash */
    0,                                                    /* tp_call */
    0,                                                    /* tp_str */
    0,                                                    /* tp_getattro */
    0,                                                    /* tp_setattro */
    0,                                                    /* tp_as_buffer */
    Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,             /* tp_flags */
    "EncodedData object",                                 /* tp_doc */
    0,                                                    /* tp_traverse */
    0,                                                    /* tp_clear */
    0,                                                    /* tp_richcompare */
    0,                                                    /* tp_weaklistoffset */
    0,                                                    /* tp_iter */
    0,                                                    /* tp_iternext */
    EncodedData_methods,                                  /* tp_methods */
    0,                                                    /* tp_members */
    EncodedData_getset,                                   /* tp_getset */
    0,                                                    /* tp_base */
    0,                                                    /* tp_dict */
    0,                                                    /* tp_descr_get */
    0,                                                    /* tp_descr_set */
    0,                                                    /* tp_dictoffset */
    0,                                                    /* tp_init */
    0,                                                    /* tp_alloc */
    EncodedData_new,                                      /* tp_new */
};
