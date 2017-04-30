#define SHM_NAME "shm_ex13"
#define N_PRIORITIES 4
#define LINE_SIZE 3
#define MSG_SIZE 50

typedef struct{
	char priorityQueue [N_PRIORITIES][LINE_SIZE][MSG_SIZE];
}buffer;
