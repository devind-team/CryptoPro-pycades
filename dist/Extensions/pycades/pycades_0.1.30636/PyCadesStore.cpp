#include "PyCadesStore.h"
#include "PyCadesCertificates.h"
#include "PyCadesCertificate.h"
#include "PyCadesCRL.h"

using namespace CryptoPro::PKI::CAdES;

static void Store_dealloc(Store *self)
{
    Py_TYPE(self)->tp_free((PyObject *)self);
}

static PyObject *Store_new(PyTypeObject *type, PyObject *args, PyObject *kwds)
{
    Store *self;
    self = (Store *)type->tp_alloc(type, 0);
    if (self != NULL)
    {
        self->m_pCppCadesImpl = boost::shared_ptr<CPPCadesCPStoreObject>(new CPPCadesCPStoreObject());
    }
    return (PyObject *)self;
}

static PyObject *Store_Add(Store *self, PyObject *args)
{
    PyObject *pPyCert = NULL;
    if (!PyArg_ParseTuple(args, "O!", &CertificateType, &pPyCert))
    {
        return NULL;
    }

    Certificate *pCert = (Certificate *)pPyCert;
    HR_METHOD_ERRORCHECK_RETURN(self->m_pCppCadesImpl->Add(pCert->m_pCppCadesImpl));
    Py_RETURN_NONE;
}

static PyObject *Store_AddCRL(Store *self, PyObject *args)
{
    PyObject *pPyCRL = NULL;
    if (!PyArg_ParseTuple(args, "O!", &CRLType, &pPyCRL))
    {
        return NULL;
    }

    CRL *pCRL = (CRL *)pPyCRL;
    HR_METHOD_ERRORCHECK_RETURN(self->m_pCppCadesImpl->AddCRL(pCRL->m_pCppCadesImpl));
    Py_RETURN_NONE;
}

static PyObject *Store_getName(Store *self)
{
    CAtlString sName;
    HR_METHOD_ERRORCHECK_RETURN(self->m_pCppCadesImpl->get_Name(sName));
    return Py_BuildValue("s", sName.GetString());
}

static PyObject *Store_getCertificates(Store *self)
{
    PyObject *pPyCertificates = PyObject_CallObject((PyObject *)&CertificatesType, NULL);
    Certificates *pCertificates = (Certificates *)pPyCertificates;
    HR_METHOD_ERRORCHECK_RETURN(self->m_pCppCadesImpl->get_Certificates(pCertificates->m_pCppCadesImpl));
    return Py_BuildValue("O", pCertificates);
}

static PyObject *Store_getLocation(Store *self)
{
    CADESCOM_STORE_LOCATION Location;
    HR_METHOD_ERRORCHECK_RETURN(self->m_pCppCadesImpl->get_Location(&Location));
    return Py_BuildValue("l", Location);
}

static PyObject *Store_Open(Store *self, PyObject *args)
{
    char *szName = "My";
    long lLocation = CADESCOM_CURRENT_USER_STORE;
    long lMode = CAPICOM_STORE_OPEN_READ_ONLY;
    if (!PyArg_ParseTuple(args, "|lsl", &lLocation, &szName, &lMode))
    {
        return NULL;
    }

    CADESCOM_STORE_LOCATION Location = (CADESCOM_STORE_LOCATION)lLocation;
    CAPICOM_STORE_OPEN_MODE Mode = (CAPICOM_STORE_OPEN_MODE)lMode;
    CAtlStringW sName = CAtlStringW(szName);
    HR_METHOD_ERRORCHECK_RETURN(self->m_pCppCadesImpl->Open(Location, sName.GetString(), Mode));
    Py_RETURN_NONE;
}

static PyObject *Store_Close(Store *self)
{
    HR_METHOD_ERRORCHECK_RETURN(self->m_pCppCadesImpl->Close());
    Py_RETURN_NONE;
}

static PyGetSetDef Store_getset[] = {
    {"Name", (getter)Store_getName, NULL, "Name", NULL},
    {"Certificates", (getter)Store_getCertificates, NULL, "Certificates", NULL},
    {"Location", (getter)Store_getLocation, NULL, "Location", NULL},
    {NULL} /* Sentinel */
};

static PyMethodDef Store_methods[] = {
    {"Open", (PyCFunction)Store_Open, METH_VARARGS, "Open"},
    {"Close", (PyCFunction)Store_Close, METH_NOARGS, "Close"},
    {"Add", (PyCFunction)Store_Add, METH_VARARGS, "Add"},
    {"AddCRL", (PyCFunction)Store_AddCRL, METH_VARARGS, "AddCRL"},
    {NULL} /* Sentinel */
};

PyTypeObject StoreType = {
    PyVarObject_HEAD_INIT(NULL, 0) "pycades.Store", /* tp_name */
    sizeof(Store),                                  /* tp_basicsize */
    0,                                              /* tp_itemsize */
    (destructor)Store_dealloc,                      /* tp_dealloc */
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
    "Store object",                                 /* tp_doc */
    0,                                              /* tp_traverse */
    0,                                              /* tp_clear */
    0,                                              /* tp_richcompare */
    0,                                              /* tp_weaklistoffset */
    0,                                              /* tp_iter */
    0,                                              /* tp_iternext */
    Store_methods,                                  /* tp_methods */
    0,                                              /* tp_members */
    Store_getset,                                   /* tp_getset */
    0,                                              /* tp_base */
    0,                                              /* tp_dict */
    0,                                              /* tp_descr_get */
    0,                                              /* tp_descr_set */
    0,                                              /* tp_dictoffset */
    0,                                              /* tp_init */
    0,                                              /* tp_alloc */
    Store_new,                                      /* tp_new */
};
