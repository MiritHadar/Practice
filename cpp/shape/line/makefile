
# make clean/all CONFIG=Debug/Release ARCH=linux64/raspi ECHO=0/1 NO_WARN=0/1 VER=c++98/c++11

# the parrent dir of "arch" dir
ROOT_DIR = ../../..

#PROJ_SRCS = $(shell xmlstarlet select -t -v //Unit/@filename xx.cbp | grep -e '\.c')
PROJ_SRCS = line.cpp line_test.cpp

# list of directories containing header files
PROJ_INC_DIR = $(ROOT_DIR)/cpp/shape/shape3rd_part/include $(ROOT_DIR)/cpp/shape/my_shape $(ROOT_DIR)/cpp/shared_ptr

# the executable file
PROJ_OUT = line_test.out

# list of compiler flags (prepended with "-" sign)
PROJ_CFLAGS = 

PROJ_MACROS =

# additional object files (created by other projects)
PROJ_ADD_OBJS = shape.obj

# additional libraries
PROJ_LIBS = ../shape3rd_part/lib/libpoint.a ../shape3rd_part/lib/libglut_utils.so

LIB_FLAG  = 1
PROJ_LIBS_DIR = .

# linker flags
PROJ_LDFLAGS =

# list of projects (makefiles) this project depends on
PROJ_DEPENDS  = $(ROOT_DIR)/cpp/shape/my_shape/makefile

include $(ROOT_DIR)/Make/Project_shape.mak




################################################################################

# make -f another name - for working with makefile with another name

# ECHO=1 - for status

# CONFIG=Release/Debug - for changing mode

#ARCH=rsbi/linux64 - for changing arch

