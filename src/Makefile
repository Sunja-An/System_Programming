
.PHONY: clean

RM = rm -f

FTM: main.o print_form.o move.o
	gcc -o FTM main.o print_form.o move.o

main.o: main.c
	gcc -Wall -g -c main.c -lpthread -lncurses

print_form.o: Print/print_form.c Print/print_form.h
	gcc -Wall -g -c Print/print_form.c

move.o: Move/move.c Move/move.h
	gcc -Wall -g -c Move/move.c

clean:
	$(RM) *.o
