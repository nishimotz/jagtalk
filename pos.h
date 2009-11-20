/* Copyright (c) 2000-2006                  */
/*   Yamashita Lab., Ritsumeikan University */
/*   All rights reserved                    */
/*                                          */
/* $Id: pos.h,v 1.7 2007/02/16 09:58:52 sako Exp $                                     */

/* �ʻ��ID */

#define H_MEISHI                      1000
#define H_MEISHI_FUTSUU_IPPAN         1010
#define H_MEISHI_FUTSUU_SAHEN         1020
#define H_MEISHI_FUTSUU_KEIJOU        1030
#define H_MEISHI_FUTSUU_FUKUSHI       1040
#define H_MEISHI_FUTSUU_SAHENKEIJOU   1050
#define H_MEISHI_KOYUU_IPPAN          1100
#define H_MEISHI_KOYUU_JINMEI_IPPAN   1110
#define H_MEISHI_KOYUU_JINMEI_SEI     1111
#define H_MEISHI_KOYUU_JINMEI_MEI     1112
#define H_MEISHI_KOYUU_CHIMEI_IPPAN   1120
#define H_MEISHI_KOYUU_CHIMEI_KUNI    1121
#define H_MEISHI_KOYUU_SOSHIKI        1137
#define H_MEISHI_JODOUSHIGOKAN        1000
#define H_MEISHI_KAZU                 1500
#define H_MEISHI_KAZU_IPPAN           1500
#define H_MEISHI_KAZU_KETA            1510
#define H_DAIMEISHI                   2000

#define H_KEIJOUSHI                   2200
#define H_KEIJOUSHI_IPPAN             2210
#define H_KEIJOUSHI_JODOUGOKAN        2220
#define H_KEIJOUSHI_TARI              2230
#define H_RENTAISHI                   2500
#define H_FUKUSHI                     3000
#define H_SETSUZOKUSHI                3500
#define H_KANDOUSHI                   4000
#define H_KANDOUSHI_IPPAN             4010
#define H_KANDOUSHI_FILLER            4020

#define H_DOUSHI                      5000
#define H_DOUSHI_IPPAN                5010
#define H_DOUSHI_HIJIRITSU            5020

#define H_KEIYOUSHI                   5500
#define H_KEIYOUSHI_IPPAN             5510
#define H_KEIYOUSHI_HIJIRITSU         5520

#define H_JODOUSHI                    4500

#define H_JOSHI                       6000
#define H_JOSHI_KAKUJOSHI             6100
#define H_JOSHI_KAKUJOSHI_IPPAN       6110
#define H_JOSHI_KAKUJOSHI_RENYOU      6120
#define H_JOSHI_KAKUJOSHI_RENTAI      6130
#define H_JOSHI_FUKUJOSHI             6200
#define H_JOSHI_KAKARIJOSHI           6300
#define H_JOSHI_SETSUZOKUJOSHI        6400
#define H_JOSHI_SHUUJOSHI             6500
#define H_JOSHI_JUNTAIJOSHI           6600

#define H_SETTOUJI                    7000
#define H_SETTOUJI_MEISHI_IPPAN       7110
#define H_SETTOUJI_MEISHI_SUUSHI      7120
#define H_SETTOUJI_KEIJOUSHI          7200
#define H_SETTOUJI_DOUSHI             7300
#define H_SETTOUJI_KEIYOUSHI          7400

#define H_SETSUBIJI                   8000
#define H_SETSUBIJI_MEISHI_IPPAN      8010
#define H_SETSUBIJI_MEISHI_SAHEN      8120
#define H_SETSUBIJI_MEISHI_KEIJOU     8130
#define H_SETSUBIJI_MEISHI_HUKUSHI    8140
#define H_SETSUBIJI_MEISHI_JINMEI     8151
#define H_SETSUBIJI_MEISHI_CHIMEI     8152
#define H_SETSUBIJI_MEISHI_SOHIKI     8153
#define H_SETSUBIJI_MEISHI_JOSHUUSHI  8160
#define H_SETSUBIJI_MEISHI_SAHENKEIJOU 8170
#define H_SETSUBIJI_KEIJOUSHI         8200
#define H_SETSUBIJI_DOUSHI            8300
#define H_SETSUBIJI_KEIYOUSHI         8400

#define H_KIGOU                       9000
#define H_KIGOU_IPPAN                 9110
#define H_KIGOU_MOJI                  9120
#define H_KIGOU_SUUJI                 9130

#define H_SONOTA                      9500
#define H_SONOTA_IPPAN                9510
#define H_SONOTA_SUUJI                9520
#define H_SONOTA_KUUHAKU              9530
#define H_SONOTA_KUTEN                9541
#define H_SONOTA_TOUTEN               9542
#define H_SONOTA_KAKKO_HIRAKU         9551
#define H_SONOTA_KAKKO_TOJIRU         9552
#define H_KUUHAKU                     9500

#define H_MICHIGO                     9999

#define	IS_MEISHI(h)	   ( ((h)>=H_MEISHI && (h)<=H_DAIMEISHI) )
#define	IS_KOYUU_MEISHI(h) ( ((h)>=H_KOYUU_IPPAN && (h)<H_KAZU_IPPAN) )
#define	IS_DAIMEISHI(h)	   ( ((h)==H_DAIMEISHI) )
#define IS_KEIJOUSHI(h)    ( ((h)>=H_KEIJOUSHI && (h)<H_RENTAISHI) )
#define IS_RENTAISHI(h)    ( ((h)==H_RENTAISHI) )
#define IS_FUKUSHI(h)      ( ((h)==H_FUKUSHI) )
#define IS_SETSUZOKUSHI(h) ( ((h)==H_SETSUZOKUSHI) )
#define IS_KANDOUSHI(h)    ( ((h)>=H_KANDOUSHI && (h)<H_DOUSHI) )
#define IS_FILLER(h)       ( ((h)==H_FILLER) )
#define	IS_DOUSHI(h)	   ( ((h)>=H_DOUSHI && (h)<H_KEIYOUSHI) )
#define	IS_KEIYOUSHI(h)	   ( ((h)>=H_KEIYOUSHI && (h)<H_JODOUSHI) )
#define	IS_JODOUSHI(h)	   ( ((h)==H_JODOUSHI) )
#define	IS_JOSHI(h)	       ( ((h)>=H_JOSHI && (h)<H_SETTOUJI) )
#define IS_SETTOUJI(h)     ( ((h)=>H_SETTOUJI && (h)<H_SETSUBIJI) )
#define IS_SETSUBIJI(h)    ( ((h)==H_SETSUBIJI && (h)<H_KIGOU) )
#define IS_KIGOU(h)        ( ((h)>=H_KIGOU && (h)<H_SONOTA) )
#define IS_SONOTA(h)       ( ((h)>=h_SONOTA && (h)<H_MICHIGO) )

#define	IS_FUZOKUGO(h)	( IS_JODOUSHI(h) || IS_JOSHI(h) )
#define	IS_JIRITSUGO(h)	( ! IS_FUZOKUGO(h) )
#define	IS_KUTOUTEN(h)	( ((h)==H_SONOTA_KUTEN || (h)==H_SONOTA_TOUTEN) )


/* ����Ū�ʥ��ƥ��꡼�ϸ��������Ƥ���ɬ�פ��ꡣ
   ��̾��-��ͭ̾��פϡ�̾��פ����ˡ� */


/* ���ѷ���ID */

#define KATA_GODAN_KAGYOU_IPPAN             1000 /* ����-����-���� */
#define KATA_GODAN_KAGYOU_IPPAN_IPPAN       1000 /* ����-����-����-���� */
#define KATA_GODAN_KAGYOU_IPPAN_IDAN        1001 /* ����-����-����-���� */
#define KATA_GODAN_KAGYOU_IKU               1002 /* ����-����-���� */
#define KATA_GODAN_KAGYOU_YUKU              1003 /* ����-����-�楯 */
#define KATA_GODAN_GAGYOU_IPPAN             1010 /* ����-����-���� */
#define KATA_GODAN_GAGYOU_IDAN              1011 /* ����-����-���� */
#define KATA_GODAN_GAGYOU                   1010 /* ����-���� */
#define KATA_GODAN_SAGYOU                   1020 /* ����-���� */
#define KATA_GODAN_TAGYOU                   1030 /* ����-���� */
#define KATA_GODAN_NAGYOU                   1040 /* ����-�ʹ� */
#define KATA_GODAN_BAGYOU                   1050 /* ����-�й� */
#define KATA_GODAN_MAGYOU_IPPAN             1060 /* ����-�޹�-���� */
#define KATA_GODAN_MAGYOU_SUMU              1061 /* ����-�޹�-�ѥ� */
#define KATA_GODAN_MAGYOU                   1060 /* ����-�޹� */
#define KATA_GODAN_RAGYOU_IPPAN             1070 /* ����-���-���� */
#define KATA_GODAN_RAGYOU_ARU               1071 /* ����-���-���� */
#define KATA_GODAN_RAGYOU_SARU              1072 /* ����-���-���� */
#define KATA_GODAN_WAAGYOU_IPPAN            1100 /* ����-�異��-���� */
#define KATA_GODAN_WAAGYOU_ADAN_IPPAN       1100 /* ����-�異��-����-���� */
#define KATA_GODAN_WAAGYOU_ADAN_AU_IPPAN    1101 /* ����-�異��-����-����-���� */
#define KATA_GODAN_WAAGYOU_ADAN_AU_AU       1102 /* ����-�異��-����-����-���� */
#define KATA_GODAN_WAAGYOU_ADAN_KAU_IPPAN   1103 /* ����-�異��-����-����-���� */
#define KATA_GODAN_WAAGYOU_ADAN_KAU_KAU     1104 /* ����-�異��-����-����-���� */
#define KATA_GODAN_WAAGYOU_ADAN_GAU_IPPAN   1105 /* ����-�異��-����-����-���� */
#define KATA_GODAN_WAAGYOU_ADAN_GAU_GAU     1106 /* ����-�異��-����-����-���� */
#define KATA_GODAN_WAAGYOU_ADAN_TAU_IPPAN   1107 /* ����-�異��-����-����-���� */
#define KATA_GODAN_WAAGYOU_ADAN_TAU_TAU     1108 /* ����-�異��-����-����-���� */
#define KATA_GODAN_WAAGYOU_ADAN_DAU_IPPAN   1109 /* ����-�異��-����-����-���� */
#define KATA_GODAN_WAAGYOU_ADAN_DAU_DAU     1110 /* ����-�異��-����-����-���� */
#define KATA_GODAN_WAAGYOU_ADAN_NAU_IPPAN   1111 /* ����-�異��-����-�ʥ�-���� */
#define KATA_GODAN_WAAGYOU_ADAN_NAU_NAU     1112 /* ����-�異��-����-�ʥ�-�ʤ� */
#define KATA_GODAN_WAAGYOU_ADAN_HAU_IPPAN   1113 /* ����-�異��-����-�ϥ�-���� */
#define KATA_GODAN_WAAGYOU_ADAN_HAU_HAU     1114 /* ����-�異��-����-�ϥ�-�Ϥ� */
#define KATA_GODAN_WAAGYOU_ADAN_BAU_IPPAN   1115 /* ����-�異��-����-�Х�-���� */
#define KATA_GODAN_WAAGYOU_ADAN_BAU_BAU     1116 /* ����-�異��-����-�Х�-�Ф� */
#define KATA_GODAN_WAAGYOU_ADAN_MAU_IPPAN   1117 /* ����-�異��-����-�ޥ�-���� */
#define KATA_GODAN_WAAGYOU_ADAN_MAU_MAU     1118 /* ����-�異��-����-�ޥ�-�ޤ� */
#define KATA_GODAN_WAAGYOU_ADAN_YAU_IPPAN   1119 /* ����-�異��-����-�䥦-���� */
#define KATA_GODAN_WAAGYOU_ADAN_YAU_YAU     1120 /* ����-�異��-����-�䥦-�䤦 */
#define KATA_GODAN_WAAGYOU_ADAN_RAU_IPPAN   1121 /* ����-�異��-����-�饦-���� */
#define KATA_GODAN_WAAGYOU_ADAN_RAU_RAU     1122 /* ����-�異��-����-�饦-�餦 */
#define KATA_GODAN_WAAGYOU_ADAN_WAU_IPPAN   1123 /* ����-�異��-����-�復-���� */
#define KATA_GODAN_WAAGYOU_ADAN_WAU_WAU     1124 /* ����-�異��-����-�復-�臘 */
#define KATA_GODAN_WAAGYOU_IDAN_IPPAN       1130 /* ����-�異��-����-���� */
#define KATA_GODAN_WAAGYOU_IDAN_IU          1131 /* ����-�異��-����-���� */
#define KATA_GODAN_WAAGYOU_UDAN_IPPAN       1140 /* ����-�異��-����-���� */
#define KATA_GODAN_WAAGYOU_UDAN_TUU         1141 /* ����-�異��-����-�ĥ� */
#define KATA_GODAN_WAAGYOU_EDAN             1150 /* ����-�異��-���� */
#define KATA_GODAN_WAAGYOU_ODAN             1160 /* ����-�異��-���� */
#define KATA_UEICHIDAN_AGYOU_IPPAN          2000 /* �����-����-���� */
#define KATA_UEICHIDAN_AGYOU_IDAN           2001 /* �����-����-���� */
#define KATA_UEICHIDAN_AGYOU                2000 /* �����-���� */
#define KATA_UEICHIDAN_KAGYOU               2010 /* �����-���� */
#define KATA_UEICHIDAN_GAGYOU               2020 /* �����-���� */
#define KATA_UEICHIDAN_ZAGYOU               2030 /* �����-���� */
#define KATA_UEICHIDAN_TAGYOU               2040 /* �����-���� */
#define KATA_UEICHIDAN_NAGYOU               2050 /* �����-�ʹ� */
#define KATA_UEICHIDAN_HAGYOU               2060 /* �����-�Ϲ� */
#define KATA_UEICHIDAN_BAGYOU               2070 /* �����-�й� */
#define KATA_UEICHIDAN_MAGYOU               2080 /* �����-�޹� */
#define KATA_UEICHIDAN_RAGYOU_IPPAN         2090 /* �����-���-���� */
#define KATA_UEICHIDAN_RAGYOU_RIRU          2091 /* �����-���-��� */
#define KATA_UEICHIDAN_RAGYOU               2090 /* �����-��� */
#define KATA_SHIMOICHIDAN_AGYOU_IPPAN       2500 /* ������-����-���� */
#define KATA_SHIMOICHIDAN_AGYOU_EDAN        2501 /* ������-����-���� */
#define KATA_SHIMOICHIDAN_AGYOU             2500 /* ������-���� */
#define KATA_SHIMOICHIDAN_KAGYOU            2510 /* ������-���� */
#define KATA_SHIMOICHIDAN_GAGYOU            2520 /* ������-���� */
#define KATA_SHIMOICHIDAN_SAGYOU_IPPAN      2530 /* ������-����-���� */
#define KATA_SHIMOICHIDAN_SAGYOU_SERU       2531 /* ������-����-���� */
#define KATA_SHIMOICHIDAN_SAGYOU            2530 /* ������-���� */
#define KATA_SHIMOICHIDAN_ZAGYOU            2540 /* ������-���� */
#define KATA_SHIMOICHIDAN_TAGYOU            2550 /* ������-���� */
#define KATA_SHIMOICHIDAN_DAGYOU            2560 /* ������-���� */
#define KATA_SHIMOICHIDAN_NAGYOU            2570 /* ������-�ʹ� */
#define KATA_SHIMOICHIDAN_HAGYOU            2590 /* ������-�Ϲ� */
#define KATA_SHIMOICHIDAN_BAGYOU            2600 /* ������-�й� */
#define KATA_SHIMOICHIDAN_MAGYOU            2610 /* ������-�޹� */
#define KATA_SHIMOICHIDAN_RAGYOU_IPPAN      2620 /* ������-���-���� */
#define KATA_SHIMOICHIDAN_RAGYOU_RERU       2621 /* ������-���-��� */
#define KATA_SHIMOICHIDAN_RAGYOU_KURERU     2622 /* ������-���-���� */
#define KATA_KAGYOUHENKAKU_IPPAN            3000 /* �����ѳ�-���� */
#define KATA_KAGYOUHENKAKU_KURU             3020 /* �����ѳ�-���� */
#define KATA_KAGYOUHENKAKU                  3000 /* �����ѳ� */
#define KATA_SAGYOUHENKAKU_IRU              3510 /* �����ѳ�-�٥� */
#define KATA_SAGYOUHENKAKU_SURU             3520 /* �����ѳ�-���� */
#define KATA_SAGYOUHENKAKU_ZURU             3530 /* �����ѳ�-���� */
#define KATA_SAGYOUHENKAKU                  3500 /* �����ѳ� */
#define KATA_ZAGYOUHENKAKU                  3500 /* �����ѳ� */
#define KATA_BUNGOYODAN_KAGYOU              4010 /* ʸ�����-���� */
#define KATA_BUNGOYODAN_GAGYOU              4020 /* ʸ�����-���� */
#define KATA_BUNGOYODAN_SAGYOU              4030 /* ʸ�����-���� */
#define KATA_BUNGOYODAN_TAGYOU              4040 /* ʸ�����-���� */
#define KATA_BUNGOYODAN_HAGYOU_ADAN_KAU_IPPAN   4050 /* ʸ�����-�Ϲ�-����-����-���� */
#define KATA_BUNGOYODAN_HAGYOU_ADAN_KAU_KAU   4051 /* ʸ�����-�Ϲ�-����-����-���� */
#define KATA_BUNGOYODAN_HAGYOU_ADAN_GAU_IPPAN   4052 /* ʸ�����-�Ϲ�-����-����-���� */
#define KATA_BUNGOYODAN_HAGYOU_ADAN_GAU_GAU   4053 /* ʸ�����-�Ϲ�-����-����-���� */
#define KATA_BUNGOYODAN_HAGYOU_ADAN_NAU_IPPAN   4054 /* ʸ�����-�Ϲ�-����-�ʥ�-���� */
#define KATA_BUNGOYODAN_HAGYOU_ADAN_NAU_NAU   4055 /* ʸ�����-�Ϲ�-����-�ʥ�-�ʤ� */
#define KATA_BUNGOYODAN_HAGYOU_ADAN_TAMAU_IPPAN   4056 /* ʸ�����-�Ϲ�-����-�륦-���� */
#define KATA_BUNGOYODAN_HAGYOU_ADAN_TAMAU_MAU   4057 /* ʸ�����-�Ϲ�-����-�륦-�ޤ� */
#define KATA_BUNGOYODAN_HAGYOU_IDAN_IPPAN   4060 /* ʸ�����-�Ϲ�-����-���� */
#define KATA_BUNGOYODAN_HAGYOU_IDAN_IU   4061 /* ʸ�����-�Ϲ�-����-���� */
#define KATA_BUNGOYODAN_HAGYOU_UDAN   4070 /* ʸ�����-�Ϲ�-���� */
#define KATA_BUNGOYODAN_HAGYOU_EDAN   4080 /* ʸ�����-�Ϲ�-���� */
#define KATA_BUNGOYODAN_HAGYOU_ODAN   4090 /* ʸ�����-�Ϲ�-���� */
#define KATA_BUNGOYODAN_HAGYOU_HU   4050 /* ʸ�����-�Ϲ�-�� */
#define KATA_BUNGOYODAN_BAGYOU   4100 /* ʸ�����-�й� */
#define KATA_BUNGOYODAN_MAGYOU   4110 /* ʸ�����-�޹� */
#define KATA_BUNGOYODAN_RAGYOU   4120 /* ʸ�����-��� */
#define KATA_BUNGONIDAN_KAGYOU   5010 /* ʸ�������-���� */
#define KATA_BUNGOKAMINIDAN_GAGYOU   5020 /* ʸ�������-���� */
#define KATA_BUNGOKAMINIDAN_TAGYOU   5030 /* ʸ�������-���� */
#define KATA_BUNGOKAMINIDAN_DAGYOU   5040 /* ʸ�������-���� */
#define KATA_BUNGOKAMINIDAN_HAGYOU   5050 /* ʸ�������-�Ϲ� */
#define KATA_BUNGOKAMINIDAN_BAGYOU   5060 /* ʸ�������-�й� */
#define KATA_BUNGOKAMINIDAN_MAGYOU   5070 /* ʸ�������-�޹� */
#define KATA_BUNGOKAMINIDAN_YAGYOU   5080 /* ʸ�������-��� */
#define KATA_BUNGOKAMINIDAN_RAGYOU   5090 /* ʸ�������-��� */
#define KATA_BUNGOSHIMONIDAN_AGYOU_IPPAN   5510 /* ʸ�첼����-����-���� */
#define KATA_BUNGOSHIMONIDAN_AGYOU_U   5511 /* ʸ�첼����-����-�� */
#define KATA_BUNGOSHIMONIDAN_AGYOU    5510 /* ʸ�첼����-���� */
#define KATA_BUNGOSHIMONIDAN_KAGYOU   5520 /* ʸ�첼����-���� */
#define KATA_BUNGOSHIMONIDAN_GAGYOU   5530 /* ʸ�첼����-���� */
#define KATA_BUNGOSHIMONIDAN_SAGYOU   5540 /* ʸ�첼����-���� */
#define KATA_BUNGOSHIMONIDAN_ZAGYOU   5550 /* ʸ�첼����-���� */
#define KATA_BUNGOSHIMONIDAN_TAGYOU   5560 /* ʸ�첼����-���� */
#define KATA_BUNGOSHIMONIDAN_DAGYOU_IPPAN   5570 /* ʸ�첼����-����-���� */
#define KATA_BUNGOSHIMONIDAN_DAGYOU_DU   5571 /* ʸ�첼����-����-�� */
#define KATA_BUNGOSHIMONIDAN_NAGYOU_IPPAN   5580 /* ʸ�첼����-�ʹ�-���� */
#define KATA_BUNGOSHIMONIDAN_NAGYOU_NU   5581 /* ʸ�첼����-�ʹ�-�� */
#define KATA_BUNGOSHIMONIDAN_NAGYOU   5580 /* ʸ�첼����-�ʹ� */
#define KATA_BUNGOSHIMONIDAN_HAGYOU_IPPAN   5590 /* ʸ�첼����-�Ϲ�-���� */
#define KATA_BUNGOSHIMONIDAN_HAGYOU   5590 /* ʸ�첼����-�Ϲ� */
#define KATA_BUNGOSHIMONIDAN_HAGYOU_KEI_IPPAN   5591 /* ʸ�첼����-�Ϲ�-��-���� */
#define KATA_BUNGOSHIMONIDAN_HAGYOU_KEI_HU   5592 /* ʸ�첼����-�Ϲ�-��-�� */
#define KATA_BUNGOSHIMONIDAN_BAGYOU   5600 /* ʸ�첼����-�й� */
#define KATA_BUNGOSHIMONIDAN_MAGYOU   5610 /* ʸ�첼����-�޹� */
#define KATA_BUNGOSHIMONIDAN_YAGYOU   5620 /* ʸ�첼����-��� */
#define KATA_BUNGOSHIMONIDAN_RAGYOU   5630 /* ʸ�첼����-��� */
#define KATA_BUNGOSHIMONIDAN_RA   5640 /* ʸ�첼����-��� */
#define KATA_BUNGOKAGYOUHENKAKU_IPPAN   6010 /* ʸ�쥫���ѳ�-���� */
#define KATA_BUNGOKAGYOUHENKAKU   6010 /* ʸ�쥫���ѳ� */
#define KATA_BUNGOKAGYOUHENKAKU_KU   6020 /* ʸ�쥫���ѳ�-�� */
#define KATA_BUNGOSAGYOUHENKAKU_SU   6110 /* ʸ�쥵���ѳ�-�� */
#define KATA_BUNGOSAGYOUHENKAKU_ZU   6120 /* ʸ�쥵���ѳ�-�� */
#define KATA_BUNGOSAGYOUHENKAKU   6100 /* ʸ�쥵���ѳ� */
#define KATA_BUNGONAGYOUHENKAKU   6210 /* ʸ��ʹ��ѳ� */
#define KATA_BUNGORAGYOUHENKAKU   6310 /* ʸ�����ѳ� */
#define KATA_KEIYOUSHI_ADAN_KAI_IPPAN   7010 /* ���ƻ�-����-����-���� */
#define KATA_KEIYOUSHI_ADAN_KAI_KAI   7011 /* ���ƻ�-����-����-���� */
#define KATA_KEIYOUSHI_ADAN_GAI_IPPAN   7020 /* ���ƻ�-����-����-���� */
#define KATA_KEIYOUSHI_ADAN_GAI_GAI   7021 /* ���ƻ�-����-����-���� */
#define KATA_KEIYOUSHI_ADAN_SAI_IPPAN   7030 /* ���ƻ�-����-����-���� */
#define KATA_KEIYOUSHI_ADAN_SAI_SAI   7031 /* ���ƻ�-����-����-���� */
#define KATA_KEIYOUSHI_ADAN_TAI_IPPAN   7040 /* ���ƻ�-����-����-���� */
#define KATA_KEIYOUSHI_ADAN_TAI_TAI   7041 /* ���ƻ�-����-����-���� */
#define KATA_KEIYOUSHI_ADAN_CHAI_IPPAN   7050 /* ���ƻ�-����-���㥤-���� */
#define KATA_KEIYOUSHI_ADAN_CHAI_CHAI   7051 /* ���ƻ�-����-���㥤-���㤤 */
#define KATA_KEIYOUSHI_ADAN_NAI_IPPAN   7060 /* ���ƻ�-����-�ʥ�-���� */
#define KATA_KEIYOUSHI_ADAN_NAI_NAI   7061 /* ���ƻ�-����-�ʥ�-�ʤ� */
#define KATA_KEIYOUSHI_ADAN_BAI_IPPAN   7070 /* ���ƻ�-����-�Х�-���� */
#define KATA_KEIYOUSHI_ADAN_BAI_BAI   7071 /* ���ƻ�-����-�Х�-�Ф� */
#define KATA_KEIYOUSHI_ADAN_PAI_IPPAN   7080 /* ���ƻ�-����-�ѥ�-���� */
#define KATA_KEIYOUSHI_ADAN_PAI_PAI   7081 /* ���ƻ�-����-�ѥ�-�Ѥ� */
#define KATA_KEIYOUSHI_ADAN_MAI_IPPAN   7090 /* ���ƻ�-����-�ޥ�-���� */
#define KATA_KEIYOUSHI_ADAN_MAI_MAI   7091 /* ���ƻ�-����-�ޥ�-�ޤ� */
#define KATA_KEIYOUSHI_ADAN_YAI_IPPAN   7100 /* ���ƻ�-����-�䥤-���� */
#define KATA_KEIYOUSHI_ADAN_YAI_YAI   7101 /* ���ƻ�-����-�䥤-�䤤 */
#define KATA_KEIYOUSHI_ADAN_RAI_IPPAN   7110 /* ���ƻ�-����-�饤-���� */
#define KATA_KEIYOUSHI_ADAN_RAI_RAI   7111 /* ���ƻ�-����-�饤-�餤 */
#define KATA_KEIYOUSHI_ADAN_WAI_IPPAN   7120 /* ���ƻ�-����-�磻-���� */
#define KATA_KEIYOUSHI_ADAN_WAI_WAI   7121 /* ���ƻ�-����-�磻-�襤 */
#define KATA_KEIYOUSHI_ADAN_KNAI_IPPAN   7120 /* ���ƻ�-����-̵��-���� */
#define KATA_KEIYOUSHI_ADAN_KNAI_NAI   7121 /* ���ƻ�-����-̵��-�ʤ� */
#define KATA_KEIYOUSHI_IDAN_IPPAN   7200 /* ���ƻ�-����-���� */
#define KATA_KEIYOUSHI_IDAN_YOI   7210 /* ���ƻ�-����-�ɥ� */
#define KATA_KEIYOUSHI_UDAN_UI_IPPAN   7310 /* ���ƻ�-����-����-���� */
#define KATA_KEIYOUSHI_UDAN_UI_UI   7311 /* ���ƻ�-����-����-���� */
#define KATA_KEIYOUSHI_UDAN_KUI_IPPAN   7320 /* ���ƻ�-����-����-���� */
#define KATA_KEIYOUSHI_UDAN_KUI_KUI   7321 /* ���ƻ�-����-����-���� */
#define KATA_KEIYOUSHI_UDAN_GUI_IPPAN   7330 /* ���ƻ�-����-����-���� */
#define KATA_KEIYOUSHI_UDAN_GUI_GUI   7331 /* ���ƻ�-����-����-���� */
#define KATA_KEIYOUSHI_UDAN_SUI_IPPAN   7340 /* ���ƻ�-����-����-���� */
#define KATA_KEIYOUSHI_UDAN_SUI_SUI   7341 /* ���ƻ�-����-����-���� */
#define KATA_KEIYOUSHI_UDAN_ZUI_IPPAN   7350 /* ���ƻ�-����-����-���� */
#define KATA_KEIYOUSHI_UDAN_ZUI_ZUI   7351 /* ���ƻ�-����-����-���� */
#define KATA_KEIYOUSHI_UDAN_TUI_IPPAN   7360 /* ���ƻ�-����-�ĥ�-���� */
#define KATA_KEIYOUSHI_UDAN_TUI_TUI   7361 /* ���ƻ�-����-�ĥ�-�Ĥ� */
#define KATA_KEIYOUSHI_UDAN_BUI_IPPAN   7370 /* ���ƻ�-����-�֥�-���� */
#define KATA_KEIYOUSHI_UDAN_BUI_BUI   7371 /* ���ƻ�-����-�֥�-�֤� */
#define KATA_KEIYOUSHI_UDAN_MUI_IPPAN   7380 /* ���ƻ�-����-�।-���� */
#define KATA_KEIYOUSHI_UDAN_MUI_MUI   7381 /* ���ƻ�-����-�।-�त */
#define KATA_KEIYOUSHI_UDAN_YUI_IPPAN   7390 /* ���ƻ�-����-�楤-���� */
#define KATA_KEIYOUSHI_UDAN_YUI_YUI   7391 /* ���ƻ�-����-�楤-�椤 */
#define KATA_KEIYOUSHI_UDAN_RUI_IPPAN   7400 /* ���ƻ�-����-�륤-���� */
#define KATA_KEIYOUSHI_UDAN_RUI_RUI   7401 /* ���ƻ�-����-�륤-�뤤 */
#define KATA_KEIYOUSHI_EDAN   7500 /* ���ƻ�-���� */
#define KATA_KEIYOUSHI_ODAN_OI_IPPAN_IPPAN   7510 /* ���ƻ�-����-����-����-���� */
#define KATA_KEIYOUSHI_ODAN_OI_IPPAN_ODAN   7511 /* ���ƻ�-����-����-����-���� */
#define KATA_KEIYOUSHI_ODAN_OI_IPPAN   7520 /* ���ƻ�-����-����-����-���� */
#define KATA_KEIYOUSHI_ODAN_OI_ODAN   7521 /* ���ƻ�-����-����-����-���� */
#define KATA_KEIYOUSHI_ODAN_KOI_IPPAN   7530 /* ���ƻ�-����-����-���� */
#define KATA_KEIYOUSHI_ODAN_KOI_KOI   7531 /* ���ƻ�-����-����-���� */
#define KATA_KEIYOUSHI_ODAN_GOI_IPPAN   7540 /* ���ƻ�-����-����-���� */
#define KATA_KEIYOUSHI_ODAN_GOI_GOI   7541 /* ���ƻ�-����-����-���� */
#define KATA_KEIYOUSHI_ODAN_SHOI_IPPAN   7550 /* ���ƻ�-����-���祤-���� */
#define KATA_KEIYOUSHI_ODAN_SHOI_SHOI   7551 /* ���ƻ�-����-���祤-���礤 */
#define KATA_KEIYOUSHI_ODAN_SOI_IPPAN   7560 /* ���ƻ�-����-����-���� */
#define KATA_KEIYOUSHI_ODAN_SOI_SOI   7561 /* ���ƻ�-����-����-���� */
#define KATA_KEIYOUSHI_ODAN_ZOI_IPPAN   7570 /* ���ƻ�-����-����-���� */
#define KATA_KEIYOUSHI_ODAN_ZOI_ZOI   7571 /* ���ƻ�-����-����-���� */
#define KATA_KEIYOUSHI_ODAN_TOI_IPPAN   7580 /* ���ƻ�-����-�ȥ�-���� */
#define KATA_KEIYOUSHI_ODAN_TOI_TOI   7581 /* ���ƻ�-����-�ȥ�-�Ȥ� */
#define KATA_KEIYOUSHI_ODAN_DOI_IPPAN   7590 /* ���ƻ�-����-�ɥ�-���� */
#define KATA_KEIYOUSHI_ODAN_DOI_DOI   7591 /* ���ƻ�-����-�ɥ�-�ɤ� */
#define KATA_KEIYOUSHI_ODAN_BOI_IPPAN   7600 /* ���ƻ�-����-�ܥ�-���� */
#define KATA_KEIYOUSHI_ODAN_BOI_BOI   7601 /* ���ƻ�-����-�ܥ�-�ܤ� */
#define KATA_KEIYOUSHI_ODAN_POI_IPPAN   7610 /* ���ƻ�-����-�ݥ�-���� */
#define KATA_KEIYOUSHI_ODAN_POI_POI   7611 /* ���ƻ�-����-�ݥ�-�ݤ� */
#define KATA_KEIYOUSHI_ODAN_MOI_IPPAN   7620 /* ���ƻ�-����-�⥤-���� */
#define KATA_KEIYOUSHI_ODAN_MOI_MOI   7621 /* ���ƻ�-����-�⥤-�⤤ */
#define KATA_KEIYOUSHI_ODAN_YOI_IPPAN   7630 /* ���ƻ�-����-�襤-���� */
#define KATA_KEIYOUSHI_ODAN_YOI_YOI   7631 /* ���ƻ�-����-�襤-�褤 */
#define KATA_KEIYOUSHI_ODAN_ROI_IPPAN   7640 /* ���ƻ�-����-��-���� */
#define KATA_KEIYOUSHI_ODAN_ROI_ROI   7641 /* ���ƻ�-����-��-�� */
#define KATA_KEIYOUSHI_ODAN_KYOI_IPPAN   7650 /* ���ƻ�-����-�ɥ�-���� */
#define KATA_KEIYOUSHI_ODAN_KYOI_YOI   7651 /* ���ƻ�-����-�ɥ�-�褤 */
#define KATA_BUNKEIYOUSHI_KU   7910 /* ʸ����ƻ�-�� */
#define KATA_BUNKEIYOUSHI_OOSHI  7910 /* ʸ����ƻ�-¿�� */
#define KATA_BUNKEIYOUSHI_SHIKU   7920 /* ʸ����ƻ�-���� */
#define KATA_KEIYOUSHI  7000 /* ���ƻ� */
#define KATA_JODOUSHI_JA   8010 /* ��ư��-���� */
#define KATA_JODOUSHI_TA   8020 /* ��ư��-�� */
#define KATA_JODOUSHI_TAI   8030 /* ��ư��-���� */
#define KATA_JODOUSHI_DA   8040 /* ��ư��-�� */
#define KATA_JODOUSHI_DESU   8050 /* ��ư��-�ǥ� */
#define KATA_JODOUSHI_NAI   8060 /* ��ư��-�ʥ� */
#define KATA_JODOUSHI_NU   8090 /* ��ư��-�� */
#define KATA_JODOUSHI_MASU   8100 /* ��ư��-�ޥ� */
#define KATA_JODOUSHI_YA   8110 /* ��ư��-�� */
#define KATA_JODOUSHI_YASU   8120 /* ��ư��-�䥹 */
#define KATA_JODOUSHI_RASHII   8130 /* ��ư��-�饷�� */
#define KATA_BUNGOJODOUSHI_KI   9010 /* ʸ���ư��-�� */
#define KATA_BUNGOJODOUSHI_KEMU   9020 /* ʸ���ư��-���� */
#define KATA_BUNGOJODOUSHI_KERI   9030 /* ʸ���ư��-���� */
#define KATA_BUNGOJODOUSHI_GOTOSHI   9040 /* ʸ���ư��-���ȥ� */
#define KATA_BUNGOJODOUSHI_ZAMASU   9050 /* ʸ���ư��-���ޥ� */
#define KATA_BUNGOJODOUSHI_ZU   9060 /* ʸ���ư��-�� */
#define KATA_BUNGOJODOUSHI_TARI   9070 /* ʸ���ư��-���� */
#define KATA_BUNGOJODOUSHI_TU   9080 /* ʸ���ư��-�� */
#define KATA_BUNGOJODOUSHI_NARI   9090 /* ʸ���ư��-�ʥ� */
#define KATA_BUNGOJODOUSHI_NU   9100 /* ʸ���ư��-�� */
#define KATA_BUNGOJODOUSHI_BESHI   9110 /* ʸ���ư��-�٥� */
#define KATA_BUNGOJODOUSHI_MAJI   9120 /* ʸ���ư��-�ޥ� */
#define KATA_BUNGOJODOUSHI_MU   9130 /* ʸ���ư��-�� */
#define KATA_BUNGOJODOUSHI_RASHI   9140 /* ʸ���ư��-�饷 */
#define KATA_BUNGOJODOUSHI_RAMU   9150 /* ʸ���ư��-��� */
#define KATA_BUNGOJODOUSHI_RI   9160 /* ʸ���ư��-�� */
#define KATA_BUNGOJODOUSHI_NSU   9170 /* ʸ���ư��-�� */
#define KATA_MUHENKAGATA   9900 /* ̵�Ѳ��� */


/* ���ѷ���ID */

#define KEI_GOKAN_IPPAN           110  /* �촴-���� */
#define KEI_GOKAN_SA              120  /* �촴-�� */
#define KEI_MIZEN_IPPAN           210  /* ̤����-���� */
#define KEI_MIZEN_IPPAN_HE        211  /* ̤����-����:�� */
#define KEI_MIZEN_HATSUON         220  /* ̤����-������ */
#define KEI_MIZEN_ZU              230  /* ̤����-����³ */
#define KEI_MIZEN_SERU            240  /* ̤����-������³ */
#define KEI_MIZEN_HOJO            250  /* ̤����-��� */
#define KEI_ISHISUIRYOU_IPPAN     310  /* �ջֿ��̷�-���� */
#define KEI_ISHISUIRYOU_IPPAN_TAN 311  /* �ջֿ��̷�-����:û�� */
#define KEI_ISHISUIRYOU_SOKUON    320  /* �ջֿ��̷�-¥���� */
#define KEI_ISHISUIRYOU           310  /* �ջֿ��̷� */
#define KEI_RENYOU_IPPAN          410  /* Ϣ�ѷ�-���� */
#define KEI_RENYOU_IPPAN_SHI      411  /* Ϣ�ѷ�-����:�� */
#define KEI_RENYOU_IONBIN         420  /* Ϣ�ѷ�-������ */
#define KEI_RENYOU_UONBIN         430  /* Ϣ�ѷ�-������ */
#define KEI_RENYOU_SOKUONBIN      440  /* Ϣ�ѷ�-¥���� */
#define KEI_RENYOU_SOKUONBIN_SU   441  /* Ϣ�ѷ�-¥����:���� */
#define KEI_RENYOU_HATSUONBIN     450  /* Ϣ�ѷ�-������ */
#define KEI_RENYOU_YUUGOU         460  /* Ϣ�ѷ�-ͻ�� */
#define KEI_RENYOU_YUUGOU_CHA     461  /* Ϣ�ѷ�-ͻ��:���� */
#define KEI_RENYOU_HOJO           470  /* Ϣ�ѷ�-��� */
#define KEI_RENYOU_TO             480  /* Ϣ�ѷ�-�� */
#define KEI_RENYOU_NI             490  /* Ϣ�ѷ�-�� */
#define KEI_KIHON_IPPAN           510  /* ���ܷ�-���� */
#define KEI_KIHON_IPPAN_CHA       511  /* ���ܷ�-����:���� */
#define KEI_KIHON_UONBIN          520  /* ���ܷ�-������ */
#define KEI_KIHON_SOKUONBIN       530  /* ���ܷ�-¥���� */
#define KEI_KIHON_HATSUONBIN      540  /* ���ܷ�-������ */
#define KEI_KIHON_E               550  /* ���ܷ�-�� */
#define KEI_RENTAI_IPPAN          560  /* Ϣ�η�-���� */
#define KEI_RENTAI_IPPAN_TAN      561  /* Ϣ�η�-����:û�� */
#define KEI_RENTAI_SHOURYAKU      570  /* Ϣ�η�-��ά */
#define KEI_RENTAI_HOJO           580  /* Ϣ�η�-��� */
#define KEI_RENTAI_E_TAN          590  /* Ϣ�η�-��:û�� */
#define KEI_KATEI_IPPAN           610  /* �����-���� */
#define KEI_KATEI_YUUGOU          620  /* �����-ͻ�� */
#define KEI_KATEI_YUUGOU_KYA      621  /* �����-ͻ��:���� */
#define KEI_IZEN_IPPAN            710  /* ������-���� */
#define KEI_IZEN_HOJO             720  /* ������-��� */
#define KEI_IZEN                  710  /* ������ */
#define KEI_MEIREI_IPPAN          810  /* ̿���-���� */
#define KEI_MEIREI_I              820  /* ̿���-�� */
#define KEI_MEIREI_KO             830  /* ̿���-�� */
#define KEI_MEIREI_SHI            840  /* ̿���-�� */
#define KEI_MEIREI_RO             850  /* ̿���-�� */
#define KEI_MEIREI                810  /* ̿��� */

#ifdef WIN32
#include "pos_sjis.h"
#else
#include "pos_eucjp.h"
#endif
