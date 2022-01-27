#include "PyCadesCertificate.h"
#include "PyCadesCertificateStatus.h"
#include "PyCadesPrivateKey.h"
#include "PyCadesPublicKey.h"
#include "PyCadesBasicConstraints.h"
#include "PyCadesKeyUsage.h"
#include "PyCadesExtendedKeyUsage.h"
#include "PyCadesStore.h"

using namespace CryptoPro::PKI::CAdES;

static void Certificate_dealloc(Certificate *self)
{
    Py_TYPE(self)->tp_free((PyObject *)self);
}

static PyObject *Certificate_new(PyTypeObject *type, PyObject *args, PyObject *kwds)
{
    Certificate *self;
    self = (Certificate *)type->tp_alloc(type, 0);
    if (self != NULL)
    {
        self->m_pCppCadesImpl = boost::shared_ptr<CPPCadesCPCertificateObject>(new CPPCadesCPCertificateObject());
    }
    return (PyObject *)self;
}

static PyObject *Certificate_getInfo(Certificate *self, PyObject *args)
{
    long lType = 0;
    if (!PyArg_ParseTuple(args, "l", &lType))
    {
        return NULL;
    }
    CAPICOM_CERT_INFO_TYPE Type = (CAPICOM_CERT_INFO_TYPE)lType;
    CAtlString sInfo;
    HR_METHOD_ERRORCHECK_RETURN(self->m_pCppCadesImpl->GetInfo(Type, sInfo));
    return Py_BuildValue("s", sInfo.GetString());
}

static PyObject *Certificate_findPrivateKey(Certificate *self, PyObject *args)
{
    PyObject *pPyCriteria = NULL;
    if (!PyArg_ParseTuple(args, "|O", &pPyCriteria))
    {
        return NULL;
    }
    HR_METHOD_ERRORCHECK_RETURN(self->m_pCppCadesImpl->FindPrivateKey(CAtlString()));
    Py_RETURN_NONE;
}

static PyObject *Certificate_hasPrivateKey(Certificate *self)
{
    BOOL has = 0;
    HR_METHOD_ERRORCHECK_RETURN(self->m_pCppCadesImpl->HasPrivateKey(&has));
    return has ? Py_True : Py_False;
}

static PyObject *Certificate_isValid(Certificate *self)
{
    boost::shared_ptr<CPPCadesCPCertificateStatusObject> pCppCadesStatus(new CPPCadesCPCertificateStatusObject());
    HR_METHOD_ERRORCHECK_RETURN(self->m_pCppCadesImpl->IsValid(pCppCadesStatus));
    PyObject *pPyStatus = PyObject_CallObject((PyObject *)&CertificateStatusType, NULL);
    CertificateStatus *pStatus = (CertificateStatus *)pPyStatus;
    pStatus->m_pCppCadesImpl = pCppCadesStatus;
    return Py_BuildValue("O", pStatus);
}

static PyObject *Certificate_KeyUsage(Certificate *self)
{
    PyObject *pPyKeyUsage = PyObject_CallObject((PyObject *)&KeyUsageType, NULL);
    KeyUsage *pKeyUsage = (KeyUsage *)pPyKeyUsage;
    HR_METHOD_ERRORCHECK_RETURN(self->m_pCppCadesImpl->KeyUsage(pKeyUsage->m_pCppCadesImpl));
    return Py_BuildValue("O", pKeyUsage);
}

static PyObject *Certificate_ExtendedKeyUsage(Certificate *self)
{
    PyObject *pPyExtendedKeyUsage = PyObject_CallObject((PyObject *)&ExtendedKeyUsageType, NULL);
    ExtendedKeyUsage *pExtendedKeyUsage = (ExtendedKeyUsage *)pPyExtendedKeyUsage;
    HR_METHOD_ERRORCHECK_RETURN(self->m_pCppCadesImpl->ExtendedKeyUsage(pExtendedKeyUsage->m_pCppCadesImpl));
    return Py_BuildValue("O", pExtendedKeyUsage);
}

static PyObject *Certificate_Export(Certificate *self, PyObject *args)
{
    long lType = 0;
    if (!PyArg_ParseTuple(args, "l", &lType))
    {
        return NULL;
    }
    CryptoPro::CBlob value;
    CAPICOM_ENCODING_TYPE Type = (CAPICOM_ENCODING_TYPE)lType;
    HR_METHOD_ERRORCHECK_RETURN(self->m_pCppCadesImpl->Export(Type, value));
    return Type == CAPICOM_ENCODE_BINARY ? 
        PyBytes_FromStringAndSize((const char *)value.pbData(), value.cbData()) : 
        Py_BuildValue("s", value.pbData());
}

static PyObject *Certificate_Import(Certificate *self, PyObject *args)
{
    PyObject *pArg = NULL;
    if (!PyArg_ParseTuple(args, "O", &pArg))
    {
        return NULL;
    }

    char *pCertificateBuf = "";
    int CertificateLength = 0;
    if (PyObject_TypeCheck(pArg, &PyBytes_Type))
    {
        pCertificateBuf = PyBytes_AS_STRING(pArg);
        CertificateLength = PyBytes_Size(pArg);
    }
    else if (PyObject_TypeCheck(pArg, &PyUnicode_Type))
    {
        if (!PyArg_Parse(pArg, "s", &pCertificateBuf))
            return NULL;
        CertificateLength = PyUnicode_GET_LENGTH(pArg);
    }
    else
    {
        PyErr_BadArgument();
        return NULL;
    }

    CryptoPro::CBlob value;
    value.assign((unsigned char *)pCertificateBuf, CertificateLength);
    HR_METHOD_ERRORCHECK_RETURN(self->m_pCppCadesImpl->Import(value));
    Py_RETURN_NONE;
}

static PyObject *Certificate_getSerialNumber(Certificate *self)
{
    CAtlString sSerialNumber;
    HR_METHOD_ERRORCHECK_RETURN(self->m_pCppCadesImpl->get_SerialNumber(sSerialNumber));
    return Py_BuildValue("s", sSerialNumber.GetString());
}

static PyObject *Certificate_getThumbprint(Certificate *self)
{
    CAtlString sThumbprint;
    HR_METHOD_ERRORCHECK_RETURN(self->m_pCppCadesImpl->get_Thumbprint(sThumbprint));
    return Py_BuildValue("s", sThumbprint.GetString());
}

static PyObject *Certificate_getSubjectName(Certificate *self)
{
    CAtlString sSubjectName;
    HR_METHOD_ERRORCHECK_RETURN(self->m_pCppCadesImpl->get_SubjectName(sSubjectName));
    return Py_BuildValue("s", sSubjectName.GetString());
}

static PyObject *Certificate_getIssuerName(Certificate *self)
{
    CAtlString sIssuerName;
    HR_METHOD_ERRORCHECK_RETURN(self->m_pCppCadesImpl->get_IssuerName(sIssuerName));
    return Py_BuildValue("s", sIssuerName.GetString());
}

static PyObject *Certificate_getVersion(Certificate *self)
{
    DWORD dwVersion;
    HR_METHOD_ERRORCHECK_RETURN(self->m_pCppCadesImpl->get_Version(&dwVersion));
    return Py_BuildValue("l", dwVersion);
}

static PyObject *Certificate_getValidFromDate(Certificate *self)
{
    CryptoPro::CDateTime date;
    CryptoPro::CStringProxy strProxyDate;
    HR_METHOD_ERRORCHECK_RETURN(self->m_pCppCadesImpl->get_ValidFromDate(date));
    strProxyDate = date.tostring();
    return Py_BuildValue("s", strProxyDate.c_str());
}

static PyObject *Certificate_getValidToDate(Certificate *self)
{
    CryptoPro::CDateTime date;
    CryptoPro::CStringProxy strProxyDate;
    HR_METHOD_ERRORCHECK_RETURN(self->m_pCppCadesImpl->get_ValidToDate(date));
    strProxyDate = date.tostring();
    return Py_BuildValue("s", strProxyDate.c_str());
}

static PyObject *Certificate_PrivateKey(Certificate *self)
{
    PyObject *pPyPrivateKey = PyObject_CallObject((PyObject *)&PrivateKeyType, NULL);
    PrivateKey *pPrivateKey = (PrivateKey *)pPyPrivateKey;
    HR_METHOD_ERRORCHECK_RETURN(self->m_pCppCadesImpl->PrivateKey(pPrivateKey->m_pCppCadesImpl));
    return Py_BuildValue("O", pPrivateKey);
}

static PyObject *Certificate_PublicKey(Certificate *self)
{
    PyObject *pPyPublicKey = PyObject_CallObject((PyObject *)&PublicKeyType, NULL);
    PublicKey *pPublicKey = (PublicKey *)pPyPublicKey;
    HR_METHOD_ERRORCHECK_RETURN(self->m_pCppCadesImpl->PublicKey(pPublicKey->m_pCppCadesImpl));
    return Py_BuildValue("O", pPublicKey);
}

static PyObject *Certificate_AdditionalStore(Certificate *self, PyObject *args)
{
    PyObject *pPyStore = NULL;
    if (!PyArg_ParseTuple(args, "O!", &StoreType, &pPyStore))
    {
        return NULL;
    }
    Store *pStore = (Store *)pPyStore;
    HR_METHOD_ERRORCHECK_RETURN(self->m_pCppCadesImpl->AdditionalStore(pStore->m_pCppCadesImpl));
    Py_RETURN_NONE;
}

static PyObject *Certificate_BasicConstraints(Certificate *self)
{
    PyObject *pPyBasicConstraints = PyObject_CallObject((PyObject *)&BasicConstraintsType, NULL);
    BasicConstraints *pBasicConstraints = (BasicConstraints *)pPyBasicConstraints;
    HR_METHOD_ERRORCHECK_RETURN(self->m_pCppCadesImpl->BasicConstraints(pBasicConstraints->m_pCppCadesImpl));
    return Py_BuildValue("O", pBasicConstraints);
}

static PyGetSetDef Certificate_getset[]{
    {"SubjectName", (getter)Certificate_getSubjectName, NULL, "SubjectName", NULL},
    {"IssuerName", (getter)Certificate_getIssuerName, NULL, "IssuerName", NULL},
    {"PrivateKey", (getter)Certificate_PrivateKey, NULL, "PrivateKey", NULL},
    {"SerialNumber", (getter)Certificate_getSerialNumber, NULL, "SerialNumber", NULL},
    {"Thumbprint", (getter)Certificate_getThumbprint, NULL, "Thumbprint", NULL},
    {"Version", (getter)Certificate_getVersion, NULL, "Version", NULL},
    {"ValidFromDate", (getter)Certificate_getValidFromDate, NULL, "ValidFromDate", NULL},
    {"ValidToDate", (getter)Certificate_getValidToDate, NULL, "ValidToDate", NULL},
    {NULL}};

static PyMethodDef Certificate_methods[] = {
    {"GetInfo", (PyCFunction)Certificate_getInfo, METH_VARARGS, "getInfo"},
    {"FindPrivateKey", (PyCFunction)Certificate_findPrivateKey, METH_VARARGS, "findPrivateKey"},
    {"HasPrivateKey", (PyCFunction)Certificate_hasPrivateKey, METH_NOARGS, "hasPrivateKey"},
    {"IsValid", (PyCFunction)Certificate_isValid, METH_NOARGS, "isValid"},
    {"ExtendedKeyUsage", (PyCFunction)Certificate_ExtendedKeyUsage, METH_NOARGS, "ExtendedKeyUsage"},
    {"KeyUsage", (PyCFunction)Certificate_KeyUsage, METH_NOARGS, "KeyUsage"},
    {"Export", (PyCFunction)Certificate_Export, METH_VARARGS, "Export"},
    {"Import", (PyCFunction)Certificate_Import, METH_VARARGS, "Import"},
    {"PublicKey", (PyCFunction)Certificate_PublicKey, METH_NOARGS, "PublicKey"},
    {"BasicConstraints", (PyCFunction)Certificate_BasicConstraints, METH_NOARGS, "BasicConstraints"},
    {"AdditionalStore", (PyCFunction)Certificate_AdditionalStore, METH_VARARGS, "AdditionalStore"},
    {NULL} /* Sentinel */
};

PyTypeObject CertificateType = {
    PyVarObject_HEAD_INIT(NULL, 0) "pycades.Certificate", /* tp_name */
    sizeof(Certificate),                                  /* tp_basicsize */
    0,                                                    /* tp_itemsize */
    (destructor)Certificate_dealloc,                      /* tp_dealloc */
    0,                                                    /* tp_print */
    0,                                                    /* tp_getattr */
    0,                                                    /* tp_setattr */
    0,                                                    /* tp_compare */
    0,                                                    /* tp_repr */
    0,                                                    /* tp_as_number */
    0,                                                    /* tp_as_sequence */
    0,                                                    /* tp_as_mapping */
    0,                                                    /* tp_hash */
    0,                                                    /* tp_call */
    0,                                                    /* tp_str */
    0,                                                    /* tp_getattro */
    0,                                                    /* tp_setattro */
    0,                                                    /* tp_as_buffer */
    Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,             /* tp_flags */
    "Certificate object",                                 /* tp_doc */
    0,                                                    /* tp_traverse */
    0,                                                    /* tp_clear */
    0,                                                    /* tp_richcompare */
    0,                                                    /* tp_weaklistoffset */
    0,                                                    /* tp_iter */
    0,                                                    /* tp_iternext */
    Certificate_methods,                                  /* tp_methods */
    0,                                                    /* tp_members */
    Certificate_getset,                                   /* tp_getset */
    0,                                                    /* tp_base */
    0,                                                    /* tp_dict */
    0,                                                    /* tp_descr_get */
    0,                                                    /* tp_descr_set */
    0,                                                    /* tp_dictoffset */
    0,                                                    /* tp_init */
    0,                                                    /* tp_alloc */
    Certificate_new,                                      /* tp_new */
};
