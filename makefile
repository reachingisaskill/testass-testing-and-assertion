############################################################################################
#
# makefile
#
# Original Author : Christopher Hunt
# Creation Date   : 05/04/2013
#
# Last Update     : Christopher Hunt & Ben Krikler
# At              : 07/01/2014
#
#
# A simple, flexible makefile designed to work well within a rigid directory structure.
# Builds multiple executables, and a library with all implementation files.
#
# For basic usage the following is required:
#
#  1.  Source files are expected to be in "./src/" 
#  2.  Header files are expected to be in "./include/".
#  3.  Executable source files must have the suffix ".cxx" 
#  4.  Implementation source files must have the suffix ".cpp"
#
# If the previous reuirements are met, the makefile will locate the necessary files and
#  build all excutables by default, placing them the "bin" directory.
#
#
# For basic use, it is advised that only the Defines, Includes and Library flags be altered.
# More complicated directory structures may warrant changes to the preset directories below.
#
# It is not advised that the user modify any code below the second hash-line 
#                                     On pain of GNU Make!
#
############################################################################################

HEAD = /home/chris/play/code

# File Locations
INC_DIR = include
SRC_DIR = src
BIN_DIR = bin
LIB_DIR = lib
TMP_DIR = .temp

EXE_SRC_DIR = ${SRC_DIR}


# Library Name
LIB_NAME = testass


# Includes and Libraries
INC_FLAGS += -I${INC_DIR} -I${HEAD}/include
LIB_FLAGS += -L${HEAD}/lib


# Compile-Time Definitions
DEFINES =


# Installation Directory
INSTALL_DIR = ${HEAD}


# The Compiler
CCC = g++ -g  -Wall -Wextra -pedantic ${DEFINES}
# CCC = g++ -O2 -Wall -Wextra -pedantic ${DEFINES} # Optimized Compilation


##############################################################################################


# Extra Compile Flags to Create Library
LIB_COMP_FLAGS = -fPIC -shared
LIB_LINK_FLAGS = -Wl,-rpath=$(realpath ${LIB_DIR}) -l${LIB_NAME} -L${LIB_DIR}


# Find The Files
EXE_FILES = ${shell ls $(EXE_SRC_DIR)}
SRC_FILES = ${shell ls $(SRC_DIR)}
INC_FILES = ${shell ls $(INC_DIR)}

# Executable Source Files
EXE_SRC = $(filter %.cxx,${EXE_FILES})



INCLUDE = $(patsubst %.h,${INC_DIR}/%.h,$(filter %.h,$(INC_FILES)))
INCLUDE+= $(patsubst %.hpp,${INC_DIR}/%.hpp,$(filter %.hpp,$(INC_FILES)))

SOURCES = $(patsubst %.cpp,${SRC_DIR}/%.cpp,$(filter %.cpp,$(SRC_FILES)))

OBJECTS = $(patsubst %.cpp,$(TMP_DIR)/%.o,$(filter %.cpp,$(SRC_FILES)))
EXE_OBJ = $(patsubst %.cxx,$(TMP_DIR)/%.o,${EXE_SRC})

LIBRARY   = ${LIB_DIR}/lib${LIB_NAME}.so
PROGRAMS  = $(patsubst %.cxx,${BIN_DIR}/%,${EXE_SRC})
PROGNAMES = $(notdir ${PROGRAMS})



.PHONY : program all _all build install clean buildall directories includes intro single_intro check_install



all : intro directories ${LIBRARY} ${PROGRAMS}
	@echo "Make Completed Successfully"
	@echo


${PROGNAMES} : % : single_intro ${BIN_DIR}/% 
	@echo "Make Completed Successfully"
	@echo


intro :
	@echo "Building All Program(s) : "$(notdir ${PROGRAMS})
	@echo "Please Wait..."
	@echo


single_intro :
	@echo "Building Selected Program"
	@echo "Please Wait..."
	@echo


${PROGRAMS} : ${BIN_DIR}/% : ${TMP_DIR}/%.o
	@echo " - Building Target  : " $(notdir $(basename $@))
	@${CCC} ${LIB_LINK_FLAGS} -o $@ $^ ${INC_FLAGS} ${LIB_FLAGS}
	@echo "Target : "$(notdir $(basename $@))" Successfully Built"
	@echo

${LIBRARY} : ${OBJECTS}
	@echo " - Building Library : " ${LIB_NAME}
	@${CCC} ${LIB_COMP_FLAGS} -o $@ $^ ${INC_FLAGS} ${LIB_FLAGS}
	@echo "Library : "${LIB_NAME}" Successfully Built"
	@echo


${EXE_OBJ} : ${TMP_DIR}/%.o : ${EXE_SRC_DIR}/%.cxx ${INCLUDE}
	@echo " - Compiling Target : " $(notdir $(basename $@))
	@${CCC} -c $< -o $@ ${INC_FLAGS}


${OBJECTS} : ${TMP_DIR}/%.o : ${SRC_DIR}/%.cpp ${INCLUDE}
	@echo " - Compiling Source : " $(notdir $(basename $@))
	@${CCC} ${LIB_COMP_FLAGS} -c $< -o $@ ${INC_FLAGS}



directories : ${BIN_DIR} ${LIB_DIR} ${SRC_DIR} ${INC_DIR} ${TMP_DIR}


${BIN_DIR} :
	mkdir -p ${BIN_DIR}

${LIB_DIR} :
	mkdir -p ${LIB_DIR}

${SRC_DIR} :
	mkdir -p ${SRC_DIR}

${INC_DIR} :
	mkdir -p ${INC_DIR}

${TMP_DIR} :
	mkdir -p ${TMP_DIR}



clean :
	rm -f ${TMP_DIR}/*
	rm -f ${PROGRAMS}


install : check_install
	@echo
	@echo "Installing Program/Libraries"
	@cp ${INCLUDE} ${INSTALL_DIR}/include
	@cp ${PROGRAMS} ${INSTALL_DIR}/bin
	@cp ${LIBRARY} ${INSTALL_DIR}/lib
	@echo

check_install :
	@if [ -z "${INSTALL_DIR}" ]; then          \
		echo                                    ;\
		echo "  INSTALLATION DIRECTORY NOT SET" ;\
		echo                                    ;\
		exit 1                                  ;\
		fi

