# Linux
# CC=gcc -fopenmp

# Mac
CC=/usr/local/opt/llvm/bin/clang -fopenmp -L/usr/local/opt/llvm/lib

test:
	$(CC) test.c -o test.o

clean:
	/bin/rm ./*.o

searchserial:
	$(CC) searchserial.c -o searchserial.o
searchparallel:
	$(CC) searchparallel.c -o searchparallel.o
sortserial:
	$(CC) sortserial.c -o sortserial.o
sortparallel:
	$(CC) sortparallel.c -o sortparallel.o

runserialsearch:
	./searchserial.o
runparallelsearch:
	./searchparallel.o
runserialsort:
	./sortserial.o
runparallelsort:
	./sortparallel.o
