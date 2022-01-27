#ifndef PY_SIGNER_H
#define PY_SIGNER_H

#include "stdafx.h"
#include "CPPCadesCPSigner.h"

typedef struct {
    PyObject_HEAD
    boost::shared_ptr<CryptoPro::PKI::CAdES::CPPCadesCPSignerObject> m_pCppCadesImpl;
} Signer;

extern PyTypeObject SignerType;
#endif
