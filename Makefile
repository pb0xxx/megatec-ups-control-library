# Compiler and flags
CXX = g++                  # Use g++ for C++ (.cpp files)
CC = gcc                   # Use gcc for C (.c files)
CFLAGS = -Wall -fPIC       # Compiler flags for C
CXXFLAGS = -Wall -fPIC     # Compiler flags for C++
LDFLAGS = -shared          # Linker flags for shared library
LIBS = -lusb-1.0           # USB library

# Directory and file names
BUILD_DIR = build
TARGET = $(BUILD_DIR)/libups-control.so
SRCS_CXX = source/ups.cpp source/operations.cpp source/utils.cpp
OBJS_CXX = $(SRCS_CXX:.cpp=.o)

# Default rule
all: $(BUILD_DIR) $(TARGET)
	@echo "Build complete: $(TARGET)"

# Rule to create the build directory
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Rule to build the target file
$(TARGET): $(OBJS_CXX)
	$(CXX) $(LDFLAGS) -o $@ $(OBJS_CXX) $(LIBS)

# Rule to build object files from C++ source files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

# Rule to build object files from C source files
%.o: %.cpp
	$(CC) $(CFLAGS) -c -o $@ $<

# Rule to clean object files and the target file
clean:
	rm -f $(OBJS_CXX) $(TARGET)
