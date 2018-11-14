EXECUTIVE = run.exe

#CXX = g++
#CXX = brown-g++-7.3.0
CXX = brown-g++-8.2.0

#CXX_FLAGS = -std=c++11
CXX_FLAGS = -std=c++17
CXX_FLAGS += -g

#CXX_SRC = CCUTestMain.cxx
#CXX_SRC = RawString.cxx
#CXX_SRC = Utility.cxx
CXX_SRC = CCUFriendClass.cxx

all : ${EXECUTIVE}

${EXECUTIVE} : ${CXX_SRC}
	${CXX} -o $@ ${CXX_FLAGS} $^

clean :
	rm -f *.exe
	rm -f *.o
	@ls

run :
	@./run.exe
