#ifndef PY_CERTIFICATE_H
#define PY_CERTIFICATE_H

#include "stdafx.h"
#include "CPPCadesCPCertificate.h"

typedef struct {
    PyObject_HEAD
    boost::shared_ptr<CryptoPro::PKI::CAdES::CPPCadesCPCertificateObject> m_pCppCadesImpl;
} Certificate;

extern PyTypeObject CertificateType;
#endif
