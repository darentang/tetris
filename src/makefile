CC=gcc
SRC=tetris_core
IDIR = ../include
ODIR = obj
INCL = $(IDIR)/blocks.h

default: lib$(SRC).a

exec: $(SRC)

exec_run: $(SRC)
	./$(SRC)


$(SRC): $(SRC).c $(INCL)
	$(CC) $< -o $(SRC)
	

lib$(SRC).a: $(SRC).o
	ar rcs $@ $^
    
$(SRC).o: $(SRC).c $(INCL)
	$(CC) -c $<

clean:
	rm *.o *.a $(SRC)
	