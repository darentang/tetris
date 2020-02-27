IDIR=/usr/local/include/Python3.7m
LDIR=/usr/local/lib/Python3.7
ODIR=bin

default: _tetris.so

_tetris.so: $(ODIR)/interface_wrap.o $(ODIR)/tetris.o
	ld -bundle -o _tetris.so $(ODIR)/interface_wrap.o $(ODIR)/tetris.o $(ODIR)/tetris_core.o -macosx_version_min 10.14 -lSystem

$(ODIR)/tetris.o:
	make -Csrc

$(ODIR)/interface_wrap.o: scripts/interface_wrap.cxx
	g++ -c scripts/interface_wrap.cpp -I$(IDIR) -L$(LDIR) -o $(ODIR)/interface_wrap.o

scripts/interface_wrap.cxx:
	swig -c++ -python -o scripts/interface_wrap.cpp -interface interface_wrap scripts/interface.i 

clean:
	rm bin/* scripts/interface_wrap.cpp