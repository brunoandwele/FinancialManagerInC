//Final project for CC2632 - DESENVOLVIMENTO DE ALGORITMOS -> date: 22 - november - 2022
//made by: 
//ANA BEATRIZ TAVARES MALHEIRO - github.com/AnaBeatrizTavaresMalheiro
//&&
//BRUNO ANDWELE ALVES ANTUNES - github.com/brunoandwele

#include "filtrarCategoria.h"
#include "poupanca.h"
#include "relatorio12meses.h"
#include "transacoes.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
  int sair = 0;
  printf("\nOla seja bem-vindo!\n\n");
  
  while (sair == 0) {
      FILE *p_arquivoReceitaUser = fopen("arquivos/receita_user.txt", "r");
  char *receitaAntiga = calloc(15,1);
  double receita_user;
  while (!feof(p_arquivoReceitaUser)) {
    fscanf(p_arquivoReceitaUser, "%s", receitaAntiga);
    break;
  }
  fclose(p_arquivoReceitaUser);
  char vazio[]={'\0'};
  int arquivo_vazio = strcmp(receitaAntiga, vazio);
  if (arquivo_vazio == 0) {
    printf("\nMenu:\n\n");
    printf("Saldo atual: (sem registro)\n\n");
  } else {
    receita_user = atof(receitaAntiga);
    printf("\nMenu:\n\n");
    printf("Saldo atual: R$ %.2lf\n\n", receita_user);
  }
    int num_escolhido;

    
    printf("\
(1) Cadastrar gasto ou receita\n\
(2) Exibir Relatorio dos ultimos 12 meses\n\
(3) Exibir Relatorio Filtrado por Categorias\n\
(4) Aba de transferencias\n\
(5) Simulacao de rendimento minimo da poupanca\n\
(6) Sair\n\n\
Digite o numero que deseja efetuar:");

    scanf("%d", &num_escolhido);
    switch (num_escolhido) {
    case 1:
      printf("\nOpcao Escolhida: (1) Cadastrar gasto ou receita\n\n");
      cadastrarReceita();
      break;

    case 2:
      printf("\nOpcao Escolhida: (2) Exibir Relatorio dos ultimos 12 meses\n\n");
      exibirRelatorio();
      break;

    case 3:
      printf(
          "\nOpcao Escolhida: (3) Exibir Relatorio Filtrado por Categorias\n\n");
      RelatorioFiltrado();
      break;

    case 4:
      printf("\nOpcao Escolhida: (4) Aba de transferencias\n\n");
      ReceitaUser();
      menuTransacoes();
      break;

    case 5:
      printf(
          "\nOpcao Escolhida: (5) Simulacao de rendimento minimo da poupanca\n\n");
      mostrarRendimentoMinPoupanca();
      break;

    case 6:
      printf("\nOpcao Escolhida: (6) Sair\n\n");
      printf("\nAte a próxima :)");
      sair = 1;
      break;

    default:
      printf(
          "\nOps... Escolha nao encontrada! Por favor digite um numero valido "
          ":)\n");
    }
  }
  return 0;
}