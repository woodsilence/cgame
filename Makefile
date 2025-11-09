TARGET = cgame

SRCS = $(wildcard *.c)
OBJS = $(SRCS:.c=.o)

CC = gcc
CFLAGS = -g -o0

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET)
	rm -f $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)