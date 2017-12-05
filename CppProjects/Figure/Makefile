CC = g++ $(CPPFLAGS)
CPPFLAGS = -std=c++17 -g -O0
all: figureTst
figureTst: figureTst.o figure.o
	$(CC) -o figureTst figureTst.o figure.o
figureTst.o: figureTst.cpp figure.h
	$(CC) -c figureTst.cpp
figure.o: figure.cpp figure.h
	$(CC) -c figure.cpp
clean:
	rm -f *.o figureTst
