# Dichiarazione delle variabili
IDIR := ../../con2redis/src
OBJDIR := ../obj
BINDIR := ../bin
TARGET := $(BINDIR)/main

CC := g++
CFLAGS=-std=c++20 -g -ggdb -fpermissive -L/usr/local/lib -Wall -I. -I$(IDIR) -lpq -lm -lhiredis

DEPS = $(wildcard $(IDIR)/*.h)
SRC = $(wildcard *.cpp)
OBJ = $(patsubst %.cpp, $(OBJDIR)/%.o, $(SRC))

con2redis_OBJ := $(wildcard ../../con2redis/obj/*.o)

all:	con2redis $(BINDIR)/main

con2redis:
	$(MAKE) -C ../../con2redis/src

$(OBJDIR)/%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

$(BINDIR)/main: $(OBJ) $(DEPS)
	$(CC) -o $@ $(OBJ) $(con2redis_OBJ) $(CFLAGS)

.PHONY: clean

clean:
	rm -f $(OBJDIR)/*.o *~ $(IDIR)/*~ core 
