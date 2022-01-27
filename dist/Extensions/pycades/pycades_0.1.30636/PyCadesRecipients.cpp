#include "PyCadesRecipients.h"
#include "PyCadesCertificate.h"

using namespace CryptoPro::PKI::CAdES;

static void Recipients_dealloc(Recipients *self)
{
    Py_TYPE(self)->tp_free((PyObject *)self);
}

static PyObject *Recipients_new(PyTypeObject *type, PyObject *args, PyObject *kwds)
{
    Recipients *self;
    self = (Recipients *)type->tp_alloc(type, 0);
    if (self != NULL)
    {
        self->m_pCppCadesImpl = boost::shared_ptr<CPPCadesCPRecipientsObject>(new CPPCadesCPRecipientsObject());
    }
    return (PyObject *)self;
}

static PyObject *Recipients_Item(Recipients *self, PyObject *args)
{
    long Index = 0;
    if (!PyArg_ParseTuple(args, "l", &Index))
    {
        return NULL;
    }
    boost::shared_ptr<CPPCadesCPCertificateObject> pCppCadesCert;
    HR_METHOD_ERRORCHECK_RETURN(self->m_pCppCadesImpl->get_Item(Index, pCppCadesCert));
    PyObject *pPyCert = PyObject_CallObject((PyObject *)&CertificateType, NULL);
    Certificate *pCert = (Certificate *)pPyCert;
    pCert->m_pCppCadesImpl = pCppCadesCert;
    return Py_BuildValue("O", pCert);
}

static PyObject *Recipients_getCount(Recipients *self)
{
    unsigned int Count = 0;
    HR_METHOD_ERRORCHECK_RETURN(self->m_pCppCadesImpl->get_Count(&Count));
    return Py_BuildValue("l", Count);
}

static PyObject *Recipients_Add(Recipients *self, PyObject *args)
{
    PyObject *pPyCert;
    if (!PyArg_ParseTuple(args, "O!", &CertificateType, &pPyCert))
    {
        return NULL;
    }
    Certificate *pCert = (Certificate *)pPyCert;
    HR_METHOD_ERRORCHECK_RETURN(self->m_pCppCadesImpl->Add(pCert->m_pCppCadesImpl));
    Py_RETURN_NONE;
}

static PyObject *Recipients_Clear(Recipients *self, PyObject *args)
{
    HR_METHOD_ERRORCHECK_RETURN(self->m_pCppCadesImpl->Clear());
    Py_RETURN_NONE;
}

static PyObject *Recipients_Remove(Recipients *self, PyObject *args)
{
    long Index = 0;
    if (!PyArg_ParseTuple(args, "l", &Index))
    {
        return NULL;
    }
    HR_METHOD_ERRORCHECK_RETURN(self->m_pCppCadesImpl->Remove(Index));
    Py_RETURN_NONE;
}

static PyGetSetDef Recipients_getset[] = {
    {"Count", (getter)Recipients_getCount, NULL, "Count", NULL},
    {NULL} /* Sentinel */
};

static PyMethodDef Recipients_methods[] = {
    {"Add", (PyCFunction)Recipients_Add, METH_VARARGS, "Add"},
    {"Clear", (PyCFunction)Recipients_Clear, METH_NOARGS, "Clear"},
    {"Remove", (PyCFunction)Recipients_Remove, METH_VARARGS, "Remove"},
    {"Item", (PyCFunction)Recipients_Item, METH_VARARGS, "Item"},
    {NULL} /* Sentinel */
};

PyTypeObject RecipientsType = {
    PyVarObject_HEAD_INIT(NULL, 0) "pycades.Recipients", /* tp_name */
    sizeof(Recipients),                                  /* tp_basicsize */
    0,                                                   /* tp_itemsize */
    (destructor)Recipients_dealloc,                      /* tp_dealloc */
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
    "Recipients object",                                 /* tp_doc */
    0,                                                   /* tp_traverse */
    0,                                                   /* tp_clear */
    0,                                                   /* tp_richcompare */
    0,                                                   /* tp_weaklistoffset */
    0,                                                   /* tp_iter */
    0,                                                   /* tp_iternext */
    Recipients_methods,                                  /* tp_methods */
    0,                                                   /* tp_members */
    Recipients_getset,                                   /* tp_getset */
    0,                                                   /* tp_base */
    0,                                                   /* tp_dict */
    0,                                                   /* tp_descr_get */
    0,                                                   /* tp_descr_set */
    0,                                                   /* tp_dictoffset */
    0,                                                   /* tp_init */
    0,                                                   /* tp_alloc */
    Recipients_new,                                      /* tp_new */
};
