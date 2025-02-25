# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -Wall -Wextra -std=c++17 -I.

# Directories
BUILD_DIR = build
SRC_DIR = .
TEST_DIR = .

# Source files
MAIN_SRC = $(SRC_DIR)/main.cpp
TEST_SRC = $(TEST_DIR)/test.cpp
LIB_SRC = $(SRC_DIR)/LongNumber.cpp

# Object files
MAIN_OBJ = $(BUILD_DIR)/main.o
TEST_OBJ = $(BUILD_DIR)/test.o
LIB_OBJ = $(BUILD_DIR)/LongNumber.o

# Executables
MAIN_EXE = $(BUILD_DIR)/main
TEST_EXE = $(BUILD_DIR)/test

# Default target
all: $(MAIN_EXE) $(TEST_EXE)

# Build main executable
$(MAIN_EXE): $(MAIN_OBJ) $(LIB_OBJ) | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Build test executable
$(TEST_EXE): $(TEST_OBJ) $(LIB_OBJ) | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Compile main.cpp
$(MAIN_OBJ): $(MAIN_SRC) $(SRC_DIR)/LongNumber.hpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

# Compile test.cpp
$(TEST_OBJ): $(TEST_SRC) $(SRC_DIR)/LongNumber.hpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

# Compile LongNumber.cpp
$(LIB_OBJ): $(LIB_SRC) $(SRC_DIR)/LongNumber.hpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

# Run the main executable
run: $(MAIN_EXE)
	./$(MAIN_EXE)

# Run the test executable
test: $(TEST_EXE)
	./$(TEST_EXE)

# Clean build artifacts
clean:
	rm -rf $(BUILD_DIR)/*

# Create build directory if it doesn't exist
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

.PHONY: all run test clean