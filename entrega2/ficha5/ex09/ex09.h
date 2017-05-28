#define N_ALUNOS 3

typedef struct{
  int numeroAluno;
  int notaG1;
  int notaG2;
  int notaG3;
  int notaFinal;
} prova;

prova array[N_ALUNOS];

int nAlunoAtual;
int nPositivas;
int nNegativas;
pthread_cond_t negativa;
pthread_cond_t positiva;
pthread_cond_t lido;
pthread_mutex_t mux;
pthread_mutex_t muxPN;

void obtem_Notas(int nAluno);
void * read_func(void * arg);
void * calc_func(void * arg);
void * func_negativa(void * arg);
void * func_positiva(void * arg);
