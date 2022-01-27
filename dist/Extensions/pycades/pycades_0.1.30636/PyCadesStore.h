#ifndef PY_STORE_H
#define PY_STORE_H

#include "stdafx.h"
#include "CPPCadesCPStore.h"

typedef struct {
    PyObject_HEAD
    boost::shared_ptr<CryptoPro::PKI::CAdES::CPPCadesCPStoreObject> m_pCppCadesImpl;
} Store;

extern PyTypeObject StoreType;
#endif
