include $(TOPDIR)/make.config

subdirs=src/pubnub

all:
	rm -rf $(PUBSUB_IMPL_BIN_DIR)
	mkdir -p $(PUBSUB_IMPL_BIN_DIR)
	 
	for dir in $(subdirs); do \
		$(MAKE) -C $$dir; \
	done

clean:
	rm -rf $(PUBSUB_IMPL_BIN_DIR)
	
	for dir in $(subdirs); do \
		$(MAKE) clean -C $$dir; \
	done
