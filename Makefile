
ROOT_DIR = .
SRC_DIR = $(ROOT_DIR)/src
OBJ_DIR = $(ROOT_DIR)/obj
DEP_DIR = $(ROOT_DIR)/dep

MAIN_TARGET = halgorithm.so
MAIN_VER = 1
MINOR_VER = 0

FULL_TARGET = lib$(MAIN_TARGET).$(MAIN_VER).$(MINOR_VER)

SRC_FILES = $(wildcard $(SRC_DIR)/*.c)

#DEP_FILES2 = $($(SRC_FILES):$(SRC_DIR)=$(DEP_DIR))
DEP_FILES2 = $(subst $(SRC_DIR),$(DEP_DIR),$(SRC_FILES))
DEP_FILES = $(subst .c,.d,$(DEP_FILES2))

#OBJ_FILES2 = $($(SRC_FILES):$(SRC_DIR)=$(OBJ_DIR))
OBJ_FILES2 = $(subst $(SRC_DIR),$(OBJ_DIR),$(SRC_FILES))
OBJ_FILES = $(subst .c,.o,$(OBJ_FILES2))


OBJS = $(OBJ_DIR)/halgorithm.o
DEPS = $()/

CC = gcc
DEBUG = #-g
CFLAGS = -c -fPIC
DEPFLAGS = -M -MT $(OBJ_DIR)/

#$(OBJ_DIR)/halgorithm.o: $($$@:.o=.c) $($$@:.o=.h)
#	$(CC) $(CFLAGS) $(DEBUG)

.PHONY: all-before all

all: all-before $(FULL_TARGET)
	@echo "All done!"

all-before: dirs

$(FULL_TARGET): $(OBJ_FILES)
	$(CC) $(DEBUG) -shared -Wl,-soname,lib$(MAIN_TARGET).$(MAIN_VER) -o $(FULL_TARGET)

dirs: $(OBJ_DIR) $(DEP_DIR)
#@echo "Directories created"

$(OBJ_DIR):
	@mkdir -p $@

$(DEP_DIR):
	@mkdir -p $@

#$(OBJ_DIR)/%.o: $(DEP_DIR)/%.d
#	$(CC) $(CFLAGS)  -o $@

#create dependency files
$(DEP_DIR)/%.d: $(SRC_DIR)/%.c
	$(CC) -M -MF $@ -MT $(OBJ_DIR)/$*.o $<

$(OBJ_DIR)/%.o:
	$(CC) $(CFLAGS) $(DEBUG) -o $@ $(SRC_DIR)/$*.c

#include dependency files
-include $(DEP_FILES)

clean:
	rm -f $(DEP_DIR)/* $(OBJ_DIR)/* $(FULL_TARGET)

