OPT= -g -Wall -Wextra #-Werror


analyse: analyse.o trace.o
	gcc $(OPT) $^ -o analyse -lpcap -lm

%.o: %.c %.h
	gcc $(OPT) $< -c


clean:
	rm *.o analyseur
