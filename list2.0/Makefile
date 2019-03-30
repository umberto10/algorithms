CC = g++
CPPFLAGS = -Wall -std=c++17

SRCS = main.cpp quick.h values.h mquick.h insert.h select.h heap.h
OBJS = $(SRCS:.cpp=.o)

MAIN = sorts

all: $(MAIN)

$(MAIN): $(OBJS)
	$(CC) $(CPPFLAGS) -o $(MAIN) $(OBJS)

.c.o:
	$(CC) $(CPPFLAGS) -c $< -o $@

.PHONY: clean
clean:
	rm -fv *.o *~$(MAIN) quick.txt mquick.txt insert.txt select.txt heap.txt
