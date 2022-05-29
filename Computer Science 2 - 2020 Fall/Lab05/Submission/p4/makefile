INCL = defs.h parse.h set.h db.h stack.h sortAndSearch.h
SRC = database.c set.c bubble.c bSearch.c stack.c parse.c db.c
OBJ = $(SRC:.c=.o)
CFLAGS = -Wall
TARGET = a.out

CC = gcc

all: $(TARGET)

%.o: %.c
	$(CC) -c $*.c

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ)

$(OBJ): $(INCL)

debug:
		$(CC) $(CFDEBUG) $(SRC)

clean:
		$(RM) $(OBJ) $(TARGET)