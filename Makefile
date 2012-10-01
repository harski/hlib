# Copyright 2011-2012 Tuomo Hartikainen <hartitu@gmail.com>.
# Licensed under the 2-clause BSD license.


MAJORVER =0
MIDVER =1
MINORVER =0

LIBNAME =libhutil

ROOT_DIR =.
SRC_DIR =$(ROOT_DIR)/src
OBJ_DIR =$(ROOT_DIR)/obj
SOBJ_DIR =$(ROOT_DIR)/sobj

PREFIX =/usr/local
LIBDIR =$(PREFIX)/lib
INCLUDEDIR =$(PREFIX)/include

CC =gcc
AR =ar
CFLAGS =-c -Wall -pedantic

ifdef DEBUG
CFLAGS += -g
else
CFLAGS += -O2
endif

LIBS =-lm

STATICCFLAGS =
STATICARFLAGS =-cvq
SCFLAGS =$(CFLAGS) -fPIC
SHAREDCFLAGS =-shared -Wl,-soname,$(LIBNAME).so.$(MAJORVER)

TARGET_STATIC =$(LIBNAME).a
TARGET_SHARED =$(LIBNAME).so.$(MAJORVER).$(MIDVER).$(MINORVER)

SRC_FILES =$(wildcard $(SRC_DIR)/*.c)

OBJ_FILES =$(subst $(SRC_DIR),$(OBJ_DIR),$(SRC_FILES))
OBJ_FILES :=$(subst .c,.o,$(OBJ_FILES))

SOBJ_FILES =$(subst $(SRC_DIR),$(SOBJ_DIR),$(SRC_FILES))
SOBJ_FILES :=$(subst .c,.o,$(SOBJ_FILES))


all: all-before shared static

all-before: dirs

install: install-shared install-static

static: $(TARGET_STATIC)

shared: $(TARGET_SHARED)

$(TARGET_SHARED): $(SOBJ_FILES)
	$(CC) $(SHAREDCFLAGS) $(LIBS) -o $@ $(SOBJ_FILES)

$(TARGET_STATIC): $(OBJ_FILES)
	$(AR) $(STATICARFLAGS) $@ $(OBJ_FILES)

install-shared: $(PREFIX) $(LIBDIR) $(INCLUDEDIR)
	install $(TARGET_SHARED) $(LIBDIR)
	ln -sf $(LIBDIR)/$(LIBNAME).so.$(MAJORVER) $(LIBDIR)/$(LIBNAME).so
	ln -sf $(LIBDIR)/$(LIBNAME).so.$(MAJORVER).$(MIDVER) $(LIBDIR)/$(LIBNAME).so.$(MAJORVER)
	ln -sf $(LIBDIR)/$(TARGET_SHARED) $(LIBDIR)/$(LIBNAME).so.$(MAJORVER).$(MIDVER)
	install src/hutil.h $(INCLUDEDIR)

install-static: $(PREFIX) $(LIBDIR) $(INCLUDEDIR)
	install $(TARGET_STATIC) $(LIBDIR)

doc: src/hutil.h
	doxygen Doxyfile

dirs: $(OBJ_DIR) $(SOBJ_DIR)

$(OBJ_DIR):
	@mkdir -p $@

$(SOBJ_DIR):
	@mkdir -p $@

$(PREFIX):
	@mkdir -p $@

$(LIBDIR):
	@mkdir -p $@

$(INCLUDEDIR):
	@mkdir -p $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(SRC_DIR)/hutil.h
	$(CC) $(CFLAGS) -o $@ $(SRC_DIR)/$*.c

$(SOBJ_DIR)/%.o: $(SRC_DIR)/%.c $(SRC_DIR)/hutil.h
	$(CC) $(SCFLAGS) -o $@ $(SRC_DIR)/$*.c

clean:
	rm -rf $(OBJ_DIR)/ $(SOBJ_DIR)/ $(LIBNAME).a $(LIBNAME).so.*

uninstall:
	rm -rf $(LIBDIR)/libhutil.so*
	rm -rf $(LIBDIR)/libhutil.a
	rm -rf $(INCLUDEDIR)/hutil.h

.PHONY: all all-before clean doc install install-shared install-static shared static uninstall

