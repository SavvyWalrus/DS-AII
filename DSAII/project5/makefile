CXX=g++
CXXFLAGS=-std=c++14 -Wall -g
RM=rm -rf

.PHONY: clean

main: main.o subsequence-controller.o similarity-calculator.o lcs-manager.o # .o files here
	$(CXX) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $<

clean:
	$(RM) -rf *.o main *.gc* *.dSYM
