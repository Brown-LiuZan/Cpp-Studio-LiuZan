EXECUTIVE = run.exe

#CXX = g++
#CXX = brown-g++-7.3.0
CXX = brown-g++-8.2.0

#CXX_FLAGS = -std=c++11
CXX_FLAGS = -std=c++17
CXX_FLAGS += -g

CXX_TEMPLATE_FILES = LZAssert.h

CXX_SRC = LZMain.cxx
CXX_SRC += LZTestEngine.cxx

all : ${EXECUTIVE}

${EXECUTIVE} : ${CXX_TEMPLATE_FILES} ${CXX_SRC}
	${CXX} -o $@ ${CXX_FLAGS} $^

clean :
	rm -f *.exe
	rm -f *.o
	@ls

run :
	@./run.exe
