
# make clean/all CONFIG=Debug/Release ARCH=linux64/raspi ECHO=0/1 NO_WARN=0/1 VER=c++98/c++11

# the parrent dir of "arch" dir
ROOT_DIR = ../../..

#PROJ_SRCS = $(shell xmlstarlet select -t -v //Unit/@filename xx.cbp | grep -e '\.c')
PROJ_SRCS = dl_loader.cpp dl_loader_test.cpp

# list of directories containing header files
PROJ_INC_DIR = $(ROOT_DIR)/cpp/uncopyable $(ROOT_DIR)/projects/minion_project/shared_object $(ROOT_DIR)/projects/minion_project/ $(ROOT_DIR)/cpp/shared_ptr

# the executable file
PROJ_OUT = dl_loader_test.out

# list of compiler flags (prepended with "-" sign)
PROJ_CFLAGS = 

PROJ_MACROS =

# additional object files (created by other projects)
PROJ_ADD_OBJS = shared_object.obj loggerST.so

# additional libraries
PROJ_LIBS = pthread boost_system boost_thread boost_chrono dl

LIB_FLAG  = 0
PROJ_LIBS_DIR = .

# linker flags
PROJ_LDFLAGS =

# list of projects (makefiles) this project depends on
PROJ_DEPENDS  = $(ROOT_DIR)/projects/minion_project/shared_object/Makefile

include $(ROOT_DIR)/Make/Project.mak



################################################################################

# make -f another name - for working with makefile with another name

# ECHO=1 - for status

# CONFIG=Release/Debug - for changing mode

#ARCH=rsbi/linux64 - for changing arch
