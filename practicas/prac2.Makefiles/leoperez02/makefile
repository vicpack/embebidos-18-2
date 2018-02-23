#archivo makefile

PROYECTO=muestreo
DESTDIR=/usr/local/bin
CFLAGS=-Wall
LDFLAGS=-lm
CC=gcc

all: $(PROYECTO)

%.o: %.c
	$(CC) -c $< $(CFLAGS)
#procesamiento.o: procesamiento.c
#	$(CC) -c procesamiento.c $(CFLAGS)

#archivos.o: archivos.c
#	$(CC) -c archivos.c $(CFLAGS)

#muestreo.o: muestreo.c
#	$(CC) -c muestreo.c $(CFLAGS)

# fecvha de entrefa: lunes 26
# tarea: investigar reduccion de la siguiente linea: reduccion de dependencias
# uso de wildcard
# enviar con ramas de practica 2 
#equipo5
$(PROYECTO): procesamiento.o archivos.o muestreo.o
	$(CC) $^ -o $@ $(LDFLAGS) 
#	$(CC) $^ -o $(PROYECTO) $(LDFLAGS) 
#	$(CC) procesamiento.o archivos.o muestreo.o -o $(PROYECTO) $(LDFLAGS) 

install: all
	if [ ! -d $(DESTDIR) ] ; then \
		sudo mkdir $(DESTDIR); \
	fi; \
	sudo cp $(PROYECTO) $(DESTDIR)

uninstall:
	sudo rm $(DESTDIR)/$(PROYECTO)

.PHONY: barrele

barrele:
	rm *.o $(PROYECTO)
