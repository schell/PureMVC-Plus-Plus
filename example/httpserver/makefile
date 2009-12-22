CC = g++
CFLAGS = -Wall -I../../src -I.
LIBRARIES = -lm -lstdc++
SRCS = main.cpp \
controller/Listen.cpp controller/Set.cpp controller/Startup.cpp \
model/SocketProxy.cpp \
view/HttpMediator.cpp view/components/Http.cpp \
../../src/pmvcpp.cpp

OBJS = main.o pmvcpp.o Listen.o Set.o Startup.o SocketProxy.o HttpMediator.o Http.o

all: pmvcpp.o httpserver

httpserver: $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS) $(LIBRARIES)

$(OBJS): $(SRCS)
	$(CC) $(CFLAGS) -c $(SRCS)
	
clean :
	rm -rf *.o *.mkout httpserver