# make clean/all CONFIG=Debug/Release ARCH=linux64/raspi ECHO=0/1 NO_WARN=0/1 VER=c++98/c++11

# the parrent dir of "arch" dir
ROOT_DIR = ../../..

#PROJ_SRCS = $(shell xmlstarlet select -t -v //Unit/@filename xx.cbp | grep -e '\.c')
PROJ_SRCS = reactor.cpp reactor_test.cpp

# list of directories containing header files
PROJ_INC_DIR = ../select/fd_listener $(ROOT_DIR)/cpp/uncopyable $(ROOT_DIR)/cpp/logging

# the executable file
PROJ_OUT = reactor_test.out

# list of compiler flags (prepended with "-" sign)
PROJ_CFLAGS =

PROJ_MACROS =

# additional object files (created by other projects)
PROJ_ADD_OBJS = fd_listener.obj logging.obj

# additional libraries
PROJ_LIBS =

# linker flags
PROJ_LDFLAGS =

# list of projects (makefiles) this project depends on
PROJ_DEPENDS  = ../select/fd_listener/makefile $(ROOT_DIR)/cpp/logging/makefile

include $(ROOT_DIR)/Make/Project.mak


