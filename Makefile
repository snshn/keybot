# Makefile for keybot - an automated keyboard input tool for X11 and macOS
# See LICENSE file for copyright and license details

PROGNAME = keybot

CFLAGS = -std=c99 -s -pedantic -Wall -Wextra -Wfatal-errors -pedantic-errors -O3 -D_XOPEN_SOURCE=500 -D_POSIX_C_SOURCE=200809L
CC     = cc $(CFLAGS)

UNAME_S := $(shell uname -s)

ifeq ($(UNAME_S),Darwin)
    LIBS = -framework ApplicationServices -framework Carbon -framework CoreFoundation
else
    LIBS = -lX11
endif

all: $(PROGNAME)
.PHONY: all

$(PROGNAME):
	$(CC) -o $(PROGNAME) src/$(PROGNAME).c $(LIBS)

clean:
	@rm -f $(PROGNAME)
.PHONY: clean

install: all
	@echo installing executable file to ${DESTDIR}${PREFIX}/bin
	@mkdir -p ${DESTDIR}${PREFIX}/bin
	@cp -f $(PROGNAME) ${DESTDIR}${PREFIX}/bin
	@chmod 755 ${DESTDIR}${PREFIX}/bin/$(PROGNAME)
.PHONY: install

uninstall:
	@echo removing executable file from ${DESTDIR}${PREFIX}/bin
	@rm -f ${DESTDIR}${PREFIX}/bin/$(PROGNAME)
.PHONY: uninstall
