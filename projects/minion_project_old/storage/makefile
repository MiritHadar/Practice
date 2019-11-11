# make clean/all CONFIG=Debug/Release ARCH=linux64/raspi ECHO=0/1 NO_WARN=0/1 VER=c++98/c++11

# the parrent dir of "arch" dir
ROOT_DIR = ../../..

#PROJ_SRCS = $(shell xmlstarlet select -t -v //Unit/@filename xx.cbp | grep -e '\.c')
PROJ_SRCS = storage.cpp storage_test.cpp

# list of directories containing header files
PROJ_INC_DIR = $(ROOT_DIR)/cpp/uncopyable $(ROOT_DIR)/cpp/logging ../packet

# the executable file
PROJ_OUT = storage_test.out

# list of compiler flags (prepended with "-" sign)
PROJ_CFLAGS = -Wunused-but-set-variable -std=c++98

PROJ_MACROS =

# additional object files (created by other projects)
PROJ_ADD_OBJS = logging.obj packet.obj

# additional libraries
PROJ_LIBS =

# linker flags
PROJ_LDFLAGS =

# list of projects (makefiles) this project depends on
PROJ_DEPENDS = $(ROOT_DIR)/cpp/logging/makefile ../packet/makefile

include $(ROOT_DIR)/Make/Project.mak


