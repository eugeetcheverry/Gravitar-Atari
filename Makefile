PROGRAM=gravitar
CC=gcc
CFLAGS =-Wall -pedantic -std=c99 -g
LDFLAGS = -lSDL2 -lm

OBJS = main.o nave.o figuras.o lista.o polilinea.o color.o caracteres.o planeta.o disparo.o torreta.o combustible.o reactor.o

all: $(PROGRAM)

$(PROGRAM):$(OBJS)
	$(CC) $(OBJS) -o $(PROGRAM) $(CFLAGS) $(LDFLAGS) 

main.o: main.c nave.h figuras.h lista.h polilinea.h color.h config.h caracteres.h planeta.h disparo.h torreta.h reactor.h
	$(CC) main.c -c $(CFLAGS) $(LDFLAGS)

nave.o: nave.c nave.h figuras.h polilinea.h config.h
	$(CC) nave.c -c $(CFLAGS) $(LDFLAGS)

figuras.o: figuras.c figuras.h polilinea.h lista.h config.h
	$(CC) figuras.c -c $(CFLAGS) $(LDFLAGS)

lista.o: lista.c lista.h
	$(CC) lista.c -c $(CFLAGS) $(LDFLAGS)

polilinea.o: polilinea.c polilinea.h color.h config.h
	$(CC) polilinea.c -c $(CFLAGS) $(LDFLAGS)

color.o: color.c color.h
	$(CC) color.c -c $(CFLAGS) $(LDFLAGS)

caracteres.o: caracteres.c caracteres.h figuras.h polilinea.h color.h
	$(CC) caracteres.c -c $(CFLAGS) $(LDFLAGS)

disparo.o: disparo.c polilinea.h lista.h figuras.h disparo.h torreta.h nave.h
	$(CC) disparo.c -c $(CFLAGS) $(LDFLAGS)

planeta.o: planeta.c figuras.h nave.h planeta.h caracteres.h torreta.h disparo.h combustible.h reactor.h
	$(CC) planeta.c -c $(CFLAGS) $(LDFLAGS)

torreta.o: torreta.c figuras.h lista.h nave.h
	$(CC) torreta.c -c $(CFLAGS) $(LDFLAGS)

combustible.o: combustible.c lista.h figuras.h
	$(CC) combustible.c -c $(CFLAGS) $(LDFLAGS)

reactor.o: reactor.c lista.h figuras.h caracteres.h
	$(CC) reactor.c -c $(CFLAGS) $(LDFLAGS)

nave.h: figuras.h polilinea.h

figuras.h: polilinea.h lista.h config.h

caracteres.h: figuras.h polilinea.h

polilinea.h: color.h

disparo.h: figuras.h lista.h nave.h torreta.h

planeta.h: figuras.h nave.h caracteres.h torreta.h combustible.h reactor.h

torreta.h: lista.h figuras.h nave.h

combustible.h: lista.h figuras.h

reactor.h: lista.h figuras.h

clean:
	rm -vf *.o $(PROGRAM)