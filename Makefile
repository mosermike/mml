##################################################
##		 MAKEFILE libmml 		##
##		 Mike Moser 			##
##################################################

PROJECT = libmml

#DVARS = -D_location=\"$(PWD)\"

GCC = /usr/bin/g++

CFLAGS		+= -Wall -O2 -fPIC -std=c++20 -Weffc++ -flto
CFLAGS_GDB	+= -Wall -fPIC -std=c++20 -O0 -ggdb -fstack-protector-strong

LDFLAGS = -Wl,-soname,libmml.so -lstdc++

INCLUDE += -I include

LIBRARY += -L ./

INSTALL_DIR = /usr/lib

SRC = $(wildcard src/*.cpp)
OBJ = $(SRC:%.cpp=%.o)

DST = libmml.a
MDST = libmml.so

HPP = $(wildcard include/*.hpp )
DST_HPP = $(wildcard $(INSTALL_DIR)/mml/*.hpp $(INSTALL_DIR)/mml.hpp)

default_target : all
target debug: override CFLAGS = $(CFLAGS_GDB)
target m.all: override INCLUDE = $(MINCLUDE)

all: $(DST)
	@echo "\e[1;32m| Only ${shell cat $(SRC) $(HPP)| grep TODO | wc -l} TODOs! \e[0m"

install: $(OBJ) $(MOBJ)
	cp -ar include /usr/local/
	$(GCC) -shared $(LDFLAGS) -o $(INSTALL_DIR)/$(MDST) $(OBJ)
	ldconfig
#ar rcs $(INSTALL_DIR)/libmml.a $(OBJ)
clean:
	rm -f $(OBJ)
	rm -f lib/$(DST)

distclean:
	rm -f $(OBJ)
	rm -f lib/$(DST)
	rm -f /usr/local/include/mml.hpp
	rm -rf /usr/local/include/mml
	rm -rf $(INSTALL_DIR)/$(MDST)

debug: $(DST)

%.o: %.cpp
	$(GCC) $(DVARS) $(INCLUDE) $(CFLAGS) -c -o $@ $<

mml: $(DST)
	@size $(DST)

	@echo "\e[1;32m| Only ${shell cat $(SRC) $(HPP)| grep TODO | wc -l} TODOs! \e[0m"
libmml.so: $(OBJ)
	$(GCC) -shared $(LDFLAGS) -o lib/$(DST) $(OBJ)

libmml.a: $(OBJ)
	ar rcs lib/libmml.a $(OBJ)


