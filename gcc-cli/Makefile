CC = gcc
PROG = program
SRC = program.c
OBJ = $(SRC:.c=.o)

all: $(PROG)

$(PROG): $(OBJ)
	$(CC) -o $@ $^

%.o: %.c
	$(CC) -c $< -o $@

clean:
	rm -f $(OBJ) $(PROG)

.PHONY: all clean
