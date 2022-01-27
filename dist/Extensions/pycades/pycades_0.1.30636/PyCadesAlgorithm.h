#ifndef PY_ALGORITHM_H
#define PY_ALGORITHM_H

#include "stdafx.h"
#include "CPPCadesCPAlgorithm.h"

typedef struct {
    PyObject_HEAD
    boost::shared_ptr<CryptoPro::PKI::CAdES::CPPCadesCPAlgorithmObject> m_pCppCadesImpl;
} Algorithm;

extern PyTypeObject AlgorithmType;
#endif
