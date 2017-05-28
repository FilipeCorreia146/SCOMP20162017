#include <stdio.h>
#include <stdlib.h>
#include "ex09.h"

void obtem_Notas(int nAluno) {

    printf("=====================================================\n");

    printf("Por favor introduza o número do aluno: ");
    scanf("%d", &array[nAluno].numeroAluno);
    printf("Por favor introduza as notas do aluno: \n");
    printf("Nota 1: ");
    scanf("%d", &array[nAluno].notaG1);
    printf("Nota 2: ");
    scanf("%d", &array[nAluno].notaG2);
    printf("Nota 3: ");
    scanf("%d", &array[nAluno].notaG3);

    printf("=====================================================\n");


}
