#ifndef PY_SYMMETRIC_ALGORITHM_H_
#define PY_SYMMETRIC_ALGORITHM_H_

#include "stdafx.h"
#include "CPPCadesSymmetricAlgorithm.h"

typedef struct {
    PyObject_HEAD
    boost::shared_ptr<CryptoPro::PKI::CAdES::CPPCadesSymmetricAlgorithmObject> m_pCppCadesImpl;
} SymmetricAlgorithm;

extern PyTypeObject SymmetricAlgorithmType;
#endif
