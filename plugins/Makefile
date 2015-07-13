include $(TOPDIR)/make.config

subdirs=src/pubnub

all:
	rm -rf $(PLUGINS_BIN_DIR)
	mkdir -p $(PLUGINS_BIN_DIR)
	 
	for dir in $(subdirs); do \
		$(MAKE) -C $$dir; \
	done

clean:
	rm -rf $(PLUGINS_BIN_DIR)
	
	for dir in $(subdirs); do \
		$(MAKE) clean -C $$dir; \
	done
