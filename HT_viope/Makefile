# compiler flags stored in variable
CFLAGS=-c -Wall -std=c99

# output program name
PROGNAME=pullonpalautus

MAIN_O_FILES=program.o funktio.o tiedosto.o tietorakenne.o

# Compile final program
all: $(MAIN_O_FILES)
	gcc $(MAIN_O_FILES) -o $(PROGNAME) -Wall

testfiles: testfilestuff.c tiedosto.o funktio.o tietorakenne.o
	gcc testfilestuff.c $(CFLAGS)
	gcc testfilestuff.o tiedosto.o funktio.o tietorakenne.o -o testfiles -Wall

grindvals: $(MAIN_O_FILES)
	gcc $(MAIN_O_FILES) -o $(PROGNAME) -Wall
	valgrind -v --leak-check=yes --leak-resolution=high --show-reachable=yes ./$(PROGNAME)

testddd: $(MAIN_O_FILES)
	gcc $(MAIN_O_FILES) -o $(PROGNAME) -Wall
	ddd ./$(PROGNAME)

program.o: program.c funktio.h tietorakenne.h tiedosto.h
	gcc program.c $(CFLAGS)

funktio.o: funktio.c funktio.h tietorakenne.h tiedosto.h
	gcc funktio.c $(CFLAGS)

tiedosto.o: tiedosto.c tiedosto.h tietorakenne.h
	gcc tiedosto.c $(CFLAGS)

tietorakenne.o: tietorakenne.c tietorakenne.h
	gcc tietorakenne.c $(CFLAGS)

clear:
	rm *.o
	rm $(PROGNAME)
	rm testfiles
