CC := clang
CFLAGS := -std=c17

.PHONY: all fmt lnt e2e rmf dev bld pkg

everything:
	make utility_math.so
	make surf.exe

fmt:
	clang-format -i *.c *.h

rmf:
	rm -rf *.exe *.o *.so

utility_math.so: utility_math.c
	${CC} ${CFLAGS} -c -o utility_math.o utility_math.c -fPIC
	${CC} ${CFLAGS} -shared -o utility_math.so utility_math.o

surf.exe: surf.c
	${CC} ${CFLAGS} $< -o $@
