CXX=g++
CXXFLAGS=-std=c++14 -Wall -g
RM=rm -rf

.PHONY: clean

main: main.o packing-controller.o bin-container.o bin.o # .o files here
	$(CXX) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $<

clean:
	$(RM) -rf *.o main *.gc* *.dSYM
