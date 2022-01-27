#include "PyCadesAbout.h"
#include "PyCadesVersion.h"

using namespace CryptoPro::PKI::CAdES;

static void About_dealloc(About *self)
{
    Py_TYPE(self)->tp_free((PyObject *)self);
}

static PyObject *About_new(PyTypeObject *type, PyObject *args, PyObject *kwds)
{
    About *self;
    self = (About *)type->tp_alloc(type, 0);
    if (self != NULL)
    {
        self->m_pCppCadesImpl = boost::shared_ptr<CPPCadesAboutObject>(new CPPCadesAboutObject());
    }
    return (PyObject *)self;
}

static PyObject *About_getMajorVersion(About *self)
{
    unsigned int version = 0;
    HR_METHOD_ERRORCHECK_RETURN(self->m_pCppCadesImpl->get_MajorVersion(&version));
    return Py_BuildValue("i", version);
}

static PyObject *About_getMinorVersion(About *self)
{
    unsigned int version = 0;
    HR_METHOD_ERRORCHECK_RETURN(self->m_pCppCadesImpl->get_MinorVersion(&version));
    return Py_BuildValue("i", version);
}

static PyObject *About_getBuildVersion(About *self)
{
    unsigned int version = 0;
    HR_METHOD_ERRORCHECK_RETURN(self->m_pCppCadesImpl->get_BuildVersion(&version));
    return Py_BuildValue("i", version);
}

static PyObject *About_getVersion(About *self)
{
    CAtlString CAtlVersion;
    HR_METHOD_ERRORCHECK_RETURN(self->m_pCppCadesImpl->get_Version(CAtlVersion));
    return Py_BuildValue("s", CAtlVersion.GetString());
}

static PyObject *About_PluginVersion(About *self)
{
    boost::shared_ptr<CPPVersionObject> version;
    HR_METHOD_ERRORCHECK_RETURN(self->m_pCppCadesImpl->get_PluginVersion(version));
    PyObject *pPluginVersionObject = PyObject_CallObject((PyObject *)&VersionType, NULL);
    Version *pPluginVersion = (Version *)pPluginVersionObject;
    pPluginVersion->m_pCppCadesImpl = version;
    return Py_BuildValue("O", pPluginVersion);
}

static PyGetSetDef About_getset[] = {
    {"MajorVersion", (getter)About_getMajorVersion, NULL, "MajorVersion", NULL},
    {"MinorVersion", (getter)About_getMinorVersion, NULL, "MinorVersion", NULL},
    {"BuildVersion", (getter)About_getBuildVersion, NULL, "BuildVersion", NULL},
    {"Version", (getter)About_getVersion, NULL, "Version", NULL},
    {"PluginVersion", (getter)About_PluginVersion, NULL, "PluginVersion", NULL},
    {NULL} /* Sentinel */
};

static PyObject *About_CSPVersion(About *self, PyObject *args)
{
    char *szProvName = "";
    long dwProvType = 75;
    if (!PyArg_ParseTuple(args, "|sl", &szProvName, &dwProvType))
    {
        return NULL;
    }
    CAtlString provName = CAtlString(CA2CT(CAtlStringA(szProvName), CP_UTF8));

    boost::shared_ptr<CPPVersionObject> version;
    HR_METHOD_ERRORCHECK_RETURN(self->m_pCppCadesImpl->get_CSPVersion(provName, dwProvType, version));

    PyObject *pCSPVersionObject = PyObject_CallObject((PyObject *)&VersionType, NULL);
    Version *pCSPVersion = (Version *)pCSPVersionObject;
    pCSPVersion->m_pCppCadesImpl = version;
    return Py_BuildValue("O", pCSPVersion);
}

static PyMethodDef About_methods[] = {
    {"CSPVersion", (PyCFunction)About_CSPVersion, METH_VARARGS, "CSPVersion"},
    {NULL} /* Sentinel */
};

PyTypeObject AboutType = {
    PyVarObject_HEAD_INIT(NULL, 0) "pycades.About", /* tp_name */
    sizeof(About),                                  /* tp_basicsize */
    0,                                              /* tp_itemsize */
    (destructor)About_dealloc,                      /* tp_dealloc */
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
    "About object",                                 /* tp_doc */
    0,                                              /* tp_traverse */
    0,                                              /* tp_clear */
    0,                                              /* tp_richcompare */
    0,                                              /* tp_weaklistoffset */
    0,                                              /* tp_iter */
    0,                                              /* tp_iternext */
    About_methods,                                  /* tp_methods */
    0,                                              /* tp_members */
    About_getset,                                   /* tp_getset */
    0,                                              /* tp_base */
    0,                                              /* tp_dict */
    0,                                              /* tp_descr_get */
    0,                                              /* tp_descr_set */
    0,                                              /* tp_dictoffset */
    0,                                              /* tp_init */
    0,                                              /* tp_alloc */
    About_new,                                      /* tp_new */
};
