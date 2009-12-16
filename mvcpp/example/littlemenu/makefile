CC = g++
CFLAGS = -Wall -I../../src
LIBRARIES = -lm -lstdc++
SRCS = main.cpp ../../src/pmvcpparch.cpp
OBJS = main.o pmvcpparch.o

all: pmvcpparch.o littlemenu

littlemenu: $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS) $(LIBRARIES)

$(OBJS): $(SRCS)
	$(CC) $(CFLAGS) -c $(SRCS)
	
clean :
	rm -rf *.o *.mkout littlemenu