#ifndef PY_CP_BLOBS_H
#define PY_CP_BLOBS_H

#include "stdafx.h"
#include "CPPCadesCollections.h"

typedef struct {
    PyObject_HEAD
    boost::shared_ptr<CryptoPro::PKI::CAdES::CPPCadesCPBlobsObject> m_pCppCadesImpl;
} Blobs;

extern PyTypeObject BlobsType;
#endif
