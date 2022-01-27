#ifndef PY_OID_H
#define PY_OID_H

#include "stdafx.h"
#include "CPPCadesCPOID.h"

typedef struct {
    PyObject_HEAD
    boost::shared_ptr<CryptoPro::PKI::CAdES::CPPCadesCPOIDObject> m_pCppCadesImpl;
} OID;

extern PyTypeObject OIDType;
#endif
