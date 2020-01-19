# make clean/all CONFIG=Debug/Release ARCH=linux64/raspi ECHO=0/1 NO_WARN=0/1 VER=c++98/c++11

# the parrent dir of "arch" dir
ROOT_DIR = ../..

#PROJ_SRCS = $(shell xmlstarlet select -t -v //Unit/@filename xx.cbp | grep -e '\.c')
PROJ_SRCS = stack_test.cpp

# list of directories containing header files
PROJ_INC_DIR = ../str

# the executable file
PROJ_OUT = stack_test.out

# list of compiler flags (prepended with "-" sign)
PROJ_CFLAGS = -std=c++11

PROJ_MACROS =

# additional object files (created by other projects)
PROJ_ADD_OBJS = str.obj

# additional libraries
PROJ_LIBS =

# linker flags
PROJ_LDFLAGS =

# list of projects (makefiles) this project depends on
PROJ_DEPENDS  = ../str/makefile

include $(ROOT_DIR)/Make/Project.mak


