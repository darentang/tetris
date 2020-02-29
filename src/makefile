CC=gcc
CCPP=g++
SRC=tetris_core
CLASS=tetris
IDIR=../include
ODIR=obj
INCL=$(IDIR)/$(SRC).h
LDIR=../lib/
ODIR=../bin/
PYDIR=/usr/include/python3.7m/
PYLIB=/usr/lib/python3.7/

default: $(ODIR)$(SRC).o $(ODIR)$(CLASS).o

exec: $(ODIR)$(SRC).o $(ODIR)$(CLASS).o $(CLASS)

exec: $(SRC)

exec_run: $(SRC)
	./$(SRC)

$(SRC): $(SRC).c $(INCL)
	$(CC) $< -o $(SRC)
	
$(LDIR)lib$(SRC).a: $(ODIR)$(SRC).o
	ar rcs $@ $^
    
$(ODIR)$(SRC).o: $(SRC).c $(INCL)
	$(CC) -c $< -o $(ODIR)$(SRC).o

$(ODIR)$(CLASS).o: $(CLASS).cpp $(INCL)
	$(CCPP) -c $< -o $(ODIR)$(CLASS).o -I$(PYDIR) -L$(PYLIB)

$(CLASS): $(ODIR)$(SRC).o $(ODIR)$(CLASS).o
	$(CCPP) -o $(CLASS) $(ODIR)$(SRC).o $(ODIR)$(CLASS).o -I$(PYDIR) -L$(PYLIB)

clean:
	rm $(ODIR)*.o $(LDIR)*.a $(SRC)
	