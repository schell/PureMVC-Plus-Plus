CC = g++
CFLAGS = -Wall -I../../src
LIBRARIES = -lm -lstdc++
SRCS = main.cpp ../../src/pmvcpp.cpp
OBJS = main.o pmvcpp.o

all: pmvcpp.o littlemenu

littlemenu: $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS) $(LIBRARIES)

$(OBJS): $(SRCS)
	$(CC) $(CFLAGS) -c $(SRCS)
	
clean :
	rm -rf *.o *.mkout littlemenu