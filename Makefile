input=src
output=out
object_dir=obj
ood=$(output)/$(object_dir)

build : $(ood)/main.o $(ood)/grid.o $(ood)/viewTerminal.o
	gcc $(ood)/main.o $(ood)/grid.o $(ood)/viewTerminal.o -o $(output)/exec

$(ood)/main.o : $(ood) $(input)/main.c
	gcc -c $(input)/main.c -o $(ood)/main.o

$(ood)/grid.o : $(ood) $(input)/grid.c $(input)/grid.c
	gcc -c $(input)/grid.c -o $(ood)/grid.o

$(ood)/viewTerminal.o : $(ood) $(input)/viewTerminal.c $(input)/viewTerminal.h
	gcc -c $(input)/viewTerminal.c -o $(ood)/viewTerminal.o

$(ood) :
	mkdir $(output)
	mkdir $(ood)