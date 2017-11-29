# Compiling options
CXX := g++
CXXFLAGS := -Wall -g -O2 -std=c++14 -std=c++11 -Wall
# Directories
SOURCES := src
OBJECTS := obj
# Separation (transforming / into DIR_SEPARATOR in file path to keep all object files in the same directory)
DIR_SEPARATOR := __
# Files
SRC := $(shell find $(SOURCES)/ -type f -name '*.cpp')
OBJ := $(patsubst %.cpp,$(OBJECTS)/%.o, $(subst /,$(DIR_SEPARATOR),$(SRC)))
INC := -Iinclude

EXECUTABLE := Lit

all: $(OBJ) # Creating executable from library and .o files
	$(CXX) $(OBJ) -o $(EXECUTABLE) $(CXXFLAGS)

$(OBJECTS)/%.o: # Compiling .o file from .cpp file
	$(CXX) -c $(INC) -o $@ $(patsubst $(OBJECTS)/%.o,%.cpp,$(subst $(DIR_SEPARATOR),/,$@)) $(CXXFLAGS)

.PHONY: clean

clean: # Cleaning
	rm -rf $(OBJECTS)/*.o
	rm -f $(EXECUTABLE)
