
CXXFLAGS += -Wall $(INCS) -I$(TOP_DIR)/controller/include -I$(PLATFORM_DIR)/controller/include -std=c++11
LDFLAGS += -L$(PLATFORM_DIR)/controller/libs -lpthread

SRCS=	\
	src/main.cpp \
	$(TOP_DIR)/controller/src/controller.cpp

all: controller

prepare-bin:
	mkdir -p $(BIN_DIR)/controller

controller: prepare-bin
	$(CC) $(SRCS) $(CXXFLAGS) $(LDFLAGS) -o $(BIN_DIR)/controller/controller

clean-bin:
	rm -rf $(BIN_DIR)/controller

clean: clean-bin
	