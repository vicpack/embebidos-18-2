#archivo makefile

PROYECTO=muestreo
DESTDIR=/usr/local/bin
CFLAGS=-Wall
LDFLAGS=-lm
CC=gcc
objects := $(patsubst %.c,%.o,$(wildcard *.c))

%.o: %.c
	$(CC) -c $< $(CFLAGS)

$(PROYECTO):  $(objects)
	     #cc -o PROYECTO $(objects)

	    $(CC) $^ -o $@ $(LDFLAGS) 

install: all
	if [ ! -d $(DESTDIR) ] ; then \
		sudo mkdir $(DESTDIR); \
	fi; \
	sudo cp $(PROYECTO) $(DESTDIR)

uninstall:
	sudo rm $(DESTDIR)/$(PROYECTO)

.PHONY: clean

clean:
	rm *.o $(PROYECTO)
