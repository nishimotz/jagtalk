/* Copyright (c) 2000-2006                  */
/*   Yamashita Lab., Ritsumeikan University */
/*   All rights reserved                    */
/*                                          */
/* $Id: make_sentence.c,v 1.13 2006/10/19 03:27:08 sako Exp $                                     */

#include	<stdio.h>
#include	<stdlib.h>
#include	<string.h>
#include	"synthesis.h"
#include	"slot.h"

int TmpMsg(char *,...);
int LogMsg(char *,...);
int ErrMsg(char *,...);
void restart(int);
void print_sentence_kanji(SENTENCE *);
void print_sentence_yomi(SENTENCE *);
void print_breath_kanji(BREATH *);
void print_breath_yomi(BREATH *);

/* �ǽ�˰��٤��� */
void init_sentence()
{
	shead = stail = sentence = NULL;
}

/* ����ʸ���Ȥ� */
/* �ȤäƤ빽¤�Τγ��� */
void refresh_sentence()
{
	SENTENCE *sent, *next;

	sent = shead;
	while( sent ) {
		next = sent->next;
		free( sent );
		sent = next;
	}
	shead = stail = sentence = NULL;
}

/* �Ƶ����� breath ��ʸ�� sent ���ɲä��� */
void add_to_sentence( BREATH *breath, SENTENCE *sent )
{
	if( sent->bhead == NULL) {
		/* ����ܤλҶ� */
		sent->bhead = sent->btail = breath;
	} else {
		/* �Ǹ����λҶ��� */
		sent->btail = breath;
	}
	breath->parent = sent;
	sent->nmora += breath->nmora;
	if( breath->silence == NON )  {
		++(sent->nbreath);
		breath->position = sent->nbreath;
	}
}

SENTENCE *new_sentence()
{
	SENTENCE *sent;

	sent = (SENTENCE *) malloc ( sizeof(SENTENCE) );
	if ( ! sent ) {
		ErrMsg(" *malloc error for 'sentence'\n" );
		restart(1);
	}
/* ��ä�ʸ������������������ */
	if( shead == NULL ) {
		/* ��Ĥ�Υ��� */
		shead = stail = sentence = sent;
		sent->prev = sent->next = NULL;
	} else {
		/* tail �θ����ɲ� */
		stail->next = sent;
		sent->prev = stail;
		sent->next = NULL;
		stail = sent;
	}
	sent->nmora = 0;
	sent->nbreath = 0;
	sent->bhead = sent->btail = NULL;

	return sent;
}

void make_sentence()
{
	SENTENCE *sent=NULL;
	BREATH *breath;
	MORPH *morph;

	for( breath = bhead; breath; breath = breath->next) {
	  	if( sent == NULL || breath->silence == SILB )  {
			sent = new_sentence();
		}
		add_to_sentence( breath, sent );
	}

	for( morph = mphead; morph; morph = morph->next )  {
		if( morph->silence != SILB && morph->silence != SILE &&
			morph->silence != PAU )
			strcat( spoken_text, morph->kanji );
	}
}

void print_sentence()
{
	int 	n;
	SENTENCE *s;

	LogMsg( "* sentence data\n" );
	n = 0;
	for( s=shead; s; s=s->next )  {
		LogMsg( "(%d) ", n+1 );
		print_sentence_kanji( s );
		LogMsg( "\n" );
/*
		LogMsg( "(%d) ", n+1 );
		print_sentence_yomi( s );
		LogMsg( "\t%d\n", s->nmora );
*/
		++n;
	}
	LogMsg( "- n_sentence: %d\n", n );
}

void print_sentence_kanji( SENTENCE *s )
{
	BREATH *b;
	for( b=s->bhead; b && b->parent==s; b=b->next) {
		print_breath_kanji(b);
	}
}

void print_sentence_yomi( SENTENCE *s )
{
	BREATH *b;
	for( b=s->bhead; b && b->parent==s; b=b->next) {
		print_breath_yomi(b);
	}
}
