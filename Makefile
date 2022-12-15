CC := gcc
DEBUG ?= 0
ifeq '$(DEBUG)' '1'
	CFLAGS ?= -Wall -MMD -g
else
	CFLAGS ?= -Wall -MMD
endif
output=out
object_dir=obj
ood=$(output)/$(object_dir)
.PHONY: build test clean

build : $(ood)/src/main.o $(ood)/src/grid.o $(ood)/src/viewTerminal.o
	$(CC) $^ -o $(output)/puissance4

test : $(ood)/test/main.o $(ood)/src/grid.O
	$(CC) $^ -o $(output)/test -lcunit

$(ood)/src/%.o : src/%.c
	@mkdir -p $(ood)/src
	$(CC) $(CFLAGS) -c $< -o $@

$(ood)/test/%.o : test/%.c
	@mkdir -p $(ood)/test
	$(CC) $(CFLAGS) -c $< -o $@

clean :
	rm -r $(output)