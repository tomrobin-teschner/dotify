### name of application
APP_NAME = parser

### compiler
CXX = g++

### compiler flags
CXXFLAGS = -c -std=c++11

### linker flags
LXXFLAGS =

### ---------------------------------------------------------------------------

SRC = $(shell find -wholename "**/*.cpp" | grep "src/")
INC = $(patsubst %,-I %,$(shell find include/ -type d))
OBJ = $(subst .cpp,.o,$(SRC))

### ---------------------------------------------------------------------------

appDebug: CXXFLAGS += -g -Og -Wall -Wextra -Wpedantic $(INC)
appDebug: $(APP_NAME)

appRelease: CXXFLAGS += -Ofast $(INC)
appRelease: $(APP_NAME)

all: $(APP_NAME)
$(APP_NAME): $(OBJ)
	$(CXX) $^ $(LXXFLAGS) -o bin/$@

$(LIB_NAME): $(OBJ)
	$(CXX) $^ $(LXXFLAGS) -o lib/$@

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $*.cpp -o $@

.PHONY: clean
clean:
	rm -f $(OBJ) bin/*~ lib/*~ bin/$(APP_NAME)
