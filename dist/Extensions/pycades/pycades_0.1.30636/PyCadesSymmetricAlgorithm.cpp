#include "PyCadesSymmetricAlgorithm.h"
#include "PyCadesCertificate.h"

using namespace CryptoPro::PKI::CAdES;
using namespace CryptoPro;

static void SymmetricAlgorithm_dealloc(SymmetricAlgorithm *self)
{
    Py_TYPE(self)->tp_free((PyObject *)self);
}

static PyObject *SymmetricAlgorithm_new(PyTypeObject *type, PyObject *args, PyObject *kwds)
{
    SymmetricAlgorithm *self;
    self = (SymmetricAlgorithm *)type->tp_alloc(type, 0);
    if (self != NULL)
    {
        self->m_pCppCadesImpl = boost::shared_ptr<CPPCadesSymmetricAlgorithmObject>(new CPPCadesSymmetricAlgorithmObject());
    }
    return (PyObject *)self;
}

static PyObject *SymmetricAlgorithm_getDiversData(SymmetricAlgorithm *self)
{
    CBlob blobValue;
    HR_METHOD_ERRORCHECK_RETURN(self->m_pCppCadesImpl->get_DiversData(blobValue));
    CAtlString sValue = CAtlString((const char *)blobValue.pbData(), blobValue.cbData());
    return Py_BuildValue("s", sValue.GetString());
}

static int SymmetricAlgorithm_setDiversData(SymmetricAlgorithm *self, PyObject *value)
{
    char *szDiversData = "";
    if (!PyArg_Parse(value, "s", &szDiversData))
    {
        return -1;
    }
    HR_SETTER_ERRORCHECK_RETURN(self->m_pCppCadesImpl->put_DiversData(szDiversData, strlen((const char *)szDiversData)));
    return 0;
}

static PyObject *SymmetricAlgorithm_getIV(SymmetricAlgorithm *self)
{
    CBlob blobValue;
    HR_METHOD_ERRORCHECK_RETURN(self->m_pCppCadesImpl->get_IV(blobValue));
    CAtlString sValue = CAtlString((const char *)blobValue.pbData(), blobValue.cbData());
    return Py_BuildValue("s", sValue.GetString());
}

static int SymmetricAlgorithm_setIV(SymmetricAlgorithm *self, PyObject *value)
{
    char *szIV = "";
    if (!PyArg_Parse(value, "s", &szIV))
    {
        return -1;
    }
    HR_SETTER_ERRORCHECK_RETURN(self->m_pCppCadesImpl->put_IV(szIV, strlen((const char *)szIV)));
    return 0;
}

static PyObject *SymmetricAlgorithm_Encrypt(SymmetricAlgorithm *self, PyObject *args)
{
    int isFinal = 1;
    char *szData = "";
    if (!PyArg_ParseTuple(args, "s|i", &szData, &isFinal))
    {
        return NULL;
    }

    CAtlString sData = CAtlString(szData);
    CStringProxy retval;
    HR_METHOD_ERRORCHECK_RETURN(self->m_pCppCadesImpl->Encrypt(sData, sData.GetLength(), isFinal, retval));
    return Py_BuildValue("s", retval.c_str());
}

static PyObject *SymmetricAlgorithm_Decrypt(SymmetricAlgorithm *self, PyObject *args)
{
    int isFinal = 1;
    char *szData = "";
    if (!PyArg_ParseTuple(args, "s|i", &szData, &isFinal))
    {
        return NULL;
    }

    CAtlString sData = CAtlString(szData);
    CBlob blobValue;
    HR_METHOD_ERRORCHECK_RETURN(self->m_pCppCadesImpl->Decrypt(sData, sData.GetLength(), isFinal, blobValue));

    CAtlString sValue = CAtlString((const char *)blobValue.pbData(), blobValue.cbData());
    return Py_BuildValue("s", sValue.GetString());
}

static PyObject *SymmetricAlgorithm_DiversifyKey(SymmetricAlgorithm *self)
{
    boost::shared_ptr<CPPCadesSymmetricAlgorithmObject> pCPPCadesSymAlg;
    HR_METHOD_ERRORCHECK_RETURN(self->m_pCppCadesImpl->DiversifyKey(pCPPCadesSymAlg));
    PyObject *pPySymAlg = PyObject_CallObject((PyObject *)&SymmetricAlgorithmType, NULL);
    SymmetricAlgorithm *pSymAlg = (SymmetricAlgorithm *)pPySymAlg;
    pSymAlg->m_pCppCadesImpl = pCPPCadesSymAlg;
    return Py_BuildValue("O", pSymAlg);
}

static PyObject *SymmetricAlgorithm_GenerateKey(SymmetricAlgorithm *self, PyObject *args)
{
    long lAlgo = CADESCOM_ENCRYPTION_ALGORITHM_GOST_28147_89;
    if (!PyArg_ParseTuple(args, "|l", &lAlgo))
    {
        return NULL;
    }
    CADESCOM_ENCRYPTION_ALGORITHM Algorithm = (CADESCOM_ENCRYPTION_ALGORITHM)lAlgo;
    HR_METHOD_ERRORCHECK_RETURN(self->m_pCppCadesImpl->GenerateKey(Algorithm));
    Py_RETURN_NONE;
}

static PyObject *SymmetricAlgorithm_ExportKey(SymmetricAlgorithm *self, PyObject *args)
{
    PyObject *pPyCert = NULL;
    if (!PyArg_ParseTuple(args, "O!", &CertificateType, &pPyCert))
    {
        return NULL;
    }
    CBlob blobValue;
    Certificate *pCert = (Certificate *)pPyCert;
    HR_METHOD_ERRORCHECK_RETURN(self->m_pCppCadesImpl->ExportKey(pCert->m_pCppCadesImpl, blobValue));

    CAtlString sValue = CAtlString((const char *)blobValue.pbData(), blobValue.cbData());
    return Py_BuildValue("s", sValue.GetString());
}

static PyObject *SymmetricAlgorithm_ImportKey(SymmetricAlgorithm *self, PyObject *args)
{
    PyObject *pPyCert = NULL;
    char *szData = "";
    char *szPassword = "";
    if (!PyArg_ParseTuple(args, "sO|s", &szData, &pPyCert, &szPassword))
    {
        return NULL;
    }

    CAtlString sData = CAtlString(szData);
    CAtlString sPassword = CAtlString(szPassword);
    Certificate *pCert = (Certificate *)pPyCert;
    HR_METHOD_ERRORCHECK_RETURN(self->m_pCppCadesImpl->ImportKey(
        sData, sData.GetLength(), pCert->m_pCppCadesImpl, sPassword, sPassword.GetLength()));
    Py_RETURN_NONE;
}

static PyGetSetDef SymmetricAlgorithm_getset[] = {
    {"DiversData", (getter)SymmetricAlgorithm_getDiversData, (setter)SymmetricAlgorithm_setDiversData, "DiversData", NULL},
    {"IV", (getter)SymmetricAlgorithm_getIV, (setter)SymmetricAlgorithm_setIV, "IV", NULL},
    {NULL} /* Sentinel */
};

static PyMethodDef SymmetricAlgorithm_methods[] = {
    {"Encrypt", (PyCFunction)SymmetricAlgorithm_Encrypt, METH_VARARGS, "Encrypt"},
    {"Decrypt", (PyCFunction)SymmetricAlgorithm_Decrypt, METH_VARARGS, "Decrypt"},
    {"DiversifyKey", (PyCFunction)SymmetricAlgorithm_DiversifyKey, METH_NOARGS, "DiversifyKey"},
    {"GenerateKey", (PyCFunction)SymmetricAlgorithm_GenerateKey, METH_VARARGS, "GenerateKey"},
    {"ExportKey", (PyCFunction)SymmetricAlgorithm_ExportKey, METH_VARARGS, "ExportKey"},
    {"ImportKey", (PyCFunction)SymmetricAlgorithm_ImportKey, METH_VARARGS, "ImportKey"},
    {NULL} /* Sentinel */
};

PyTypeObject SymmetricAlgorithmType = {
    PyVarObject_HEAD_INIT(NULL, 0) "pycades.SymmetricAlgorithm", /* tp_name */
    sizeof(SymmetricAlgorithm),                                  /* tp_basicsize */
    0,                                                           /* tp_itemsize */
    (destructor)SymmetricAlgorithm_dealloc,                      /* tp_dealloc */
    0,                                                           /* tp_print */
    0,                                                           /* tp_getattr */
    0,                                                           /* tp_setattr */
    0,                                                           /* tp_compare */
    0,                                                           /* tp_repr */
    0,                                                           /* tp_as_number */
    0,                                                           /* tp_as_sequence */
    0,                                                           /* tp_as_mapping */
    0,                                                           /* tp_hash */
    0,                                                           /* tp_call */
    0,                                                           /* tp_str */
    0,                                                           /* tp_getattro */
    0,                                                           /* tp_setattro */
    0,                                                           /* tp_as_buffer */
    Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,                    /* tp_flags */
    "SymmetricAlgorithm object",                                 /* tp_doc */
    0,                                                           /* tp_traverse */
    0,                                                           /* tp_clear */
    0,                                                           /* tp_richcompare */
    0,                                                           /* tp_weaklistoffset */
    0,                                                           /* tp_iter */
    0,                                                           /* tp_iternext */
    SymmetricAlgorithm_methods,                                  /* tp_methods */
    0,                                                           /* tp_members */
    SymmetricAlgorithm_getset,                                   /* tp_getset */
    0,                                                           /* tp_base */
    0,                                                           /* tp_dict */
    0,                                                           /* tp_descr_get */
    0,                                                           /* tp_descr_set */
    0,                                                           /* tp_dictoffset */
    0,                                                           /* tp_init */
    0,                                                           /* tp_alloc */
    SymmetricAlgorithm_new,                                      /* tp_new */
};
