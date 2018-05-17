#Directory & file variables
#Project source code tree
CCU_ROOTDIR = ../CppUsage
CCU_SRC = ${CCU_ROOTDIR}/*.cpp
CCU_SRC += ${CCU_ROOTDIR}/*.h


#Build tool chain settings
#If gcc used instead of c++, we must add '-lstdc++' into CFLAGS.
CC_CPP485 = c++
CC_CPP494 = brown-c++-4.9.4
CC_CPP550 = brown-c++-5.5.0
CC_CPP640 = brown-c++-6.4.0
CC_CPP730 = brown-c++-7.3.0
CC = ${CC_CPP730}
#Possible C++ versions: c++98, gnu++98, c++11, gnu++11, c++14, gnu++14, c++17, gnu++17
CC_CPP_VER = c++17
CFLAGS = -std=${CC_CPP_VER}
CFLAGS += -Wall -Wextra -Werror
ifeq ('c++', $(findstring 'c++',${CC_CPP_VER}))
CFLAGS += -Wpedantic
endif


#Phony targets
.PHONY : clean

clean :
ifneq (,$(wildcard *.exe))
	rm *.exe
else
	@echo 'No executable to remove.'
endif


#Build targets
Dccu : ${CCU_SRC}
	${CC} -o ccu.exe -g ${CFLAGS} ${CCU_SRC}

Rccu : ${CCU_SRC}
	${CC} -o ccu.exe -O2 ${CFLAGS} ${CCU_SRC}

