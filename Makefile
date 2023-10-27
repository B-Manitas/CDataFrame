# Compiler, flags, and libraries
CC = g++
CFLAGS = -std=c++11 -Wall -I./include -I./test
LIBS_TEST = -lgtest -lpthread

# Files
SRC = $(wildcard ./src/*.cpp)
OBJ = $(SRC:.cpp=.o)
EXE = cdataframe

# Main file
MAIN = $(wildcard main.cpp)
MAIN_OBJ = $(MAIN:.cpp=.o)
MAIN_EXE = $(MAIN:.cpp=)

# Test files
TEST = $(wildcard ./test/*.cpp)
TEST_OBJ = $(TEST:.cpp=.o)
TEST_EXE = $(TEST:.cpp=)

all : test

%.o : %.cpp
	$(CC) $(CFLAGS) -o $@ -c $<

test : $(TEST_OBJ)
	$(CC) $(CFLAGS) $^ $(LIBS_TEST) -o $(TEST_EXE)
	./$(TEST_EXE)

main : $(MAIN_OBJ)
	$(CC) $(CFLAGS) $^ -o $@
	./$@

clean_obj :
	rm -rf $(TEST_OBJ) $(OBJ) $(MAIN_OBJ)
	clear

clean_exe :
	rm -rf $(TEST_EXE) $(MAIN_EXE) $(EXE)
	clear

docs :
	doxygen doxygen.conf
	cd docs/latex 
	make pdf
	cd ../..
	mv docs/latex/refman.pdf docs/cdataframe.pdf
	clear

clean : clean_obj clean_exe

install :
	mkdir lib
	git clone https://github.com/B-Manitas/CDataFrame.git
	cd ..

.PHONY : all test main clean_obj clean_exe docs clean install
