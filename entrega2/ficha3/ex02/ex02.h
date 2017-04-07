#define ARRAY_SIZE 10
#define SHM_NAME "/shm_ex02"


typedef struct{
	int flag;
	int array[ARRAY_SIZE];
} Numbers;
