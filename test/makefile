###################
# MAKEFILE tests  #
###################

PROJECT = test

GCC = /usr/bin/g++

std = c++20

CFLAGS += -Wall -O2 -pipe -Weffc++ -flto -std=$(std)

CFLAGS_GDB = -Wall -Weffc++ -O0 -ggdb #-Werror

INCLUDE = -I ../include
LDFLAGS = -L ../lib -lmml

target debug   : override CFLAGS = $(CFLAGS_GDB)

SRC = $(wildcard ./src/*.cpp *.cpp )
OBJ = $(SRC:%.cpp=%.o)
DST = $(SRC:%.cpp=%.x)

.SECONDARY: $(OBJ) # Keep the object files

all: $(DST)

clean:
	rm *.o *.x

debug: $(DST)

%.o: %.cpp
	$(GCC) $(LDFLAGS) $(INCLUDE) $(CFLAGS) -c -o $@ $<

%.x: %.o
	$(GCC) $< $(CFLAGS) $(INCLUDE) $(LIBRARY) $(LDFLAGS) -o $@ 
