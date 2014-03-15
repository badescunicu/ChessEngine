CC=g++
FLAGS=-Wall -std=c++0x -g
EXE=chess
SRC=src
INCLUDE_FLAGS=-Iinclude

build:
	$(CC) $(FLAGS) $(INCLUDE_FLAGS) $(SRC)/*.cpp -o $(EXE) 
