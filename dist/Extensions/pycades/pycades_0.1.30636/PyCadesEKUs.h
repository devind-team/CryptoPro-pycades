#ifndef PY_CP_EKUS_H
#define PY_CP_EKUS_H

#include "stdafx.h"
#include "CPPCadesCollections.h"

typedef struct {
    PyObject_HEAD
    boost::shared_ptr<CryptoPro::PKI::CAdES::CPPCadesCPEKUsObject> m_pCppCadesImpl;
} EKUs;

extern PyTypeObject EKUsType;
#endif
