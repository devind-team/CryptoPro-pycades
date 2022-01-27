#include "PyCadesExtendedKeyUsage.h"
#include "PyCadesEKUs.h"

using namespace CryptoPro::PKI::CAdES;

static void ExtendedKeyUsage_dealloc(ExtendedKeyUsage *self)
{
    Py_TYPE(self)->tp_free((PyObject *)self);
}

static PyObject *ExtendedKeyUsage_new(PyTypeObject *type, PyObject *args, PyObject *kwds)
{
    ExtendedKeyUsage *self;
    self = (ExtendedKeyUsage *)type->tp_alloc(type, 0);
    if (self != NULL)
    {
        self->m_pCppCadesImpl = boost::shared_ptr<CPPCadesCPExtendedKeyUsageObject>(new CPPCadesCPExtendedKeyUsageObject());
    }
    return (PyObject *)self;
}

static PyObject *ExtendedKeyUsage_getIsPresent(ExtendedKeyUsage *self)
{
    BOOL bIsPresent;
    HR_METHOD_ERRORCHECK_RETURN(self->m_pCppCadesImpl->get_IsPresent(&bIsPresent));
    return bIsPresent ? Py_True : Py_False;
}

static PyObject *ExtendedKeyUsage_getIsCritical(ExtendedKeyUsage *self)
{
    BOOL bIsCritical;
    HR_METHOD_ERRORCHECK_RETURN(self->m_pCppCadesImpl->get_IsCritical(&bIsCritical));
    return bIsCritical ? Py_True : Py_False;
}

static PyObject *ExtendedKeyUsage_getEKUs(ExtendedKeyUsage *self)
{
    boost::shared_ptr<CPPCadesCPEKUsObject> pCppCadesEKUs(new CPPCadesCPEKUsObject());
    HR_METHOD_ERRORCHECK_RETURN(self->m_pCppCadesImpl->get_EKUs(pCppCadesEKUs));
    PyObject *pPyEKUs = PyObject_CallObject((PyObject *)&EKUsType, NULL);
    EKUs *pEKUs = (EKUs *)pPyEKUs;
    pEKUs->m_pCppCadesImpl = pCppCadesEKUs;
    return Py_BuildValue("O", pEKUs);
}

static PyGetSetDef ExtendedKeyUsage_getset[] = {
    {"IsPresent", (getter)ExtendedKeyUsage_getIsPresent, NULL, "IsPresent", NULL},
    {"IsCritical", (getter)ExtendedKeyUsage_getIsCritical, NULL, "IsCritical", NULL},
    {"EKUs", (getter)ExtendedKeyUsage_getEKUs, NULL, "EKUs", NULL},
    {NULL} /* Sentinel */
};

static PyMethodDef ExtendedKeyUsage_methods[] = {
    {NULL} /* Sentinel */
};

PyTypeObject ExtendedKeyUsageType = {
    PyVarObject_HEAD_INIT(NULL, 0) "pycades.ExtendedKeyUsage", /* tp_name */
    sizeof(ExtendedKeyUsage),                                  /* tp_basicsize */
    0,                                                         /* tp_itemsize */
    (destructor)ExtendedKeyUsage_dealloc,                      /* tp_dealloc */
    0,                                                         /* tp_print */
    0,                                                         /* tp_getattr */
    0,                                                         /* tp_setattr */
    0,                                                         /* tp_compare */
    0,                                                         /* tp_repr */
    0,                                                         /* tp_as_number */
    0,                                                         /* tp_as_sequence */
    0,                                                         /* tp_as_mapping */
    0,                                                         /* tp_hash */
    0,                                                         /* tp_call */
    0,                                                         /* tp_str */
    0,                                                         /* tp_getattro */
    0,                                                         /* tp_setattro */
    0,                                                         /* tp_as_buffer */
    Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,                  /* tp_flags */
    "ExtendedKeyUsage object",                                 /* tp_doc */
    0,                                                         /* tp_traverse */
    0,                                                         /* tp_clear */
    0,                                                         /* tp_richcompare */
    0,                                                         /* tp_weaklistoffset */
    0,                                                         /* tp_iter */
    0,                                                         /* tp_iternext */
    ExtendedKeyUsage_methods,                                  /* tp_methods */
    0,                                                         /* tp_members */
    ExtendedKeyUsage_getset,                                   /* tp_getset */
    0,                                                         /* tp_base */
    0,                                                         /* tp_dict */
    0,                                                         /* tp_descr_get */
    0,                                                         /* tp_descr_set */
    0,                                                         /* tp_dictoffset */
    0,                                                         /* tp_init */
    0,                                                         /* tp_alloc */
    ExtendedKeyUsage_new,                                      /* tp_new */
};
