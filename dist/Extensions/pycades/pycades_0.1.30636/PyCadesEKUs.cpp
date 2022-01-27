#include "PyCadesEKUs.h"
#include "PyCadesEKU.h"

using namespace CryptoPro::PKI::CAdES;

static void EKUs_dealloc(EKUs *self)
{
    Py_TYPE(self)->tp_free((PyObject *)self);
}

static PyObject *EKUs_new(PyTypeObject *type, PyObject *args, PyObject *kwds)
{
    EKUs *self;
    self = (EKUs *)type->tp_alloc(type, 0);
    if (self != NULL)
    {
        self->m_pCppCadesImpl = boost::shared_ptr<CPPCadesCPEKUsObject>(new CPPCadesCPEKUsObject());
    }
    return (PyObject *)self;
}

static PyObject *EKUs_getCount(EKUs *self)
{
    unsigned int count = 0;
    HR_METHOD_ERRORCHECK_RETURN(self->m_pCppCadesImpl->get_Count(&count));
    return Py_BuildValue("l", count);
}

static PyObject *EKUs_getItem(EKUs *self, PyObject *args)
{
    long index = 0;
    if (!PyArg_ParseTuple(args, "l", &index))
    {
        return NULL;
    }
    boost::shared_ptr<CPPCadesCPEKUObject> pCppCadesEKU = boost::shared_ptr<CPPCadesCPEKUObject>(new CPPCadesCPEKUObject());
    HR_METHOD_ERRORCHECK_RETURN(self->m_pCppCadesImpl->get_Item(index, pCppCadesEKU));
    PyObject *pPyEKU = PyObject_CallObject((PyObject *)&EKUType, NULL);
    EKU *pEKU = (EKU *)pPyEKU;
    pEKU->m_pCppCadesImpl = pCppCadesEKU;
    return Py_BuildValue("O", pEKU);
}

static PyGetSetDef EKUs_getset[] = {
    {"Count", (getter)EKUs_getCount, NULL, "Count", NULL},
    {NULL} /* Sentinel */
};

static PyMethodDef EKUs_methods[] = {
    {"Item", (PyCFunction)EKUs_getItem, METH_VARARGS, "Item"},
    {NULL} /* Sentinel */
};

PyTypeObject EKUsType = {
    PyVarObject_HEAD_INIT(NULL, 0) "pycades.EKUs", /* tp_name */
    sizeof(EKUs),                                  /* tp_basicsize */
    0,                                             /* tp_itemsize */
    (destructor)EKUs_dealloc,                      /* tp_dealloc */
    0,                                             /* tp_print */
    0,                                             /* tp_getattr */
    0,                                             /* tp_setattr */
    0,                                             /* tp_compare */
    0,                                             /* tp_repr */
    0,                                             /* tp_as_number */
    0,                                             /* tp_as_sequence */
    0,                                             /* tp_as_mapping */
    0,                                             /* tp_hash */
    0,                                             /* tp_call */
    0,                                             /* tp_str */
    0,                                             /* tp_getattro */
    0,                                             /* tp_setattro */
    0,                                             /* tp_as_buffer */
    Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,      /* tp_flags */
    "EKUs object",                                 /* tp_doc */
    0,                                             /* tp_traverse */
    0,                                             /* tp_clear */
    0,                                             /* tp_richcompare */
    0,                                             /* tp_weaklistoffset */
    0,                                             /* tp_iter */
    0,                                             /* tp_iternext */
    EKUs_methods,                                  /* tp_methods */
    0,                                             /* tp_members */
    EKUs_getset,                                   /* tp_getset */
    0,                                             /* tp_base */
    0,                                             /* tp_dict */
    0,                                             /* tp_descr_get */
    0,                                             /* tp_descr_set */
    0,                                             /* tp_dictoffset */
    0,                                             /* tp_init */
    0,                                             /* tp_alloc */
    EKUs_new,                                      /* tp_new */
};
