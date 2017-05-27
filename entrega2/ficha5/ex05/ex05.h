#define DATA_SIZE 1000
#define CALCULATE_NUM 200

int resultados[DATA_SIZE];
int dados[DATA_SIZE];
int threadVerify;
pthread_mutex_t  mutex;

void * thread_func (void *arg);
