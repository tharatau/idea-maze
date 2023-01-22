utility: utility_cli.cc
	clang++ -std=c++20 -c utility_cli.cc

surf: surf.cc utility_cli.o
	clang++ -std=c++20 surf.cc utility_cli.o -o surf.exe

exe: surf.exe
	./surf.exe