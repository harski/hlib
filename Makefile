

MAJORVER =1
MINORVER =0

LIBNAME =libhutil

ROOT_DIR =.
SRC_DIR =$(ROOT_DIR)/src
OBJ_DIR =$(ROOT_DIR)/obj
SOBJ_DIR =$(ROOT_DIR)/sobj
DEP_DIR =$(ROOT_DIR)/dep

PREFIX =/usr/local
LIBDIR =$(PREFIX)/lib
INCLUDEDIR =$(PREFIX)/include

CC =gcc
AR =ar
CFLAGS =-c -Wall
DEBUG =

STATICCFLAGS =
STATICARFLAGS =-cvq
SCFLAGS =$(CFLAGS) -fPIC
SHAREDCFLAGS =-shared -Wl,-soname,$(LIBNAME).so.$(MAJORVER)
DEPFLAGS =-M -MT $(OBJDIR)/

TARGET_STATIC =$(LIBNAME).a
TARGET_SHARED =$(LIBNAME).so.$(MAJORVER).$(MINORVER)

SRC_FILES =$(wildcard $(SRC_DIR)/*.c)

DEP_FILES2 =$(subst $(SRC_DIR),$(DEP_DIR),$(SRC_FILES))
DEP_FILES =$(subst .c,.d,$(DEP_FILES2))

OBJ_FILES2 =$(subst $(SRC_DIR),$(OBJ_DIR),$(SRC_FILES))
OBJ_FILES =$(subst .c,.o,$(OBJ_FILES2))

SOBJ_FILES2 =$(subst $(SRC_DIR),$(SOBJ_DIR),$(SRC_FILES))
SOBJ_FILES =$(subst .c,.o,$(SOBJ_FILES2))


all: all-before shared static

all-before: dirs

install: install-shared install-static

static: $(TARGET_STATIC)

shared: $(TARGET_SHARED)

$(TARGET_SHARED): $(SOBJ_FILES)
	$(CC) $(SHAREDCFLAGS) -o $@ $(SOBJ_FILES)

$(TARGET_STATIC): $(OBJ_FILES)
	$(AR) $(STATICARFLAGS) $@ $(OBJ_FILES)

# TODO: install the headers, too!
install-shared: $(PREFIX) $(LIBDIR) $(INCLUDEDIR)
	install $(TARGET_SHARED) $(LIBDIR)
	ln -sf $(LIBDIR)/$(LIBNAME).so.$(MAJORVER) $(LIBDIR)/$(LIBNAME).so
	ln -sf $(LIBDIR)/$(TARGET_SHARED) $(LIBDIR)/$(LIBNAME).so.$(MAJORVER)

install-static: $(PREFIX) $(LIBDIR) $(INCLUDEDIR)
	install $(TARGET_STATIC) $(LIBDIR)

dirs: $(OBJ_DIR) $(DEP_DIR) $(SOBJ_DIR)

$(OBJ_DIR):
	@mkdir -p $@

$(DEP_DIR):
	@mkdir -p $@

$(SOBJ_DIR):
	@mkdir -p $@

$(PREFIX):
	@mkdir -p $@

$(LIBDIR):
	@mkdir -p $@

$(INCLUDEDIR):
	@mkdir -p $@

#create and include dependency files
$(DEP_DIR)/%.d: $(SRC_DIR)/%.c
	$(CC) -M -MF $@ -MT $(OBJ_DIR)/$*.o $<
	-include $(DEP_FILES)

$(OBJ_DIR)/%.o:
	$(CC) $(CFLAGS) $(DEBUG) -o $@ $(SRC_DIR)/$*.c

$(SOBJ_DIR)/%.o:
	$(CC) $(SCFLAGS) $(DEBUG) -o $@ $(SRC_DIR)/$*.c

clean:
	rm -rf $(DEP_DIR)/ $(OBJ_DIR)/ $(SOBJ_DIR)/ $(LIBNAME).a $(LIBNAME).so.$(MAJORVER).$(MINORVER)

.PHONY: all all-before clean install install-shared install-static shared static

