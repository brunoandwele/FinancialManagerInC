#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *maiusculo(char *palavra) {
  char *palavra_nova = malloc(sizeof(char)*255);

  for (int i = 0; i < 255; i++) {
    if (*(palavra + i) == '\0') {
      break;
    } else {
      *(palavra_nova + i) = toupper(*(palavra + i));
    }
  }

  return (palavra_nova);
}

int verificarSeArquivoVazio(FILE *p_arquivo) {

  char linha[255];
  double receita_user;
  char vazio[] = "\0";

  while (!feof(p_arquivo)) {
    fscanf(p_arquivo, "%s", linha);
    int arquivo_vazio = strcmp(linha, vazio);

    if (arquivo_vazio == 0) {
      return 1;
    } else {
      return 0;
    }
  }
  return 1;
}