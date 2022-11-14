#--------------------------------------------------------------------
# Makefile for Assignment 4, Part 2
# dt* targets are built using checkerDT
# rules to build dtBad*.o and nodeBad*.o from source will fail
# Author: Christopher Moretti
#--------------------------------------------------------------------

GCC = gcc217
#GCC = gcc217m

TARGETS = ft

.PRECIOUS: %.o

all: $(TARGETS)

clean:
	rm -f $(TARGETS) meminfo*.out

clobber: clean
	rm -f dynarray.o path.o ft_client.o node.o ft.o *~

ft: dynarray.o checker.o path.o node.o ft.o ft_client.o
	$(GCC) -g $^ -o $@

dynarray.o: dynarray.c dynarray.h
	$(GCC) -g -c $<

path.o: path.c path.h
	$(GCC) -g -c $<

ft_client.o: ft_client.c ft.h a4def.h
	$(GCC) -g -c $<

checker.o: checker.c dynarray.h checker.h node.h path.h a4def.h
	$(GCC) -g -c $<

node.o: node.c dynarray.h checker.h node.h path.h a4def.h
	$(GCC) -g -c $<

ft.o: ft.c dynarray.h checker.h node.h ft.h path.h a4def.h
	$(GCC) -g -c $<

