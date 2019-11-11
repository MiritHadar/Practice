# make clean/all CONFIG=Debug/Release ARCH=linux64/raspi ECHO=0/1 NO_WARN=0/1 VER=c++98/c++11

# the parrent dir of "arch" dir
ROOT_DIR = ../..

#PROJ_SRCS = $(shell xmlstarlet select -t -v //Unit/@filename xx.cbp | grep -e '\.c')
PROJ_SRCS = loggerMT.cpp loggerMT_test.cpp

# list of directories containing header files
PROJ_INC_DIR = $(ROOT_DIR)/cpp/logMsg $(ROOT_DIR)/cpp/thread $(ROOT_DIR)/cpp/waitable_queue $(ROOT_DIR)/cpp/uncopyable $(ROOT_DIR)/cpp/writer

# the executable file
PROJ_OUT = loggerMT_test.out

# list of compiler flags (prepended with "-" sign)
PROJ_CFLAGS = #-Wunused-but-set-variable -std=c++11

PROJ_MACROS =

# additional object files (created by other projects)
PROJ_ADD_OBJS = thread.obj logMsg.obj writer.obj

# additional libraries
PROJ_LIBS = boost_system boost_thread boost_chrono

# linker flags
PROJ_LDFLAGS = -pthread

# list of projects (makefiles) this project depends on
PROJ_DEPENDS  = $(ROOT_DIR)/cpp/thread/makefile $(ROOT_DIR)/cpp/logMsg/makefile $(ROOT_DIR)/cpp/waitable_queue/makefile $(ROOT_DIR)/cpp/writer/makefile

include $(ROOT_DIR)/Make/Project.mak


