
#Ordered_binary_tree

# make clean/all CONFIG=Debug/Release ARCH=linux64/raspi ECHO=0/1

# the parrent dir of "arch" dir
ROOT_DIR = ../..

#PROJ_SRCS = $(shell xmlstarlet select -t -v //Unit/@filename xx.cbp | grep -e '\.c')
PROJ_SRCS = shuf_threads.c  shuf_threads_test.c

# list of directories containing header files
PROJ_INC_DIR = $(ROOT_DIR)/include

# the executable file
PROJ_OUT = shuf_threads_test.out

# list of compiler flags (prepended with "-" sign)
PROJ_CFLAGS =

PROJ_MACROS =

# additional object files (created by other projects)S
PROJ_ADD_OBJS =	sort.o	heapify.o

# additional libraries
PROJ_LIBS =

# linker flags
PROJ_LDFLAGS =	-pthread

# list of projects (makefiles) this project depends on
PROJ_DEPENDS  = $(ROOT_DIR)/ds/sort/Makefile

include $(ROOT_DIR)/Make/Project.mak
