
CPPFLAGS += -Wall -I$(TOPDIR)/include -I$(TOPDIR)/controller/include
LDFLAGS += -lzmq

all:
	$(CC) src/controller.cpp $(CPPFLAGS) $(LDFLAGS) -o $(BIN_DIR)/controller

clean:
	rm -f $(BIN_DIR)/controller