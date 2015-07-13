include $(TOPDIR)/make.config

CFLAGS = -fPIC -Wall -Wextra -O3 -g 
CFLAGS += $(HOME_HUB_INCLUDES) 
CFLAGS += -I/usr/local/include -I/usr/include/json # C flags
LDFLAGS = -shared -L/usr/local/lib -lpubnub -ljson -lcurl -lcrypto -levent # linking flags
RM = rm -f  # rm command
TARGET_LIB = $(PLUGINS_BIN_DIR)/pubnubimpl.a # target lib
 
SRCS = pubnub.c # source files
OBJS = $(SRCS:.c=.o)
 
.PHONY: all
all: ${TARGET_LIB}
 
$(TARGET_LIB): $(OBJS)
	$(CC) ${LDFLAGS} -o $@ $^
 
$(SRCS:.c=.d):%.d:%.c
	$(CC) $(CFLAGS) -MM $< >$@
 
include $(SRCS:.c=.d)
 
.PHONY: clean
clean:
	-${RM} ${TARGET_LIB} ${OBJS} $(SRCS:.c=.d)
 	