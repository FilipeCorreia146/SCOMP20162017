all: writer reader

writer: writer.c ex01.h
	gcc -lrt -lm -Wall -g -o writer writer.c

reader: reader.c ex01.h
	gcc -lrt -lm -Wall -g -o reader reader.c

clean:
	rm -f writer reader

run_reader: reader
	./reader

run_writer: writer
	./writer

