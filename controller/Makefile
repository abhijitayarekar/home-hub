
CXXFLAGS += -Wall -I$(TOPDIR)/include -I$(TOPDIR)/controller/include -std=c++11
LDFLAGS += -lzmq

all:
	$(CC) src/*.cpp $(CXXFLAGS) $(LDFLAGS) -o $(BIN_DIR)/controller

clean:
	rm -f $(BIN_DIR)/controller