CC = g++
CFLAGS = -Wall -I../../src
LIBRARIES = -lm -lstdc++ -lpthread
SRCS = main.cpp ../../src/pmvcpp.cpp
OBJS = main.o pmvcpp.o

all: pmvcpp.o threads

threads: $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS) $(LIBRARIES)

$(OBJS): $(SRCS)
	$(CC) $(CFLAGS) -c $(SRCS)
	
clean :
	rm -rf *.o *.mkout threads