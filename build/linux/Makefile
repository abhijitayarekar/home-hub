export TOPDIR=$(shell pwd)
export BIN_DIR=$(TOPDIR)/bin
export CC=$(CROSS_COMPILE)g++

CFLAGS=-std=gnu99 -Wall -ggdb3 -O3 -I$(TOPDIR)/include -I$(TOPDIR)/pubsub-impl/include
CPPFLAGS=-std=c++11 -I$(TOPDIR)/include -Wattributes
SRCS=src/main.cpp
LDFLAGS += -lzmq -std=c++11

#pubnub flags and srcs start
#CFLAGS+=-I/usr/local/include -I/usr/include/json # C flags
#LDFLAGS+=-L/usr/local/lib -lpubnub -ljson -lcurl -lcrypto -levent # linking flags
#SRCS+=pubsub-impl/src/pubnub/*.c
#pubnub flags and srcs end

all: controller home-hub

prepare-bin:
	rm -rf $(BIN_DIR)
	mkdir -p $(BIN_DIR)

controller: prepare-bin
	$(MAKE) -C controller

controller-clean:
	$(MAKE) clean -C controller

home-hub: prepare-bin
	$(CC) $(SRCS) $(CPPFLAGS) $(LDFLAGS) -o $(BIN_DIR)/home-hub

clean: controller-clean
	rm -rf $(BIN_DIR)
	rm -f *.o
