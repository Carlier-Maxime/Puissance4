CC := gcc
DEBUG ?= 0
ifeq '$(DEBUG)' '1'
	CFLAGS ?= -Wall -MMD -g
else
	CFLAGS ?= -Wall -MMD
endif
input=src
output=out
object_dir=obj
ood=$(output)/$(object_dir)
.PHONY: build test

build : $(ood)/main.o $(ood)/grid.o $(ood)/viewTerminal.o
	$(CC) $(ood)/main.o $(ood)/grid.o $(ood)/viewTerminal.o -o $(output)/puissance4

$(ood)/main.o : $(ood) $(input)/main.c
	$(CC) -c $(input)/main.c -o $(ood)/main.o $(CFLAGS)

$(ood)/grid.o : $(ood) $(input)/grid.c $(input)/grid.c
	$(CC) -c $(input)/grid.c -o $(ood)/grid.o $(CFLAGS)

$(ood)/viewTerminal.o : $(ood) $(input)/viewTerminal.c $(input)/viewTerminal.h
	$(CC) -c $(input)/viewTerminal.c -o $(ood)/viewTerminal.o $(CFLAGS)

$(ood) :
	mkdir $(output)
	mkdir $(ood)

test : test/main.c src/grid.c
	$(CC) test/main.c src/grid.c -o $(output)/test -lcunit

clean :
	rm -r $(output)