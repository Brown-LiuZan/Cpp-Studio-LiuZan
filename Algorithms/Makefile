EXECUTIVE = run.exe
LZLIB_DIR = ../Common

#CXX = g++
#CXX = brown-g++-7.3.0
CXX = brown-g++-8.2.0

#CXX_FLAGS = -std=c++98
#CXX_FLAGS = -std=c++11
CXX_FLAGS = -std=c++17
CXX_FLAGS += -g
CXX_FLAGS += -I${LZLIB_DIR}

CXX_TEMPLATE_FILES = ${LZLIB_DIR}/LZAssert.h
CXX_TEMPLATE_FILES += AlgQuickSort.h

CXX_SRC = AlgMain.cxx

all : ${EXECUTIVE}

${EXECUTIVE} : ${CXX_TEMPLATE_FILES} ${CXX_SRC}
	${CXX} -o $@ ${CXX_FLAGS} $^

clean :
	rm -f *.exe
	rm -f *.o
	@ls

run :
	@./run.exe
