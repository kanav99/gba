CXXFLAGS = -O3 -std=c++2a

.PHONY: all clean elf docker

all: game

main.o: main.cc
	$(CXX) $(CXXFLAGS) -c main.cc -o main.o

game: main.o
	$(CXX) -o game $(CXXFLAGS) main.o

elf:
	$(CXX) -o game.elf $(CXXFLAGS) main.cc

docker:
	docker run -w /app -v "$(shell pwd):/app" -it kanav99/gba make elf

clean:
	rm -f *.o game *.elf
