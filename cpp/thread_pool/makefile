# make clean/all CONFIG=Debug/Release ARCH=linux64/raspi ECHO=0/1 NO_WARN=0/1 VER=c++98/c++11

# the parrent dir of "arch" dir
ROOT_DIR = ../..

#PROJ_SRCS = $(shell xmlstarlet select -t -v //Unit/@filename xx.cbp | grep -e '\.c')
PROJ_SRCS = thread_pool.cpp thread_pool_test.cpp

# list of directories containing header files
PROJ_INC_DIR = ../uncopyable ../waitable_queue ../thread ../shared_ptr

# the executable file
PROJ_OUT = thread_pool_test.out

# list of compiler flags (prepended with "-" sign)
PROJ_CFLAGS = -Wunused-but-set-variable -std=c++98

PROJ_MACROS =

# additional object files (created by other projects)
PROJ_ADD_OBJS = thread.obj

# additional libraries
PROJ_LIBS = boost_system boost_thread boost_chrono

# linker flags
PROJ_LDFLAGS = -lpthread

# list of projects (makefiles) this project depends on
PROJ_DEPENDS  =

include $(ROOT_DIR)/Make/Project.mak


