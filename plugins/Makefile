CC?=gcc

subdirs=src/pubnub

all: 
	for dir in $(subdirs); do \
		$(MAKE) -C $$dir; \
	done

clean:
	for dir in $(subdirs); do \
		$(MAKE) clean -C $$dir; \
	done
