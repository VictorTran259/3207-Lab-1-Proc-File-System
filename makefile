MYps: processhandling.o displayprocessinfo.o parsers.o
	gcc processhandling.o displayprocessinfo.o parsers.o -o MYps MYps.c -Wall -Werror
processhandling: processhandling.c
	gcc -c processhandling.c
displayprocessinfo: displayprocessinfo.c
	gcc -c displayprocessinfo.c
parsers: parsers.c
	gcc -c parsers.c
clean: 
	rm  *.o MYps