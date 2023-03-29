CXX= g++
CXXFLAGS = -std=c++17 -Wall
SOURCES = $(wildcard src/*.cpp) $(wildcard src/*/*.cpp)
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=bgame

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $@

.cpp.o:
	$(CXX) $(CXXFLAGS) $< -o $@

clean:
	rm -rf $(OBJECTS) $(EXECUTABLE)