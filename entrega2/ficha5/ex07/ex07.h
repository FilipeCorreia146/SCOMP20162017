#define VEC_SIZE 15
#define N_PRODUTOS 5

typedef struct{
  int id_h;
  int id_p;
  int x;
} hipermercado;

hipermercado vec[VEC_SIZE];
hipermercado vec1[N_PRODUTOS];
hipermercado vec2[N_PRODUTOS];
hipermercado vec3[N_PRODUTOS];

pthread_mutex_t mux;
pthread_mutex_t cMux;

int menorCusto;
int custo;

void fillVector();
void * sort_func(void* arg);
void * calc_func(void* arg);
