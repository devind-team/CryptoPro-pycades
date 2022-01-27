#include "PyCadesBlobs.h"

using namespace CryptoPro;
using namespace CryptoPro::PKI::CAdES;

static void Blobs_dealloc(Blobs *self)
{
    Py_TYPE(self)->tp_free((PyObject *)self);
}

static PyObject *Blobs_new(PyTypeObject *type, PyObject *args, PyObject *kwds)
{
    Blobs *self;
    self = (Blobs *)type->tp_alloc(type, 0);
    if (self != NULL)
    {
        self->m_pCppCadesImpl = boost::shared_ptr<CPPCadesCPBlobsObject>(new CPPCadesCPBlobsObject());
    }
    return (PyObject *)self;
}

static PyObject *Blobs_getCount(Blobs *self)
{
    unsigned int count;
    HR_METHOD_ERRORCHECK_RETURN(self->m_pCppCadesImpl->get_Count(&count));
    return Py_BuildValue("l", count);
}

static PyObject *Blobs_Item(Blobs *self, PyObject *args)
{
    long lIndex = 0;
    if (!PyArg_ParseTuple(args, "l", &lIndex))
    {
        return NULL;
    }
    boost::shared_ptr<CBlob> pEncValueBlob = boost::shared_ptr<CBlob>(new CBlob());
    HR_METHOD_ERRORCHECK_RETURN(self->m_pCppCadesImpl->get_Item(lIndex, pEncValueBlob));

    CAtlString sValue;
    sValue = CAtlString((const TCHAR *)pEncValueBlob->pbData(), pEncValueBlob->cbData() / sizeof(TCHAR));

    return Py_BuildValue("s", sValue.GetString());
}

static PyGetSetDef Blobs_getset[] = {
    {"Count", (getter)Blobs_getCount, NULL, "Count", NULL},
    {NULL} /* Sentinel */
};

static PyMethodDef Blobs_methods[] = {
    {"Item", (PyCFunction)Blobs_Item, METH_VARARGS, "Item"},
    {NULL} /* Sentinel */
};

PyTypeObject BlobsType = {
    PyVarObject_HEAD_INIT(NULL, 0) "pycades.Blobs", /* tp_name */
    sizeof(Blobs),                                  /* tp_basicsize */
    0,                                              /* tp_itemsize */
    (destructor)Blobs_dealloc,                      /* tp_dealloc */
    0,                                              /* tp_print */
    0,                                              /* tp_getattr */
    0,                                              /* tp_setattr */
    0,                                              /* tp_compare */
    0,                                              /* tp_repr */
    0,                                              /* tp_as_number */
    0,                                              /* tp_as_sequence */
    0,                                              /* tp_as_mapping */
    0,                                              /* tp_hash */
    0,                                              /* tp_call */
    0,                                              /* tp_str */
    0,                                              /* tp_getattro */
    0,                                              /* tp_setattro */
    0,                                              /* tp_as_buffer */
    Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,       /* tp_flags */
    "Blobs object",                                 /* tp_doc */
    0,                                              /* tp_traverse */
    0,                                              /* tp_clear */
    0,                                              /* tp_richcompare */
    0,                                              /* tp_weaklistoffset */
    0,                                              /* tp_iter */
    0,                                              /* tp_iternext */
    Blobs_methods,                                  /* tp_methods */
    0,                                              /* tp_members */
    Blobs_getset,                                   /* tp_getset */
    0,                                              /* tp_base */
    0,                                              /* tp_dict */
    0,                                              /* tp_descr_get */
    0,                                              /* tp_descr_set */
    0,                                              /* tp_dictoffset */
    0,                                              /* tp_init */
    0,                                              /* tp_alloc */
    Blobs_new,                                      /* tp_new */
};
