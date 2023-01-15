.PHONY: clean

surf: ./src/surf.cc
	clang++ -std=c++20 ./src/surf.cc -o ./out/surf.exe

exe: ./out/surf.exe
	./out/surf.exe

clean:
	rm -rf ./out/surf.exe