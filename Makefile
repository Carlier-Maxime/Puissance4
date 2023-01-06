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
OBJS_SRC = $(ood)/src/grid.o $(ood)/src/viewTerminal.o $(ood)/src/error.o $(ood)/src/player.o $(ood)/src/playerHuman.o $(ood)/src/view.o $(ood)/src/playerAIBase.o $(ood)/src/playerAIEasy.o $(ood)/src/playerAINormal.o $(ood)/src/playerAIHard.o $(ood)/src/viewSDL.o
OBJS_TEST = $(ood)/test/grid.o $(ood)/test/viewTerminal.o $(ood)/test/player.o $(ood)/test/playerHuman.o $(ood)/test/playerAIEasy.o
#MACRO = -DREQUIRE_USER_INPUT=1
.PHONY: build test clean mrproper

build : $(ood)/src/main.o $(OBJS_SRC)
	$(CC) $^ -o $(output)/puissance4

test : $(ood)/test/main.o $(OBJS_TEST) $(OBJS_SRC)
	$(CC) $^ -o $(output)/test -lcunit

$(ood)/src/%.o : src/%.c
	@mkdir -p $(ood)/src
	$(CC) $(CFLAGS) -c $< -o $@ $(MACRO)

$(ood)/test/%.o : test/%.c
	@mkdir -p $(ood)/test
	$(CC) $(CFLAGS) -c $< -o $@ $(MACRO)

clean :
	rm -r $(ood)

mrproper : clean
	rm $(output)/puissance4
	rm $(output)/test