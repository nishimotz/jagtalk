/* $Id: strings_sjis.h,v 1.5 2009/02/12 17:43:42 sako Exp $                                            */
#define TOKEN_MEISHI "����"
#define TOKEN_DOUSHI "����"
#define TOKEN_KEIYOUSHI "�`�e��"

#define KUTEN "�A"
#define TOUTEN "�B"
#define GIMONFU "�H"

#define KATAKANA_SMALL_A "�@"
#define KATAKANA_SMALL_I "�B"
#define KATAKANA_SMALL_U "�D"
#define KATAKANA_SMALL_E "�F"
#define KATAKANA_SMALL_O "�H"
#define KATAKANA_SMALL_YA "��"
#define KATAKANA_SMALL_YU "��"
#define KATAKANA_SMALL_YO "��"

/*---- for text.c ----*/
#define KANSUUJI_ZERO "�Z"
#define KANSUUJI_ICHI "��"
#define KANSUUJI_NI "��"
#define KANSUUJI_SAN "�O"
#define KANSUUJI_SHI "�l"
#define KANSUUJI_GO "��"
#define KANSUUJI_ROKU "�Z"
#define KANSUUJI_SHICHI "��"
#define KANSUUJI_HACHI "��"
#define KANSUUJI_KYUU "��"

#define KANSUUJI_KETA_ZERO "�Z"
#define KANSUUJI_KETA_ICHI "��"
#define KANSUUJI_KETA_JUU "�\"
#define KANSUUJI_KETA_HYAKU "�S"
#define KANSUUJI_KETA_SEN "��"
#define KANSUUJI_KETA_MAN "��"
#define KANSUUJI_KETA_OKU "��"
#define KANSUUJI_KETA_CHOU "��"

#define KANJI_TIME_NEN "�N"
#define KANJI_TIME_TSUKI "��"
#define KANJI_TIME_NICHI "��"
#define KANJI_TIME_JI "��"
#define KANJI_TIME_FUN "��"
#define KANJI_TIME_BYOU "�b"

#define ZENKAKU_EXCLAMATION "�I"
#define ZENKAKU_DOUBLE_QUOTATION "�h"
#define ZENKAKU_SHARP "��"
#define ZENKAKU_DOLLAR "��"
#define ZENKAKU_PERCENT "��"
#define ZENKAKU_AMPERSAND "��"
#define ZENKAKU_QUOTATION "�f"
#define ZENKAKU_LEFT_PARENTHESIS "�i"
#define ZENKAKU_RIGHT_PARENTHESIS "�j"
#define ZENKAKU_ASTERISK "��"
#define ZENKAKU_PLUS "�{"
#define ZENKAKU_COMMA "�C"
#define ZENKAKU_CHOUON "�["
#define ZENKAKU_PERIOD "�D"
#define ZENKAKU_TOUTEN "�A"
#define ZENKAKU_MINUS "�|"
#define ZENKAKU_KUTEN "�B"
#define ZENKAKU_SLASH "�^"
#define ZENKAKU_EQUAL "��"
#define ZENKAKU_QUESTION "�H"
#define ZENKAKU_COLON "�F"
#define ZENKAKU_SEMICOLON "�G"
#define ZENKAKU_EN "��"
#define ZENKAKU_ATMARK "��"
#define ZENKAKU_HAT "�O"
#define ZENKAKU_LT "��"
#define ZENKAKU_GT "��"
#define ZENKAKU_UNDERSCORE "�Q"
#define ZENKAKU_LEFT_BRACKET "�m"
#define ZENKAKU_RIGHT_BRACKET "�n"
#define ZENKAKU_BACK_QUOTATION "�e"
#define ZENKAKU_LEFT_BRACE "�o"
#define ZENKAKU_RIGHT_BRACE "�p"
#define ZENKAKU_VERTICAL_BAR "�b"

#define PRON_SYM_TSUITACHI "<PRON SYM='�c�C�^�`'>"
#define PRON_SYM_FUTSUKA "<PRON SYM='�t�c�J'>"
#define PRON_SYM_MIKKA "<PRON SYM='�~�b�J'>"
#define PRON_SYM_YOKKA "<PRON SYM='���b�J'>"
#define PRON_SYM_ITSUKA "<PRON SYM='�C�c�J'>"
#define PRON_SYM_MUIKA "<PRON SYM='���C�J'>"
#define PRON_SYM_NANOKA "<PRON SYM='�i�m�J'>"
#define PRON_SYM_YOUKA "<PRON SYM='���[�J'>"
#define PRON_SYM_KOKONOKA "<PRON SYM='�R�R�m�J'>"
#define PRON_SYM_TOUKA "<PRON SYM='�g�[�J'>"
#define PRON_SYM_HATSUKA "<PRON SYM='�n�c�J'>"

#define ZENKAKU_ALPHABET_FIRST_BYTE 0x82
#define ZENKAKU_NUMBER_SECOND_BYTE_MIN 0x4F
#define ZENKAKU_NUMBER_SECOND_BYTE_MAX 0x58
#define ZENKAKU_CAPITAL_ALPHABET_SECOND_BYTE_MIN 0x60
#define ZENKAKU_CAPITAL_ALPHABET_SECOND_BYTE_MAX 0x79
#define ZENKAKU_ALPHABET_SECOND_BYTE_MIN 0x81
#define ZENKAKU_ALPHABET_SECOND_BYTE_MAX 0x9A

#define ACCENT_MARK "�f"
#define is_ZENKAKU_ALPNUM(x,y) ( (x) == ZENKAKU_ALPHABET_FIRST_BYTE && ( \
( ((y) >= ZENKAKU_NUMBER_SECOND_BYTE_MIN) && ((y) <= ZENKAKU_ALPHABET_SECOND_BYTE_MAX))))
