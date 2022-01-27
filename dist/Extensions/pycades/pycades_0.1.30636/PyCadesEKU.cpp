#include "PyCadesEKU.h"

using namespace CryptoPro::PKI::CAdES;

static void EKU_dealloc(EKU *self)
{
    Py_TYPE(self)->tp_free((PyObject *)self);
}

static PyObject *EKU_new(PyTypeObject *type, PyObject *args, PyObject *kwds)
{
    EKU *self;
    self = (EKU *)type->tp_alloc(type, 0);
    if (self != NULL)
    {
        self->m_pCppCadesImpl = boost::shared_ptr<CPPCadesCPEKUObject>(new CPPCadesCPEKUObject());
    }
    return (PyObject *)self;
}

static PyObject *EKU_getName(EKU *self)
{
    CAPICOM_EKU Name;
    HR_METHOD_ERRORCHECK_RETURN(self->m_pCppCadesImpl->get_Name(&Name));
    return Py_BuildValue("l", Name);
}

static int EKU_setName(EKU *self, PyObject *value)
{
    long lName = 0;
    if (!PyArg_Parse(value, "l", &lName))
    {
        return -1;
    }
    CAPICOM_EKU Name = (CAPICOM_EKU)lName;
    HR_SETTER_ERRORCHECK_RETURN(self->m_pCppCadesImpl->put_Name(Name));
    return 0;
}

static PyObject *EKU_getOID(EKU *self)
{
    CAtlStringA OID;
    HR_METHOD_ERRORCHECK_RETURN(self->m_pCppCadesImpl->get_OID(OID));
    return Py_BuildValue("s", OID.GetString());
}

static int EKU_setOID(EKU *self, PyObject *args)
{
    char *szOID = "";
    if (!PyArg_Parse(args, "s", &szOID))
    {
        return -1;
    }
    CAtlStringA sOID = CAtlString(szOID);
    HR_SETTER_ERRORCHECK_RETURN(self->m_pCppCadesImpl->put_OID(sOID));
    return 0;
}

static PyGetSetDef EKU_getset[] = {
    {"Name", (getter)EKU_getName, (setter)EKU_setName, "Name", NULL},
    {"OID", (getter)EKU_getOID, (setter)EKU_setOID, "OID", NULL},
    {NULL} /* Sentinel */
};

static PyMethodDef EKU_methods[] = {
    {NULL} /* Sentinel */
};

PyTypeObject EKUType = {
    PyVarObject_HEAD_INIT(NULL, 0) "pycades.EKU", /* tp_name */
    sizeof(EKU),                                  /* tp_basicsize */
    0,                                            /* tp_itemsize */
    (destructor)EKU_dealloc,                      /* tp_dealloc */
    0,                                            /* tp_print */
    0,                                            /* tp_getattr */
    0,                                            /* tp_setattr */
    0,                                            /* tp_compare */
    0,                                            /* tp_repr */
    0,                                            /* tp_as_number */
    0,                                            /* tp_as_sequence */
    0,                                            /* tp_as_mapping */
    0,                                            /* tp_hash */
    0,                                            /* tp_call */
    0,                                            /* tp_str */
    0,                                            /* tp_getattro */
    0,                                            /* tp_setattro */
    0,                                            /* tp_as_buffer */
    Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,     /* tp_flags */
    "EKU object",                                 /* tp_doc */
    0,                                            /* tp_traverse */
    0,                                            /* tp_clear */
    0,                                            /* tp_richcompare */
    0,                                            /* tp_weaklistoffset */
    0,                                            /* tp_iter */
    0,                                            /* tp_iternext */
    EKU_methods,                                  /* tp_methods */
    0,                                            /* tp_members */
    EKU_getset,                                   /* tp_getset */
    0,                                            /* tp_base */
    0,                                            /* tp_dict */
    0,                                            /* tp_descr_get */
    0,                                            /* tp_descr_set */
    0,                                            /* tp_dictoffset */
    0,                                            /* tp_init */
    0,                                            /* tp_alloc */
    EKU_new,                                      /* tp_new */
};
