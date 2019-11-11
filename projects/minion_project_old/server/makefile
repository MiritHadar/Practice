# make clean/all CONFIG=Debug/Release ARCH=linux64/raspi ECHO=0/1 NO_WARN=0/1 VER=c++98/c++11

# the parrent dir of "arch" dir
ROOT_DIR = ../../..

#PROJ_SRCS = $(shell xmlstarlet select -t -v //Unit/@filename xx.cbp | grep -e '\.c')
PROJ_SRCS = server.cpp server_test.cpp

# list of directories containing header files
PROJ_INC_DIR = $(ROOT_DIR)/system_programming/udp/server $(ROOT_DIR)/system_programming/udp/client $(ROOT_DIR)/system_programming/tcp/server $(ROOT_DIR)/system_programming/tcp/client $(ROOT_DIR)/cpp/logging

# the executable file
PROJ_OUT = server_test.out

# list of compiler flags (prepended with "-" sign)
PROJ_CFLAGS = -Wunused-but-set-variable -std=c++11

PROJ_MACROS =

# additional object files (created by other projects)
PROJ_ADD_OBJS = logging.obj server_udp.obj server_tcp.obj

# additional libraries
PROJ_LIBS =

# linker flags
PROJ_LDFLAGS = -pthread

# list of projects (makefiles) this project depends on
PROJ_DEPENDS  = $(ROOT_DIR)/system_programming/udp/server/makefile $(ROOT_DIR)/system_programming/udp/client/makefile $(ROOT_DIR)/system_programming/tcp/server/makefile $(ROOT_DIR)/system_programming/tcp/client/makefile $(ROOT_DIR)/cpp/logging/makefile

include $(ROOT_DIR)/Make/Project.mak


