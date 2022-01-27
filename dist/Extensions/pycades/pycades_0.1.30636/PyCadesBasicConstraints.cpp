#include "PyCadesBasicConstraints.h"

using namespace CryptoPro::PKI::CAdES;

static void BasicConstraints_dealloc(BasicConstraints *self)
{
    Py_TYPE(self)->tp_free((PyObject *)self);
}

static PyObject *BasicConstraints_new(PyTypeObject *type, PyObject *args, PyObject *kwds)
{
    BasicConstraints *self;
    self = (BasicConstraints *)type->tp_alloc(type, 0);
    if (self != NULL)
    {
        self->m_pCppCadesImpl = boost::shared_ptr<CPPCadesCPBasicConstraintsObject>(new CPPCadesCPBasicConstraintsObject());
    }
    return (PyObject *)self;
}

static PyObject *BasicConstraints_getIsPresent(BasicConstraints *self)
{
    BOOL bIsPresent = 0;
    HR_METHOD_ERRORCHECK_RETURN(self->m_pCppCadesImpl->get_IsPresent(&bIsPresent));
    return bIsPresent ? Py_True : Py_False;
}

static PyObject *BasicConstraints_getIsCritical(BasicConstraints *self)
{
    BOOL bIsCritical = 0;
    HR_METHOD_ERRORCHECK_RETURN(self->m_pCppCadesImpl->get_IsCritical(&bIsCritical));
    return bIsCritical ? Py_True : Py_False;
}

static PyObject *BasicConstraints_getIsCertificateAuthority(BasicConstraints *self)
{
    BOOL bIsCA = 0;
    HR_METHOD_ERRORCHECK_RETURN(self->m_pCppCadesImpl->get_IsCertificateAuthority(&bIsCA));
    return bIsCA ? Py_True : Py_False;
}

static PyObject *BasicConstraints_getIsPathLenConstraintPresent(BasicConstraints *self)
{
    BOOL bIsPathLenConstr = 0;
    HR_METHOD_ERRORCHECK_RETURN(self->m_pCppCadesImpl->get_IsPathLenConstraintPresent(&bIsPathLenConstr));
    return bIsPathLenConstr ? Py_True : Py_False;
}

static PyObject *BasicConstraints_getPathLenConstraint(BasicConstraints *self)
{
    DWORD dwPathLenConst;
    HR_METHOD_ERRORCHECK_RETURN(self->m_pCppCadesImpl->get_PathLenConstraint(&dwPathLenConst));
    return Py_BuildValue("l", dwPathLenConst);
}

static PyGetSetDef BasicConstraints_getset[] = {
    {"IsPresent", (getter)BasicConstraints_getIsPresent, NULL, "IsPresent", NULL},
    {"IsCritical", (getter)BasicConstraints_getIsCritical, NULL, "IsCritical", NULL},
    {"IsCertificateAuthority", (getter)BasicConstraints_getIsCertificateAuthority, NULL, "IsCertificateAuthority", NULL},
    {"IsPathLenConstraintPresent", (getter)BasicConstraints_getIsPathLenConstraintPresent, NULL, "IsPathLenConstraintPresent", NULL},
    {"PathLenConstraint", (getter)BasicConstraints_getPathLenConstraint, NULL, "PathLenConstraint", NULL},
    {NULL} /* Sentinel */
};

static PyMethodDef BasicConstraints_methods[] = {
    {NULL} /* Sentinel */
};

PyTypeObject BasicConstraintsType = {
    PyVarObject_HEAD_INIT(NULL, 0) "pycades.BasicConstraints", /* tp_name */
    sizeof(BasicConstraints),                                  /* tp_basicsize */
    0,                                                         /* tp_itemsize */
    (destructor)BasicConstraints_dealloc,                      /* tp_dealloc */
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
    "BasicConstraints object",                                 /* tp_doc */
    0,                                                         /* tp_traverse */
    0,                                                         /* tp_clear */
    0,                                                         /* tp_richcompare */
    0,                                                         /* tp_weaklistoffset */
    0,                                                         /* tp_iter */
    0,                                                         /* tp_iternext */
    BasicConstraints_methods,                                  /* tp_methods */
    0,                                                         /* tp_members */
    BasicConstraints_getset,                                   /* tp_getset */
    0,                                                         /* tp_base */
    0,                                                         /* tp_dict */
    0,                                                         /* tp_descr_get */
    0,                                                         /* tp_descr_set */
    0,                                                         /* tp_dictoffset */
    0,                                                         /* tp_init */
    0,                                                         /* tp_alloc */
    BasicConstraints_new,                                      /* tp_new */
};
