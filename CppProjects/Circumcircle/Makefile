CFLAGS= -g -O0 -Wall -I/usr/X11R6/include -L/usr/X11R6/lib -I.. -I.
CC= g++ $(CFLAGS)

all: circumcircle

circumcircle: circumcircle.o gwindow.o R2Graph/R2Graph.o
	$(CC) -o circumcircle circumcircle.o gwindow.o R2Graph/R2Graph.o -lX11

circumcircle.o: circumcircle.cpp gwindow.h
	$(CC) -c circumcircle.cpp

R2Graph/R2Graph.o:
	cd R2Graph; make R2Graph.o; cd ..

gwindow.h: R2Graph/R2Graph.h

clean:
	rm -f *.o circumcircle *\~
	cd R2Graph; make clean; cd ..
