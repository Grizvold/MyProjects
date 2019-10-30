CC= gcc
CFLAGS= -ansi -pedantic-errors -Wall -Wextra -g

OBJ_DIR:= ../../obj
OBJ:= $(addprefix $(OBJ_DIR)/, fsa.o)


all: fsa_test.out

fsa_test.out: fsa_test.o $(OBJ)
	$(CC) fsa_test.o $(OBJ) -o $@
	rm fsa_test.o
	
fsa_test.o: fsa_test.c fsa.h
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/fsa.o: fsa.c fsa.h
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY:
	clean
clean:
	rm fsa_test.out $(OBJ)
