Project: main.o Q1.o Q2.o Q3.o Q4.o Q5.o Q6.o
	gcc -g	main.o Q1.o Q2.o Q3.o Q4.o Q5.o Q6.o	-lm	-o x

Menu.o: main.c main.h
		gcc -c main.c

Q1.o: Q1.c Q1.h
		gcc -c Q1.c

Q2.o: Q2.c Q2.h
		gcc -c Q2.c

Q3.o: Q3.c Q3.h
		gcc -c Q3.c
	
Q4.o: Q4.c Q4.h
		gcc -c Q4.c

Q5.o: Q5.c Q5.h
		gcc -c Q5.c -lm

Q6.o: Q6.c Q6.h
		gcc -c Q6.c
						
clean:
	rm -f *.o
