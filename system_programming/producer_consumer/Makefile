
#Ordered_binary_tree

# make clean/all CONFIG=Debug/Release ARCH=linux64/raspi ECHO=0/1

# the parrent dir of "arch" dir
ROOT_DIR = ../..

#PROJ_SRCS = $(shell xmlstarlet select -t -v //Unit/@filename xx.cbp | grep -e '\.c')
PROJ_SRCS = producer_consumer.c

# list of directories containing header files
PROJ_INC_DIR = $(ROOT_DIR)/include

# the executable file
PROJ_OUT = producer_consumer.out

# list of compiler flags (prepended with "-" sign)
PROJ_CFLAGS =

PROJ_MACROS =

# additional object files (created by other projects)S
PROJ_ADD_OBJS =	doubly_linked_list.o  new_circular_buffer.o

# additional libraries
PROJ_LIBS =

# linker flags
PROJ_LDFLAGS =	-pthread

# list of projects (makefiles) this project depends on
PROJ_DEPENDS  = $(ROOT_DIR)/ds/doubly_linked_list/Makefile  $(ROOT_DIR)/system_programming/new_circular_buffer/Makefile

include $(ROOT_DIR)/Make/Project.mak
