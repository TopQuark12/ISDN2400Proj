# Makefile
# Author		Wong Tat Hang (Alex)    thwongaz@connect.ust.hk
# date        28/4/2019
# copyright   Copyright (c) 2019

IDIR =../include
CC=g++
CFLAGS=-I$(IDIR)

ODIR=obj
LDIR =../lib

LIBS=-lm

_DEPS = $(wildcard $(IDIR)/*.hpp)
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

ccsrc = $(wildcard *.cpp)
_OBJ = $(ccsrc:.cpp=.o)
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

run: $(OBJ)
	$(CC) -o ../$@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~ 