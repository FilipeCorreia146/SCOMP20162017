#define SHM_NAME "/shm_ex06"
#define ARRAY_SIZE 100

typedef struct{
	char path[ARRAY_SIZE];
	char word[ARRAY_SIZE];
	int num_occurrences;
} Search;
