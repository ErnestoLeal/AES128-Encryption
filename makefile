# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++11 -Wall -g

# Source files
SOURCES = addConstant.cpp addRoundKey.cpp AES128.cpp keyExpansion.cpp mixColumns.cpp rotateWord.cpp subByte.cpp stringToHex.cpp padBlock.cpp xorEncrypt.cpp shiftRows.cpp

# Object files (auto-generates .o files for each .cpp file)
OBJECTS = $(SOURCES:.cpp=.o)

# Executable name
EXEC = AES128.exe

# Default target to build the executable
all: $(EXEC)

# Linking step to create the executable
$(EXEC): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(EXEC) $(OBJECTS)

# Compile .cpp files into .o files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up generated files
clean:
	del /f $(OBJECTS) $(EXEC)
