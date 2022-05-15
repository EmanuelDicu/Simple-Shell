CC=gcc
CFLAGS=-I.
DEPS = data_types.h commands.h file_utils.h dir_utils.h 
OBJ = tema1.o commands.o file_utils.o dir_utils.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

build: $(OBJ)
	$(CC) -o tema $^ $(CFLAGS)

clean:
	rm tema *.o

valgrind:
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./tema

checker:
	python3 checker.py
