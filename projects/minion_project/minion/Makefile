
# make clean/all CONFIG=Debug/Release ARCH=linux64/raspi ECHO=0/1 NO_WARN=0/1 VER=c++98/c++11

# the parrent dir of "arch" dir
ROOT_DIR = ../../..

#PROJ_SRCS = $(shell xmlstarlet select -t -v //Unit/@filename xx.cbp | grep -e '\.c')
PROJ_SRCS = minion.cpp minion_test.cpp

# list of directories containing header files
PROJ_INC_DIR = $(ROOT_DIR)/projects/minion_project/server $(ROOT_DIR)/projects/minion_project/request_handler $(ROOT_DIR)/projects/minion_project/storage $(ROOT_DIR)/cpp/uncopyable $(ROOT_DIR)/cpp/shared_ptr $(ROOT_DIR)/cpp/factory $(ROOT_DIR)/projects/minion_project/action $(ROOT_DIR)/projects/minion_project/request $(ROOT_DIR)/projects/minion_project/response $(ROOT_DIR)/projects/minion_project/packet $(ROOT_DIR)/projects/minion_project/fd_listener $(ROOT_DIR)/projects/minion_project/reactor $(ROOT_DIR)/cpp/loggerMT $(ROOT_DIR)/cpp/writer $(ROOT_DIR)/cpp/thread $(ROOT_DIR)/cpp/waitable_queue $(ROOT_DIR)/cpp/loggerST $(ROOT_DIR)/projects/minion_project/ $(ROOT_DIR)/projects/minion_project/dl_loader $(ROOT_DIR)/projects/minion_project/shared_object $(ROOT_DIR)/projects/minion_project/service_locator $(ROOT_DIR)/projects/minion_project/dir_monitor $(ROOT_DIR)/cpp/logMsg $(ROOT_DIR)/cpp/writer

# the executable file
PROJ_OUT = minion_test.out

# list of compiler flags (prepended with "-" sign)
PROJ_CFLAGS = 

PROJ_MACROS =

# additional object files (created by other projects)
PROJ_ADD_OBJS = server.obj request_handler.obj storage.obj action.obj request.obj response.obj packet.obj fd_listener.obj reactor.obj loggerST.so dir_monitor.obj dl_loader.obj shared_object.obj

# additional libraries
PROJ_LIBS = dl pthread boost_system boost_thread boost_chrono

LIB_FLAG  = 0
PROJ_LIBS_DIR = .

# linker flags
PROJ_LDFLAGS =

# list of projects (makefiles) this project depends on
PROJ_DEPENDS  = $(ROOT_DIR)/projects/minion_project/server/Makefile $(ROOT_DIR)/projects/minion_project/request_handler/Makefile $(ROOT_DIR)/projects/minion_project/storage/Makefile $(ROOT_DIR)/projects/minion_project/action/Makefile $(ROOT_DIR)/projects/minion_project/request/Makefile $(ROOT_DIR)/projects/minion_project/response/Makefile $(ROOT_DIR)/projects/minion_project/packet/Makefile $(ROOT_DIR)/projects/minion_project/reactor/Makefile $(ROOT_DIR)/projects/minion_project/dir_monitor/Makefile #$(ROOT_DIR)/cpp/logMsg/makefile $(ROOT_DIR)/cpp/writer/makefile

include $(ROOT_DIR)/Make/Project.mak




################################################################################

# make -f another name - for working with makefile with another name

# ECHO=1 - for status

# CONFIG=Release/Debug - for changing mode

#ARCH=rsbi/linux64 - for changing arch
