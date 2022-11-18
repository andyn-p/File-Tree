#--------------------------------------------------------------------
# Makefile for Assignment 4, Part 3
# Author: me
#--------------------------------------------------------------------

GCC = gcc217

TARGETS = ft

.PRECIOUS: %.o

all: $(TARGETS)

clean:
	rm -f $(TARGETS) meminfo*.out

clobber: clean
	rm -f dynarray.o path.o ft_client.o node.o ft.o *~

ft: dynarray.o path.o node.o ft.o ft_client.o
	$(GCC) -g $^ -o $@

dynarray.o: dynarray.c dynarray.h
	$(GCC) -g -c $<

path.o: path.c path.h
	$(GCC) -g -c $<

ft_client.o: ft_client.c ft.h a4def.h
	$(GCC) -g -c $<

node.o: node.c dynarray.h node.h path.h a4def.h
	$(GCC) -g -c $<

ft.o: ft.c dynarray.h node.h ft.h path.h a4def.h
	$(GCC) -g -c $<

