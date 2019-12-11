# make clean/all CONFIG=Debug/Release ARCH=linux64/raspi ECHO=0/1

# the parrent dir of "arch" dir
ROOT_DIR = ../../..

#PROJ_SRCS = $(shell xmlstarlet select -t -v //Unit/@filename xx.cbp | grep -e '\.c')
PROJ_SRCS = ex_4.c 

# list of directories containing header files
PROJ_INC_DIR = ../../../ds/src/cir_buffer

# the executable file
PROJ_OUT = ex_4.out

# list of compiler flags (prepended with "-" sign)
PROJ_CFLAGS = -Wunused-but-set-variable

PROJ_MACROS = 

# additional object files (created by other projects)
PROJ_ADD_OBJS = cir_buffer.o

# additional libraries
PROJ_LIBS =

# linker flags
PROJ_LDFLAGS = -pthread

# list of projects (makefiles) this project depends on
PROJ_DEPENDS  = ../../../ds/src/cir_buffer/Makefile

include $(ROOT_DIR)/Make/Project.mak