OPT= -g -Wall -Wextra #-Werror


main: analyse.o trace.o
	gcc $(OPT) $^ -o main -lm

%.o: %.c %.h
	gcc $(OPT) $< -c


clean:
	rm *.o main
