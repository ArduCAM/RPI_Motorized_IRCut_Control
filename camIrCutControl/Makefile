Target		= irCut
CXX         = g++
LIBS		= -lgpiod
ODIR		= obj
SRC			=$(wildcard *.cpp)
DIR			=$(notdir $(SRC))
OBJ 		= $(patsubst %.cpp, %.o, $(DIR))
$(Target): $(OBJ)
	$(CXX) $^ -o $@ $(CXXFLAGS) $(LIBS)
.PHONY:clean
clean:
	rm -rf *.o
	rm -rf $(Target)
