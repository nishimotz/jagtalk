/* Copyright (c) 2000-2006                  */
/*   Yamashita Lab., Ritsumeikan University */
/*   All rights reserved                    */
/*                                          */
/* $Id: chasen.c,v 1.13 2006/10/19 03:27:08 sako Exp $                                     */

#include	<stdio.h>
#include	<stdlib.h>
#include	<string.h>
#include	"confpara.h"

int TmpMsg(char *,...);
int ErrMsg(char *,...);
void restart(int);

int chasen_process = 0;

char chasen_rc_option[] = "-r";

#if defined(USE_CHASENLIB) || defined(USE_SPLIB)
#include "chasen_lib.c"
#else

#include	<unistd.h>

#ifdef MACOSX
typedef struct _pipe_chain {
	char *command[100];
	int last;	/* 最後のプロセスのみ 1 にする。他は 0 に。*/
} PIPE_CHAIN;

PIPE_CHAIN pchain[4];
#else
typedef struct _pipe_chain {
	char *command[20];
	int last;	/* 最後のプロセスのみ 1 にする。他は 0 に。*/
} PIPE_CHAIN;

PIPE_CHAIN pchain[3];
#endif

/*
#define CHASEN "/usr/local/bin/chasen"
#define CHASENRC "chasenrc"

PIPE_CHAIN pchain[] = {
	{ { CHASEN, "-r", CHASENRC, (char *)0 }, 0 },
	{ { CHAONE, (char *)0 }, 0 },
	{ { POSTP, (char *)0 }, 1 }
};
*/

int make_pipe_child(PIPE_CHAIN *,int *);

void set_command( char *str, char *command[] )
{
	int i;
	char *c;

	command[0] = str;
	i = 1;  c = str+1;
	while( *c != '\0' )  {
		if( *c == ' ' || *c == '\t' )  *c = '\0';
		if( *(c-1) == '\0' && *c != ' ' && *c != '\t' )  {
			command[i] = c;
			++i;
		}
		++c;
	}
	command[i] = '\0';
}

int make_chasen_process( CHASEN_FD *fd_in, CHASEN_FD *fd_out )
{
#ifdef MACOSX
	int to_parent[2];

	if( chasen_process != 0 )  return 0;

#if 0
	pchain[0].command[0] = "/opt/local/bin/nkf";
	pchain[0].command[1] = "-Ew";
	pchain[0].command[2] = '\0';
	pchain[0].last = 0;	
	pchain[1].command[0] = "/opt/local/bin/chasen";
	pchain[1].command[1] = "-r";
	pchain[1].command[2] = "chasenrc-utf8-macosx";
	pchain[1].command[3] = "-i";
	pchain[1].command[4] = "w";
	pchain[1].command[5] = '\0';
	pchain[1].last = 0;
	pchain[2].command[0] = "/opt/local/bin/nkf";
	pchain[2].command[1] = "-We";
	pchain[2].command[2] = '\0';
	pchain[2].last = 0;	
	pchain[3].command[0] = "/usr/local/bin/chaone";
	pchain[3].command[1] = "-s";
	pchain[3].command[2] = "gtalk";
	pchain[3].command[3] = "--encoding";
	pchain[3].command[4] = "EUC-JP";
	pchain[3].command[5] = '\0';
	pchain[3].last = 1;	
# else
	pchain[0].command[0] = "./run-chasen-macosx.sh";
	pchain[0].command[1] = '\0';
	pchain[0].last = 1;	
#endif
#else
	int to_parent[2];

	if( chasen_process != 0 )  return 0;

	pchain[0].command[0] = chasen_bin;
	pchain[0].command[1] = chasen_rc_option;
	pchain[0].command[2] = chasen_rc;
	pchain[0].command[3] = '\0';
	if( chaone_bin[0] == '\0' )  {
		pchain[0].last = 1;		/* set 1 if this process is the last */
	} else {
		pchain[0].last = 0;
		set_command( chaone_bin, pchain[1].command );
		pchain[1].last = 1;	
	}
#endif

	/* to_parent は「最後の子 -> 親」で使う。*/
	if( pipe(to_parent) < 0 )  {
		ErrMsg( "pipe error in init_text_analysis\n" );
		return -1;
	}

	/* 親が書き込むfdはこのルーチンの中で決まる。*/
	*fd_out = make_pipe_child( pchain, to_parent );
	if( *fd_out < 0 )  return -1;

	*fd_in = to_parent[0];		/* 親はここから読み出す。*/
	close( to_parent[1] );		/* 親はここへは書かない。*/
	chasen_process = 1;
#ifdef PRINTDATA
	TmpMsg( "* chasen start.\n" );
#endif
	return 0;
}

/* 子へ書き込むときのfdを返す。 */
int make_pipe_child( PIPE_CHAIN *pc, int *to_parent )
{
	pid_t pid;
	int to_child[2], out;

	/* to_child は「親 -> 子」で使う。*/
	if( pipe(to_child) < 0 )  {
		ErrMsg( "pipe error in init_text_analysis\n" );
		return -1;
	}

	switch( (pid=fork()) ) {
	case 0:					/* child */
		/* 子はここへは書かない。*/
		close( to_child[1] );

		/* 読み込み先を標準入力に */
		if( to_child[0] != 0 )  {
			dup2( to_child[0], 0 );
			close( to_child[0] );
		}

		/* 書き込み先の設定 */
		if( pc->last )  {
		  /* 最後の子 */
			close( to_parent[0] );	/* 子はここから読まない */
			/* 最後の子は親へ書き込む。*/
			if( to_parent[1] != 1 )  {
				dup2( to_parent[1], 1 );
				close( to_parent[1] );
			}
		} else {
		  /* 途中の子 */
			/* 書き込むfdはこのルーチンの中で決まる。*/
			out = make_pipe_child( (pc+1), to_parent );
			/* 書き込み先を標準出力に */
			if( out != 1 )  {
				dup2( out, 1 );
				close( out );
			}
			close( to_parent[0] );	/* 途中の子プロセスでは使わない。 */
			close( to_parent[1] );	
		}

		if( execv( pc->command[0], pc->command ) < 0 )  {
			ErrMsg( "execv error in init_text_analysis\n" );
			exit(1);
		}
		break;

	case -1:				/* error */
		ErrMsg( "fork error\n" );
		return -1;

	default:				/* parant */
		close( to_child[0] );	/* 親はここから読まない。*/
		return to_child[1];		/* 親はここへ書き込む。*/
	}
	return 0;
}

int chasen_write_line( CHASEN_FD fd_out, char *text )
{
        int n;
	
	n = strlen( text );
#ifdef DEBUG_CHASEN
	ErrMsg( "writing:\n" );	
	ErrMsg( text );	
	ErrMsg( "\n" );	
#endif
	if( write( fd_out, text, n ) != n )  {
		ErrMsg( "write error\n" );
		restart( 1 );
		return EOF;
	}
	write( fd_out, "\n", 1 );
#ifdef DEBUG_CHASEN
	fsync(fd_out);
	ErrMsg( "write done.\n" );	
#endif
        return 0;
}

int chasen_read_line( CHASEN_FD fd, char *buf, int len )
{
	char *buffer;

	buffer = buf;
#ifdef DEBUG_CHASEN
	ErrMsg( "reading:\n" );	
#endif
	while( read( fd, buf, 1 ) != 0 )  {
		if( *buf == '\n' )  {
			*(buf) = '\0';		/* NLコードは削除 */
			return( 0 );
		}
		++buf;  --len;
		if( len <= 1 )  {
			ErrMsg( "Too long line ...\n%s\n", buffer );
			*buf = '\0';
			return( 0 );
		}
	}
	*buf = '\0';
#ifdef DEBUG_CHASEN
	ErrMsg( "read done:\n" );	
	ErrMsg( buf );	
	ErrMsg( "\n" );	
#endif
	return( EOF );
}
#endif /* !USE_SPLIB */
