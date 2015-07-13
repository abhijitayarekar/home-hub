export TOPDIR=$(shell pwd)

include make.config

CFLAGS=-std=gnu99 -Wall -ggdb3 -O3 $(HOME_HUB_INCLUDES)
LDFLAGS=$(PLUGINS_DEPS)
SRCS= src/main.c src/pubsub.c $(PLUGINS_BIN_DIR)/*.a

all: setup-bin-dir home-hub-plugins home-hub

setup-bin-dir:
	rm -rf $(BIN_DIR)
	mkdir -p $(BIN_DIR)

home-hub:
	$(CC) $(SRCS) $(CFLAGS) $(LDFLAGS) -o $(BIN_DIR)/home-hub
	rm -rf $(PLUGINS_BIN_DIR)

home-hub-plugins:
	$(MAKE) -C plugins

home-hub-plugins-clean:
	rm -rf $(PLUGINS_BIN_DIR)
	$(MAKE) clean -C plugins
	
clean: home-hub-plugins-clean
	rm -rf $(BIN_DIR)
	rm -f *.o
