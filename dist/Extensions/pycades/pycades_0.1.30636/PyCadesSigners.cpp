#include "PyCadesSigners.h"
#include "PyCadesSigner.h"

using namespace CryptoPro::PKI::CAdES;

static void Signers_dealloc(Signers *self)
{
    Py_TYPE(self)->tp_free((PyObject *)self);
}

static PyObject *Signers_new(PyTypeObject *type, PyObject *args, PyObject *kwds)
{
    Signers *self;
    self = (Signers *)type->tp_alloc(type, 0);
    if (self != NULL)
    {
        self->m_pCppCadesImpl = boost::shared_ptr<CPPCadesCPSignersObject>(new CPPCadesCPSignersObject());
    }
    return (PyObject *)self;
}

static PyObject *Signers_getCount(Signers *self)
{
    unsigned int Count = 0;
    HR_METHOD_ERRORCHECK_RETURN(self->m_pCppCadesImpl->get_Count(&Count));
    return Py_BuildValue("l", Count);
}

static PyObject *Signers_getItem(Signers *self, PyObject *args)
{
    long lIndex = 0;
    if (!PyArg_ParseTuple(args, "l", &lIndex))
    {
        return NULL;
    }
    boost::shared_ptr<CPPCadesCPSignerObject> pCPPCadesCPSigner;
    HR_METHOD_ERRORCHECK_RETURN(self->m_pCppCadesImpl->get_Item(lIndex, pCPPCadesCPSigner));
    PyObject *pPySigner = PyObject_CallObject((PyObject *)&SignerType, NULL);
    Signer *pSigner = (Signer *)pPySigner;
    pSigner->m_pCppCadesImpl = pCPPCadesCPSigner;
    return Py_BuildValue("O", pSigner);
}

static PyGetSetDef Signers_getset[] = {
    {"Count", (getter)Signers_getCount, NULL, "Count", NULL},
    {NULL} /* Sentinel */
};

static PyMethodDef Signers_methods[] = {
    {"Item", (PyCFunction)Signers_getItem, METH_VARARGS, "Item"},
    {NULL} /* Sentinel */
};

PyTypeObject SignersType = {
    PyVarObject_HEAD_INIT(NULL, 0) "pycades.Signers", /* tp_name */
    sizeof(Signers),                                  /* tp_basicsize */
    0,                                                /* tp_itemsize */
    (destructor)Signers_dealloc,                      /* tp_dealloc */
    0,                                                /* tp_print */
    0,                                                /* tp_getattr */
    0,                                                /* tp_setattr */
    0,                                                /* tp_compare */
    0,                                                /* tp_repr */
    0,                                                /* tp_as_number */
    0,                                                /* tp_as_sequence */
    0,                                                /* tp_as_mapping */
    0,                                                /* tp_hash */
    0,                                                /* tp_call */
    0,                                                /* tp_str */
    0,                                                /* tp_getattro */
    0,                                                /* tp_setattro */
    0,                                                /* tp_as_buffer */
    Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,         /* tp_flags */
    "Signers object",                                 /* tp_doc */
    0,                                                /* tp_traverse */
    0,                                                /* tp_clear */
    0,                                                /* tp_richcompare */
    0,                                                /* tp_weaklistoffset */
    0,                                                /* tp_iter */
    0,                                                /* tp_iternext */
    Signers_methods,                                  /* tp_methods */
    0,                                                /* tp_members */
    Signers_getset,                                   /* tp_getset */
    0,                                                /* tp_base */
    0,                                                /* tp_dict */
    0,                                                /* tp_descr_get */
    0,                                                /* tp_descr_set */
    0,                                                /* tp_dictoffset */
    0,                                                /* tp_init */
    0,                                                /* tp_alloc */
    Signers_new,                                      /* tp_new */
};
