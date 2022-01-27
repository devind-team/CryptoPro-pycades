#ifndef PY_ENCODED_DATA_H
#define PY_ENCODED_DATA_H

#include "stdafx.h"
#include "CPPCadesCPEncodedData.h"

typedef struct {
    PyObject_HEAD
    boost::shared_ptr<CryptoPro::PKI::CAdES::CPPCadesCPEncodedDataObject> m_pCppCadesImpl;
} EncodedData;

extern PyTypeObject EncodedDataType;
#endif
