/*!
* \file $RCSfile$
* \version $Revision$
* \date $Date::                           $
* \author $Author$
*
* \brief Интерфейс для форматирования сообщений об ошибках.
*
* Интерфейс для форматирования сообщений об ошибках.
*/
#ifndef _ERRORMSG_H_INCLUDED
#define _ERRORMSG_H_INCLUDED

#if defined _WIN32
#ifdef __cplusplus
extern "C" {
#endif // __cplusplus
BOOL GetErrorMessage(HRESULT hr, LPWSTR szBuf, DWORD chBufLen, DWORD dwLangId = 0);
#if defined( __cplusplus )
}
#endif /* defined( __cplusplus ) */

#else //_WIN32
const ATL::CAtlStringW GetErrorMessage(HRESULT hr, DWORD dwLangId = 0);
#endif	/* _WIN32 */

#if defined _WIN32 && defined  __CSTRINGT_H__
const ATL::CAtlStringW GetErrorMessage(HRESULT hr, DWORD dwLangId = 0);
#endif // _WIN32 && __CSTRINGT_H__

#endif /* _ERRORMSG_H_INCLUDED */
