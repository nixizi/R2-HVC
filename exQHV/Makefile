#
# This is a multipurpose makefile
#
# Procedures:
# To run Valgrind, start GUD in emacs and then press F9. The yes file will put the GUD in the first problem
# IMPORTANT: splint main.c
# To pack the project use the pack-F2 dir, with symlinks and the archiver, for both procedures there are nautilus scripts.
# Profiling: gprof project
# kprof is graphical gprof: kprof
# Anotated code : gprof -l -A -x project
# Better anotated code : make coverage (then just less the .c.cov)
# WARNING just use kcachegrind it is good:
#                    valgrind --tool=callgrind -v ./project && kcachegrind callgrind.out.4330
# Memory alignment stuff
# pahole project
# valgrind --tool=cachegrind -v ./project 

# The compiler to use
CC        = gcc
# The name of the executable to produce
EXEC      = project
# Ansi flags, make the compiler more informative
ANSI      = -ansi -pedantic -Wall -Wextra -std=c99 
# Puts cacheline size in a macro
CLS       = -DCLS=$$(getconf LEVEL1_DCACHE_LINESIZE)
# Use this if you want to use SSE2 instructions
SSE2      = -msse2
# Debug flags for gdb/GUD
DEBUG     = -O0 -gdwarf-2 -g3 -ggdb
# Profile flags for gprof
PROFILE   = -pg -fprofile-arcs -ftest-coverage
# Optimization flags for production
# The -s makes smaller executables. It is a strong strip command.
OPTIMIZE  = -O9 -march=core2

DIM = 3

# Uncomment the flags that you need in a particular compile
# Always use ANSI
CFLAGS    = $(ANSI) $(CLS) $(SSE2) -D D=$(DIM)
#CFLAGS    += -static
#CFLAGS   += $(DEBUG)
CFLAGS  += $(OPTIMIZE)
#CFLAGS  += $(PROFILE)
#CFLAGS += -D COUNT

##  Base Makefile
##  Diferent classes of files
CS    = $(wildcard *.c)
HS    = $(wildcard *.h)
IS    = $(addsuffix .i, $(basename $(CS)))
SS    = $(addsuffix .s, $(basename $(IS)))
OS    = $(addsuffix .o, $(basename $(SS)))
HOLES = $(addsuffix .hls, $(basename $(SS)))
COVS  = $(addsuffix .c.gcov, $(basename $(CS)))
STATS = $(addsuffix .gcda, $(basename $(CS))) $(addsuffix .gcno, $(basename $(CS)))

# Phony targets 
.PHONY: all coverage clean tags depend dox

# Default Compile
#all: $(SS) $(EXEC) $(HOLES)
all: $(SS) $(EXEC)

coverage: $(COVS)

## Linking rule
$(EXEC): $(OS)
	@echo Linking $@
	$(CC) $(CFLAGS) $(OS) -lm -o $@

## Run Preprocessor
%.i: %.c
	@echo Run Preprocessor: $<
	$(CC) $(CFLAGS) -E -o $@ $<

## Generate Assembly
%.s: %.i
	@echo Get Assembly: $<
	$(CC) $(CFLAGS) -S -o $@ $<

## Build Object
%.o: %.s
	@echo Build Objects: $<
	$(CC) $(CFLAGS) -c -o $@ $<

## Find Holes
%.hls: %.o
	@echo Show struct holes
	pahole -I -H 1 $< | sed 's/.* \(.\+:[0-9]\+\) .*/\1:1:/'

## Pack using directory links
%.tgz: $(CS) $(HS) Makefile
	@echo Pack Using directory
	tar -chvzf $@ $(basename $@ .tgz)

## Coverage statistics
%.c.gcov: %.gcda %.gcno	
	@echo Anotated coverage source $<
	gcov -a -b -f $<
	dos2unix $@

## Make dependencies
depend: depend.mak

## Make dependencies forcing creation of all files
depend.mak: $(CS) $(HS)
	@echo Making dependencies ...
	$(CC) $(CFLAGS) -MM $(CS) | sed 's/\.o/\.i/g' > depend.mak

-include depend.mak

## Clean up
clean:
	@echo Cleaning Up
	rm -f $(EXEC) $(STATS) $(COVS) $(IS) $(SS) $(OS) gmon.out depend.mak *~ callgrind.out.* cachegrind.out.*

## TAGS
tags: TAGS
TAGS: $(CS) $(HS)
	@echo Making TAGS
	etags $(CS) $(HS)

## doc, make documentation with doxymacs
dox: $(CS) $(HS) Doxyfile
	doxygen

## run splint for checking code
check: $(CS) $(HS)
	splint $<
