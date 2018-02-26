# Archivo Makefile simple 
PROYECTO=muestreo
DESTDIR=/usr/local/bin
CFLAGS=-Wall
LDFLAGS=-lm
CC=gcc
objetos= $(patsubst %.c, %.o, $(wildcard *.c))

all: $(PROYECTO)

%.o: %.c 
	$(CC) -c $< $(CFLAGS)

$(PROYECTO): $(objetos) 
	$(CC) $^ -o $@ $(LDFLAGS)
PHONY: clean


#Todo lo comentado se ha reemplazado por variables

#muestro.o: muestreo.c
#	$(CC) -c muestreo.c $(CFLAGS)
#
#procesamiento.o: procesamiento.c 
#	$(CC) -c procesamiento.c $(CFLAGS)
#
#archivos.o: archivos.c
#	$(CC) -c archivos.c $(CFLAGS)
#
#muestreo: muestreo.o procesamiento.o archivos.o 
#	$(CC) muestreo.o procesamiento.o archivos.o -o $(PROYECTO) $(LDFLAGS)
#PHONY: clean

install: all
	if [ ! -d $(DESTDIR) ]; then \
		sudo mkdir $(DESTDIR); \
	fi; \
	sudo cp $(PROYECTO) $(DESTDIR)

uninstall: 
	sudo rm $(DESTDIR)/$(PROYECTO)

clean: 
	rm -f *.o $(PROYECTO)
