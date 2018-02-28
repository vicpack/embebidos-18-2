#Archivo Makefile con objetivos falsos,
# variables automaticas y reglas de patron

PROYECTO = muestreo
DESTDIR = /usr/local/bin
CFLAGS = -Wall
LDFLAGS = -lm
CC = gcc
SRC = $(wildcard *.c)
OBJECTS = $(SRC:.c=.o)

all: $(PROYECTO)

%.o: %.c
	$(CC) -c $< $(CFLAGS)

$(PROYECTO): $(OBJECTS)
	$(CC) $^ -o $@ $(LDFLAGS)
	
.PHONY: clean

install: all
	if [ ! -d $(DESTDIR) ]; then \
		sudo mkdir $(DESTDIR); \
	fi; \
	sudo cp $(PROYECTO) $(DESTDIR)
	
uninstall:
	sudo rm $(DESTDIR)/$(PROYECTO)

clean:
	rm -f *.o $(PROYECTO)

