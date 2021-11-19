Target		= irCut
CXX         = g++
ODIR		= obj
SRC			=$(wildcard *.cpp)
DIR			=$(notdir $(SRC))
OBJ 		= $(patsubst %.cpp, %.o, $(DIR))
$(Target): $(OBJ)
	$(CXX) $^ -o $@ $(CXXFLAGS)
.PHONY:clean
clean:
	rm -rf *.o
	rm -rf $(Target)
