all: writer reader

writer: writer.c ex02.h
	gcc -lrt -lm -Wall -g -o writer writer.c
	
reader: reader.c ex02.h
	gcc -lrt -lm -Wall -g -o reader reader.c
	
clean:
	rm -f writer reader
	
run_reader: reader 
	./reader
	
run_writer: writer
	./writer

delete_memory:
	./reader -rm
	
run: run_writer delete_memory
