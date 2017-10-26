OPT= -g -Wall -Wextra #-Werror


analyseurSimu: analyse.o trace.o analyseurSimu.o matrice.o
	gcc $(OPT) $^ -o $@ -lm

%.o: %.c %.h
	gcc $(OPT) $< -c


clean:
	rm *.o analyseurSimu
