export TOPDIR=$(shell pwd)

include make.config

CFLAGS=-std=gnu99 -Wall -ggdb3 -O3 $(ALL_INCLUDES)
LDFLAGS=$(PUBSUB_IMPL_DEPS)
SRCS= src/main.c src/pubsub.c $(PUBSUB_IMPL_BIN_DIR)/*.a

all: bin-dir pubsubimpl home-hub

bin-dir:
	rm -rf $(BIN_DIR)
	mkdir -p $(BIN_DIR)

home-hub:
	$(CC) $(SRCS) $(CFLAGS) $(LDFLAGS) -o $(BIN_DIR)/home-hub
	rm -rf $(PUBSUB_IMPL_BIN_DIR)

pubsubimpl:
	$(MAKE) -C pubsub-impl

pubsubimpl-clean:
	rm -rf $(PUBSUB_IMPL_BIN_DIR)
	$(MAKE) clean -C pubsub-impl
	
clean: pubsubimpl-clean
	rm -rf $(BIN_DIR)
	rm -f *.o
