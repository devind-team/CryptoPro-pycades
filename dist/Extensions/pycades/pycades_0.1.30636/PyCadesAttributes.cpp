#include "PyCadesAttributes.h"
#include "PyCadesAttribute.h"

using namespace CryptoPro::PKI::CAdES;

static void Attributes_dealloc(Attributes *self)
{
    Py_TYPE(self)->tp_free((PyObject *)self);
}

static PyObject *Attributes_new(PyTypeObject *type, PyObject *args, PyObject *kwds)
{
    Attributes *self;
    self = (Attributes *)type->tp_alloc(type, 0);
    if (self != NULL)
    {
        self->m_pCppCadesImpl = boost::shared_ptr<CPPCadesCPAttributesObject>(new CPPCadesCPAttributesObject());
    }
    return (PyObject *)self;
}

static PyObject *Attributes_getCount(Attributes *self)
{
    long count = 0;
    HR_METHOD_ERRORCHECK_RETURN(self->m_pCppCadesImpl->get_Count(&count));
    return Py_BuildValue("l", count);
}

static PyObject *Attributes_Add(Attributes *self, PyObject *args)
{
    PyObject *item = NULL;
    if (!PyArg_ParseTuple(args, "O!", &AttributeType, &item))
    {
        return NULL;
    }
    Attribute *pAttribute = (Attribute *)item;
    HR_METHOD_ERRORCHECK_RETURN(self->m_pCppCadesImpl->Add(pAttribute->m_pCppCadesImpl));
    Py_RETURN_NONE;
}

static PyObject *Attributes_getItem(Attributes *self, PyObject *args)
{
    long index = 0;
    if (!PyArg_ParseTuple(args, "l", &index))
    {
        return NULL;
    }

    PyObject *pPyAttribute = PyObject_CallObject((PyObject *)&AttributeType, NULL);
    Attribute *pAttribute = (Attribute *)pPyAttribute;
    HR_METHOD_ERRORCHECK_RETURN(self->m_pCppCadesImpl->get_Item(index, pAttribute->m_pCppCadesImpl));
    return Py_BuildValue("O", pAttribute);
}

static PyObject *Attributes_Clear(Attributes *self, PyObject *args)
{
    HR_METHOD_ERRORCHECK_RETURN(self->m_pCppCadesImpl->Clear());
    Py_RETURN_NONE;
}

static PyObject *Attributes_Remove(Attributes *self, PyObject *args)
{
    long index = 0;
    if (!PyArg_ParseTuple(args, "l", &index))
    {
        return NULL;
    }
    HR_METHOD_ERRORCHECK_RETURN(self->m_pCppCadesImpl->Remove(index));
    Py_RETURN_NONE;
}

static PyGetSetDef Attributes_getset[] = {
    {"Count", (getter)Attributes_getCount, NULL, "Count", NULL},
    {NULL} /* Sentinel */
};

static PyMethodDef Attributes_methods[] = {
    {"Add", (PyCFunction)Attributes_Add, METH_VARARGS, "Add"},
    {"Clear", (PyCFunction)Attributes_Clear, METH_NOARGS, "Clear"},
    {"Remove", (PyCFunction)Attributes_Remove, METH_VARARGS, "Remove"},
    {"Item", (PyCFunction)Attributes_getItem, METH_VARARGS, "Item"},
    {NULL} /* Sentinel */
};

PyTypeObject AttributesType = {
    PyVarObject_HEAD_INIT(NULL, 0) "pycades.Attributes", /* tp_name */
    sizeof(Attributes),                                  /* tp_basicsize */
    0,                                                   /* tp_itemsize */
    (destructor)Attributes_dealloc,                      /* tp_dealloc */
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
    "Attributes object",                                 /* tp_doc */
    0,                                                   /* tp_traverse */
    0,                                                   /* tp_clear */
    0,                                                   /* tp_richcompare */
    0,                                                   /* tp_weaklistoffset */
    0,                                                   /* tp_iter */
    0,                                                   /* tp_iternext */
    Attributes_methods,                                  /* tp_methods */
    0,                                                   /* tp_members */
    Attributes_getset,                                   /* tp_getset */
    0,                                                   /* tp_base */
    0,                                                   /* tp_dict */
    0,                                                   /* tp_descr_get */
    0,                                                   /* tp_descr_set */
    0,                                                   /* tp_dictoffset */
    0,                                                   /* tp_init */
    0,                                                   /* tp_alloc */
    Attributes_new,                                      /* tp_new */
};
