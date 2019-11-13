# make clean/all CONFIG=Debug/Release ARCH=linux64/raspi ECHO=0/1 NO_WARN=0/1 VER=c++98/c++11

# the parrent dir of "arch" dir
ROOT_DIR = ../..

#PROJ_SRCS = $(shell xmlstarlet select -t -v //Unit/@filename xx.cbp | grep -e '\.c')
PROJ_SRCS = loggerST.cpp loggerST_test.cpp

# list of directories containing header files
PROJ_INC_DIR = ../uncopyable ../loggerMT ../thread ../waitable_queue ../writer ../shared_ptr

# the executable file
PROJ_OUT = loggerST_test.out

# list of compiler flags (prepended with "-" sign)
PROJ_CFLAGS = -Wunused-but-set-variable -std=c++98

PROJ_MACROS = 

# additional object files (created by other projects)
PROJ_ADD_OBJS = loggerMT.obj logMsg.obj thread.obj writer.obj

# additional libraries
PROJ_LIBS = boost_system boost_thread boost_chrono dl

# linker flags
PROJ_LDFLAGS = -pthread

# list of projects (makefiles) this project depends on
PROJ_DEPENDS  = ../loggerMT/makefile ../logMsg/makefile ../thread/makefile ../waitable_queue/makefile ../writer/makefile

include $(ROOT_DIR)/Make/Project.mak


