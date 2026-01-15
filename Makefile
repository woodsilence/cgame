TARGET = cgame

SRCS = $(wildcard *.c)
OBJS = $(SRCS:.c=.o)

CC = clang
CFLAGS = -g -o0

.PHONY: all clean

all: $(TARGET)

LDFLAGS = -lncurses

$(TARGET): $(OBJS)
	$(CC) $(OBJS) $(LDFLAGS) -o $(TARGET)
	rm -f $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)