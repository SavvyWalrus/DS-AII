# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -Wall -std=c++11

# Executable name
EXEC = password_manager

# Source files
SRCS = main.cpp password-manager.cpp hash-table.cpp

# Header files
HEADERS = password-manager.hpp hash-table.hpp

# Object files
OBJS = main.o password-manager.o hash-table.o

# Default target to build the executable
all: $(EXEC)

# Rule to build the executable
$(EXEC): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(EXEC) $(OBJS)

# Rule to compile main.cpp
main.o: main.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c main.cpp

# Rule to compile password-manager.cpp
password-manager.o: password-manager.cpp password-manager.hpp
	$(CXX) $(CXXFLAGS) -c password-manager.cpp

# Rule to compile hash-table.cpp
hash-table.o: hash-table.cpp hash-table.hpp
	$(CXX) $(CXXFLAGS) -c hash-table.cpp

# Clean up object files and the executable
clean:
	rm -f $(OBJS) $(EXEC)
