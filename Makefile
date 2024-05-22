CC=gcc
CFLAGS=-Wall -Werror -Wextra -pedantic -std=c99 -Wvla -fsanitize=address -g
LDFLAGS=-fsanitize=address
LDLIBS=-lcriterion

OBJS=src/grid_display.o \
	 src/grid_init_destroy.o\
	 src/grid.o\
	 src/llist.o\
	 src/grid_iterator.o\
	 src/input_parser.o\
	 src/main.o

DEBUG_OBJS=src/grid_display.o \
	 src/grid_init_destroy.o\
	 tests/tests.o

all: wildfireSimulator

check: $(DEBUG_OBJS)
	$(CC) $(LDFLAGS) -o test-suite $(DEBUG_OBJS) $(LDLIBS)

wildfireSimulator: $(OBJS)
	$(CC) $(LDFLAGS) -o wildfireSimulator $(OBJS)

clean:
	$(RM) $(BIN) $(OBJS) $(DEBUG_OBJS) wildfireSimulator test-suite
