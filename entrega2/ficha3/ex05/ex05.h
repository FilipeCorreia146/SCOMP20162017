#define STR_SIZE 50
#define NR_DISC 10
#define SHM_NAME "/shm_ex05"

struct aluno{
	int numero;
	char nome[STR_SIZE];
	int disciplinas[NR_DISC];
	int flag;
};

typedef struct aluno aluno;
