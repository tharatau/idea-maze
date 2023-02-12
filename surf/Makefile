CC = clang
CFLAGS = -std=c17

all:
	make clean
	make surf
	make utility_math

clean:
	rm -f *.o *.exe *.so

surf:
	${CC} ${CFLAGS} surf.c -o surf.exe

utility_math:
	${CC} ${CFLAGS} -c utility_math.c -o utility_math.o -fPIC
	${CC} ${CFLAGS} -shared utility_math.o -o utility_math.so