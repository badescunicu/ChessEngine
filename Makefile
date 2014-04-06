CC=g++
FLAGS=-Wall -std=c++0x -g
EXE=chess
SRC=src
INCLUDE_FLAGS=-Iinclude
XBOARD_DIR=~/xboard/xboard-4.7.2/

all : chess

build: $(patsubst %.cpp, %.o, $(wildcard $(SRC)/*.cpp))

$(SRC)/%.o : $(SRC)/%.cpp
	$(CC) -c $(FLAGS) $(INCLUDE_FLAGS) $< -o $@

chess : build 
	$(CC) $(FLAGS) $(INCLUDE_FLAGS) $(SRC)/*.o -o chess

clean:
	rm -f chess $(XBOARD_DIR)chess $(SRC)/*.o &>/dev/null
	
