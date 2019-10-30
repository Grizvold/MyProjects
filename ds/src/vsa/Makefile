CC = gcc
CFLAGS = -ansi -pedantic-errors -Wall -Wextra -g

OBJ_DIR:=../../obj
OBJ:= $(addprefix $(OBJ_DIR)/, vsa.o)

all: vsa_test.out

vsa_test.out: vsa_test.o $(OBJ)
		$(CC) vsa_test.o $(OBJ) -o $@
		rm vsa_test.o
		
vsa_test.o: vsa_test.c vsa.h
		$(CC) $(CFLAGS) -c $< -o $@
		
$(OBJ_DIR)/vsa.o: vsa.c vsa.h
		$(CC) $(CFLAGS) -c $< -o $@
		
.PHONY:
	clean
clean:
	rm vsa_test.out $(OBJ)

