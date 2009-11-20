/* Copyright (c) 2002-2006                  */
/*   Studio ARC, ASTEM RI/Kyoto             */
/*   All rights reserved                    */

#include <stdio.h>
#include <comdef.h>
#include <atlbase.h>

#ifdef WIN32
#include <windows.h>

/**
 * MSXML��DLL�Ŏg�p����ꍇ��
 * #define _XSL_DLL_
 * ���`���Ă�������
 */
//#define _XSL_DLL_

#ifndef _XSL_DLL_
#include "msxml2.h"
#endif

#endif // WIN32

#include "chaone.h"

#ifndef _XSL_DLL_
#pragma comment(lib, "msxml2.lib")
#else
#include "synXSLT.h"
#endif

extern "C" {
#include "confpara.h"
int ErrMsg(char *, ...);
int TmpMsg(char *,...);
}

char* XslTransform( char* pszXml );

char* pszXml;

void refresh_chaone()
{
	if( pszXml )
	{
		free( pszXml );
	}
}

// chaone process
char* make_chaone_process( char* pszXmlIn )
{
	char* head = "<?xml version=\"1.0\" encoding=\"Shift_JIS\"?>";

	char* pszIn = NULL;

	pszIn = ( char* ) malloc ( ( strlen( head ) + strlen( pszXmlIn ) + 2 ) * sizeof( char ) );
	memset( pszIn, 0, ( strlen( head ) + strlen( pszXmlIn ) + 2 ) * sizeof( char ) );
	sprintf( pszIn, "%s\n%s", head, pszXmlIn  );

	CoInitialize( NULL );

/**
 * DLL ���g�p����ꍇ�́Achaone.h �� #define _XSL_DLL_ ���`���Ă�������
 */
	/*TmpMsg( "chaone_xsl = %s, pszIn = %s\n", chaone_xsl, pszIn );*/

#ifdef _XSL_DLL_
	char* pszTrans = XslTransform_DLL( pszIn , chaone_xsl );
#else
	char* pszTrans = XslTransform( pszIn );
#endif
	/*TmpMsg( "pszTrans = %s\n", pszTrans );*/

	CoUninitialize( );

	free( pszIn );

	if( pszTrans )
	{
		return pszTrans;
	}
	else
	{
		return pszXmlIn;
	}
}

char* XslTransform( char* pszXmlIn )
{

#ifndef _XSL_DLL_	
	HRESULT			hr;
	VARIANT_BOOL	result;

	// DOM���쐬
	CComPtr<IXMLDOMDocument> xmldom;
	CComPtr<IXMLDOMDocument> xsldom;

	// ������
	pszXml = NULL;

	/*TmpMsg( "XslTransform ...\n" );*/

	// �C���X�^���X�̍쐬
	hr = CoCreateInstance( CLSID_DOMDocument, NULL, CLSCTX_INPROC_SERVER, IID_IXMLDOMDocument, ( void** )&xmldom );
	if( hr != S_OK )
	{
		if( hr == CLASS_E_NOAGGREGATION )
		{
			return NULL;
		}
		if( hr == REGDB_E_CLASSNOTREG )
		{
			return NULL;
		}
		return NULL;
	}
	hr = CoCreateInstance( CLSID_DOMDocument, NULL, CLSCTX_INPROC_SERVER, IID_IXMLDOMDocument, ( void** )&xsldom );
	if( hr != S_OK )
	{
		return NULL;
	}
	// �t�@�C���ǂݍ���
	xmldom->put_async( VARIANT_FALSE );
	xsldom->put_async( VARIANT_FALSE );

	// �����R�[�h�ϊ�����
	WCHAR* lpwXmlstr;

	lpwXmlstr = ( WCHAR* ) malloc ( ( strlen( pszXmlIn ) + 1 ) * sizeof( WCHAR ) * 2 );
	memset( lpwXmlstr, 0, ( strlen( pszXmlIn ) + 1 ) * sizeof( WCHAR ) * 2 );

	MultiByteToWideChar( CP_ACP, 0, pszXmlIn, -1, lpwXmlstr, strlen( pszXmlIn ) * sizeof( WCHAR ) * 2 );

	// XML�̓ǂݍ���
	xmldom->loadXML( lpwXmlstr, &result );
	/*TmpMsg( "loadXML result = %d\n", result );*/
	if( result != VARIANT_TRUE )
	{
	        ErrMsg( "loadXML error (error code %d)\n", result );
		free( lpwXmlstr );
		return NULL;
	}
	
	// XSL�t�@�C���̓ǂݍ���
	xsldom->load( _variant_t( chaone_xsl ), &result );
	/*TmpMsg( "load %s result = %d\n", chaone_xsl, result );*/
	if( result != VARIANT_TRUE )
	{
	        ErrMsg( "load XSL file error (error code %d)\n", result );
		free( lpwXmlstr );
		return NULL;
	}
	// �ϊ�����
	WCHAR* lpbuf = L"";
	xmldom->transformNode( xsldom, &lpbuf );

	if( lpbuf == NULL )
	{
		// �ϊ����s
	        ErrMsg( "transform XSL error\n" );
		free( lpwXmlstr );
		return NULL;
	}

	// �ϊ�������̕����R�[�h�ϊ�����
	int		len		= wcslen( lpbuf ) + 1;
	char*	pszStr	= ( char* ) malloc ( len * 2 );
	memset( pszStr, 0, len * 2  );

	WideCharToMultiByte( CP_ACP, 0, ( LPCWSTR )lpbuf, -1, pszStr, len * 2, NULL, NULL );
	
	// �ϊ��O�̕���������
	free( lpwXmlstr );
	// refresh_chaone() �̂��߂ɃA�h���X��ݒ�
	pszXml = pszStr;

	/*TmpMsg( "XslTransform done: pszStr = %s\n", pszStr );*/

	return pszStr;
#else
	return NULL;
#endif // _XSL_DLL_

}
