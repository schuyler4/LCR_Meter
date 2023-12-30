# Test Program Compilation
BIN = ./bin

make: calc_test.c 
	@echo POOP
	gcc calcs.c -o $(BIN)/calcs.o -c
	gcc codes.c -o $(BIN)/codes.o -c
	gcc calc_test.c -o $(BIN)/calc_test.o -c
	gcc -o $(BIN)/test_program $(BIN)/calcs.o $(BIN)/codes.o $(BIN)/calc_test.o
	./$(BIN)/test_program
