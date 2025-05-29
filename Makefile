all:
	x86_64-w64-mingw32-gcc -c LNKgenerator-bof.c -o LNKgenerator-BOF.x64.o
	x86_64-w64-mingw32-strip --strip-unneeded LNKgenerator-BOF.x64.o
	i686-w64-mingw32-gcc -c LNKgenerator-bof.c -o LNKgenerator-BOF.x86.o
clean:
	rm LNKgenerator-BOF.x64.o
	rm LNKgenerator-BOF.x86.o
