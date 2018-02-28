PROYECTO=muestreo
DESTDIR=/usr/local/bin
CFLAGS=-Wall
LDFLAGS=-lm
CC=gcc
OBJ=muestreo.o procesamiento.o archivos.o

all: $(PROYECTO)

$(OBJ): %.o: %.c
	$(CC) -c $< $(CFLAGS)

$(PROYECTO): $(OBJ)
	$(CC) $^ -o $@ $(LDFLAGS)

.PHONY: clean

install: all
	if[! -d $(DESTDIR) ]; then \
		sudo mkdir $(DESTDIR); \
	fi; \
	sudo cp $(PROYECTO) $(DESTDIR)

uninstall:
	sudo rm $(DESTDIR)/$(PROYECTO)

clean:
	rm -f *.o $(PROYECTO)