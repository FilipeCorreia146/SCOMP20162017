#define DATA_SIZE 1000
#define CALCULATE_NUM 200
#define THREAD_NUM 5


int resultados[DATA_SIZE];
int dados[DATA_SIZE];
int threadVerify;
pthread_mutex_t  mutex;
pthread_cond_t cond;

void * thread_func (void *arg);
