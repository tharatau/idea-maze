CC := clang
CFLAGS := -std=c17

obj/tau.exe: obj/tau.o
	$(CC) $(CFLAGS) $< -o $@

obj/tau.o: src/tau.c
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: e2e

e2e: obj/tau.exe
	./obj/tau.exe ./e2e/var.tau