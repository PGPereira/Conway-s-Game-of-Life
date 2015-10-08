#include <stdio.h>
#include <stdlib.h>

void imprimelinha(int tamanho) {
  int i;

  for (i = 0; i < tamanho * 3 + 2; i++) {
    printf("_");
  }

  printf("\n");
}

void alocaMatriz(int ***m, int linha, int coluna) {
  int i, **matriz;

  matriz = (int **)calloc(linha, sizeof(int *));

  for (i = 0; i < linha; i++) {
    matriz[i] = (int *)calloc(coluna, sizeof(int));
  }

  *m = matriz;
}

void liberaMatriz(int **matriz, int linha) {
  int i;
  for (i = 0; i < linha; i++)
    free(matriz[linha]);

  free(matriz);
}

void imprimeMatriz(int **matriz, int linha, int coluna) {
  int i, j;

  imprimelinha(coluna);
  for (i = 0; i < linha; i++) {
    printf("|");
    for (j = 0; j < coluna; j++) {
      if (matriz[i][j] == 0) {
        printf(" %c ", ' ');
      } else {
        printf(" %c ", '*');
      }
    }
    printf("|\n");
  }
  imprimelinha(coluna);
  printf("\n");
}

int quantidadeDeVizinhos(int **campo, int X, int Y, int n, int m) {
  int l, c, viz = 0;
  int Linha, Coluna;
  int Linha2, Coluna2;

  // Tratamento de erro: Caso a posicao analizada saia da matriz.
  if (X - 1 < 0) {
    Linha = X;
  } else {
    Linha = X - 1;
  }

  if (Y - 1 < 0) {
    Coluna = Y;
  } else {
    Coluna = Y - 1;
  }

  if (X + 1 > n - 1) {
    Linha2 = X;
  } else {
    Linha2 = X + 1;
  }

  if (Y + 1 > m - 1) {
    Coluna2 = Y;
  } else {
    Coluna2 = Y + 1;
  }

  for (l = Linha; l <= Linha2; l++) {
    for (c = Coluna; c <= Coluna2; c++) {
      viz += campo[l][c];
    }
  }

  return viz - campo[X][Y];
}

void novaGeracao(int **geracao1, int **geracao2, int linha, int coluna) {
  int i, j, vizinhos;

  for (i = 0; i < linha; i++) {
    for (j = 0; j < coluna; j++) {
      vizinhos = quantidadeDeVizinhos(geracao1, i, j, linha, coluna);

      if (geracao1[i][j] == 0) {
        if (vizinhos != 3) {
          geracao2[i][j] = 0;
        } else if (vizinhos == 3) {
          geracao2[i][j] = 1;
        }
      } else if (geracao1[i][j] == 1) {
        if (vizinhos < 2 || vizinhos > 3) {
          geracao2[i][j] = 0;
        } else {
          geracao2[i][j] = 1;
        }
      }
    }
  }
}

void copiaMatriz(int **m1, int **m2, int linha, int coluna) {
  int i, j;

  for (i = 0; i < linha; i++) {
    for (j = 0; j < coluna; j++) {
      m1[i][j] = m2[i][j];
    }
  }
}

void imprimeConway(char *nome, int linha, int coluna, int **cornway) {
  FILE *gravacao;
  int i, j;

  gravacao = fopen(nome, "w");
  fprintf(gravacao, "%d %d\n", linha, coluna);
  for (i = 0; i < linha; i++) {
    for (j = 0; j < coluna; j++) {
      fprintf(gravacao, "%d ", cornway[i][j]);
    }
    fprintf(gravacao, "\n");
  }
  fclose(gravacao);
}
