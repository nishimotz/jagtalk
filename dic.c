/* $Id: dic.c,v 1.4 2006/10/19 03:27:08 sako Exp $                                               */
#include	<stdio.h>
#include	<stdlib.h>
#include	<string.h>

#ifdef WIN32
#include "strings_sjis.h"
#else
#include "strings_eucjp.h"
#endif

int ErrMsg(char *,...);
void restart(int);
char *malloc_char( char *, char * );

typedef struct _dic {
	char *word;		/* ������ */
	char *pron;		/* �ߥʥߥ����� */
	char *psym;		/* �ߥʥߥ��ǥ��� */
	int aType;		/* 4 */
	int len;	/* word �ΥХ���ñ�̤Ǥ�ʸ���� ('\0' ��ޤޤ�) */
} DIC;

static DIC *dic;
static int n_dic_word;
static int dic_size;

void read_dic( char *dfile )
{
	FILE *fp;
	char word[512], pron[512];
	int aType, plen;

	if( dfile == NULL )  return;

	fp = fopen( dfile, "r" );
	if( fp == NULL )  {
		ErrMsg( "* Can not open the dictionary ('%s').\n", dfile );
		return;
	}

	dic_size = 100;  /* �ޤ���100ñ��ʬ�� */
	dic = (DIC *) malloc( sizeof(DIC) * dic_size );
	if( ! dic )  {
		ErrMsg( "* malloc error in read_dic.\n" );
		restart(1);
	}

	n_dic_word = 0;
	while( fscanf( fp, "%s %s %d\n", word, pron, &aType )==3 )  {
		if( dic_size <= n_dic_word )  {
			dic_size += 100;
			dic = realloc( dic, sizeof(DIC) * dic_size );
			if( ! dic )  {
				ErrMsg( "* malloc error in read_dic.\n" );
				restart(1);
			}
		}
		dic[n_dic_word].word = malloc_char( word, "word in dictionary" );
		dic[n_dic_word].pron = malloc_char( pron, "pron in dictionary" );
		dic[n_dic_word].aType = aType;
		dic[n_dic_word].len = strlen( word );
		plen = strlen( pron );
		dic[n_dic_word].psym = malloc( sizeof(char) * (plen+2+1) );
		if( ! dic[n_dic_word].psym )  {
			ErrMsg( "* malloc error in read_dic.\n" );
			restart(1);
		}
		if( aType == 0 )  {
			strcpy( dic[n_dic_word].psym, dic[n_dic_word].pron );
		} else {
			strncpy( dic[n_dic_word].psym, dic[n_dic_word].pron, 2*aType );
			dic[n_dic_word].psym[2*aType] = '\0';
			strcat( dic[n_dic_word].psym, ACCENT_MARK );  /* �֡ǡפε��� */
			strcat( dic[n_dic_word].psym, &(dic[n_dic_word].pron[2*aType]) );
		}
/*
		printf( "%s %s %d %d\n", dic[n_dic_word].word, 
			dic[n_dic_word].psym, dic[n_dic_word].aType, dic[n_dic_word].len );
*/
		++n_dic_word;
	}
/*	printf( "# of words in dictionary: %d\n", n_dic_word );	*/
	fclose( fp );
}

void consult_dic( char *text, int max_text_len )
{
	char *buf, *p, *top;
	int i;

	if( n_dic_word <= 0 )  return;

	buf = (char *) malloc( sizeof(char) * max_text_len );
	if( ! buf )  {
		ErrMsg( "* malloc error in consult_dic.\n" );
		restart(1);
	}

	top = text;
	p = buf;
	while( *top != '\0' )  {
		/* PRON ��������ϼ����Ŭ���ϰϳ��Ȥ��롣*/
		if( strncmp(top,"<PRON ",6)==0 )  {
			/* PRON �����ν�λ�ޤ����Ϥ򥳥ԡ� */
			while( strncmp(top,"</PRON>",7) != 0 )  {
				*(p++) = *(top++);
				if( *top == '\0' )  {
					ErrMsg( "* </PRON> is NOT found input.\n" );
					restart(1);
				}
			}
			continue;
		}

		/* �������Ҥϼ����Ŭ���ϰϳ��Ȥ��롣*/
		if( *top == '<' )  {
			do {
				*(p++) = *(top++);
				if( *top == '\0' )  {
					ErrMsg( "* Tag description is NOT closed by '>'.\n" );
					restart(1);
				}
			} while( *top != '>' );
			continue;
		}

		/* ���Ϥ���Ƭ���鼭���ñ�줴�Ȥ˥ޥå����뤫�ɤ�����Ĵ�٤롣*/
		for( i=0; i<n_dic_word; ++i )  {
			if( strncmp( top, dic[i].word, dic[i].len )==0 )  {
				break;
			}
		}
		if( i < n_dic_word )  {	/* i ���ܤ�ñ��ȥޥå� */
			sprintf( p, "<PRON SYM=\"%s\">%s</PRON>", 
				dic[i].psym, dic[i].word );
			top += dic[i].len;
			while( *p )  ++p;

		} else {		/* ����ȥޥå����Ƥ��ʤ� */
			if (
#ifdef WIN32
		     ( *top >= (char)0x81 && *top <= (char)0x9f )
		     || ( *top >= (char)0xe0 && *top <= (char)0xfc )
#else
		     *top >= (char)0xa1 && *top <= (char)0xf4
#endif
			)  {	/* ����ʸ���ʤ飲ʸ���򥳥ԡ� */
				*(p++) = *(top++);
			}
			*(p++) = *(top++);
		}
		if( p > buf+max_text_len )  {
			ErrMsg( "* Too long input text in consult_dic.\n" );
			free( buf );
			return;
		}
	}
	*p = '\0';
	strcpy( text, buf );
	free( buf );
}
