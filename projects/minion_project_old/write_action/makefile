# make clean/all CONFIG=Debug/Release ARCH=linux64/raspi ECHO=0/1 NO_WARN=0/1 VER=c++98/c++11

# the parrent dir of "arch" dir
ROOT_DIR = ../../..

#PROJ_SRCS = $(shell xmlstarlet select -t -v //Unit/@filename xx.cbp | grep -e '\.c')
PROJ_SRCS = write_action_test.cpp

# list of directories containing header files
PROJ_INC_DIR = ../action ../storage ../request ../response $(ROOT_DIR)/cpp/uncopyable ../packet  $(ROOT_DIR)/cpp/shared_ptr $(ROOT_DIR)/cpp/loggerMT $(ROOT_DIR)/cpp/loggerST

# the executable file
PROJ_OUT = write_action_test.out

# list of compiler flags (prepended with "-" sign)
PROJ_CFLAGS =

PROJ_MACROS =

# additional object files (created by other projects)
PROJ_ADD_OBJS = storage.obj request.obj response.obj action.obj packet.obj

# additional libraries
PROJ_LIBS = dl

# linker flags
PROJ_LDFLAGS =

# list of projects (makefiles) this project depends on
PROJ_DEPENDS  = ../storage/makefile ../request/makefile ../response/makefile ../action/makefile ../packet/makefile

include $(ROOT_DIR)/Make/Project.mak


