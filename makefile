CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -pedantic

.PHONY: all clean
all: searchengine

searchengine: Searchengine.o Readinput.o Map.o Trienode.o Search.o Listnode.o
	$(CXX) $(CXXFLAGS) -o $@ $^

Listnode.o: Listnode.cpp Listnode.h
Searchengine.o: Searchengine.cpp Searchengine.h
Readinput.o: Readinput.cpp Readinput.h Map.h Trienode.h
Map.o: Map.cpp Map.h
Trienode.o: Trienode.cpp Trienode.h
Search.o: Search.cpp Search.h

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $<

clean:
	rm -f *.o searchengine
