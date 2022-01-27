CMAKE_MINIMUM_REQUIRED(VERSION 3.0)
SET(Python_INCLUDE_DIR "/usr/include/python3.9")
PROJECT(PythonModule LANGUAGES CXX)
    SET (pycades_LIB_SRCS
            errormsg.cpp
            PyCades.cpp
            PyCadesAbout.cpp
            PyCadesAlgorithm.cpp
            PyCadesAttribute.cpp
            PyCadesAttributes.cpp
            PyCadesBasicConstraints.cpp
            PyCadesBlobs.cpp
            PyCadesCertificate.cpp
            PyCadesCertificates.cpp
            PyCadesCertificateStatus.cpp
            PyCadesCRL.cpp
            PyCadesEncodedData.cpp
            PyCadesEnvelopedData.cpp
            PyCadesEKU.cpp
            PyCadesEKUs.cpp
            PyCadesExtendedKeyUsage.cpp
            PyCadesHashedData.cpp
            PyCadesKeyUsage.cpp
            PyCadesOID.cpp
            PyCadesPrivateKey.cpp
            PyCadesPublicKey.cpp
            PyCadesRawSignature.cpp
            PyCadesRecipients.cpp
            PyCadesSignatureStatus.cpp
            PyCadesSignedData.cpp
            PyCadesSignedXML.cpp
            PyCadesSigner.cpp
            PyCadesSigners.cpp
            PyCadesStore.cpp
            PyCadesSymmetricAlgorithm.cpp
            PyCadesVersion.cpp
        )
FIND_PACKAGE( Boost REQUIRED )

ADD_DEFINITIONS(-DUNIX -DSIZEOF_VOID_P=${CMAKE_SIZEOF_VOID_P})

#SET(CMAKE_BUILD_TYPE Debug)
SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -Wno-write-strings")
SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -Wno-deprecated-declarations")
SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -Wno-narrowing")
SET(CMAKE_INCLUDE_CURRENT_DIR ON)
SET(pycades_DIRS
     /opt/cprocsp/include
     /opt/cprocsp/include/cpcsp
     /opt/cprocsp/include/pki/atl
     /opt/cprocsp/include/pki/cppcades
     /opt/cprocsp/include/pki/cplib
     /opt/cprocsp/include/pki
)    

INCLUDE_DIRECTORIES( ${Boost_INCLUDE_DIRS} )
INCLUDE_DIRECTORIES( ${Python_INCLUDE_DIR})
INCLUDE_DIRECTORIES( ${pycades_DIRS})

ADD_LIBRARY(pycades SHARED ${pycades_LIB_SRCS})
SET_TARGET_PROPERTIES(pycades PROPERTIES PREFIX "")

FIND_LIBRARY(FOUND_LIB_CPPCADES
    NAMES cppcades
    HINTS /opt/cprocsp/lib/amd64 /opt/cprocsp/lib/ia32)
TARGET_LINK_LIBRARIES(pycades ${FOUND_LIB_CPPCADES})

ADD_CUSTOM_COMMAND(TARGET pycades
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:pycades> ..)
