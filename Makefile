CXXFLAGS = -O3 -std=c++2a

.PHONY: all clean elf docker

all: game

main.o: main.cc
	$(CXX) $(CXXFLAGS) -c main.cc -o main.o

game: main.o
	$(CXX) -o game $(CXXFLAGS) main.o

game.elf: main.cc
	$(CXX) -o game.elf $(CXXFLAGS) main.cc

docker: main.cc
	docker run -w /app -v "$(shell pwd):/app" -it kanav99/gba make game.elf

clean:
	rm -f *.o game *.elf

venv:
	python3 -m venv venv

disas: docker venv
	python3 minidis.py

