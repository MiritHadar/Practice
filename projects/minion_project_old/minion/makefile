# make clean/all CONFIG=Debug/Release ARCH=linux64/raspi ECHO=0/1 NO_WARN=0/1 VER=c++98/c++11

# the parrent dir of "arch" dir
ROOT_DIR = ../../..

#PROJ_SRCS = $(shell xmlstarlet select -t -v //Unit/@filename xx.cbp | grep -e '\.c')
PROJ_SRCS = minion.cpp minion_app.cpp

# list of directories containing header files
PROJ_INC_DIR = $(ROOT_DIR)/cpp/logging ../storage $(ROOT_DIR)/cpp/uncopyable $(ROOT_DIR)/cpp/factory ../action ../read_action ../write_action ../request ../response ../packet ../server ../request_handler ../reactor ../select/fd_listener $(ROOT_DIR)/cpp/shared_ptr

# the executable file
PROJ_OUT = minion.out

# list of compiler flags (prepended with "-" sign)
PROJ_CFLAGS = 

PROJ_MACROS = 

# additional object files (created by other projects)
PROJ_ADD_OBJS = logging.obj storage.obj action.obj read_action.obj write_action.obj request.obj response.obj packet.obj server.obj request_handler.obj reactor.obj fd_listener.obj

# additional libraries
PROJ_LIBS =

# linker flags
PROJ_LDFLAGS = -pthread

# list of projects (makefiles) this project depends on
PROJ_DEPENDS  = $(ROOT_DIR)/cpp/logging/makefile ../storage/makefile  $(ROOT_DIR)/cpp/factory/makefile ../action/makefile ../read_action/makefile ../write_action/makefile ../request/makefile ../response/makefile ../packet/makefile ../server/makefile ../request_handler/makefile ../reactor/makefile ../select/fd_listener/makefile
include $(ROOT_DIR)/Make/Project.mak


