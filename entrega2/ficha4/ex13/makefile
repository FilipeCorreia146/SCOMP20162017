all: producer consumer

producer: producer.c ex13.h
	gcc -lrt -lm -Wall -g -o producer producer.c -lpthread

consumer: consumer.c ex13.h
	gcc -lrt -lm -Wall -g -o consumer consumer.c -lpthread

clean:
	rm -f producer consumer

run_consumer: consumer
	./consumer

run_producer: producer
	./producer

