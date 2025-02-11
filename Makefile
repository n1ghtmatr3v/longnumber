# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -Wall -Wextra -std=c++17

# Target executable
TARGET = build/main

# Source files
SRCS = main.cpp LongNumber.cpp

# Object files (placed in the build directory)
OBJS = $(SRCS:%.cpp=build/%.o)

# Default target
all: $(TARGET)

# Ensure the build directory exists
build:
	mkdir -p build

# Link the object files to create the executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJS)

# Compile the source files into object files in the build directory
build/%.o: %.cpp | build
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Run the executable
run: $(TARGET)
	./$(TARGET)

# Clean up the build files
clean:
	rm -rf build

# Phony targets
.PHONY: all clean run