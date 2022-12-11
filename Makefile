# *** Make utility to build CServer. This file builds multiple component of CServer\
  *** This Makefile builds following components\
  *** Stream handlers - Provides generic interface to perform stream operations\
  *** Utilites - CServer utilities and common C-stdlib safe methods.\
  *** APP - CServer app\
  *** server - CServer library to handle/parse and route requests\
  *********************************************************************************\
  Author - Anand Kumar\
  ********************************************************************************* 

CC=gcc
CFLAGS=-Wall -pedantic

IODIR=./stream/
UTILSDIR=./utils/
SERVERDIR=./server/
APPDIR=./app/
OBJDIR=./obj/

ALLINCLUDES=-I$(UTILSDIR)include -I$(IODIR)include -I$(SERVERDIR)include -I$(APPDIR)include

ENABLE_LOG=-DLOG_ENABLED -DDEBUG

MACRO=

UTILOBJS=$(patsubst $(UTILSDIR)%.c,$(OBJDIR)%.o,$(wildcard $(UTILSDIR)*.c))
IOOBJS=$(patsubst $(IODIR)%.c,$(OBJDIR)%.o,$(wildcard $(IODIR)*.c))
APPOBJS=$(patsubst $(APPDIR)%.c,$(OBJDIR)%.o,$(wildcard $(APPDIR)*.c))
SERVEROBJS=$(patsubst $(SERVERDIR)%.c,$(OBJDIR)%.o,$(wildcard $(SERVERDIR)*.c))

$(OBJDIR)%.o : $(IODIR)%.c
	$(CC) -c -I$(IODIR)include -I$(UTILSDIR)include $(CFLAGS) $(MACRO) $< -o $@
$(OBJDIR)%.o : $(UTILSDIR)%.c
	$(CC) -c -I$(UTILSDIR)include $(CFLAGS) $(MACRO) $< -o $@
$(OBJDIR)%.o : $(APPDIR)%.c
	$(CC) -c $(ALLINCLUDES) $(CFLAGS) $(MACRO)  $< -o $@ 
$(OBJDIR)%.o : $(SERVERDIR)%.c
	$(CC) -c $(CFLAGS) $(MACRO) $(ALLINCLUDES) $< -o $@

#auto-generated file is to be generated before code compilation can begin.
pre-built :
	mkdir -p $(OBJDIR)
	python3 tools/register_handlers.py

deps : $(UTILOBJS)  $(IOOBJS) $(APPOBJS) $(SERVEROBJS)

cserver : pre-built deps
	$(CC) $(CFLAGS) $(ALLINCLUDES) $(MACRO) $(UTILOBJS) $(IOOBJS) $(APPOBJS) $(SERVEROBJS) cserver.c -o cserver

clean :
	rm -f $(OBJDIR)/*
	rmdir $(OBJDIR)
	rm -f cserver
