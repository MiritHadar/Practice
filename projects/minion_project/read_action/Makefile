
# make clean/all CONFIG=Debug/Release ARCH=linux64/raspi ECHO=0/1 NO_WARN=0/1 VER=c++98/c++11

# the parrent dir of "arch" dir
ROOT_DIR = ../../..

#PROJ_SRCS = $(shell xmlstarlet select -t -v //Unit/@filename xx.cbp | grep -e '\.c')
PROJ_SRCS = read_action_test.cpp

# list of directories containing header files
PROJ_INC_DIR = $(ROOT_DIR)/projects/minion_project/action $(ROOT_DIR)/projects/minion_project/storage $(ROOT_DIR)/cpp/uncopyable $(ROOT_DIR)/cpp/shared_ptr $(ROOT_DIR)/projects/minion_project/request $(ROOT_DIR)/projects/minion_project/response $(ROOT_DIR)/projects/minion_project/packet $(ROOT_DIR)/cpp/loggerMT $(ROOT_DIR)/cpp/loggerMT_singleton $(ROOT_DIR)/cpp/writer $(ROOT_DIR)/cpp/thread $(ROOT_DIR)/cpp/waitableQueue

# the executable file
PROJ_OUT = read_action_test.out

# list of compiler flags (prepended with "-" sign)
PROJ_CFLAGS = 

PROJ_MACROS =

# additional object files (created by other projects)
PROJ_ADD_OBJS = action.obj storage.obj response.obj request.obj packet.obj

# additional libraries
PROJ_LIBS = dl

LIB_FLAG  = 0
PROJ_LIBS_DIR = ../../../cpp/loggerMT_singleton

# linker flags
PROJ_LDFLAGS =

# list of projects (makefiles) this project depends on
PROJ_DEPENDS  = $(ROOT_DIR)/projects/minion_project/action/Makefile $(ROOT_DIR)/projects/minion_project/storage/Makefile $(ROOT_DIR)/projects/minion_project/request/Makefile $(ROOT_DIR)/projects/minion_project/response/Makefile $(ROOT_DIR)/projects/minion_project/packet/Makefile

include $(ROOT_DIR)/Make/Project.mak



################################################################################

# make -f another name - for working with makefile with another name

# ECHO=1 - for status

# CONFIG=Release/Debug - for changing mode

#ARCH=rsbi/linux64 - for changing arch
