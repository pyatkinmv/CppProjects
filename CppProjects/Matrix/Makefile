CC = g++ $(CPPFLAGS)
CPPFLAGS = -std=c++17 -g -O0
all: MatrixTst
MatrixTst: MatrixTst.o Matrix.o
	$(CC) -o MatrixTst MatrixTst.o Matrix.o
MatricTst.o: MatrixTst.cpp Matrix.h
	$(CC) -c MatrixTst.cpp
Matrix.o: Matrix.cpp Matrix.h
	$(CC) -c Matrix.cpp
clean:
	rm -f *.o MatrixTst
