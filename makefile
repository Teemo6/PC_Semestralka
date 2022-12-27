CC=gcc
CFLAGS=-Wall -Wextra -ansi -pedantic
OBJ=main.o hash_table.o hash_table_entry.o loader.o
BIN=spamid.exe

$(BIN): $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@ -lm

.c.o:
	$(CC) $(CFLAGS) -c $^

clean :
	rm $(BIN) $(OBJ)

clean_win :
	del $(BIN) $(OBJ)