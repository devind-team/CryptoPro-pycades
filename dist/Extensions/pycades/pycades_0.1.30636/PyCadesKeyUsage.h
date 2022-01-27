#ifndef PY_KEY_USAGE_H
#define PY_KEY_USAGE_H

#include "stdafx.h"
#include "CPPCadesCPKeyUsage.h"

typedef struct {
    PyObject_HEAD
    boost::shared_ptr<CryptoPro::PKI::CAdES::CPPCadesCPKeyUsageObject> m_pCppCadesImpl;
} KeyUsage;

extern PyTypeObject KeyUsageType;
#endif
