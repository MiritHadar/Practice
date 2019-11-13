
# make clean/all CONFIG=Debug/Release ARCH=linux64/raspi ECHO=0/1 NO_WARN=0/1 VER=c++98/c++11

# the parrent dir of "arch" dir
ROOT_DIR = ../../..

#PROJ_SRCS = $(shell xmlstarlet select -t -v //Unit/@filename xx.cbp | grep -e '\.c')
PROJ_SRCS = dir_monitor.cpp dir_monitor_test.cpp

# list of directories containing header files
PROJ_INC_DIR = $(ROOT_DIR)/cpp/uncopyable $(ROOT_DIR)/cpp/shared_ptr $(ROOT_DIR)/cpp/loggerMT $(ROOT_DIR)/cpp/writer $(ROOT_DIR)/cpp/thread $(ROOT_DIR)/cpp/waitable_queue $(ROOT_DIR)/cpp/loggerST $(ROOT_DIR)/projects/minion_project/fd_listener $(ROOT_DIR)/projects/minion_project/action $(ROOT_DIR)/projects/minion_project/storage $(ROOT_DIR)/projects/minion_project/request $(ROOT_DIR)/projects/minion_project/response $(ROOT_DIR)/projects/minion_project/packet $(ROOT_DIR)/projects/minion_project/minion $(ROOT_DIR)/projects/minion_project/server $(ROOT_DIR)/projects/minion_project/request_handler $(ROOT_DIR)/projects/minion_project/ $(ROOT_DIR)/projects/minion_project/service_locator $(ROOT_DIR)/projects/minion_project/dl_loader $(ROOT_DIR)/projects/minion_project/shared_object $(ROOT_DIR)/cpp/factory $(ROOT_DIR)/projects/minion_project/reactor

# the executable file
PROJ_OUT = dir_monitor_test.out 

# list of compiler flags (prepended with "-" sign)
PROJ_CFLAGS = 

PROJ_MACROS =

# additional object files (created by other projects)
PROJ_ADD_OBJS = loggerST.so reactor.obj fd_listener.obj dl_loader.obj shared_object.obj

# additional libraries
PROJ_LIBS = pthread boost_system boost_thread boost_chrono dl

LIB_FLAG  = 0
PROJ_LIBS_DIR = .

# linker flags
PROJ_LDFLAGS =

# list of projects (makefiles) this project depends on
PROJ_DEPENDS  = $(ROOT_DIR)/projects/minion_project/dl_loader/Makefile

include $(ROOT_DIR)/Make/Project.mak




################################################################################

# make -f another name - for working with makefile with another name

# ECHO=1 - for status

# CONFIG=Release/Debug - for changing mode

#ARCH=rsbi/linux64 - for changing arch
