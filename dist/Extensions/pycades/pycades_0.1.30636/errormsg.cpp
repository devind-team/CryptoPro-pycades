/*!
* \file $RCSfile$
* \version $Revision: 201331 $
* \date $Date:: 2019-10-25 11:27:11 +0300#$
* \author $Author: cross $
*
* \brief     .
*
*     .
*/

//   "*_e.h"
#define FACILITY_TSPCLI                  0x210
#define FACILITY_OCSPCLI                 0x211
#define FACILITY_TSPSRV                  0x212
#define FACILITY_OCSPSRV                 0x213

#ifdef UNIX
#   include "CSP_WinCrypt.h"
#   include "CSP_WinError.h"
#   include <string>
#   include "ocspcli_e.h"
#   include "tspcli_e.h"
#else //_WIN32

#   define STRICT //    .    MS, 
          //  Visual C++ STRICT   .
#   define WIN32_LEAN_AND_MEAN //   
#   define _WIN32_WINNT 0x0501 //     XP

//  ActCtx.h
#define ISOLATION_AWARE_ENABLED 1

#include <windows.h>
#include <ole2.h>
#include <lmerr.h>
#include <lmcons.h>
#include <activeds.h>
#include <ActCtx.h>

#endif //_WIN32

#ifndef UNIX
#pragma warning (push)
#pragma warning (disable:4838)
#endif
#include <atlstr.h>
#ifndef UNIX
#pragma warning (pop)
#endif
#include "errormsg.h"

static LPCWSTR eng_wrong_name = L"Wrong name format or an attempt is made to open container of another CSP.";

#ifndef UNIX
inline void _trimrigth(LPTSTR szBuf, LPCTSTR pszTargets);

static LPCWSTR rus_wrong_name = L"        .";
static BOOL MakeOurMessage(HRESULT hr, LPWSTR szBuf, DWORD chBufLen, DWORD dwLangId)
{
    if (hr == SCARD_E_CARD_UNSUPPORTED) {
    LPCWSTR wrong_name_text;
    if (PRIMARYLANGID(dwLangId) == 0x19)
        wrong_name_text = rus_wrong_name;
    else
        wrong_name_text = eng_wrong_name;
    _tcsncpy(szBuf, wrong_name_text, chBufLen - 1);
    return TRUE;
    }
    return FALSE;
}

BOOL GetErrorMessage(
    HRESULT hr, LPTSTR szBuf, DWORD chBufLen, DWORD dwLangId)
{
    static CryptoPro::ActCtx::CActCtxHandle actCtxAssociated;

    if (!chBufLen)
    {
        return FALSE;
    }
    szBuf[0] = 0;
    HMODULE hInst = 0;
    DWORD dwFacility = HRESULT_FACILITY(hr);
    switch (dwFacility) {
    case FACILITY_TSPCLI:
        {
            CryptoPro::ActCtx::CActCtxActivator activator(actCtxAssociated);
            hInst = ::GetModuleHandle(TEXT("tspcli.dll"));
            if (hInst)
            {
                break;
            }
            hInst = ::GetModuleHandle(TEXT("cades.dll"));
            if (hInst)
            {
                //TODO:    ,   
                // .
                static CryptoPro::ActCtx::CActCtxHandle actCtxCadesDll(hInst);
                CryptoPro::ActCtx::CActCtxActivator activatorCadesDll(actCtxCadesDll);
                hInst = ::GetModuleHandle(TEXT("tspcli.dll"));
            }
        }
        break;
    case FACILITY_OCSPCLI:
        {
            CryptoPro::ActCtx::CActCtxActivator activator(actCtxAssociated);
            hInst = ::GetModuleHandle(TEXT("ocspcli.dll"));
            if (hInst)
            {
                break;
            }
            hInst = ::GetModuleHandle(TEXT("cades.dll"));
            if (hInst)
            {
                //TODO:    ,   
                // .
                static CryptoPro::ActCtx::CActCtxHandle actCtxCadesDll(hInst);
                CryptoPro::ActCtx::CActCtxActivator activatorCadesDll(actCtxCadesDll);
                hInst = ::GetModuleHandle(TEXT("ocspcli.dll"));
            }
        }
        break;
    case FACILITY_MSMQ:
        hInst = ::GetModuleHandle(TEXT("mqutil.dll"));
        break;
    case FACILITY_ITF:
        hInst = ::GetModuleHandle(TEXT("oledb32r.dll"));
        break;
    }

    if (!hInst
        && (dwFacility == FACILITY_TSPCLI || dwFacility == FACILITY_OCSPCLI))
    {
        //         ,
        //    . , cadescom.dll
        //     .
        //
        //     GetModuleHandleEx(
        // GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS)   ,
        //       
        // .    , ..  
        // ,   hInst  0.
        ::GetModuleHandleEx(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS
            | GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT, _T(" "), &hInst);
    }

    DWORD dwCode = HRESULT_CODE(hr);
    if (!hInst)
    {
    if (dwCode >= NERR_BASE && dwCode <= MAX_NERR)
    {
        hInst = ::GetModuleHandle(MESSAGE_FILENAME);
    }
    }
    BOOL dwRet = FALSE;
    DWORD dwFlagsMod = FORMAT_MESSAGE_IGNORE_INSERTS | FORMAT_MESSAGE_FROM_HMODULE;

    dwRet = MakeOurMessage(hr, szBuf, chBufLen, dwLangId);
    if (!dwRet) {
    if (hInst) {
        dwRet = FormatMessage(dwFlagsMod, hInst, hr, dwLangId, szBuf, chBufLen, NULL);
        //        ,
        //    0 (     )
        if (!dwRet && dwLangId)
        dwRet = FormatMessage(dwFlagsMod, hInst, hr, 0, szBuf, chBufLen, NULL);
        hInst = 0;
    }
    }
    DWORD dwFlagsSys = FORMAT_MESSAGE_IGNORE_INSERTS | FORMAT_MESSAGE_FROM_SYSTEM;
    if (!dwRet) {
    dwRet = FormatMessage(dwFlagsSys, 0, hr, dwLangId, szBuf, chBufLen, NULL);
    //        ,
    //    0 (     )
    if (!dwRet && dwLangId)
        dwRet = FormatMessage(dwFlagsSys, 0, hr, 0, szBuf, chBufLen, NULL);
    }
    if (!dwRet)
    {
    hInst = ::GetModuleHandle(TEXT("winhttp.dll"));
    if (hInst)
    {
        //   dwCode,    hr!
        dwRet = FormatMessage(dwFlagsMod, hInst, dwCode, dwLangId, szBuf, chBufLen, NULL);
        //        ,
        //    0 (     )
        if (!dwRet && dwLangId)
        dwRet = FormatMessage(dwFlagsMod, hInst, dwCode, 0, szBuf, chBufLen, NULL);
    }
    }
    if (!dwRet)
    {
    hInst = ::GetModuleHandle(TEXT("ntdsbmsg.dll"));
    if (hInst)
    {
        dwRet = FormatMessage(dwFlagsMod, hInst, hr, dwLangId, szBuf, chBufLen, NULL);
        //        ,
        //    0 (     )
        if (!dwRet && dwLangId)
        dwRet = FormatMessage(dwFlagsMod, hInst, hr, 0, szBuf, chBufLen, NULL);
    }
    }
    if (!dwRet)
    {
    hInst = ::GetModuleHandle(TEXT("wininet.dll"));
    if (hInst)
    {
        dwRet = FormatMessage(dwFlagsMod, hInst, hr, dwLangId, szBuf, chBufLen, NULL);
        //        ,
        //    0 (     )
        if (!dwRet && dwLangId)
        dwRet = FormatMessage(dwFlagsMod, hInst, hr, 0, szBuf, chBufLen, NULL);
    }
    }
    if (!dwRet && hr >= 0x80005000 && hr < 0x80006000) {
    switch(hr) {
#define ADSERROR(x) case x: _tcsncpy_s(szBuf, chBufLen, _T(#x), _TRUNCATE); dwRet = TRUE; break
        ADSERROR(E_ADS_BAD_PATHNAME);
        ADSERROR(E_ADS_INVALID_DOMAIN_OBJECT);
        ADSERROR(E_ADS_INVALID_USER_OBJECT);
        ADSERROR(E_ADS_INVALID_COMPUTER_OBJECT);
        ADSERROR(E_ADS_UNKNOWN_OBJECT);
        ADSERROR(E_ADS_PROPERTY_NOT_SET);
        ADSERROR(E_ADS_PROPERTY_NOT_SUPPORTED);
        ADSERROR(E_ADS_PROPERTY_INVALID);
        ADSERROR(E_ADS_BAD_PARAMETER);
        ADSERROR(E_ADS_OBJECT_UNBOUND);
        ADSERROR(E_ADS_PROPERTY_NOT_MODIFIED);
        ADSERROR(E_ADS_PROPERTY_MODIFIED);
        ADSERROR(E_ADS_CANT_CONVERT_DATATYPE);
        ADSERROR(E_ADS_PROPERTY_NOT_FOUND);
        ADSERROR(E_ADS_OBJECT_EXISTS);
        ADSERROR(E_ADS_SCHEMA_VIOLATION);
        ADSERROR(E_ADS_COLUMN_NOT_SET);
        ADSERROR(E_ADS_INVALID_FILTER);
#undef ADSERROR
    }
    }
    if (dwRet && szBuf[0])
    _trimrigth(szBuf, _T("\r\n"));
    if (dwFacility == FACILITY_WIN32 || hr >= 0x80005000 && hr < 0x80006000)
    {
    WCHAR szExtErr[256];
    WCHAR szProv[256];
    LPCTSTR szFormat;
    if (szBuf[0])
        szFormat = _T(" [%ws, #%d (%ws)]");
    else
        szFormat = _T("ADs [%ws, #%d (%ws)]");
    // Get extended error value.
    hInst = ::GetModuleHandle(TEXT("activeds.dll"));
    if (hInst)
    {
        typedef HRESULT (WINAPI *LPADSGETLASTERROR)
        (LPDWORD, LPWSTR, DWORD, LPWSTR, DWORD);
        LPADSGETLASTERROR lpADsGetLastError = LPADSGETLASTERROR(
        GetProcAddress(hInst, "ADsGetLastError"));
        if (lpADsGetLastError != NULL) {
        hr = lpADsGetLastError( &dwCode, szExtErr, 256, szProv, 256);
        if (SUCCEEDED(hr) && dwCode != 0) {
            TCHAR szFormattedBuf[MAX_PATH];
            if (_stprintf_s(szFormattedBuf, MAX_PATH,
            szFormat, szProv, dwCode, szExtErr) > 0)
            if (!_tcsncat_s(szBuf, chBufLen, szFormattedBuf,
                _TRUNCATE))
                dwRet = TRUE;
        }
        }
    }
    }
    return dwRet ? TRUE : FALSE;
}

void _trimrigth(LPTSTR szBuf, LPCTSTR pszTargets)
{
    // if we're not trimming anything, we're not doing any work
    if( (pszTargets == NULL) || (*pszTargets == 0) )
    return;
    // find beginning of trailing matches
    // by starting at beginning
    LPCTSTR psz = szBuf;
    LPCTSTR pszLast = NULL;
    while (*psz != 0) {
    if (_tcschr( pszTargets, *psz ) != NULL) {
        if (pszLast == NULL)
        pszLast = psz;
    } else
        pszLast = NULL;
    psz = psz + 1;
    }
    if (pszLast != NULL ) {
    // truncate at left-most matching character
    int iLast = int(pszLast - szBuf);
    szBuf[iLast] = 0;
    }
}

const ATL::CAtlStringW GetErrorMessage(HRESULT hr, DWORD dwLangId)
{
    ATL::CAtlString sBuf;
    TCHAR *szBuf = sBuf.GetBuffer(1024);
    BOOL res = GetErrorMessage(hr, szBuf, 1024, dwLangId);
    sBuf.ReleaseBuffer();
    if (!res)
        sBuf.AppendFormat(L"Unknown error code (0x%08X)", hr);

    return sBuf;
}
#else //UNIX

typedef enum _CAPICOM_ERROR_CODE
{
    CAPICOM_E_ENCODE_INVALID_TYPE   = 0x80880100,
    CAPICOM_E_EKU_INVALID_OID   = 0x80880200,
    CAPICOM_E_EKU_OID_NOT_INITIALIZED   = 0x80880201,
    CAPICOM_E_CERTIFICATE_NOT_INITIALIZED   = 0x80880210,
    CAPICOM_E_CERTIFICATE_NO_PRIVATE_KEY    = 0x80880211,
    CAPICOM_E_CHAIN_NOT_BUILT   = 0x80880220,
    CAPICOM_E_STORE_NOT_OPENED  = 0x80880230,
    CAPICOM_E_STORE_EMPTY   = 0x80880231,
    CAPICOM_E_STORE_INVALID_OPEN_MODE   = 0x80880232,
    CAPICOM_E_STORE_INVALID_SAVE_AS_TYPE    = 0x80880233,
    CAPICOM_E_ATTRIBUTE_NAME_NOT_INITIALIZED    = 0x80880240,
    CAPICOM_E_ATTRIBUTE_VALUE_NOT_INITIALIZED   = 0x80880241,
    CAPICOM_E_ATTRIBUTE_INVALID_NAME    = 0x80880242,
    CAPICOM_E_ATTRIBUTE_INVALID_VALUE   = 0x80880243,
    CAPICOM_E_SIGNER_NOT_INITIALIZED    = 0x80880250,
    CAPICOM_E_SIGNER_NOT_FOUND  = 0x80880251,
    CAPICOM_E_SIGNER_NO_CHAIN   = 0x80880252,
    CAPICOM_E_SIGNER_INVALID_USAGE  = 0x80880253,
    CAPICOM_E_SIGN_NOT_INITIALIZED  = 0x80880260,
    CAPICOM_E_SIGN_INVALID_TYPE = 0x80880261,
    CAPICOM_E_SIGN_NOT_SIGNED   = 0x80880262,
    CAPICOM_E_INVALID_ALGORITHM = 0x80880270,
    CAPICOM_E_INVALID_KEY_LENGTH    = 0x80880271,
    CAPICOM_E_ENVELOP_NOT_INITIALIZED   = 0x80880280,
    CAPICOM_E_ENVELOP_INVALID_TYPE  = 0x80880281,
    CAPICOM_E_ENVELOP_NO_RECIPIENT  = 0x80880282,
    CAPICOM_E_ENVELOP_RECIPIENT_NOT_FOUND   = 0x80880283,
    CAPICOM_E_ENCRYPT_NOT_INITIALIZED   = 0x80880290,
    CAPICOM_E_ENCRYPT_INVALID_TYPE  = 0x80880291,
    CAPICOM_E_ENCRYPT_NO_SECRET = 0x80880292,
    CAPICOM_E_NOT_SUPPORTED = 0x80880900,
    CAPICOM_E_UI_DISABLED   = 0x80880901,
    CAPICOM_E_CANCELLED = 0x80880902,
    CAPICOM_E_NOT_ALLOWED   = 0x80880903,
    CAPICOM_E_OUT_OF_RESOURCE   = 0x80880904,
    CAPICOM_E_INTERNAL  = 0x80880911,
    CAPICOM_E_UNKNOWN   = 0x80880999,
    CAPICOM_E_PRIVATE_KEY_NOT_INITIALIZED   = 0x80880300,
    CAPICOM_E_PRIVATE_KEY_NOT_EXPORTABLE    = 0x80880301,
    CAPICOM_E_ENCODE_NOT_INITIALIZED    = 0x80880320,
    CAPICOM_E_EXTENSION_NOT_INITIALIZED = 0x80880330,
    CAPICOM_E_PROPERTY_NOT_INITIALIZED  = 0x80880340,
    CAPICOM_E_FIND_INVALID_TYPE = 0x80880350,
    CAPICOM_E_FIND_INVALID_PREDEFINED_POLICY    = 0x80880351,
    CAPICOM_E_CODE_NOT_INITIALIZED  = 0x80880360,
    CAPICOM_E_CODE_NOT_SIGNED   = 0x80880361,
    CAPICOM_E_CODE_DESCRIPTION_NOT_INITIALIZED  = 0x80880362,
    CAPICOM_E_CODE_DESCRIPTION_URL_NOT_INITIALIZED  = 0x80880363,
    CAPICOM_E_CODE_INVALID_TIMESTAMP_URL    = 0x80880364,
    CAPICOM_E_HASH_NO_DATA  = 0x80880370,
    CAPICOM_E_INVALID_CONVERT_TYPE  = 0x80880380
} CAPICOM_ERROR_CODE;

const ATL::CAtlStringW GetErrorMessage(HRESULT hr, DWORD dwLangId){
    UNUSED(dwLangId);
    ATL::CAtlStringW ret;
    switch(hr){
        case TSPCLI_ERROR_HTTP:
        case OCSPCLI_ERROR_HTTP:
           ret = L"HTTP error occurred while sending request.";
           break;
        case TSPCLI_ERROR_PolicyDeniedAuthType:
        case OCSPCLI_ERROR_PolicyDeniedAuthType:
            ret  = L"Specified authentication type prohibited by group policy.";
            break;
        case TSPCLI_ERROR_PolicyDeniedProxyAuthType:
        case OCSPCLI_ERROR_PolicyDeniedProxyAuthType:
            ret = L"Specified proxy authentication type prohibited by group policy.";
            break;
        case TSPCLI_ERROR_PolicyDeniedURL:
            ret = L"Specified time-stamp authority prohibited by group policy.";
            break;
        case OCSPCLI_ERROR_PolicyDeniedURL:
            ret = L"Specified OCSP server authority prohibited by group policy.";
            break;
        case TSPCLI_ERROR_PolicyDeniedNonce:
            ret = L"Nonce usage prohibited by group policy.";
            break;
        case TSPCLI_ERROR_PolicyDeniedHashAlg:
            ret = L"Specified hash algorithm prohibited by group policy.";
            break;
        case TSPCLI_ERROR_PolicyDeniedPolicyID:
            ret = L"Specified PolicyID prohibited by group policy.";
            break;
        case TSPCLI_ERROR_IncorrectNonce:
            ret = L" The values of request's and stamp's \"Nonce\" fields are not equal.";
            break;
        case TSPCLI_ERROR_AddressIsEmpty:
            ret = L"The URL of TSP service is not specified.";
            break;
        case TSPCLI_ERROR_ExpiredStamp:
            ret = L"The time stamp is expired (ProducedAt value).";
            break;
        case TSPCLI_ERROR_DataHashIsEmpty:
            ret = L"Request does not contain data hash.";
            break;
        case TSPCLI_ERROR_UnsuccessfullResponse:
            ret = L"TSA response is unsuccessful.";
            break;
        case 0xC2100140: //TSPCLI_ERROR_LicenseExpired
            ret = L"No TSP Client license has been entered or TSP Client license is expired.";
            break;
        case OCSPCLI_ERROR_PolicyDeniedSignedRequest:
            ret = L"Signed OCSP requests prohibited by group policy.";
            break;
        case OCSPCLI_ERROR_PolicyDeniedUnsignedRequest:
            ret = L"Unsigned OCSP requests prohibited by group policy.";
            break;
        case OCSPCLI_ERROR_IncorrectNonce:
            ret = L"The values of OCSP-request's and response's \"Nonce\" extensions are not equal.";
            break;
        case OCSPCLI_ERROR_AddressIsEmpty:
            ret = L"The URL of OCSP service is not specified.";
            break;
        case OCSPCLI_ERROR_ExpiredResponse:
            ret = L"OCSP-response is expired by ProducedAt or by NextUpdate.";
            break;
        case OCSPCLI_ERROR_ExpiredThisUpdate:
            ret = L"ThisUpdate value of single response is expired.";
            break;
        case OCSPCLI_ERROR_IncorrectNextUpdate:
            ret = L" NextUpdate value of single response is less than ThisUpdate.";
            break;
        case OCSPCLI_ERROR_ReqRespNotMatch:
            ret = L"OCSP-response does not contain requested certificate status.";
            break;
        case OCSPCLI_ERROR_CertStatusIsRevoked:
            ret = L"Certificate is revoked.";
            break;
        case OCSPCLI_ERROR_CertStatusIsUnknown:
            ret = L"Certificate status is unknown.";
            break;
        case OCSPCLI_ERROR_UnsuccessfullResponse:
            ret = L"OCSP-response is unsuccessful.";
            break;
        case OCSPCLI_ERROR_PolicyDeniedExtension:
            ret = L"Encountered extension (AcceptableTypes or Nonce) prohibited by group policy.";
            break;
        case ERROR_BAD_CONFIGURATION:
            ret = L"The configuration data or license for this product is corrupt or not present.";
            break;
        case 0x8007064a: //License info isn't present
            ret = L"The configuration data or license for this product is corrupt or not present.";
            break;
        case CRYPT_E_REVOKED:
            ret = L"The certificate is revoked.";
            break;
        case ERROR_NO_DATA_DETECTED:
            ret = L"The data you supplied have zero length.";
            break;
        case CRYPT_E_NO_REVOCATION_CHECK:
            ret  =  L"The revocation function was unable to check revocation for the certificate.";
            break;
        case 0x8007006E:
            ret = L"The system cannot open the device or file specified.";
            break;
        case NTE_BAD_ALGID:
        case CRYPT_E_OID_FORMAT: //       oid       UNIX
            ret = L"Invalid algorithm specified.";
            break;
        case REGDB_E_CLASSNOTREG:
            ret = L"Class not registered.";
            break;
        case OLE_E_BLANK:
            ret = L"Uninitialized object.";
            break;
        case CAPICOM_E_STORE_NOT_OPENED:
            ret = L"The Store object does not represent an opened certificate store.";
            break;
        case E_INVALIDARG:
            ret = L"The parameter is incorrect.";
            break;
        case 0x80070002: // returned by OpenStore(Existing) if no store
            ret = L"The system cannot find the file specified.";
            break;
        case E_NOT_VALID_STATE:
            ret = L"The group or resource is not in the correct state to perform the requested operation.";
            break;
        case E_NOTIMPL:
            ret = L"Not implemented.";
            break;
        case ERROR_ALREADY_EXISTS:
            ret = L"Cannot create a file when that file already exists.";
            break;
        case 0x800700B7: //ERROR_ALREADY_EXISTS in HRESULT variant
            ret = L"Cannot create a file when that file already exists.";
            break;
        case NS_E_CURL_INVALIDSCHEME:
            ret = L"The URL contains an invalid scheme.";
            break;
        case SCARD_W_WRONG_CHV:
            ret = L"The private key cannot be accessed because the wrong PIN was presented.";
            break;
        case CRYPT_E_NOT_FOUND:
            ret = L"Cannot find object or property.";
            break;
        case NTE_BAD_SIGNATURE:
            ret = L"Invalid Signature.";
            break;
        case ERROR_DS_INSUFF_ACCESS_RIGHTS:
            ret = L"Insufficient access rights to perform the operation.";
            break;
        case 0x800705B9: //ERROR_XML_PARSE_ERROR in HRESULT variant
            ret = L"The system was unable to parse the requested XML data.";
            break;
        case 0x800705BA: //ERROR_XMLDSIG_ERROR in HRESULT variant
            ret = L"An error was encountered while processing an XML digital signature.";
            break;
        case 0x800B010E: //CERT_E_REVOCATION_FAILURE
            ret = L"The revocation process could not continue - the certificate(s) could not be checked.";
            break;
        case OCSPCLI_ERROR_ResponseWithUnallowedExtension:
            ret = L"OCSP-response contains unallowed critical extension.";
            break;
        case NTE_EXISTS:
            ret = L"Object already exists.";
            break;
        case CRYPT_E_HASH_VALUE:
            ret = L"The hash value is not correct";
            break;
        case OCSPCLI_ERROR_ResponseWithIncorrectTimeStamp:
            ret = L"OCSP Responder time is out of sync with Time Stamping Authority";
            break;
        case OCSPCLI_ERROR_UntrustedSitesDisabled:
            ret = L"Untrusted sites disabled";
            break;
        case 0xC2110140: //OCSPCLI_ERROR_LicenseExpired
            ret = L"No OCSP Client license has been entered or OCSP Client license is expired";
            break;
        case SCARD_E_CARD_UNSUPPORTED:
            ret = eng_wrong_name;
            break;
        case NTE_PERM:
            ret = L"Access denied";
            break;
        case CERT_E_UNTRUSTEDROOT:
            ret = L"A certificate chain processed correctly, but terminated in a root certificate which is not trusted by the trust provider";
            break;
        case CRYPT_E_NO_DECRYPT_CERT:
            ret = L"Cannot find the certificate and private key to use for decryption";
            break;
        default:
            ret = L"Internal error.";
            break;
    }
    return ret;
}
#endif //UNIX
