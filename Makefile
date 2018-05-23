CXX = g++
CXXFLAGS = -c -g -Wall -std=c++11 -O3 -fpermissive
CXXSOURCES = $(wildcard src/*.cpp)
CXXOBJECTS = $(CXXSOURCES:.cpp=.o)
CXXHEADERS = $(wildcard src/*.h)
EXECUTABLE = algoritmogenetico.out

all: $(EXECUTABLE)

$(EXECUTABLE): $(CXXOBJECTS)
	$(CXX) -o $@ $^

%.o: %.c %.h
	$(CXX) -o $@ $< $(CXXFLAGS)

main.o: main.cpp $(CXXHEADERS) $(CXXSOURCES)
	$(CXX) -o $@ $< $(CXXFLAGS)

clean:
	rm -rf src/*.o src/*~ $(EXECUTABLE)
