#ifndef PY_PRIVATE_KEY_H
#define PY_PRIVATE_KEY_H

#include "stdafx.h"
#include "CPPCadesCPPrivateKey.h"

typedef struct {
    PyObject_HEAD
    boost::shared_ptr<CryptoPro::PKI::CAdES::CPPCadesCPPrivateKeyObject> m_pCppCadesImpl;
} PrivateKey;

extern PyTypeObject PrivateKeyType;
#endif
