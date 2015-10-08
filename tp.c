#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "conway.h"

int main(int argc, char const *argv[]) {
  int linha, coluna, i, j;
  int **n0, **n1;
  char controle = 'a';
  char output[10] = "saida.txt";
  FILE *entrada;

  entrada = fopen("dados.txt", "r");
  if (entrada == NULL) {
    printf("Erro de abertura do arquivo.\n");
    return -1;
  }

  fscanf(entrada, "%d %d", &linha, &coluna);
  alocaMatriz(&n0, linha, coluna);
  alocaMatriz(&n1, linha, coluna);

  for (i = 0; i < linha; i++) {
    for (j = 0; j < coluna; j++) {
      fscanf(entrada, "%d", &n0[i][j]);
    }
  }
  fclose(entrada);

  while (toupper(controle) != 'N') {
    system("clear");
    imprimeMatriz(n0, linha, coluna);

    printf("Você gostaria de continuar executando a evolução das "
           "gerações?\nDigite 's' se gostaria e 'n' se não gostaria.\n");
    scanf(" %c", &controle);

    if (toupper(controle) == 'S') {
      novaGeracao(n0, n1, linha, coluna);
      copiaMatriz(n0, n1, linha, coluna);
    }
  }

  imprimeConway(output, linha, coluna, n0);
  liberaMatriz(n0, linha);
  liberaMatriz(n1, linha);

  return 0;
}
