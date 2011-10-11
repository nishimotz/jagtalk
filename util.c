/* Copyright (c) 2000-2006                  */
/*   Yamashita Lab., Ritsumeikan University */
/*   All rights reserved                    */
/*                                          */
/* $Id: util.c,v 1.15 2009/02/12 17:43:42 sako Exp $                                     */
/* UTF-8 support by Takuya Nishimoto (nishimotz.com) */

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include "confpara.h"

#ifdef UTF8
# include <iconv.h>
# define ICONV_BUFSIZE 4096
#endif

void restart(int);
int ByteSwap( void *, int, int);

/*******↓for server mode *******/
int server_send ( char *message );
extern int s_mode;
/*******↑***********************/

/* to report messages to Control Unit */


static void eucjp_to_utf8(char *orig_buf, char *buf)
{
  iconv_t m_iconv = iconv_open("UTF-8", "EUC-JP"); // tocode, fromcode
  size_t in_size = (size_t)ICONV_BUFSIZE;
  size_t out_size = (size_t)ICONV_BUFSIZE;
  char *in = orig_buf;
  char *out = buf;
  iconv(m_iconv, &in, &in_size, &out, &out_size);
  iconv_close(m_iconv);
}

int RepMsg(char *fmt, ...)
{
# ifdef UTF8
	va_list ap;
	int error;
        char orig_buf[ICONV_BUFSIZE];
        char buf[ICONV_BUFSIZE];

	va_start( ap, fmt );
	error = vsprintf( orig_buf, fmt, ap );
	va_end( ap );
	eucjp_to_utf8(orig_buf, buf);
        fputs( buf, stdout );
	fflush( stdout );
# else
	va_list ap;
	int error;

	va_start( ap, fmt );
	error = vfprintf( stdout, fmt, ap );
	fflush( stdout );
	va_end( ap );
# endif	
	/*******↓for server mode *******/
	if ( s_mode ) {
	        char *chrMsg;
		
    	        if( error > 0 ) {
		        chrMsg = (char*)malloc((error + 4) * sizeof(char*));
			va_start( ap, fmt );
			error = vsprintf( chrMsg, fmt, ap );
			va_end( ap );
		    
			if( error > 0 ) {
			        strcat( chrMsg, "./\n" );
			        server_send( chrMsg );
			}
			
			free(chrMsg);
	        }
	}
	/*******↑***********************/
	
	return( error );
}

/* to print messages to debug */

int TmpMsg(char *fmt, ...)
{
	va_list ap;
	int error;

	va_start( ap, fmt );
	error = vfprintf( stderr, fmt, ap );
	fflush( stderr );
	va_end( ap );
	return( error );
}

/* to log messages to debug */

int LogMsg(char *fmt, ...)
{
#ifdef UTF8
	va_list ap;
	int error;
        char orig_buf[ICONV_BUFSIZE];
        char buf[ICONV_BUFSIZE];

	va_start( ap, fmt );
	error = vsprintf( orig_buf, fmt, ap );
	va_end( ap );
	eucjp_to_utf8( orig_buf, buf );
	fputs( buf, logfp );
	fflush( logfp );
	return( error );
#else
	va_list ap;
	int error;

	va_start( ap, fmt );
	error = vsprintf( orig_buf, fmt, ap );
	va_end( ap );
	fflush( logfp );
	return( error );
#endif
}

/* to log error messages */

FILE *fp_err;

int ErrMsg(char *fmt, ...)
{
#ifdef UTF8
	va_list ap;
	int error;
        char orig_buf[ICONV_BUFSIZE];
        char buf[ICONV_BUFSIZE];

	va_start( ap, fmt );
	error = vsprintf( orig_buf, fmt, ap );
	va_end( ap );
	eucjp_to_utf8( orig_buf, buf );
	fputs( buf, fp_err );
	fflush( fp_err );
	return( error );
#else
	va_list ap;
	int error;

	va_start( ap, fmt );
	error = vfprintf( fp_err, fmt, ap );
	va_end( ap );
	fflush( fp_err );
	return( error );
#endif
}

char* malloc_char( char* str, char *str_name )
{
	char *p;

	p = (char *) malloc( sizeof(char) * (strlen(str)+1) );
	if( ! p )  {
		ErrMsg( "* malloc error in '%s'\n", str_name );
		restart(1);
	}
	strcpy( p, str );
	return p;
}

/* 合成音声データの書き出しに使う。 */
/* BIG ENDIAN での書き出しを行う。もとのメモリ内容は保存しておく。 */
int xfwrite(void *p, int size, int num, FILE *fp){
	int block;
	void *tmp;

#ifdef WORDS_LITTLEENDIAN
	tmp = malloc( size*num );
	if( ! tmp )  {
		ErrMsg( "* malloc error in xfwrite\n" );
		restart(1);
	}
	memcpy( tmp, p, size*num );
	ByteSwap( tmp, size, num );
#else
/* BIG_ENDIAN */
	tmp = p;
#endif

	block = fwrite( tmp, size, num, fp);

#ifdef WORDS_LITTLEENDIAN
	free( tmp );
#endif

	return block;
}

/* 合成音声データの書き出しに使う。 */
/* LITTLE ENDIAN での書き出しを行う。もとのメモリ内容は保存しておく。 */
int xfwrite_LE(void *p, int size, int num, FILE *fp){
	int block;
	void *tmp;

#ifndef WORDS_LITTLEENDIAN
	tmp = malloc( size*num );
	if( ! tmp )  {
		ErrMsg( "* malloc error in xfwrite\n" );
		restart(1);
	}
	memcpy( tmp, p, size*num );
	ByteSwap( tmp, size, num );
#else
/* BIG_ENDIAN */
	tmp = p;
#endif

	block = fwrite( tmp, size, num, fp);

#ifndef WORDS_LITTLEENDIAN
	free( tmp );
#endif

	return block;
}

int xfread(void *p, int size, int num, FILE *fp)
{
	int block;

	block = fread( p, size, num, fp);

#ifdef WORDS_LITTLEENDIAN
	ByteSwap( p, size, block);
#endif /* !BIG_ENDIAN */

	return block;
}

int xfread_LE(void *p, int size, int num, FILE *fp)
{
	int block;

	block = fread( p, size, num, fp);

#ifndef WORDS_LITTLEENDIAN
	ByteSwap( p, size, block);
#endif /* !BIG_ENDIAN */

	return block;
}

int ByteSwap( void *p, int size, int blocks)
{
        char *q, tmp;
        int i, j;

        q = (char *)p;

        for( i = 0; i < blocks; i++){
                for( j = 0; j < (size/2); j++){
                        tmp = *(q+j);
                        *(q+j) = *(q+(size-1-j));
                        *(q+(size-1-j)) = tmp;
                }
                q += size;
        }
        return i;
}

#if defined(WIN32) || defined(USE_CHASENLIB)

int snprintf( char *str, size_t size, const char *fmt, ... )
{
	va_list ap;
	int error;

	va_start( ap, fmt );
	error = vsprintf( str, fmt, ap );
	va_end( ap );
	return( error );
}

#endif

