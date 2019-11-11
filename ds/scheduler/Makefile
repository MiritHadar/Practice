
#schedualer

# make clean/all CONFIG=Debug/Release ARCH=linux64/raspi ECHO=0/1

# the parrent dir of "arch" dir
ROOT_DIR = ../..

#PROJ_SRCS = $(shell xmlstarlet select -t -v //Unit/@filename xx.cbp | grep -e '\.c')
PROJ_SRCS = sched.c sched_test_Mirit.c task.c

# list of directories containing header files
PROJ_INC_DIR =  $(ROOT_DIR)/include

# the executable file
PROJ_OUT = sched.out

# list of compiler flags (prepended with "-" sign)
PROJ_CFLAGS =

PROJ_MACROS =

# additional object files (created by other projects)
PROJ_ADD_OBJS = p_queue.o doubly_linked_list.o sorted_list.o uuid.o

# additional libraries
PROJ_LIBS =

# linker flags
PROJ_LDFLAGS =

# list of projects (makefiles) this project depends on
PROJ_DEPENDS  = $(ROOT_DIR)/ds/p_queue/Makefile $(ROOT_DIR)/ds/uuid/Makefile

include $(ROOT_DIR)/Make/Project.mak
