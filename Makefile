.PHONY: all base clean install

MAKE_FLAGS=--no-print-directory

all:
	$(MAKE) $(MAKE_FLAGS) -C lib_dir
	$(MAKE) $(MAKE_FLAGS) -C src

install:
	$(MAKE) $(MAKE_FLAGS) -C lib_dir
	$(MAKE) $(MAKE_FLAGS) -C src $@

clean:
	$(MAKE) $(MAKE_FLAGS) -C lib_dir $@
	$(MAKE) $(MAKE_FLAGS) -C src $@
