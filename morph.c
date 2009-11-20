/* Copyright (c) 2000-2006                  */
/*   Yamashita Lab., Ritsumeikan University */
/*   All rights reserved                    */
/*                                          */
/* $Id: morph.c,v 1.30 2006/10/19 03:27:08 sako Exp $                                     */

#include	<stdio.h>
#include	<stdlib.h>
#include	<string.h>
#include	"synthesis.h"
#include	"tag.h"

#define INIT_HINSHI_DATA_TABLE
#include	"pos.h"

int match_hinshi(char *,char *);
int match_katsuyougata(char *,char *);
int match_katsuyoukei(char *,char *);
int TmpMsg(char *,...);
int LogMsg(char *,...);
int ErrMsg(char *,...);
void restart(int);
char *malloc_char( char *, char * );
void parse_aConType( char *, MORPH * );
void print_morph_yomi(MORPH *);
void make_sil_morph( SILENCE );
void refresh_mora();
char *aformName( int );
int attributeID(char *);

/* �ǽ�˰��٤��� */
void init_morph()
{
	mphead = mptail = NULL;
}

void free_submorph( MORPH *morph )
{
	MORPH *next;

	while( morph )  {
		next = morph->next;
		free( morph->kanji );
		if( morph->pron != NULL )  free( morph->pron );
		free( morph );
		morph = next;
	}
}

/* ����ʸ���Ȥ� */
/* �ȤäƤ�������ǤΥ���γ��� */
void refresh_morph()
{
	MORPH *morph, *next;

	morph = mphead;
	while( morph )  {
		next = morph->next;
		free( morph->kanji );
		if( morph->pron != NULL )  free( morph->pron );
		if( morph->submorph != NULL )  free_submorph( morph->submorph );
		free( morph );
		morph = next;
	}
	mphead = mptail = NULL;
}

/* �ʻ�ʬ��μ��Ф� */
int hinshiID( char *h )
{
	int 	i;
	for( i=0; i<NUM_HINSHI; ++i )  {
		if( match_hinshi( h, hinshiTable[i].name ) )  return hinshiTable[i].id;
	}
	ErrMsg( "Unknown hinshi ... %s\n", h );
	return( H_MEISHI );
/*	restart(1);	*/
/*	return -1;	*/
}

int match_hinshi( char *h, char *hname )
{
	/* ��Ͽ����Ƥ����ʻ�̾����Ƭ����ȹ硣�Ĥ��̵�뤹�롣*/
	while( *hname  )  {
		if( *h != *hname )  return 0;
		++h;  ++hname;
	}
	return 1;	/* matched */
}

/* ���ѷ�ʬ��μ��Ф� */
int katsuyogataID( char *h )
{
	int 	i;
	for( i=0; i<NUM_KATSUYOUGATA; ++i )  {
		if( match_katsuyougata( h, katsuyougataTable[i].name ) )
		  return katsuyougataTable[i].id;
	}
	ErrMsg( "Unknown katsuyougata ... %s\n", h );
	return( -1 );
}

int match_katsuyougata( char *h, char *kname)
{
	/* ��Ͽ����Ƥ�����ѷ�̾����Ƭ����ȹ硣�Ĥ��̵�뤹�롣*/
	while( *kname  )  {
		if( *h != *kname )  return 0;
		++h;  ++kname;
	}
	return 1;	/* matched */
}

/* ���ѷ�ʬ��μ��Ф� */
int katsuyokeiID( char *k )
{
	int 	i;
	for( i=0; i<NUM_KATSUYOUKEI; ++i )  {
		if( match_katsuyoukei( k, katsuyoukeiTable[i].name ) )
		  return katsuyoukeiTable[i].id;
	}
	ErrMsg( "Unknown katsuyoukei ... %s\n", k );
	return( -1);
}

int match_katsuyoukei( char *h, char *kname)
{
	/* ��Ͽ����Ƥ�����ѷ�̾����Ƭ����ȹ硣�Ĥ��̵�뤹�롣*/
	while( *kname  )  {
		if( *h != *kname )  return 0;
		++h;  ++kname;
	}
	return 1;	/* matched */

}

void init_morph_data( MORPH *morph, SILENCE sil )
{
	int i;

	morph->parent = atail;

	morph->kanji = NULL;
	morph->pron = NULL;
	morph->nmora = 0;
	morph->nbyte = 0;
	morph->hinshiID = -1;
	morph->katsuyogataID = -1;
	morph->katsuyokeiID = -1;
	morph->accentType = -1;
	morph->n_accent = 0;
	for( i=0; i<MAX_ACCENT; ++i )  {
		morph->accent[i].prepos = '-';
		morph->accent[i].form = -1;
		morph->accent[i].ctype = -999;
		morph->accent[i].ctype2 = -999;
	}
	morph->submorph = NULL;
	morph->silence = sil;
	morph->mrhead = morph->mrtail = NULL;
}

MORPH *new_morph(SILENCE sil)
{
	MORPH *morph;

	morph = (MORPH *) malloc( sizeof(MORPH) );
	if( ! morph )  {
		ErrMsg( "* malloc error for 'morph'\n" );
		restart(1);
	}

/* ��ä������ǥ�������������������� */
	if( mphead == NULL )  {
		/* ��Ĥ�Υ��� */
		mphead = mptail = morph;
		morph->prev = morph->next = NULL;
	} else {
		/* tail �θ����ɲ� */
		mptail->next = morph;
		morph->prev = mptail;
		morph->next = NULL;
		mptail = morph;
	}
	init_morph_data( morph, sil );

	return morph;
}

/*-----------------------------------------------------------------------*/

/* ���ϹԤϡ�
	<W2 orth="�ռ�����" pron="�������եᥤ" accent="1" 
		pos="̾��-����̾��-�������ǽ" aType="1">
�η����ǡ�ʣ���ǡ�����
aType �ϼ���ǤΥ�������ȷ���accent �Ϥ���ȯ�äǤΥ�������ȷ���
W2�ǡ������Ĥ� morph �ǡ����Ȥ��ư����� */

int open_W2( int n_op, TAGOPTIONS *op )
{
	int 	i, nbyte;
	char	*attr, *val;
	MORPH	*morph;
	APHRASE	*ap;

	ap = atail;

	/* ����ܰʹߤ�ʸ�λϤޤ� */
	if( mptail->silence == SILE )  make_sil_morph( SILB );

	morph = new_morph( ap->silence );

	nbyte = 0;
	for( i=0; i<n_op; ++i )  {
		attr = op[i].attr;   val = op[i].val;
/*		TmpMsg( "%s='%s'\n", attr, val );	*/
		switch( attributeID( attr ) )  {
		case W_ORTH:
			morph->kanji = malloc_char( val, "morph.kanji" );
			nbyte = morph->nbyte = strlen( val );
			break;
		case W_PRON:
			morph->pron = malloc_char( val, "morph.pron" );
			break;
		case W_POS:
			morph->hinshiID = hinshiID( val );
			break;
		case W_C_TYPE:
			morph->katsuyogataID = katsuyogataID( val );
			break;
		case W_C_FORM:
			morph->katsuyokeiID = katsuyokeiID( val );
			break;
		case W_A_TYPE:
			morph->accentType = ( val[0]=='\0' ) ? 0 : atoi( val );
			break;
		case W_A_CON_TYPE:
	        parse_aConType( val, morph );
			break;
		default:
/*			ErrMsg( "Unknown option ... %s='%s'\n", attr, val );	*/
			break;
		}
/*		if( strcmp("��",kanji)==0 )  break;	*/
	}

	if( ap->mphead == NULL )  {	/* ��������ȶ����Ƭ������ */
		ap->mphead = morph;
	}
	ap->mptail = morph;

	return( nbyte );
}

void close_W2()
{
}

void proc_W1( int n_op, TAGOPTIONS *op )
{
}

/* ̵�����򣱷����ǡ����⡼��Ȥ��ƺ��� */
void make_sil_morph( SILENCE sil )
{
	char sil_str[5];
	MORPH *morph, *new_morph();

	if( sil == SILB )  {
		strcpy( sil_str, "silB" );
	} else if( sil == SILE )  {
		strcpy( sil_str, "silE" );
	} else if( sil == PAU )  {
		strcpy( sil_str, "pau" );
	} else {
		ErrMsg( "* Unknown silence in make_sil_morph\n" );
		strcpy( sil_str, "pau" );
/*		restart(1);	*/
	}

	morph = new_morph( sil );
	morph->kanji = malloc_char( sil_str, "morph.kanji of SILENCE" );
}

/*------------------------------------------------------------*/

void print_hinshi_name( int hid )
{
	int 	i;
	for( i=0; i<NUM_HINSHI; ++i )  {
		if( hinshiTable[i].id == hid )  {
		  LogMsg( "%s", hinshiTable[i].name );
		  return;
		}
	}
}

void print_aConType( MORPH *morph )
{
	int i;

	if( morph->n_accent == 0 )  {
		LogMsg( "\t-" );
		return;
	}
	for( i=0; i<morph->n_accent; ++i )  {
		if( i == 0 )  {
			LogMsg( "\t" );
		} else {
			LogMsg( "," );
		}
		LogMsg( "%c%%%s", morph->accent[i].prepos, 
			aformName( morph->accent[i].form ) );
	}
}


void print_morph()
{
	int 	n;
	MORPH	*morph;

	LogMsg( "* morph data\n" );
	LogMsg( "(orth\tpron\tPOS\t[accent]\taConType\tmora)\n" );
	n = 0;
	for( morph=mphead; morph; morph=morph->next )  {
		LogMsg( "%s\t", morph->kanji );
		print_morph_yomi( morph );
/*		LogMsg( "%s", morph->pron );	*/
		LogMsg( "\t" );
		print_hinshi_name( morph->hinshiID );
		LogMsg( ":%d/%d/%d\t[%d]", 
			morph->hinshiID, 
			morph->katsuyogataID, morph->katsuyokeiID, 
			morph->accentType );
		print_aConType( morph );
		LogMsg( "\t%d\n", morph->nmora );
		++n;
	}
	LogMsg( "- n_morph: %d\n", n );
}

void print_morph_yomi( MORPH *morph )
{
	MORA	*m;

	if( morph->mrhead == NULL )  {
		LogMsg( "-" );
		return;
	}
	for( m=morph->mrhead; m && m->parent==morph; m=m->next )  {
		LogMsg( "%s", m->yomi );
	}
}
