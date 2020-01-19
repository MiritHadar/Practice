
# make clean/all CONFIG=Debug/Release ARCH=linux64/raspi ECHO=0/1 NO_WARN=0/1 VER=c++98/c++11

# the parrent dir of "arch" dir
ROOT_DIR = ../..

#PROJ_SRCS = $(shell xmlstarlet select -t -v //Unit/@filename xx.cbp | grep -e '\.c')
PROJ_SRCS = parser.cpp parser_test.cpp

# list of directories containing header files
PROJ_INC_DIR = ../uncopyable ../stack

# the executable file
PROJ_OUT = parser_test.out

# list of compiler flags (prepended with "-" sign)
PROJ_CFLAGS = -std=c++11

PROJ_MACROS =

# additional object files (created by other projects)
PROJ_ADD_OBJS = 

# additional libraries
PROJ_LIBS = 

LIB_FLAG  = 0
PROJ_LIBS_DIR = .

# linker flags
PROJ_LDFLAGS =

# list of projects (makefiles) this project depends on
PROJ_DEPENDS  = 

include $(ROOT_DIR)/Make/Project.mak




################################################################################

# make -f another name - for working with makefile with another name

# ECHO=1 - for status

# CONFIG=Release/Debug - for changing mode

#ARCH=rsbi/linux64 - for changing arch
