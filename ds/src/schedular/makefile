CC= gcc
CFLAGS= -ansi -pedantic-errors -Wall -Wextra -g

OBJ= dll.o sl.o pq.o uid.o sched_test.o
INCLUDE_PATH= ../../src
SRC_PARTH= ../../src

all: $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o sched.out 

dll.o: $(SRC_PATH)/dll/dll.c $(INCLUDE_PATH)/dll/dll.h
	$(CC) $(CFLAGS) -c $(SRC_PATH)/dll/dll.c -I $(INCLUDE_PATH)/dll/

sl.o: $(SRC_PATH)/sorted_list/sl.c $(INCLUDE_PATH)/sorted_list/sl.h dll.o
	$(CC) $(CFLAGS) -c $(SRC_PATH)/sorted_list/sl.c -I $(INCLUDE_PATH)/sorted_list/

pq.o: $(SRC_PATH)

