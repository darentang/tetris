CC=gcc
SRC=tetris_core
IDIR = ../include
ODIR = obj
INCL = $(IDIR)/$(SRC).h
LDIR = ../lib/
ODIR = ../bin/

default: $(ODIR)$(SRC).o $(LDIR)lib$(SRC).a 

exec: $(SRC)

exec_run: $(SRC)
	./$(SRC)

$(SRC): $(SRC).c $(INCL)
	$(CC) $< -o $(SRC)
	
$(LDIR)lib$(SRC).a: $(ODIR)$(SRC).o
	ar rcs $@ $^
    
$(ODIR)$(SRC).o: $(SRC).c $(INCL)
	$(CC) -c $< -o $(ODIR)$(SRC).o

clean:
	rm $(ODIR)*.o $(LDIR)*.a $(SRC)
	