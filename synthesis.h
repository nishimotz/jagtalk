/* Copyright (c) 2000-2006                             */
/*   Yamashita Lab.                                    */
/*   (Ritsumeikan University)                          */
/*   Takao Kobayashi, Takashi Masuko, Masatsune Tamura */
/*   (Tokyo Institute of Technology)                   */
/*   Keiichi Tokuda, Takayoshi Yoshimura, Heiga Zen    */
/*   (Nagoya Institute of Technology)                  */
/*   All rights reserved                               */
/*                                                     */
/* $Id: synthesis.h,v 1.18 2009/02/12 17:43:42 sako Exp $                                                */

typedef enum {NON,SILB,SILE,PAU} SILENCE;
typedef enum {NO,YES} GBOOLEAN;
typedef enum {RAW,WAV} SPEECHFILETYPE;

/* ���� */

typedef struct _phoneme {
	char *phoneme;
	double time;
	double ctime;	/* ľ���ޤǤ����ѻ��֡�����Ĺ�����θ������ */
	struct _phoneme *next;
	struct _phoneme *prev;
	struct _mora *parent;
	int sid;	/* speaker ID */
	double alpha;	/* warping parameter */
} PHONEME;

extern PHONEME *phhead;
extern PHONEME *phtail;

/* �⡼�� */

typedef struct _mora {
	char *yomi;     /* ����ɽ�� */
	int position;
	int acdist;
	GBOOLEAN chouonka;
	GBOOLEAN devoiced;
	SILENCE silence;
	PHONEME *phead;
	PHONEME *ptail;
	struct _mora *next;
	struct _mora *prev;
	struct _morph *parent;
} MORA;

extern MORA *mrhead;
extern MORA *mrtail;

typedef struct _accent{
	char prepos; /* ����ʻ����: V, A, N, *(all), -(None) */
	int form;   /* ��������ȷ���ͼ� */
	int ctype;  /* ��祢������Ȳ� */
	int ctype2;  /* ��祢������Ȳ� (��°��ǡ���Ը줬ͭ�ˡ�̵�ˤˤ�ä�
	                ��祢��������ͤ��Ѥ���� (F6��F9) �����롣) */
} ACCENT;

#define MAX_ACCENT      4

/* ������ */
typedef struct _morph {
	char *kanji;    /* ����ɽ�� */
	char *pron;     /* ����ɽ������䥤Ρ��ɤߡ׽��� */
	int nmora;
	int nbyte;		/* ����ɽ���Ǥ�ʸ���� */
	int hinshiID;
	int katsuyogataID;
	int katsuyokeiID;
	int accentType;
	ACCENT accent[MAX_ACCENT];
	int n_accent;
	struct _morph *submorph;
	SILENCE silence;
	MORA *mrhead;
	MORA *mrtail;
	struct _morph *next;
	struct _morph *prev;
	struct _aphrase *parent;
} MORPH;

extern MORPH *mphead;
extern MORPH *mptail;

/* ��������ȶ� */
typedef struct _aphrase {
	int nmora;
	int accentType;
	int position;		/* �Ƶ�������ǤΥ�������ȶ�ΰ��� */
	SILENCE silence;
	GBOOLEAN interrogative;
	MORPH *mphead;
	MORPH *mptail;
	struct _aphrase *next;
	struct _aphrase *prev;
	struct _breath *parent;
} APHRASE;

extern APHRASE *ahead;
extern APHRASE *atail;

/* �Ƶ����� */
typedef struct _breath {
	int nmora;
	int position;   /* ʸ��ǤθƵ�����ΰ��֡��ݡ������ĤθƵ������
	                   �ʤ뤬���ˤϤ��줺������ position �� -1 */
	SILENCE silence;
	APHRASE *ahead;
	APHRASE *atail;
	struct _breath *next;
	struct _breath *prev;
	struct _sentence *parent;
} BREATH;

extern BREATH *bhead;
extern BREATH *btail;

/* ʸ�� */
typedef struct _sentence {
	int nmora;
	int nbreath;	/* �ݡ����ʳ��θƵ�����ο� */
	BREATH *bhead;
	BREATH *btail;
	struct _sentence *prev;
	struct _sentence *next;
} SENTENCE;

extern SENTENCE *shead;
extern SENTENCE *stail;
extern SENTENCE *sentence;

typedef struct _wave
{
  short *data;
  int rate;
  int nsample;
} WAVE;

extern WAVE wave;

typedef struct _param
{
  double *data;
  int rate;
} PARAM;

extern PARAM power;
extern PARAM f0;
extern PARAM alpha;

typedef struct _pros
{
	int	nPhoneme;
	char **ph_name;
	int *ph_dur;
	int	nFrame;
	double *fr_f0;
	double *fr_power;
} PROS;

extern PROS prosBuf;	/* ��Χ�ǡ����ΰ����Ǽ�� */
