# Simplified Makefile for building mconf
# Adapted from Linux kernel kconfig system

CC ?= gcc
CFLAGS := -Wall -Wmissing-prototypes -Wstrict-prototypes -O2 -fomit-frame-pointer -I. -Iinclude
LDFLAGS :=

# ncurses flags
NCURSES_CFLAGS := $(shell pkg-config --cflags ncursesw 2>/dev/null || pkg-config --cflags ncurses 2>/dev/null || echo "-I/usr/include/ncursesw")
NCURSES_LIBS := $(shell pkg-config --libs ncursesw 2>/dev/null || pkg-config --libs ncurses 2>/dev/null || echo "-lncursesw -ltinfo")

CFLAGS += $(NCURSES_CFLAGS)
LDFLAGS += $(NCURSES_LIBS)

# Common object files
COMMON_OBJS := \
	confdata.o \
	expr.o \
	lexer.lex.o \
	menu.o \
	parser.tab.o \
	preprocess.o \
	symbol.o \
	util.o

# mconf object files
MCONF_OBJS := \
	mconf.o \
	$(COMMON_OBJS) \
	lxdialog/checklist.o \
	lxdialog/inputbox.o \
	lxdialog/menubox.o \
	lxdialog/textbox.o \
	lxdialog/util.o \
	lxdialog/yesno.o \
	mnconf-common.o

# conf object files
CONF_OBJS := \
	conf.o \
	$(COMMON_OBJS)

# Targets
.PHONY: all clean mconf conf

all: mconf conf

mconf: $(MCONF_OBJS)
	$(CC) -o $@ $^ $(LDFLAGS)

conf: $(CONF_OBJS)
	$(CC) -o $@ $^ $(LDFLAGS)

# Pattern rules
%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

# lxdialog objects
lxdialog/%.o: lxdialog/%.c
	$(CC) $(CFLAGS) -c -o $@ $<

# Dependencies
lexer.lex.o: lexer.lex.c parser.tab.h
parser.tab.o: parser.tab.c parser.tab.h

mconf.o: mconf.c lkc.h internal.h mnconf-common.h
conf.o: conf.c lkc.h internal.h
mnconf-common.o: mnconf-common.c lkc.h internal.h mnconf-common.h

clean:
	rm -f mconf conf *.o lxdialog/*.o