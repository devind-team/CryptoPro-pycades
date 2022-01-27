#include "PyCadesSigner.h"
#include "PyCadesCertificate.h"
#include "PyCadesAttributes.h"
#include "PyCadesBlobs.h"
#include "PyCadesSignatureStatus.h"

using namespace CryptoPro::PKI::CAdES;

static void Signer_dealloc(Signer *self)
{
    Py_TYPE(self)->tp_free((PyObject *)self);
}

static PyObject *Signer_new(PyTypeObject *type, PyObject *args, PyObject *kwds)
{
    Signer *self;
    self = (Signer *)type->tp_alloc(type, 0);
    if (self != NULL)
    {
        self->m_pCppCadesImpl = boost::shared_ptr<CPPCadesCPSignerObject>(new CPPCadesCPSignerObject());
    }
    return (PyObject *)self;
}

static PyObject *Signer_getCertificate(Signer *self)
{
    boost::shared_ptr<CPPCadesCPCertificateObject> pCPPCadesCPCert;
    HR_METHOD_ERRORCHECK_RETURN(self->m_pCppCadesImpl->get_Certificate(pCPPCadesCPCert));
    PyObject *pPyCert = PyObject_CallObject((PyObject *)&CertificateType, NULL);
    Certificate *pCert = (Certificate *)pPyCert;
    pCert->m_pCppCadesImpl = pCPPCadesCPCert;
    return Py_BuildValue("O", pCert);
}

static int Signer_setCertificate(Signer *self, PyObject *arg)
{
    PyObject *pPyCert = NULL;
    if (!PyArg_Parse(arg, "O!", &CertificateType, &pPyCert))
    {
        return -1;
    }

    Certificate *pCert = (Certificate *)arg;
    CCertContext certContext;
    HR_SETTER_ERRORCHECK_RETURN(pCert->m_pCppCadesImpl->get_CertContext(certContext));
    boost::shared_ptr<CPPCadesCPCertificateObject> pCPPCadesCPCert(new CPPCadesCPCertificateObject());
    pCPPCadesCPCert->put_CertContext(certContext);
    HR_SETTER_ERRORCHECK_RETURN(self->m_pCppCadesImpl->put_Certificate(pCPPCadesCPCert));
    return 0;
}

static PyObject *Signer_getCheckCertificate(Signer *self)
{
    BOOL bValue = 0;
    HR_METHOD_ERRORCHECK_RETURN(self->m_pCppCadesImpl->get_CheckCertificate(bValue));
    return bValue ? Py_True : Py_False;
}

static int Signer_setCheckCertificate(Signer *self, PyObject *value)
{
    int bValue = 0;
    if (!PyArg_Parse(value, "i", &bValue))
    {
        return -1;
    }
    HR_SETTER_ERRORCHECK_RETURN(self->m_pCppCadesImpl->put_CheckCertificate(bValue));
    return 0;
}

static PyObject *Signer_getSignatureStatus(Signer *self)
{
    boost::shared_ptr<CPPCadesSignatureStatusObject> pCPPCadesSignatureStatus;
    HR_METHOD_ERRORCHECK_RETURN(self->m_pCppCadesImpl->get_SignatureStatus(pCPPCadesSignatureStatus));
    PyObject *pPyStatus = PyObject_CallObject((PyObject *)&SignatureStatusType, NULL);
    SignatureStatus *pStatus = (SignatureStatus *)pPyStatus;
    pStatus->m_pCppCadesImpl = pCPPCadesSignatureStatus;
    return Py_BuildValue("O", pStatus);
}

static PyObject *Signer_getOptions(Signer *self)
{
    CAPICOM_CERTIFICATE_INCLUDE_OPTION option;
    HR_METHOD_ERRORCHECK_RETURN(self->m_pCppCadesImpl->get_Options(&option));
    return Py_BuildValue("l", option);
}

static int Signer_setOptions(Signer *self, PyObject *value)
{
    long lOpt = 0;
    if (!PyArg_Parse(value, "l", &lOpt))
    {
        return -1;
    }
    CAPICOM_CERTIFICATE_INCLUDE_OPTION Opt = (CAPICOM_CERTIFICATE_INCLUDE_OPTION)lOpt;
    HR_SETTER_ERRORCHECK_RETURN(self->m_pCppCadesImpl->put_Options(Opt));
    return 0;
}

static PyObject *Signer_getTSAAddress(Signer *self)
{
    CAtlString sTSAAddress;
    HR_METHOD_ERRORCHECK_RETURN(self->m_pCppCadesImpl->get_TSAAddress(sTSAAddress));
    return Py_BuildValue("s", sTSAAddress.GetString());
}

static int Signer_setTSAAddress(Signer *self, PyObject *value)
{
    char *szTSAAddress = "";
    if (!PyArg_Parse(value, "s", &szTSAAddress))
    {
        return -1;
    }
    HR_SETTER_ERRORCHECK_RETURN(self->m_pCppCadesImpl->put_TSAAddress(CAtlString(szTSAAddress)));
    return 0;
}

static PyObject *Signer_getUnauthenticatedAttributes(Signer *self)
{
    PyObject *pPyAttributes = PyObject_CallObject((PyObject *)&AttributesType, NULL);
    Attributes *pAttributes = (Attributes *)pPyAttributes;
    HR_METHOD_ERRORCHECK_RETURN(self->m_pCppCadesImpl->get_UnauthenticatedAttributes(pAttributes->m_pCppCadesImpl));
    return Py_BuildValue("O", pAttributes);
}

static PyObject *Signer_getAuthenticatedAttributes(Signer *self)
{
    PyObject *pPyAttributes = PyObject_CallObject((PyObject *)&AttributesType, NULL);
    Attributes *pAttributes = (Attributes *)pPyAttributes;
    HR_METHOD_ERRORCHECK_RETURN(self->m_pCppCadesImpl->get_AuthenticatedAttributes(pAttributes->m_pCppCadesImpl));
    return Py_BuildValue("O", pAttributes);
}

static PyObject *Signer_getCRLs(Signer *self)
{
    PyObject *pPyBlobs = PyObject_CallObject((PyObject *)&BlobsType, NULL);
    Blobs *pBlobs = (Blobs *)pPyBlobs;
    HR_METHOD_ERRORCHECK_RETURN(self->m_pCppCadesImpl->get_CRLs(pBlobs->m_pCppCadesImpl));
    return Py_BuildValue("O", pBlobs);
}

static PyObject *Signer_getOCSPResponses(Signer *self)
{
    PyObject *pPyBlobs = PyObject_CallObject((PyObject *)&BlobsType, NULL);
    Blobs *pBlobs = (Blobs *)pPyBlobs;
    HR_METHOD_ERRORCHECK_RETURN(self->m_pCppCadesImpl->get_OCSPResponses(pBlobs->m_pCppCadesImpl));
    return Py_BuildValue("O", pBlobs);
}

static PyObject *Signer_getSigningTime(Signer *self)
{
    CryptoPro::CDateTime Time;
    CryptoPro::CStringProxy strProxySigningTime;
    HR_METHOD_ERRORCHECK_RETURN(self->m_pCppCadesImpl->get_SigningTime(Time));
    strProxySigningTime = Time.tostring();
    return Py_BuildValue("s", strProxySigningTime.c_str());
}

static PyObject *Signer_getSignatureTimeStampTime(Signer *self)
{
    CryptoPro::CDateTime Time;
    CryptoPro::CStringProxy strProxySigningTime;
    HR_METHOD_ERRORCHECK_RETURN(self->m_pCppCadesImpl->get_SignatureTimeStampTime(Time));
    strProxySigningTime = Time.tostring();
    return Py_BuildValue("s", strProxySigningTime.c_str());
}

static int Signer_setKeyPin(Signer *self, PyObject *value)
{
    char *szKeyPin = "";
    if (!PyArg_Parse(value, "s", &szKeyPin))
    {
        return -1;
    }
    CAtlStringA sKeyPin(CA2CA(CAtlStringA(szKeyPin), CP_UTF8));
    HR_SETTER_ERRORCHECK_RETURN(self->m_pCppCadesImpl->put_KeyPin(sKeyPin));
    return 0;
}

static PyGetSetDef Signer_getset[] = {
    {"Certificate", (getter)Signer_getCertificate, (setter)Signer_setCertificate, "Certificate", NULL},
    {"CheckCertificate", (getter)Signer_getCheckCertificate, (setter)Signer_setCheckCertificate, "Certificate", NULL},
    {"Options", (getter)Signer_getOptions, (setter)Signer_setOptions, "Options", NULL},
    {"TSAAddress", (getter)Signer_getTSAAddress, (setter)Signer_setTSAAddress, "TSAAddress", NULL},
    {"UnauthenticatedAttributes", (getter)Signer_getUnauthenticatedAttributes, NULL, "UnauthenticatedAttributes", NULL},
    {"AuthenticatedAttributes", (getter)Signer_getAuthenticatedAttributes, NULL, "AuthenticatedAttributes", NULL},
    {"CRLs", (getter)Signer_getCRLs, NULL, "CRLs", NULL},
    {"OCSPResponses", (getter)Signer_getOCSPResponses, NULL, "OCSPResponses", NULL},
    {"SigningTime", (getter)Signer_getSigningTime, NULL, "SigningTime", NULL},
    {"SignatureTimeStampTime", (getter)Signer_getSignatureTimeStampTime, NULL, "SignatureTimeStampTime", NULL},
    {"SignatureStatus", (getter)Signer_getSignatureStatus, NULL, "SignatureStatus", NULL},
    {"KeyPin", NULL, (setter)Signer_setKeyPin, "KeyPin", NULL},
    {NULL} /* Sentinel */
};

static PyMethodDef Signer_methods[] = {
    {NULL} /* Sentinel */
};

PyTypeObject SignerType = {
    PyVarObject_HEAD_INIT(NULL, 0) "pycades.Signer", /* tp_name */
    sizeof(Signer),                                  /* tp_basicsize */
    0,                                               /* tp_itemsize */
    (destructor)Signer_dealloc,                      /* tp_dealloc */
    0,                                               /* tp_print */
    0,                                               /* tp_getattr */
    0,                                               /* tp_setattr */
    0,                                               /* tp_compare */
    0,                                               /* tp_repr */
    0,                                               /* tp_as_number */
    0,                                               /* tp_as_sequence */
    0,                                               /* tp_as_mapping */
    0,                                               /* tp_hash */
    0,                                               /* tp_call */
    0,                                               /* tp_str */
    0,                                               /* tp_getattro */
    0,                                               /* tp_setattro */
    0,                                               /* tp_as_buffer */
    Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,        /* tp_flags */
    "Signer object",                                 /* tp_doc */
    0,                                               /* tp_traverse */
    0,                                               /* tp_clear */
    0,                                               /* tp_richcompare */
    0,                                               /* tp_weaklistoffset */
    0,                                               /* tp_iter */
    0,                                               /* tp_iternext */
    Signer_methods,                                  /* tp_methods */
    0,                                               /* tp_members */
    Signer_getset,                                   /* tp_getset */
    0,                                               /* tp_base */
    0,                                               /* tp_dict */
    0,                                               /* tp_descr_get */
    0,                                               /* tp_descr_set */
    0,                                               /* tp_dictoffset */
    0,                                               /* tp_init */
    0,                                               /* tp_alloc */
    Signer_new,                                      /* tp_new */
};
