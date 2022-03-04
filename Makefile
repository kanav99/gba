CXXFLAGS = -O3 -std=c++2a

.PHONY: all clean

all: game

main.o: main.cc
	$(CXX) $(CXXFLAGS) -c main.cc -o main.o

game: main.o
	$(CXX) -o game $(CXXFLAGS) main.o