CC = gcc
CFLAGS = -Wall -g `pkg-config --cflags gtk+-3.0` -Wno-deprecated-declarations -Wno-unused-parameter
LDFLAGS = `pkg-config --libs gtk+-3.0`
PROG = program
SRC = program.c
OBJ = $(SRC:.c=.o)

all: $(PROG)

$(PROG): $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS)

%.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@

clean:
	rm -f $(OBJ) $(PROG)

.PHONY: all clean
