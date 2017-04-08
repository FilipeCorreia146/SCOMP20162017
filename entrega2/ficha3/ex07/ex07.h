#define BUFFER_SIZE 10
#define EXCHANGE_NUM 30
#define SHM_NAME "/shm_ex07"

typedef struct {
	int buffer[BUFFER_SIZE];
	int counter;
} storage;
