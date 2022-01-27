#ifndef PY_SIGNATURE_STATUS_H
#define PY_SIGNATURE_STATUS_H

#include "stdafx.h"
#include "CPPCadesSignatureStatus.h"

typedef struct {
    PyObject_HEAD
    boost::shared_ptr<CryptoPro::PKI::CAdES::CPPCadesSignatureStatusObject> m_pCppCadesImpl;
} SignatureStatus;

extern PyTypeObject SignatureStatusType;
#endif
