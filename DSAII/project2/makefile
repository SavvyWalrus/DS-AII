CXX=g++
CXXFLAGS=-std=c++14 -Wall -g
RM=rm -rf

.PHONY: clean

sim: main.o simulation-controller.o math-model.o priority-queue.o fifo-queue.o customer.o
	$(CXX) -o $@ $^

test: test.o math-model.o customer.o
	$(CXX) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $<

clean:
	$(RM) -rf *.o sim test *.gc* *.dSYM
