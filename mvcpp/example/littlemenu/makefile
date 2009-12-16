CC = g++
CFLAGS = -Wall -I../../src
LIBRARIES = -lm -lstdc++
SRCS = main.cpp
OBJS = main.o

all: pmvcpp.o littlemenu

pmvcpp.o : pmvcpparch.cpp
	$(CC) $(CFLAGS) -c $@ $^
	
littlemenu: $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS) $(LIBRARIES)

$(OBJS): $(SRCS)
	$(CC) $(CFLAGS) -c $(SRCS)