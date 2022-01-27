#include "PyCadesVersion.h"

using namespace CryptoPro::PKI::CAdES;

static void Version_dealloc(Version *self)
{
    Py_TYPE(self)->tp_free((PyObject *)self);
}

static PyObject *Version_new(PyTypeObject *type, PyObject *args, PyObject *kwds)
{
    Version *self;
    self = (Version *)type->tp_alloc(type, 0);
    if (self != NULL)
    {
        self->m_pCppCadesImpl = boost::shared_ptr<CPPVersionObject>(new CPPVersionObject());
    }
    return (PyObject *)self;
}

static PyObject *Version_getMajorVersion(Version *self)
{
    unsigned int version = 0;
    HR_METHOD_ERRORCHECK_RETURN(self->m_pCppCadesImpl->get_MajorVersion(&version));
    return Py_BuildValue("i", version);
}

static PyObject *Version_getMinorVersion(Version *self)
{
    unsigned int version = 0;
    HR_METHOD_ERRORCHECK_RETURN(self->m_pCppCadesImpl->get_MinorVersion(&version));
    return Py_BuildValue("i", version);
}

static PyObject *Version_getBuildVersion(Version *self)
{
    unsigned int version = 0;
    HR_METHOD_ERRORCHECK_RETURN(self->m_pCppCadesImpl->get_BuildVersion(&version));
    return Py_BuildValue("i", version);
}

static PyGetSetDef Version_getset[] = {
    {"MajorVersion", (getter)Version_getMajorVersion, NULL, "MajorVersion", NULL},
    {"MinorVersion", (getter)Version_getMinorVersion, NULL, "MinorVersion", NULL},
    {"BuildVersion", (getter)Version_getBuildVersion, NULL, "BuildVersion", NULL},
    {NULL} /* Sentinel */
};

static PyObject *Version_toString(Version *self)
{
    CAtlString AtlVersion;
    HR_METHOD_ERRORCHECK_RETURN(self->m_pCppCadesImpl->toString(AtlVersion));
    return Py_BuildValue("s", AtlVersion.GetString());
}

static PyMethodDef Version_methods[] = {
    {"toString", (PyCFunction)Version_toString, METH_NOARGS, "toString"},
    {NULL} /* Sentinel */
};

PyTypeObject VersionType = {
    PyVarObject_HEAD_INIT(NULL, 0) "pycades.Version", /* tp_name */
    sizeof(Version),                                  /* tp_basicsize */
    0,                                                /* tp_itemsize */
    (destructor)Version_dealloc,                      /* tp_dealloc */
    0,                                                /* tp_print */
    0,                                                /* tp_getattr */
    0,                                                /* tp_setattr */
    0,                                                /* tp_compare */
    0,                                                /* tp_repr */
    0,                                                /* tp_as_number */
    0,                                                /* tp_as_sequence */
    0,                                                /* tp_as_mapping */
    0,                                                /* tp_hash */
    0,                                                /* tp_call */
    0,                                                /* tp_str */
    0,                                                /* tp_getattro */
    0,                                                /* tp_setattro */
    0,                                                /* tp_as_buffer */
    Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,         /* tp_flags */
    "Version object",                                 /* tp_doc */
    0,                                                /* tp_traverse */
    0,                                                /* tp_clear */
    0,                                                /* tp_richcompare */
    0,                                                /* tp_weaklistoffset */
    0,                                                /* tp_iter */
    0,                                                /* tp_iternext */
    Version_methods,                                  /* tp_methods */
    0,                                                /* tp_members */
    Version_getset,                                   /* tp_getset */
    0,                                                /* tp_base */
    0,                                                /* tp_dict */
    0,                                                /* tp_descr_get */
    0,                                                /* tp_descr_set */
    0,                                                /* tp_dictoffset */
    0,                                                /* tp_init */
    0,                                                /* tp_alloc */
    Version_new,                                      /* tp_new */
};
