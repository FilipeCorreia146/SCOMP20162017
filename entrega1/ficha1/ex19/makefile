backup: main.o backup.o resize.o
	gcc -Wall -g main.o backup.o resize.o -o backupfiles
	
main.o: main.c backup.h resize.h
	gcc -Wall -g -ansi -c main.c -o main.o

backup.o: backup.c
	gcc -Wall -g -ansi -c backup.c -o backup.o

resize.o: resize.c
	gcc -Wall -g -ansi -c resize.c -o resize.o

run: backup
	./backupfiles

clean:
	rm *.o backupfiles
