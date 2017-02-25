main: main.o palindrome.o
	gcc -Wall -g main.o palindrome.o -o palindrome

main.o: main.c palindrome.h
	gcc -Wall -g -c main.c

palindrome.o: palindrome.c
	gcc -Wall -g -c palindrome.c

run: main
	./palindrome

clean: 
	rm *.o palindrome
