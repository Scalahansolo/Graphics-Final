EXE = shift

# Main target
all: $(EXE)

CFLG=-O3 -Wall
LIBS=-lglut -lGLU -lGL -lm

CLEAN=rm -f $(EXE) *.o *.a


# Dependencies
gears.o: gears.c
shift.o: shift.c CSCIx229.h
fatal.o: fatal.c CSCIx229.h
loadtexbmp.o: loadtexbmp.c CSCIx229.h
print.o: print.c CSCIx229.h
project.o: project.c CSCIx229.h
errcheck.o: errcheck.c CSCIx229.h
object.o: object.c CSCIx229.h

#  Create archive
CSCIx229.a:fatal.o loadtexbmp.o print.o project.o errcheck.o object.o
	ar -rcs $@ $^

# Compile rules
.c.o:
	gcc -c $(CFLG) $<
.cpp.o:
	g++ -c $(CFLG) $<

#  Link
shift:shift.o CSCIx229.a
	gcc -O3 -o $@ $^   $(LIBS)

#  Clean
clean:
	$(CLEAN)