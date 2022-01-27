#include "PyCadesCertificates.h"
#include "PyCadesCertificate.h"

using namespace CryptoPro::PKI::CAdES;

static void Certificates_dealloc(Certificates *self)
{
    Py_TYPE(self)->tp_free((PyObject *)self);
}

static PyObject *Certificates_new(PyTypeObject *type, PyObject *args, PyObject *kwds)
{
    Certificates *self;
    self = (Certificates *)type->tp_alloc(type, 0);
    if (self != NULL)
    {
        self->m_pCppCadesImpl = boost::shared_ptr<CPPCadesCPCertificatesObject>(new CPPCadesCPCertificatesObject());
    }
    return (PyObject *)self;
}

static PyObject *Certificates_Item(Certificates *self, PyObject *args)
{
    long lIndex = 0;
    if (!PyArg_ParseTuple(args, "l", &lIndex))
    {
        return NULL;
    }
    boost::shared_ptr<CPPCadesCPCertificateObject> pCPPCadesCPCert;
    HR_METHOD_ERRORCHECK_RETURN(self->m_pCppCadesImpl->Item(lIndex, pCPPCadesCPCert));
    PyObject *pPyCertificate = PyObject_CallObject((PyObject *)&CertificateType, NULL);
    Certificate *pCertificate = (Certificate *)pPyCertificate;
    pCertificate->m_pCppCadesImpl = pCPPCadesCPCert;
    return Py_BuildValue("O", pCertificate);
}

static PyObject *Certficates_Count(Certificates *self)
{
    unsigned int count = 0;
    HR_METHOD_ERRORCHECK_RETURN(self->m_pCppCadesImpl->Count(&count));
    return Py_BuildValue("l", count);
}

static PyObject *Certificates_Find(Certificates *self, PyObject *args)
{
    PyObject *pPyQuery = NULL;
    long lType = 0;
    int iValidOnly = 0;
    if (!PyArg_ParseTuple(args, "l|Oi", &lType, &pPyQuery, &iValidOnly))
    {
        return NULL;
    }

    CAPICOM_CERTIFICATE_FIND_TYPE Type = (CAPICOM_CERTIFICATE_FIND_TYPE)lType;
    FindCriteria findCriteria;
    char *szQuery = "";
    long lQuery = 0;

    switch (Type)
    {
    case CAPICOM_CERTIFICATE_FIND_SHA1_HASH:
    case CAPICOM_CERTIFICATE_FIND_SUBJECT_NAME:
    case CAPICOM_CERTIFICATE_FIND_ISSUER_NAME:
    case CAPICOM_CERTIFICATE_FIND_ROOT_NAME:
    case CAPICOM_CERTIFICATE_FIND_TEMPLATE_NAME:
    case CAPICOM_CERTIFICATE_FIND_CERTIFICATE_POLICY:
    {
        if (!PyArg_Parse(pPyQuery, "s", &szQuery))
        {
            return NULL;
        }

        findCriteria.str = CAtlString(szQuery);
        findCriteria.dwCriteriaFlag = FIND_CRITERIA_STRING;
        break;
    }
    case CAPICOM_CERTIFICATE_FIND_EXTENDED_PROPERTY:
    case CAPICOM_CERTIFICATE_FIND_KEY_USAGE:
    {
        if (!PyArg_Parse(pPyQuery, "l", &lQuery))
        {
            return NULL;
        }
        findCriteria.dwCriteriaFlag = FIND_CRITERIA_DWORD;
        findCriteria.dword = static_cast<DWORD>(lQuery);
        break;
    }
    case CAPICOM_CERTIFICATE_FIND_EXTENSION:
    case CAPICOM_CERTIFICATE_FIND_APPLICATION_POLICY:
    {
        if (PyArg_Parse(pPyQuery, "s", &szQuery))
        {
            findCriteria.str = CAtlString(szQuery);
            findCriteria.dwCriteriaFlag = FIND_CRITERIA_STRING;
        }
        else
        {
            if (!PyArg_Parse(pPyQuery, "l", &lQuery))
            {
                return NULL;
            }
            findCriteria.dwCriteriaFlag = FIND_CRITERIA_DWORD;
            findCriteria.dword = static_cast<DWORD>(lQuery);
        }
        break;
    }
    case CAPICOM_CERTIFICATE_FIND_TIME_VALID:
    case CAPICOM_CERTIFICATE_FIND_TIME_NOT_YET_VALID:
    case CAPICOM_CERTIFICATE_FIND_TIME_EXPIRED:
    {
        CryptoPro::CDateTime utcDate;
        if (pPyQuery)
        {
            if (!PyArg_Parse(pPyQuery, "s", &szQuery))
            {
                return NULL;
            }
            try
            {
                utcDate = CryptoPro::CDateTime(szQuery);
            }
            catch (...)
            {
                PyErr_BadArgument();
                return NULL;
            }
        }
        else
        {
            utcDate = CryptoPro::CDateTime::Now();
        }
        findCriteria.dwCriteriaFlag = FIND_CRITERIA_DATE;
        findCriteria.date = utcDate;
        break;
    }
    default:
        PyErr_BadArgument();
        return NULL;
    }

    PyObject *pPyCertificates = PyObject_CallObject((PyObject *)&CertificatesType, NULL);
    Certificates *pCertificates = (Certificates *)pPyCertificates;
    BOOL bValidOnly = (BOOL)iValidOnly;
    HR_METHOD_ERRORCHECK_RETURN(self->m_pCppCadesImpl->Find(Type, &findCriteria, bValidOnly, pCertificates->m_pCppCadesImpl));
    return Py_BuildValue("O", pCertificates);
}

static PyGetSetDef Certificates_getset[] = {
    {"Count", (getter)Certficates_Count, NULL, "Count", NULL},
    {NULL} /* Sentinel */
};

static PyMethodDef Certificates_methods[] = {
    {"Find", (PyCFunction)Certificates_Find, METH_VARARGS, "Find"},
    {"Item", (PyCFunction)Certificates_Item, METH_VARARGS, "Item"},
    {NULL} /* Sentinel */
};

PyTypeObject CertificatesType = {
    PyVarObject_HEAD_INIT(NULL, 0) "pycades.Certificates", /* tp_name */
    sizeof(Certificates),                                  /* tp_basicsize */
    0,                                                     /* tp_itemsize */
    (destructor)Certificates_dealloc,                      /* tp_dealloc */
    0,                                                     /* tp_print */
    0,                                                     /* tp_getattr */
    0,                                                     /* tp_setattr */
    0,                                                     /* tp_compare */
    0,                                                     /* tp_repr */
    0,                                                     /* tp_as_number */
    0,                                                     /* tp_as_sequence */
    0,                                                     /* tp_as_mapping */
    0,                                                     /* tp_hash */
    0,                                                     /* tp_call */
    0,                                                     /* tp_str */
    0,                                                     /* tp_getattro */
    0,                                                     /* tp_setattro */
    0,                                                     /* tp_as_buffer */
    Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,              /* tp_flags */
    "Certificates object",                                 /* tp_doc */
    0,                                                     /* tp_traverse */
    0,                                                     /* tp_clear */
    0,                                                     /* tp_richcompare */
    0,                                                     /* tp_weaklistoffset */
    0,                                                     /* tp_iter */
    0,                                                     /* tp_iternext */
    Certificates_methods,                                  /* tp_methods */
    0,                                                     /* tp_members */
    Certificates_getset,                                   /* tp_getset */
    0,                                                     /* tp_base */
    0,                                                     /* tp_dict */
    0,                                                     /* tp_descr_get */
    0,                                                     /* tp_descr_set */
    0,                                                     /* tp_dictoffset */
    0,                                                     /* tp_init */
    0,                                                     /* tp_alloc */
    Certificates_new,                                      /* tp_new */
};
