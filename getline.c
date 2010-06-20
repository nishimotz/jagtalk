/* Copyright (c) 2000-2006                  */
/*   Yamashita Lab., Ritsumeikan University */
/*   All rights reserved                    */
/*                                          */
/*  $Id: getline.c,v 1.6 2006/10/19 03:27:08 sako Exp $                                    */

#include <stdio.h>
#include <string.h>
#ifdef HAVE_READLINE
#include <readline/readline.h>
#include <readline/history.h>
#endif

#ifdef HAVE_READLINE

int g_getline( char *buf, int MAX_LENGTH )
{
	char *s;
	int p;

	s = readline( NULL );
	if( s == NULL) return -1;

	strncpy( buf, s, MAX_LENGTH-1);
	free( s );

	buf[MAX_LENGTH-1] = '\0';
	p = strlen( buf );
	if( buf[p-1] == '\n' )  buf[p-1] = '\0';
	add_history( buf );

	return p;
}
 
#else  /* ~HAVE_READLINE */

# ifdef UTF8
#  include <iconv.h>
#  define ICONV_BUFSIZE 4096
# endif

int g_getline( char *buf, int MAX_LENGTH )
{
# ifdef UTF8
        char read_buf[ICONV_BUFSIZE];
	fgets( read_buf, ICONV_BUFSIZE, stdin );
	if( read_buf == NULL) return -1;
        iconv_t m_iconv = iconv_open("EUC-JP", "UTF-8"); // tocode, fromcode
        size_t in_size = (size_t)ICONV_BUFSIZE;
        size_t out_size = (size_t)MAX_LENGTH;
        char *in = read_buf;
        char *out = buf;
        iconv(m_iconv, &in, &in_size, &out, &out_size);
        iconv_close(m_iconv);
	int p = strlen( buf ) - 1;
	if( buf[p] == '\n' )  buf[p] = '\0';
	return p;
# else
	int p;

	fgets( buf, MAX_LENGTH, stdin );
	if( buf == NULL) return -1;
 	p = strlen( buf ) - 1;
	if( buf[p] == '\n' )  buf[p] = '\0';

	return p;
# endif
}

#endif /* HAVE_READLINE */

