#ifndef PY_RAW_SIGNATURE_H
#define PY_RAW_SIGNATURE_H

#include "stdafx.h"
#include "CPPCadesRawSignature.h"

typedef struct {
    PyObject_HEAD
    boost::shared_ptr<CryptoPro::PKI::CAdES::CPPCadesRawSignatureObject> m_pCppCadesImpl;
} RawSignature;

extern PyTypeObject RawSignatureType;
#endif
