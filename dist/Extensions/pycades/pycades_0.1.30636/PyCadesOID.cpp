#include "PyCadesOID.h"

using namespace CryptoPro::PKI::CAdES;

static void OID_dealloc(OID *self)
{
    Py_TYPE(self)->tp_free((PyObject *)self);
}

static PyObject *OID_new(PyTypeObject *type, PyObject *args, PyObject *kwds)
{
    OID *self;
    self = (OID *)type->tp_alloc(type, 0);
    if (self != NULL)
    {
        self->m_pCppCadesImpl = boost::shared_ptr<CPPCadesCPOIDObject>(new CPPCadesCPOIDObject());
    }
    return (PyObject *)self;
}

static PyObject *OID_getValue(OID *self)
{
    boost::shared_ptr<CAtlStringA> pValue;
    HR_METHOD_ERRORCHECK_RETURN(self->m_pCppCadesImpl->get_Value(pValue));
    return Py_BuildValue("s", (*pValue).GetString());
}

static int OID_setValue(OID *self, PyObject *value)
{
    char *szValue = "";
    if (!PyArg_Parse(value, "s", &szValue))
    {
        return -1;
    }
    HR_SETTER_ERRORCHECK_RETURN(self->m_pCppCadesImpl->put_Value(CAtlStringA(szValue)));
    return 0;
}

static PyObject *OID_getName(OID *self)
{
    CAPICOM_OID Name;
    HR_METHOD_ERRORCHECK_RETURN(self->m_pCppCadesImpl->get_Name(&Name));
    return Py_BuildValue("l", Name);
}

static int OID_setName(OID *self, PyObject *value)
{
    long lName = 0;
    if (!PyArg_Parse(value, "l", &lName))
    {
        return -1;
    }
    CAPICOM_OID Name = (CAPICOM_OID)lName;
    HR_SETTER_ERRORCHECK_RETURN(self->m_pCppCadesImpl->put_Name(Name));
    return 0;
}

static PyObject *OID_getFriendlyName(OID *self)
{
    CAtlString sFriendlyName;
    HR_METHOD_ERRORCHECK_RETURN(self->m_pCppCadesImpl->get_FriendlyName(sFriendlyName));
    return Py_BuildValue("s", sFriendlyName.GetString());
}

static int OID_setFriendlyName(OID *self, PyObject *value)
{
    char *szFriendlyName = "";
    if (!PyArg_Parse(value, "s", &szFriendlyName))
    {
        return -1;
    }
    HR_SETTER_ERRORCHECK_RETURN(self->m_pCppCadesImpl->put_FriendlyName(CAtlString(szFriendlyName)));
    return 0;
}

static PyGetSetDef OID_getset[] = {
    {"FriendlyName", (getter)OID_getFriendlyName, (setter)OID_setFriendlyName, "FriendlyName", NULL},
    {"Name", (getter)OID_getName, (setter)OID_setName, "Name", NULL},
    {"Value", (getter)OID_getValue, (setter)OID_setValue, "Value", NULL},
    {NULL} /* Sentinel */
};

static PyMethodDef OID_methods[] = {
    {NULL} /* Sentinel */
};

PyTypeObject OIDType = {
    PyVarObject_HEAD_INIT(NULL, 0) "pycades.OID", /* tp_name */
    sizeof(OID),                                  /* tp_basicsize */
    0,                                            /* tp_itemsize */
    (destructor)OID_dealloc,                      /* tp_dealloc */
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
    "OID object",                                 /* tp_doc */
    0,                                            /* tp_traverse */
    0,                                            /* tp_clear */
    0,                                            /* tp_richcompare */
    0,                                            /* tp_weaklistoffset */
    0,                                            /* tp_iter */
    0,                                            /* tp_iternext */
    OID_methods,                                  /* tp_methods */
    0,                                            /* tp_members */
    OID_getset,                                   /* tp_getset */
    0,                                            /* tp_base */
    0,                                            /* tp_dict */
    0,                                            /* tp_descr_get */
    0,                                            /* tp_descr_set */
    0,                                            /* tp_dictoffset */
    0,                                            /* tp_init */
    0,                                            /* tp_alloc */
    OID_new,                                      /* tp_new */
};
