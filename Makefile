

MAJORVER =1
MINORVER =0

LIBNAME =libhutil

ROOT_DIR =.
SRC_DIR =$(ROOT_DIR)/src
OBJ_DIR =$(ROOT_DIR)/obj
SOBJ_DIR =$(ROOT_DIR)/sobj
DEP_DIR =$(ROOT_DIR)/dep

SHARED_DIR =/opt/lib

CC =gcc
AR =ar
CFLAGS =-c -Wall
DEBUG =

STATICCFLAGS =
STATICARFLAGS =-cvq
SCFLAGS =$(CFLAGS) -fPIC
SHAREDCFLAGS =-shared -Wl,-soname,$(LIBNAME).so.$(MAJORVER)
DEPFLAGS =-M -MT $(OBJDIR)/

SRC_FILES =$(wildcard $(SRC_DIR)/*.c)

DEP_FILES2 =$(subst $(SRC_DIR),$(DEP_DIR),$(SRC_FILES))
DEP_FILES =$(subst .c,.d,$(DEP_FILES2))

OBJ_FILES2 =$(subst $(SRC_DIR),$(OBJ_DIR),$(SRC_FILES))
OBJ_FILES =$(subst .c,.o,$(OBJ_FILES2))

SOBJ_FILES2 =$(subst $(SRC_DIR),$(SOBJ_DIR),$(SRC_FILES))
SOBJ_FILES =$(subst .c,.o,$(SOBJ_FILES2))


.PHONY: all all-before clean libs dirs install-shared install-static

all: all-before libs

all-before: dirs

install: install-shared install-static

libs: $(LIBNAME).a $(LIBNAME).so.$(MAJORVER).$(MINORVER)

$(LIBNAME).so.$(MAJORVER).$(MINORVER): $(SOBJ_FILES)
	$(CC) $(SHAREDCFLAGS) -o $(LIBNAME).so.$(MAJORVER).$(MINORVER) $(SOBJ_FILES)

$(LIBNAME).a: $(OBJ_FILES)
	$(AR) $(STATICARFLAGS) $(LIBNAME).a $(OBJ_FILES)

install-shared:
	mv $(LIBNAME).so.$(MAJORVER).$(MINORVER) /opt/lib
	ln -sf $(SHARED_DIR)/$(LIBNAME).so.$(MAJORVER).$(MINORVER) $(SHARED_DIR)/$(LIBNAME).so
	ln -sf $(SHARED_DIR)/$(LIBNAME).so.$(MAJORVER).$(MINORVER) $(SHARED_DIR)/$(LIBNAME).so.$(MAJORVER)

install-static:

dirs: $(OBJ_DIR) $(DEP_DIR) $(SOBJ_DIR)

$(OBJ_DIR):
	@mkdir -p $@

$(DEP_DIR):
	@mkdir -p $@

$(SOBJ_DIR):
	@mkdir -p $@

#create dependency files
$(DEP_DIR)/%.d: $(SRC_DIR)/%.c
	$(CC) -M -MF $@ -MT $(OBJ_DIR)/$*.o $<

$(OBJ_DIR)/%.o:
	$(CC) $(CFLAGS) $(DEBUG) -o $@ $(SRC_DIR)/$*.c

$(SOBJ_DIR)/%.o:
	$(CC) $(SCFLAGS) $(DEBUG) -o $@ $(SRC_DIR)/$*.c

#include dependency files
-include $(DEP_FILES)

clean:
	rm -f $(DEP_DIR)/* $(OBJ_DIR)/* $(SOBJ_DIR)/* $(LIBNAME).a $(LIBNAME).so.$(MAJORVER).$(MINORVER)


