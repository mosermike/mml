##################################################
##		 MAKEFILE libmml 		##
##		 Mike Moser 			##
##################################################

TODOFILE1  = .mml.todo
TODOFILE2  = .math.todo

PROJECT = libmml

DVARS = -D_location=\"$(PWD)\"

GCC = /usr/bin/g++

CFLAGS		+= -Wall -O2 -fPIC -std=c++20 -Weffc++ -flto
CFLAGS_GDB	+= -Wall -fPIC -std=c++20 -O0 -ggdb -fstack-protector-strong

LDFLAGS = -Wl,-soname,libmml.so -lstdc++
MLDFLAGS = -Wl,-soname,libmath.so -lmml

INCLUDE += -I include
MINCLUDE += -I include -I include/math

LIBRARY += -L ./

INSTALL_DIR = /usr/local/lib

SRC = $(wildcard src/*.cpp)
MSRC = $(wildcard src/math/*.cpp)
OBJ = $(SRC:%.cpp=%.o)
MOBJ = $(MSRC:%.cpp=%.o)

DST = libmml.a
MDST = libmath.a

HPP = $(wildcard include/*.hpp )
MHPP = $(wildcard include/math/*.hpp)

default_target : all
target debug: override CFLAGS = $(CFLAGS_GDB)
target m.all: override INCLUDE = $(MINCLUDE)

all: $(DST) $(MDST)
	@cat $(SRC) $(HPP)| grep TODO | wc -l > $(TODOFILE1)
	@cat $(MSRC) $(MHPP)| grep TODO | wc -l > $(TODOFILE2)
	@echo "\e[1;32m| Only $(shell cat ${TODOFILE1}) and $(shell cat ${TODOFILE2}) TODOs! \e[0m"

install: $(OBJ) $(MOBJ)
	cp -ar include /usr/local/include/mml
	ar rcs $(INSTALL_DIR)/libmml.a $(OBJ)
	ar rcs $(INSTALL_DIR)/libmath.a $(MOBJ)

clean:
	rm -f $(OBJ) $(MOBJ)
	rm -f lib/$(DST) lib/$(MDST)
	
debug: $(DST)

%.o: %.cpp
	$(GCC) $(DVARS) $(INCLUDE) $(CFLAGS) -c -o $@ $<

mml: $(DST)
	@size $(DST)

	@cat $(SRC) $(HPP)| grep TODO | wc -l > $(TODOFILE1)
	
	@echo -e "\e[1;32m| Only $(shell cat ${TODOFILE1}) TODOs! \e[0m"

m.clean:
	@echo "| Delete $(OBJ)"
	@rm $(OBJ)

m.debug: $(DST)

libmml.so: $(OBJ)
	$(GCC) -shared $(LDFLAGS) -o lib/$(DST) $(OBJ)

libmml.a: $(OBJ)
	ar rcs lib/libmml.a $(OBJ)

math: $(MDST)
	@size $(MDST)
	@cat $(MSRC) $(MHPP)| grep TODO | wc -l > $(TODOFILE2)

M.clean:
	rm $(MOBJ)


M.debug: $(MDST)

libmath.so: $(MOBJ)
	$(GCC) -shared -o lib/$(MDST) $(MOBJ) $(MLDFLAGS) $(LIBRARY)

libmath.a: $(MOBJ)
	ar rcs lib/libmath.a $(MOBJ)

