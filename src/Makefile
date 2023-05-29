.PHONY: clean

RM = rm -f

FTM: main.o print_form.o move.o
	gcc -o FTM Object/main.o Object/print_form.o Object/move.o -lpthread -lncurses -g

main.o: main.c	
	mkdir Object
	gcc -c main.c -lpthread -lncurses -o Object/main.o -g

print_form.o: Print/print_form.c Print/print_form.h
	gcc -c Print/print_form.c -lncurses -o Object/print_form.o -g

move.o: Move/move.c Move/move.h
	gcc -c Move/move.c -o Object/move.o -g

clean:
	$(RM) *.o
	$(RM) FTM