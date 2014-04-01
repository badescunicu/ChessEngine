CC=g++
FLAGS=-Wall -std=c++0x -g
EXE=chess
SRC=src
INCLUDE_FLAGS=-Iinclude
XBOARD_DIR=~/xboard/xboard-4.7.2/

build:
	$(CC) $(FLAGS) $(INCLUDE_FLAGS) $(SRC)/*.cpp -o $(XBOARD_DIR)chess
	cp $(XBOARD_DIR)chess chess
run:
	./chess
clean:
	rm -f xboard.debug log game.log chess
	
