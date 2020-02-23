SRC=tetris_core
LIB_DIR=lib
SETUP=scripts/setup.py
WRAPPER=scripts/wrapper.pyx

default: something

something: $(SETUP) $(WRAPPER) $(LIB_DIR)/lib$(SRC).a
	python3 $(SETUP) build_ext --inplace

$(LIB_DIR)/lib$(SRC).a:
	make -C src

clean:
	rm *.so