include make.config

CC?=gcc

CFLAGS=-std=gnu99 -Wall -ggdb3 -O3 -I/usr/local/include -I/usr/include/json

LIBS=-L/usr/local/lib -lpubnub -ljson -lcurl -lcrypto -levent

OBJS=main.o

all: home-hub

home-hub:
	$(CC) src/main.c $(CFLAGS) $(LIBS) -o home-hub

home-hub-plugins:
	$(MAKE) -C plugins

home-hub-plugins-clean:
	$(MAKE) clean -C plugins
	
clean:
	rm -f *.o home-hub
