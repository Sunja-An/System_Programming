.PHONY: clean

RM = rm -f

FTM: main.o print_form.o move.o
	gcc -o FTM main.o print_form.o move.o -lpthread -lncurses

main.o: main.c
	gcc -c main.c -lpthread -lncurses -o main.o

print_form.o: Print/print_form.c Print/print_form.h
	gcc -c Print/print_form.c -lncurses -o print_form.o

move.o: Move/move.c Move/move.h
	gcc -c Move/move.c -o move.o

clean:
	$(RM) *.o