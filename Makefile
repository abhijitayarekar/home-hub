TOPDIR=$(shell pwd)

CC=$(CROSS_COMPILE)g++

BIN_DIR=$(TOPDIR)/bin

#CFLAGS=-std=gnu99 -Wall -ggdb3 -O3 -I$(TOPDIR)/include -I$(TOPDIR)/pubsub-impl/include
CPPFLAGS=-Wc++11-extensions -Wall -I$(TOPDIR)/include
SRCS=src/main.cpp src/devices/*.cpp

#pubnub flags and srcs start
#CFLAGS+=-I/usr/local/include -I/usr/include/json # C flags
#LDFLAGS+=-L/usr/local/lib -lpubnub -ljson -lcurl -lcrypto -levent # linking flags
#SRCS+=pubsub-impl/src/pubnub/*.c
#pubnub flags and srcs end

all:
	rm -rf $(BIN_DIR)
	mkdir -p $(BIN_DIR)
	$(CC) $(SRCS) $(CPPFLAGS) $(LDFLAGS) -o $(BIN_DIR)/home-hub

clean:
	rm -rf $(BIN_DIR)
	rm -f *.o
