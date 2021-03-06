PACKAGE = jagtalk
VERSION = 1.5.1

CC	= gcc
RM	= /bin/rm
TAR	= /bin/tar
GZIP	= /bin/gzip

CFLAGS	= -DPACKAGE_NAME=\"jagtalk\" -DPACKAGE_TARNAME=\"jagtalk\" -DPACKAGE_VERSION=\"1.5.1\" -DPACKAGE_STRING=\"jagtalk\ 1.5.1\" -DPACKAGE_BUGREPORT=\"nishimotz@gmail.com\" -DLINUX=1 -DUTF8=1 -DAUTO_DA=1 -DWORDS_LITTLEENDIAN=1
LIBS	=  -lm  -lpthread -ldl
TARGET	= jagtalk

OBJ	= accent.o \
	chasen.o \
	chaone.o \
	dic.o \
	do_output.o \
	do_synthesis.o \
	fileIO.o \
	getline.o \
	hmmsynth.o \
	main.o \
	server.o \
	make_aphrase.o \
	make_breath.o \
	make_duration.o \
	make_mora.o \
	make_parameter.o \
	make_phoneme.o \
	make_sentence.o \
	misc.o \
	mlpg.o \
	model.o \
	modify_parameter.o \
	morph.o \
	read_conf.o \
	send.o \
	sleep.o \
	tag.o \
	text.o \
	tree.o \
	util.o \
	vocoder.o

SRC	= accent.c \
	accent.h \
	chasen.c \
	chaone.c \
	command.h \
	confpara.h \
	da.h \
	defaults.h \
	dic.c \
	do_output.c \
	do_synthesis.c \
	fileIO.c \
	getline c \
	hmmsynth.c \
	hmmsynth.h \
	main.c \
	server.c \
	make_aphrase.c \
	make_breath.c \
	make_duration.c \
	make_mora.c \
	make_parameter.c \
	make_phoneme.c \
	make_sentence.c \
	misc.c \
	misc.h \
	mlpg.c \
	mlpg.h \
	model.c \
	model.h \
	modify_parameter.c \
	morph.c \
	pronunciation.h \
	read_conf.c \
	send.c \
	sleep.c \
	slot.h \
	synthesis.h \
	tag.c \
	tag.h \
	text.c \
	tree.c \
	tree.h \
	util.c \
	vocoder.c \
	vocoder.h

gtalk: $(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ) $(LIBS)

all: $(TARGET)

main.o: synthesis.h command.h slot.h confpara.h

server.o: confpara.h

read_conf.o: synthesis.h confpara.h slot.h

dic.o: strings_eucjp.h strings_sjis.h

text.o: synthesis.h confpara.h slot.h tag.h strings_eucjp.h strings_sjis.h

chasen.o: confpara.h chasen_lib.c

chaone.o: confpara.h chaone.h

tag.o: synthesis.h tag.h

morpph.o: synthesis.h tag.h pos.h pos_eucjp.h

accent.o: synthesis.h accent.h

make_mora.o: synthesis.h pos.h strings_eucjp.h strings_sjis.h pos_eucjp.h

make_aphrase.o: synthesis.h accent.h tag.h

make_breath.o: synthesis.h pos.h pos_eucjp.h

make_phoneme.o: synthesis.h pronunciation.h confpara.h

make_sentence.o: synthesis.h slot.h

send.o: synthesis.h confpara.h

hmmsynth.o: synthesis.h defaults.h misc.h model.h mlpg.h vocoder.h tree.h hmmsynth.h confpara.h

make_duration.o: synthesis.h defaults.h misc.h model.h tree.h hmmsynth.h confpara.h

make_parameter.o: synthesis.h defaults.h misc.h model.h tree.h mlpg.h hmmsynth.h confpara.h

do_synthesis.o: synthesis.h defaults.h misc.h mlpg.h vocoder.h tree.h hmmsynth.h confpara.h slot.h

modify_parameter.o: synthesis.h tag.h defaults.h confpara.h misc.h tree.h hmmsynth.h model.h slot.h

do_output.o: synthesis.h defaults.h confpara.h da.h slot.h do_output_sp.c do_output_portaudio.c do_output_oss.c

fileIO.o: synthesis.h defaults.h slot.h

model.o: synthesis.h misc.h model.h tree.h defaults.h confpara.h hmmsynth.h

tree.o: misc.h tree.h confpara.h hmmsynth.h

mlpg.o: synthesis.h defaults.h misc.h model.h mlpg.h confpara.h tree.h hmmsynth.h vocoder.h

vocoder.o: synthesis.h defaults.h misc.h model.h vocoder.h

misc.o: misc.h

util.o: confpara.h

clean:
	$(RM) -rf *~ $(OBJ) core

allclean:
	$(RM) -rf *~ *.o core .nfs* $(TARGET) config.log config.cache config.status

dist-src = $(SRC)
dist-info  = README RUN Changelog
dist-common = configure configure.in Makefile.in config
dist-etc = data mono.lst ssm.conf chasenrc
DISTFILES = $(dist-src) $(dist-info) $(dist-common) $(dist-etc)

distdir	= $(PACKAGE)-$(VERSION)
dist: distdir
	-chmod -R a+r $(distdir)
	$(TAR) chof $(distdir).tar $(distdir)
	$(GZIP) -f $(distdir).tar
	-rm -rf $(distdir)
distdir: $(DISTFILES)
	-rm -rf $(distdir)
	mkdir $(distdir)
	-chmod 777 $(distdir)
	@for file in $(DISTFILES); do \
	  if test -d $$file; then \
	    cp -pr $$file $(distdir); \
	  else \
	    cp -p $$file $(distdir); \
	  fi \
	done
