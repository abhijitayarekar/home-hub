export PLATFORM_DIR=$(shell pwd)
export TOP_DIR=$(PLATFORM_DIR)/../../
export BIN_DIR=$(PLATFORM_DIR)/bin
export CC=$(CROSS_COMPILE)g++
export INCS=-I$(TOP_DIR)/include

CFLAGS=-std=gnu99 -Wall -ggdb3 -O3 -I$(TOP_DIR)/include -I$(TOP_DIR)/pubsub-impl/include
CXXFLAGS=-std=c++11 -I$(TOP_DIR)/include -Wattributes
LDFLAGS += -std=c++11

#pubnub flags and srcs start
#CFLAGS+=-I/usr/local/include -I/usr/include/json # C flags
#LDFLAGS+=-L/usr/local/lib -lpubnub -ljson -lcurl -lcrypto -levent # linking flags
#SRCS+=pubsub-impl/src/pubnub/*.c
#pubnub flags and srcs end

all: controller

prepare-bin:
	mkdir -p $(BIN_DIR)

controller: prepare-bin
	$(MAKE) -C controller

controller-clean:
	$(MAKE) clean -C controller

clean-bin:
	rm -rf $(BIN_DIR)

clean: controller-clean clean-bin
