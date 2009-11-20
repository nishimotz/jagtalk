/* Copyright (c) 2000-2006                  */
/*   Yamashita Lab., Ritsumeikan University */
/*   All rights reserved                    */
/*                                          */
/* $Id: make_phoneme.c,v 1.15 2006/10/19 03:27:08 sako Exp $                                     */

#include	<stdio.h>
#include	<stdlib.h>
#include	<string.h>
#include	"synthesis.h"
#include	"pronunciation.h"
#include	"confpara.h"

int TmpMsg(char *,...);
int LogMsg(char *,...);
int ErrMsg(char *,...);
void restart(int);
void print_mora();

static char **phonemeList;
static int n_phoneme;

#define is_unvoice(p) (( (p)==ph_k  || (p)==ph_s  || (p)==ph_sh || \
                         (p)==ph_t  || (p)==ph_ch || (p)==ph_ts || \
                         (p)==ph_h  || (p)==ph_f  || (p)==ph_p  || \
                         (p)==ph_ky || (p)==ph_hy || (p)==ph_py ))

#define is_voice(p) (( (p)==a  || (p)==i  || (p)==u || \
                       (p)==e  || (p)==o ))

static char *ph_i  = NULL, *ph_u  = NULL;
static char *ph_I  = NULL, *ph_U  = NULL;
static char *ph_k  = NULL, *ph_s  = NULL, *ph_sh = NULL;
static char *ph_t  = NULL, *ph_ch = NULL, *ph_ts = NULL;
static char *ph_h  = NULL, *ph_f  = NULL, *ph_p  = NULL;
static char *ph_ky = NULL, *ph_hy = NULL, *ph_py = NULL;
static char *ph_sil = NULL;

char *get_phoneme( char *phm )
{
	int i;

	for( i=0; i<n_phoneme; ++i )  {
		if( strcmp(phm,phonemeList[i])==0 )  {
			return phonemeList[i];
		}
	}
	ErrMsg( "* Unknown phoneme ... '%s'\n", phm );
	restart(1);
	return NULL;
}

void read_phonemes( char *pfile )
{
	FILE *fp;
	char line[256];
	int n;

	fp = fopen( pfile, "r" );
	if( fp == NULL )  {
		ErrMsg( "* Open error ... %s\n", pfile );
		return;
	}

/* ���ǿ��γ�ǧ */
	n = 0;
	while( fgets( line, 256, fp ) != NULL )  {
		++n;
	}
	rewind( fp );

/* �ΰ���� */
	phonemeList = (char **) malloc( n*sizeof(char *) );
	if( ! phonemeList )  {
		ErrMsg( "* malloc error for 'phonemeList'\n" );
		return;
	}
	n = 0;
	while( fgets( line, 256, fp ) != NULL )  {
/*		phonemeList[n] = (char *) malloc( sizeof(char) * (strlen(line)+1) ); */
		/* ������ '\n' ������Τǡ�(strlen(line)) �Х��ȤǤ褤 */
		phonemeList[n] = (char *) malloc( sizeof(char) * (strlen(line)) );
		if( ! phonemeList[n] )  {
			ErrMsg( "* malloc error for 'phonemeList[%d]'\n", n );
			return;
		}
/*		strcpy( phonemeList[n], line );		*/
		sscanf( line, "%s\n", phonemeList[n] );
		++n;
	}
	n_phoneme = n;
#ifdef PRINTDATA
	TmpMsg( "# of phonemes: %d\n", n_phoneme );
#endif
	fclose( fp );

	ph_i  = get_phoneme( "i" );
	ph_u  = get_phoneme( "u" );
	ph_I  = get_phoneme( "I" );		/* ̵�����첻 */
	ph_U  = get_phoneme( "U" );		/* ̵�����첻 */
	ph_k  = get_phoneme( "k" );
	ph_s  = get_phoneme( "s" );
	ph_sh = get_phoneme( "sh" );
	ph_t  = get_phoneme( "t" );
	ph_ch = get_phoneme( "ch" );
	ph_ts = get_phoneme( "ts" );
	ph_h  = get_phoneme( "h" );
	ph_f  = get_phoneme( "f" );
	ph_p  = get_phoneme( "p" );
	ph_ky = get_phoneme( "ky" );
	ph_hy = get_phoneme( "hy" );
	ph_py = get_phoneme( "py" );
	ph_sil = get_phoneme( "sil" );
}

/* �ǽ�˰��٤��� */
void init_phoneme()
{
	phhead = phtail = NULL;
}

/* ����ʸ���Ȥ� */
/* �ȤäƤ��벻�ǤΥ���γ��� */
void refresh_phoneme()
{
	PHONEME *phoneme, *next;

	phoneme = phhead;
	while( phoneme )  {
		next = phoneme->next;
		free( phoneme );
		phoneme = next;
	}
	phhead = phtail = NULL;
}

/* ʸ���� p ����ǥ�ߥ��ޤǤ�ʸ���� data �����졢���ξ����֤� */
static char *get_token( char *p, char *data )
{
	if( *p == '\0' )  return NULL;

	while( *p != ' ' && *p != '\0' )  {
		*(data++) = *(p++);
	}
	*data = '\0';
	if( *p == ' ' )  ++p;
	return p;
}

void kana2phoneme( char *kana, char *phms )
{
	int 	i;

	if( strcmp(kana,"pau")==0 )  {
		strcpy( phms, "pau" );
		return;
	}

	for( i=0; i<NUM_KANA; ++i )  {
		if( strcmp(kana,prnTable[i].kana)==0 )  {
			strcpy( phms, prnTable[i].phonemes );
			return;
		}
	}
	ErrMsg( "* Unknown KANA ... %s\n", kana );
	strcpy( phms, "pau" );
	return;
/*	restart(1);	*/
}

/* ���� phoneme ��⡼�� mora ���ɲä��� */
void add_to_phoneme( MORA *mora, PHONEME *phoneme )
{
	if( mora->phead == NULL )  {
		/* ��Ĥ�λҶ� */
		mora->phead = mora->ptail = phoneme;
	} else {
		/* �Ǹ����λҶ��� */
		mora->ptail = phoneme;
	}
	phoneme->parent = mora;
}

PHONEME *new_phoneme()
{
	PHONEME	*phoneme;

	phoneme = (PHONEME *) malloc( sizeof(PHONEME) );
	if( ! phoneme )  {
		ErrMsg( "* malloc error for 'phoneme'\n" );
		restart(1);
	}
/* ��ä����ǥ�������������������� */
	if( phhead == NULL )  {
		/* ��Ĥ�Υ��� */
		phhead = phtail = phoneme;
		phoneme->prev = phoneme->next = NULL;
	} else {
		/* tail �θ����ɲ� */
		phtail->next = phoneme;
		phoneme->prev = phtail;
		phoneme->next = NULL;
		phtail = phoneme;
	}
	phoneme->parent = NULL;

	phoneme->phoneme = NULL;
	phoneme->time = 0.0;
	phoneme->sid = spid;
	phoneme->alpha = speaker[spid].alpha;

	return phoneme;
}

void do_devoicing()
{
	MORPH *m;
	PHONEME	*p;

	/* �ݡ��������Ρ֤ޤ��ס֤Ǥ��פ�̵���������롣*/
	for( m=mphead; m->next; m=m->next )  {
		if( m->next->silence == NON )  continue;

		if( m->mrtail == NULL )  continue;		/* �֡פʤɡ�*/

		if( strcmp(m->mrtail->yomi,"��")==0 &&
			strcmp(m->mrtail->prev->yomi,"��")==0 )  {
				m->mrtail->ptail->phoneme = ph_U;
				m->mrtail->devoiced = YES;
		} else if( strcmp(m->mrtail->yomi,"��")==0 &&
			strcmp(m->mrtail->prev->yomi,"��")==0 )  {
				m->mrtail->ptail->phoneme = ph_U;
				m->mrtail->devoiced = YES;
		}
	}

	/* ��Բ��Ǥ�̵�����ǡ���³���Ǥ�̵������ /i/, /u/ ��̵�����첻 */

	for( p=phtail; p; p=p->prev )  {
/*  for( p=phhead; p; p=p->next )  { */

		/* ̵���������첻�� /i/ �� /u/ ���� */
		if( p->phoneme != ph_i && p->phoneme != ph_u )  continue;

		/* ��Բ��ǤΥ����å� */
		if( ! is_unvoice(p->prev->phoneme) )  continue;

		/* ��³���ǤΥ����å� */
		if( ! is_unvoice(p->next->phoneme) )  continue;

		/* ³����̵���������ʤ� */
		if( p->parent->next->devoiced == YES )  continue;
/* 		if( p->parent->prev->devoiced == YES )  continue;	*/

		p->parent->devoiced = YES;
		if( p->phoneme == ph_i )  {
			p->phoneme = ph_I;
		} else if( p->phoneme == ph_u )  {
			p->phoneme = ph_U;
		}
	}
}

void make_phoneme()
{
	MORA *mora;
	PHONEME	*phoneme;
	char phms[16], phm[8], *p;

	for( mora=mrhead; mora; mora=mora->next )  {
		if( mora->silence == SILB || mora->silence == SILE) {
			phoneme = new_phoneme();
			add_to_phoneme(mora,phoneme);
			phoneme->phoneme = get_phoneme( "sil" );
		} else if( mora->chouonka == YES )  {
			phoneme = new_phoneme();
			add_to_phoneme( mora, phoneme );
			/* ������β��Ǥ�Ʊ�� */
			phoneme->phoneme = phoneme->prev->phoneme;
		} else {
			kana2phoneme( mora->yomi, phms );
			p = phms;
			while( (p=get_token(p, phm)) )  {
				phoneme = new_phoneme();
				add_to_phoneme( mora, phoneme );
				phoneme->phoneme = get_phoneme( phm );
			}
		}
	}
	do_devoicing();
/*	print_mora();	*/
}

void print_phoneme()
{
	PHONEME	*p;

	LogMsg( "* phoneme data\n" );
	for( p=phhead; p; p=p->next )  {
		LogMsg( "%s ", p->phoneme );
	}
	LogMsg( "\n" );
}
