#include "PyCadesAttribute.h"
#include "PyCadesOID.h"

using namespace CryptoPro::PKI::CAdES;

static void Attribute_dealloc(Attribute *self)
{
    Py_TYPE(self)->tp_free((PyObject *)self);
}

static PyObject *Attribute_new(PyTypeObject *type, PyObject *args, PyObject *kwds)
{
    Attribute *self;
    self = (Attribute *)type->tp_alloc(type, 0);
    if (self != NULL)
    {
        self->m_pCppCadesImpl = boost::shared_ptr<CPPCadesCPAttributeObject>(new CPPCadesCPAttributeObject());
    }
    return (PyObject *)self;
}

static PyObject *Attribute_getOID(Attribute *self)
{
    boost::shared_ptr<CPPCadesCPOIDObject> pCPPCadesCPOID(new CPPCadesCPOIDObject());
    HR_METHOD_ERRORCHECK_RETURN(self->m_pCppCadesImpl->get_OID(pCPPCadesCPOID));

    PyObject *pPyOID = PyObject_CallObject((PyObject *)&OIDType, NULL);
    OID *pOID = (OID *)pPyOID;
    pOID->m_pCppCadesImpl = pCPPCadesCPOID;
    return Py_BuildValue("O", pOID);
}

static int Attribute_setValue(Attribute *self, PyObject *value)
{
    char *szValue = "";
    if (!PyArg_Parse(value, "s", &szValue))
    {
        return -1;
    }
    CADESCOM_ATTRIBUTE Name;
    HR_SETTER_ERRORCHECK_RETURN(self->m_pCppCadesImpl->get_Name(&Name));
    if (Name == CADESCOM_AUTHENTICATED_ATTRIBUTE_SIGNING_TIME)
    {
        CryptoPro::CDateTime time(szValue);
        HR_SETTER_ERRORCHECK_RETURN(self->m_pCppCadesImpl->put_DateTimeValue(time));
    }
    else
    {
        CryptoPro::CBlob blobValue;
        blobValue.assign((unsigned char *)szValue, strlen(szValue));
        HR_SETTER_ERRORCHECK_RETURN(self->m_pCppCadesImpl->put_Value(blobValue));
    }
    return 0;
}

static PyObject *Attribute_getValue(Attribute *self)
{
    CryptoPro::CBlob blobValue;
    CADESCOM_ATTRIBUTE Name;
    HR_METHOD_ERRORCHECK_RETURN(self->m_pCppCadesImpl->get_Value(blobValue));
    HR_METHOD_ERRORCHECK_RETURN(self->m_pCppCadesImpl->get_Name(&Name));

    DWORD dwLen = blobValue.cbData();
    std::vector<BYTE> vbValue(dwLen + 1, 0);
    if (Name != CADESCOM_AUTHENTICATED_ATTRIBUTE_SIGNING_TIME)
    {
        memcpy(&vbValue[0], blobValue.pbData(), dwLen);
    }
    else
    {
        FILETIME fTime;
        DWORD fTimeSize = sizeof(FILETIME);
        CryptStringToBinary(reinterpret_cast<TCHAR *>(blobValue.pbData()), dwLen,
                            CRYPT_STRING_BASE64, &vbValue[0], &dwLen, NULL, NULL);
        CryptDecodeObject(X509_ASN_ENCODING | PKCS_7_ASN_ENCODING,
                          (LPCSTR)szOID_RSA_signingTime, &vbValue[0], dwLen, 0, &fTime,
                          &fTimeSize);
        CryptoPro::CDateTime Time(fTime);
        CryptoPro::CStringProxy strProxyTime = Time.tostring();
        return Py_BuildValue("s", strProxyTime.c_str());
    }
    return Py_BuildValue("s", &vbValue[0]);
}

static int Attribute_setName(Attribute *self, PyObject *value)
{
    long lName = 0;
    if (!PyArg_Parse(value, "l", &lName))
    {
        return -1;
    }
    CADESCOM_ATTRIBUTE Name = (CADESCOM_ATTRIBUTE)lName;
    HR_SETTER_ERRORCHECK_RETURN(self->m_pCppCadesImpl->put_Name(Name));
    return 0;
}

static PyObject *Attribute_getName(Attribute *self)
{
    CADESCOM_ATTRIBUTE Name;
    HR_METHOD_ERRORCHECK_RETURN(self->m_pCppCadesImpl->get_Name(&Name));
    return Py_BuildValue("l", (long)Name);
}

static int Attribute_setValueEncoding(Attribute *self, PyObject *value)
{
    long lType = 0;
    if (!PyArg_Parse(value, "l", &lType))
    {
        return -1;
    }
    CAPICOM_ENCODING_TYPE Type = (CAPICOM_ENCODING_TYPE)lType;
    HR_SETTER_ERRORCHECK_RETURN(self->m_pCppCadesImpl->put_ValueEncoding(Type));
    return 0;
}

static PyObject *Attribute_getValueEncoding(Attribute *self)
{
    CAPICOM_ENCODING_TYPE Type;
    HR_METHOD_ERRORCHECK_RETURN(self->m_pCppCadesImpl->get_ValueEncoding(&Type));
    return Py_BuildValue("l", (long)Type);
}

static PyGetSetDef Attribute_getset[] = {
    {"OID", (getter)Attribute_getOID, NULL, "OID", NULL},
    {"Value", (getter)Attribute_getValue, (setter)Attribute_setValue, "Value", NULL},
    {"Name", (getter)Attribute_getName, (setter)Attribute_setName, "Name", NULL},
    {"ValueEncoding", (getter)Attribute_getValueEncoding, (setter)Attribute_setValueEncoding, "ValueEncoding", NULL},
    {NULL} /* Sentinel */
};

static PyMethodDef Attribute_methods[] = {
    {NULL} /* Sentinel */
};

PyTypeObject AttributeType = {
    PyVarObject_HEAD_INIT(NULL, 0) "pycades.Attribute", /* tp_name */
    sizeof(Attribute),                                  /* tp_basicsize */
    0,                                                  /* tp_itemsize */
    (destructor)Attribute_dealloc,                      /* tp_dealloc */
    0,                                                  /* tp_print */
    0,                                                  /* tp_getattr */
    0,                                                  /* tp_setattr */
    0,                                                  /* tp_compare */
    0,                                                  /* tp_repr */
    0,                                                  /* tp_as_number */
    0,                                                  /* tp_as_sequence */
    0,                                                  /* tp_as_mapping */
    0,                                                  /* tp_hash */
    0,                                                  /* tp_call */
    0,                                                  /* tp_str */
    0,                                                  /* tp_getattro */
    0,                                                  /* tp_setattro */
    0,                                                  /* tp_as_buffer */
    Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,           /* tp_flags */
    "Attribute object",                                 /* tp_doc */
    0,                                                  /* tp_traverse */
    0,                                                  /* tp_clear */
    0,                                                  /* tp_richcompare */
    0,                                                  /* tp_weaklistoffset */
    0,                                                  /* tp_iter */
    0,                                                  /* tp_iternext */
    Attribute_methods,                                  /* tp_methods */
    0,                                                  /* tp_members */
    Attribute_getset,                                   /* tp_getset */
    0,                                                  /* tp_base */
    0,                                                  /* tp_dict */
    0,                                                  /* tp_descr_get */
    0,                                                  /* tp_descr_set */
    0,                                                  /* tp_dictoffset */
    0,                                                  /* tp_init */
    0,                                                  /* tp_alloc */
    Attribute_new,                                      /* tp_new */
};
