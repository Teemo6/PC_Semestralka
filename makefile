CC=gcc
CFLAGS=-Wall -Wextra -ansi -pedantic
BIN=spamid.exe
OBJ=main.o error.o hash_table.o hash_table_entry.o classifier.o

%.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@

$(BIN): $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@ -lm

clean :
	rm $(BIN) $(OBJ)

clean_win :
	del $(BIN) $(OBJ)