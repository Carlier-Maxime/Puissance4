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
	$(CC) $^ -o $(output)/puissance4

$(ood)/%.o : $(input)/%.c
	@mkdir -p $(ood)
	$(CC) $(CFLAGS) -c $< -o $@

test : test/main.c src/grid.c
	$(CC) test/main.c src/grid.c -o $(output)/test -lcunit

clean :
	rm -r $(output)