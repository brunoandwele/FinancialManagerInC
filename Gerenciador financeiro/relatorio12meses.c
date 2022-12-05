#include "filtrarCategoria.h"
#include "funcoesAuxiliares.h"
#include "transacoes.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

struct cadastroStruct {
  char sinal[3];
  char valor[15];
  char descricao[255];
  char dia[4];
  char mes[4];
  char ano[10];
  char categoria[64];
};

void criarRelatorio() {

  struct tm *data_atual;

  time_t segundos;

  time(&segundos);

  data_atual = localtime(&segundos);
  int mesAtual = (data_atual->tm_mon) + 1;
  int anoAtual = (data_atual->tm_year) + 1900;

  char mesesNum[12][3] = {"01", "02", "03", "04", "05", "06",
                          "07", "08", "09", "10", "11", "12"};
  char mesesNome[12][10] = {"Janeiro",  "Fevereiro", "Marco",    "Abril",
                            "Maio",     "Junho",     "Julho",    "Agosto",
                            "Setembro", "Outubro",   "Novembro", "Dezembro"};

  FILE *p_arquivoCadastroBin = fopen("arquivos/receitasTotais.bin", "rb");
  FILE *p_arquivoRelatorio12mesesTxt =
      fopen("arquivos/relatorio12meses.txt", "w");

  struct cadastroStruct cadastroRegistrado;

  while (!feof(p_arquivoCadastroBin)) {
    fread(&cadastroRegistrado, sizeof(struct cadastroStruct), 1,
          p_arquivoCadastroBin);
  }

  rewind(p_arquivoCadastroBin);

  int indiceMesInicial = mesAtual - 1;
  int anoRererencial = anoAtual;
  int jaVoltouJaneiro = 0;

  int mesReferencial = indiceMesInicial;

  for (int quantMes = 0; quantMes < 13; quantMes++) {

    if (mesReferencial == -1) {
      mesReferencial = 11;
      anoRererencial = anoRererencial - 1;
    }

    fprintf(p_arquivoRelatorio12mesesTxt, "--------------------------------\n");
    fprintf(p_arquivoRelatorio12mesesTxt, "%s %d\n\n",
            mesesNome[mesReferencial], anoRererencial);

    while (1) {

      fread(&cadastroRegistrado, sizeof(struct cadastroStruct), 1,
            p_arquivoCadastroBin);

      if (feof(p_arquivoCadastroBin)) {
        rewind(p_arquivoCadastroBin);
        break;
      } else {
        int mesEstaCorreto =
            strcmp(cadastroRegistrado.mes, mesesNum[mesReferencial]);

        int anoDoMes = atoi(cadastroRegistrado.ano);

        if (mesEstaCorreto == 0 && anoDoMes == anoRererencial) {
          fprintf(p_arquivoRelatorio12mesesTxt, "\nValor: %s%s",
                  cadastroRegistrado.sinal, cadastroRegistrado.valor);
          setbuf(stdin, NULL);
          fprintf(p_arquivoRelatorio12mesesTxt, "\nDescricao: %s",
                  cadastroRegistrado.descricao);
          setbuf(stdin, NULL);
          fprintf(p_arquivoRelatorio12mesesTxt, "\nDia: %s ",
                  cadastroRegistrado.dia);
          fprintf(p_arquivoRelatorio12mesesTxt, "Mes: %s ",
                  cadastroRegistrado.mes);
          fprintf(p_arquivoRelatorio12mesesTxt, "Ano: %s",
                  cadastroRegistrado.ano);
          setbuf(stdin, NULL);
          fprintf(p_arquivoRelatorio12mesesTxt, "\nCategoria: %s\n\n",
                  cadastroRegistrado.categoria);
          setbuf(stdin, NULL);
        }
      }
    }
    mesReferencial = mesReferencial - 1;
  }

  fprintf(p_arquivoRelatorio12mesesTxt, "--------------------------------\n\n");

  fclose(p_arquivoCadastroBin);
  fclose(p_arquivoRelatorio12mesesTxt);
}

void cadastrarReceita(void) {

  //verifica se arquivo esta vazio

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
    printf("Antes de iniciarmos, por gentiliza defina um saldo inicial: ");
    scanf("%lf", &receita_user);
    CadastroReceitaUser(receita_user);
  } else {
    receita_user = atof(receitaAntiga);

  }
  
  struct cadastroStruct novo_cadastro;
  printf("\nO que sera registrado?\n(0) Gasto\n(1) Receita\n");
  int gastoOuReceita;
  scanf("%d", &gastoOuReceita);

  printf("Digite as informacoes da receita ou gasto por gentileza:\n");
  printf("\nDigite o valor:");
  scanf("%s", novo_cadastro.valor);

  if (gastoOuReceita == 0) {
    novo_cadastro.sinal[0] = '-';
    novo_cadastro.sinal[1] = ' ';
    novo_cadastro.sinal[2] = '\0';
    receita_user -= atof(novo_cadastro.valor);
  } else {
    novo_cadastro.sinal[0] = '+';
    novo_cadastro.sinal[1] = ' ';
    novo_cadastro.sinal[2] = '\0';
    receita_user += atof(novo_cadastro.valor);
  }

  CadastroReceitaUser(receita_user);

  printf("Digite a descricao:");
  setbuf(stdin, NULL);
  scanf("%255[^\n]", novo_cadastro.descricao);
  setbuf(stdin, NULL);

  printf("Digite o data no formato dd mm aaaa:");
  scanf("%s %s %s", novo_cadastro.dia, novo_cadastro.mes, novo_cadastro.ano);

  printf(
      "Digite a categoria - (OBS: com letras minusculas e separe as palavras "
      "usando 'underline' -> '_' ):");
  setbuf(stdin, NULL);
  scanf("%64[^\n]", novo_cadastro.categoria);
  setbuf(stdin, NULL);

  cadastroCategoria(novo_cadastro);

  FILE *p_arquivoCadastroBin = fopen("arquivos/receitasTotais.bin", "ab");
  fwrite(&novo_cadastro, sizeof(struct cadastroStruct), 1,
         p_arquivoCadastroBin);
  fclose(p_arquivoCadastroBin);

  criarRelatorio();
}

void exibirRelatorio() {

  char letra;
  FILE *p_arquivoCadastro = fopen("arquivos/relatorio12meses.txt", "r");

  int arquivoEhVazio = verificarSeArquivoVazio(p_arquivoCadastro);

  if (arquivoEhVazio == 1) {
    printf("\n###############################################\n");
    printf("Arquivo de receitas esta vazio, por favor insira informacoes de "
           "receita!\n");
  } else {
    printf("\n###############################################\n");
    printf("\nRelatorio dos ultimos 12 meses: \n");
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
