#include "PyCadesCRL.h"

using namespace CryptoPro::PKI::CAdES;

static void CRL_dealloc(CRL *self)
{
    Py_TYPE(self)->tp_free((PyObject *)self);
}

static PyObject *CRL_new(PyTypeObject *type, PyObject *args, PyObject *kwds)
{
    CRL *self;
    self = (CRL *)type->tp_alloc(type, 0);
    if (self != NULL)
    {
        self->m_pCppCadesImpl = boost::shared_ptr<CPPCadesCPCRLObject>(new CPPCadesCPCRLObject());
    }
    return (PyObject *)self;
}

static PyObject *CRL_Import(CRL *self, PyObject *args)
{
    char *szCRL = "";
    if (!PyArg_ParseTuple(args, "s", &szCRL))
    {
        return NULL;
    }
    CryptoPro::CBlob blobCRL;
    blobCRL.assign((unsigned char *)szCRL, strlen((const char *)szCRL));
    HR_METHOD_ERRORCHECK_RETURN(self->m_pCppCadesImpl->Import(blobCRL));
    Py_RETURN_NONE;
}

static PyObject *CRL_Export(CRL *self, PyObject *args)
{
    long lType = 0;
    if (!PyArg_ParseTuple(args, "l", &lType))
    {
        return NULL;
    }
    CAPICOM_ENCODING_TYPE Type = (CAPICOM_ENCODING_TYPE)lType;
    CryptoPro::CBlob blobCRL;
    HR_METHOD_ERRORCHECK_RETURN(self->m_pCppCadesImpl->Export(Type, blobCRL));
    return Py_BuildValue("s", blobCRL.pbData());
}

static PyObject *CRL_getAuthKeyID(CRL *self)
{
    CAtlString sKeyID;
    HR_METHOD_ERRORCHECK_RETURN(self->m_pCppCadesImpl->get_AuthKeyID(sKeyID));
    return Py_BuildValue("s", sKeyID.GetString());
}

static PyObject *CRL_getIssuerName(CRL *self)
{
    CAtlString sIssuerName;
    HR_METHOD_ERRORCHECK_RETURN(self->m_pCppCadesImpl->get_IssuerName(sIssuerName));
    return Py_BuildValue("s", sIssuerName.GetString());
}

static PyObject *CRL_getNextUpdate(CRL *self)
{
    CryptoPro::CDateTime nextUpdate;
    CryptoPro::CStringProxy strProxyNextUpdate;
    HR_METHOD_ERRORCHECK_RETURN(self->m_pCppCadesImpl->get_NextUpdate(nextUpdate));
    strProxyNextUpdate = nextUpdate.tostring();
    return Py_BuildValue("s", strProxyNextUpdate.c_str());
}

static PyObject *CRL_getThisUpdate(CRL *self)
{
    CryptoPro::CDateTime thisUpdate;
    CryptoPro::CStringProxy strProxyThisUpdate;
    HR_METHOD_ERRORCHECK_RETURN(self->m_pCppCadesImpl->get_ThisUpdate(thisUpdate));
    strProxyThisUpdate = thisUpdate.tostring();
    return Py_BuildValue("s", strProxyThisUpdate.c_str());
}

static PyObject *CRL_getThumbprint(CRL *self)
{
    CAtlString sThumbprint;
    HR_METHOD_ERRORCHECK_RETURN(self->m_pCppCadesImpl->get_Thumbprint(sThumbprint));
    return Py_BuildValue("s", sThumbprint.GetString());
}

static PyGetSetDef CRL_getset[] = {
    {"AuthKeyID", (getter)CRL_getAuthKeyID, NULL, "AuthKeyID", NULL},
    {"IssuerName", (getter)CRL_getIssuerName, NULL, "IssuerName", NULL},
    {"NextUpdate", (getter)CRL_getNextUpdate, NULL, "NextUpdate", NULL},
    {"ThisUpdate", (getter)CRL_getThisUpdate, NULL, "ThisUpdate", NULL},
    {"Thumbprint", (getter)CRL_getThumbprint, NULL, "Thumbprint", NULL},
    {NULL} /* Sentinel */
};

static PyMethodDef CRL_methods[] = {
    {"Import", (PyCFunction)CRL_Import, METH_VARARGS, "Import"},
    {"Export", (PyCFunction)CRL_Export, METH_VARARGS, "Export"},
    {NULL} /* Sentinel */
};

PyTypeObject CRLType = {
    PyVarObject_HEAD_INIT(NULL, 0) "pycades.CRL", /* tp_name */
    sizeof(CRL),                                  /* tp_basicsize */
    0,                                            /* tp_itemsize */
    (destructor)CRL_dealloc,                      /* tp_dealloc */
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
    "CRL object",                                 /* tp_doc */
    0,                                            /* tp_traverse */
    0,                                            /* tp_clear */
    0,                                            /* tp_richcompare */
    0,                                            /* tp_weaklistoffset */
    0,                                            /* tp_iter */
    0,                                            /* tp_iternext */
    CRL_methods,                                  /* tp_methods */
    0,                                            /* tp_members */
    CRL_getset,                                   /* tp_getset */
    0,                                            /* tp_base */
    0,                                            /* tp_dict */
    0,                                            /* tp_descr_get */
    0,                                            /* tp_descr_set */
    0,                                            /* tp_dictoffset */
    0,                                            /* tp_init */
    0,                                            /* tp_alloc */
    CRL_new,                                      /* tp_new */
};
