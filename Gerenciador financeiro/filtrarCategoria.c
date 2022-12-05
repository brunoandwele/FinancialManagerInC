#include "funcoesAuxiliares.h"
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct cadastroStruct {
  char sinal[3];
  char valor[15];
  char descricao[255];
  char dia[4];
  char mes[4];
  char ano[10];
  char categoria[64];
};

void cadastroCategoria(struct cadastroStruct cadastro) {

  char categoria[255];
  int controle = 0;
  FILE *p_Cadastro_Categoria =
      fopen("arquivos/categorias_cadastradas.txt", "r");
  // enquanto não chegar ao final do arquivo

  while (!feof(p_Cadastro_Categoria)) {
    fscanf(p_Cadastro_Categoria, "%s", categoria);
    int categoria_cadastrada = strcmp(cadastro.categoria, categoria);

    if (categoria_cadastrada == 0) {
      controle = 1;
    } else {
      continue;
    }
  }

  if (controle == 1) {
    fclose(p_Cadastro_Categoria);
    return;
  } else {
    FILE *p_Cadastro_Categoria =
        fopen("arquivos/categorias_cadastradas.txt", "a");
    fprintf(p_Cadastro_Categoria, "\n%s", cadastro.categoria);
    fclose(p_Cadastro_Categoria);
  }
}

void exibirRelatorioFiltrado() {
  char letra;

  FILE *p_arquivoCadastro = fopen("arquivos/relatorio_por_categoria.txt", "r");

  int arquivoEhVazio = verificarSeArquivoVazio(p_arquivoCadastro);
  printf("\n###############################################\n");
  if (arquivoEhVazio == 1) {
    printf("Arquivo de receitas esta vazio, por favor insira informacoes de "
           "receita!\n");
  } else {
    printf("\nRelatorio do ultimo mes filtrado por categoria: \n");
    // enquanto não chegar ao final do arquivo
    while (!feof(p_arquivoCadastro)) {
      letra = fgetc(p_arquivoCadastro);

      if (letra != '\n') {
        printf("%c", letra);
      } else {
        printf("\n");
      }
    }
  }
  printf("\n###############################################\n");
}

void RelatorioFiltrado() {

  struct tm *data_atual;

  time_t segundos;

  time(&segundos);

  data_atual = localtime(&segundos);
  int mesAtual = (data_atual->tm_mon) + 1;
  int anoAtual = (data_atual->tm_year) + 1900;
  
  char linha[255];
  FILE *p_arquivoCategoria = fopen("arquivos/categorias_cadastradas.txt", "r");
  FILE *p_arquivoCadastroBin = fopen("arquivos/receitasTotais.bin", "r");
  FILE *p_arquivoRelatorioFiltrado =
      fopen("arquivos/relatorio_por_categoria.txt", "w");

  struct cadastroStruct cadastroRegistrado;


  while (!feof(p_arquivoCategoria)) {

    fscanf(p_arquivoCategoria, "%s", linha);
    fprintf(p_arquivoRelatorioFiltrado, "--------------------------------\n");
    fprintf(p_arquivoRelatorioFiltrado, "Catergoria: %s\n\n", linha);

    while (1) {
      fread(&cadastroRegistrado, sizeof(struct cadastroStruct), 1,
            p_arquivoCadastroBin);

      if (feof(p_arquivoCadastroBin)) {
        rewind(p_arquivoCadastroBin);
        break;

      } else {

        if (atoi(cadastroRegistrado.mes) == mesAtual && atoi(cadastroRegistrado.ano) == anoAtual) {

          int comparacaoCategoria = strcmp(linha, cadastroRegistrado.categoria);

          if (comparacaoCategoria == 0) {
            fprintf(p_arquivoRelatorioFiltrado, "Valor: %s%s\n",cadastroRegistrado.sinal,
                    cadastroRegistrado.valor);
            fprintf(p_arquivoRelatorioFiltrado, "Descricao: %s\n",
                    cadastroRegistrado.descricao);
            fprintf(p_arquivoRelatorioFiltrado, "Dia: %s\n",
                    cadastroRegistrado.dia);
            fprintf(p_arquivoRelatorioFiltrado, "Mes: %s\n",
                    cadastroRegistrado.mes);
            fprintf(p_arquivoRelatorioFiltrado, "Ano: %s\n\n",
                    cadastroRegistrado.ano);
          }
        }
      }
    }
  }

  fprintf(p_arquivoRelatorioFiltrado, "\n");
  fclose(p_arquivoCategoria);
  fclose(p_arquivoCadastroBin);
  fclose(p_arquivoRelatorioFiltrado);
  exibirRelatorioFiltrado();
}
