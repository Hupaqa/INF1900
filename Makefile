.PHONY: all base clean install

LIB_FOLDER=lib_dir
SRC_FOLDER=src
MAKE_FLAGS=--no-print-directory

all:
	$(MAKE) $(MAKE_FLAGS) -C $(LIB_FOLDER)
	$(MAKE) $(MAKE_FLAGS) -C $(SRC_FOLDER)

install:
	$(MAKE) $(MAKE_FLAGS) -C $(LIB_FOLDER)
	$(MAKE) $(MAKE_FLAGS) -C $(SRC_FOLDER) $@

clean:
	$(MAKE) $(MAKE_FLAGS) -C $(LIB_FOLDER) $@
	$(MAKE) $(MAKE_FLAGS) -C $(SRC_FOLDER) $@
