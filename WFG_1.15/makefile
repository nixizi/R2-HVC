EXE = wfg
OBJ = read.o 
OPT = -O3 

CC = gcc -std=c99

$(EXE): $(OBJ) wfg.c
	$(CC) -o wfg wfg.c $(OBJ)

%.o: %.c
	$(CC) -c $<

clean: 
	rm -f wfg *.o 
	rm -rf *.dSYM
