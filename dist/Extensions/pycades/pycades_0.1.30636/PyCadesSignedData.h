#ifndef PY_SIGNED_DATA_H
#define PY_SIGNED_DATA_H

#include "stdafx.h"
#include "CPPCadesCPSignedData.h"

typedef struct {
    PyObject_HEAD
    CryptoPro::PKI::CAdES::CPPCadesSignedDataObject *m_pCppCadesImpl;
} SignedData;

extern PyTypeObject SignedDataType;
#endif
