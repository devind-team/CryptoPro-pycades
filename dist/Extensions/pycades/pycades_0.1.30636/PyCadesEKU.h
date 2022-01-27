#ifndef PY_CP_EKU_H
#define PY_CP_EKU_H

#include "stdafx.h"
#include "CPPCadesCPEKU.h"

typedef struct {
    PyObject_HEAD
    boost::shared_ptr<CryptoPro::PKI::CAdES::CPPCadesCPEKUObject> m_pCppCadesImpl;
} EKU;

extern PyTypeObject EKUType;
#endif
