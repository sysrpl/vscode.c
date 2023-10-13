CC = gcc
CFLAGS = -Wall -g `pkg-config --cflags webkit2gtk-4.0` -Wno-deprecated-declarations -Wno-unused-parameter
LDFLAGS = `pkg-config --libs webkit2gtk-4.0`
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
