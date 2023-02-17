CC := clang
CFLAGS := -std=c17 -fPIC
SOFLAGS := -shared

SRC=$(wildcard utility_*.c)
OBJ=$(SRC:.c=.o)

.PHONY: all dep fmt lnt e2e doc rmf

all:
	make libsurf.so
	make surf.exe

dep:
	echo "Installing..."

rmf:
	rm -rf *.exe *.o *.so

surf.exe: surf.c
	$(CC) -o $@ $<

libsurf.so: $(OBJ)
	$(CC) $(SOFLAGS) -o $@ $<

$(OBJ): $(SRC)
	$(CC) $(CFLAGS) -c $<