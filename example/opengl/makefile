LIBPATH += -L"/System/Library/Frameworks/OpenGL.framework/Libraries"

FRAMEWORK = -framework GLUT
FRAMEWORK += -framework OpenGL

CC = g++
CFLAGS = -Wall
LIBRARIES = -lGL -lGLU -lm -lstdc++

OBJS = main.o pmvcpp.o
SRCS = main.cpp ../../src/pmvcpp.cpp

all: opengl pmvcpp.o

opengl: $(OBJS)
	$(CC) $(FRAMEWORK) $(CFLAGS) -o $@ $(LIBPATH) $(LIBRARIES) $(OBJS)
	
$(OBJS): $(SRCS)
	$(CC) $(CFLAGS) -c $(SRCS)

clean :
	rm -rf *.o *.mkout opengl