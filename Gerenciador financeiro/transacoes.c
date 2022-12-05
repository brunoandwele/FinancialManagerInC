#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct cadastroTransacao {
  char destinatario[100];
  char valor[50];
  char descricao[255];
  char dia[4];
  char mes[4];
  char ano[10];
};

void CadastroReceitaUser(double receita_user) {
  FILE *p_CadastroReceitaUser = fopen("arquivos/receita_user.txt", "w");
  fprintf(p_CadastroReceitaUser, "%.2lf", receita_user);
  fclose(p_CadastroReceitaUser);
}

void ReceitaUser() {

  FILE *p_arquivoTransacoes = fopen("arquivos/receita_user.txt", "r");
  char *linha = calloc(255,1);;
  double receita_user;
  char vazio[]={'\0'};

  while (!feof(p_arquivoTransacoes)) {
    fscanf(p_arquivoTransacoes, "%s", linha);
    int arquivo_vazio = strcmp(linha, vazio);

    if (arquivo_vazio == 0) {
      printf("Antes de iniciarmos, por gentiliza defina um saldo inicial: ");
      scanf("%lf", &receita_user);
      fclose(p_arquivoTransacoes);
      CadastroReceitaUser(receita_user);
      printf("\nSaldo total para transferencias = R$ %.2lf\n", receita_user);
      break;
    } else {
      printf("\nSaldo total para transferencias = R$ %s\n", linha);
    }
  }
}

void Transacoes(void) {
  struct cadastroTransacao novo_cadastroTransacoes;

  printf("Digite o valor da transacao:");
  scanf("%s", novo_cadastroTransacoes.valor);

  printf("Digite a descricao da transacao:");
  setbuf(stdin, NULL);
  scanf("%64[^\n]", novo_cadastroTransacoes.descricao);
  setbuf(stdin, NULL);

  printf("Digite a data que foi feita a transacao:");

  printf("Digite a data (na formatacao dd mm yyyy):");
  scanf("%s %s %s", novo_cadastroTransacoes.dia, novo_cadastroTransacoes.mes,
        novo_cadastroTransacoes.ano);

  printf("\nDigite o destinatario da transacao:\n\n");
  printf("1)Para voce mesmo\n2)Para outra pessoa\nDigite aqui: ");
  scanf("%s", (novo_cadastroTransacoes.destinatario));

  char sinal;
  char escolha[] = "1";
  float receita_user;

  FILE *p_arquivoTransacoes = fopen("arquivos/receita_user.txt", "r");
  char linha[255];

  while (!feof(p_arquivoTransacoes)) {
    fscanf(p_arquivoTransacoes, "%s", linha);
    receita_user = atof(linha);
    break;
  }

  int ehverdade = strcmp(novo_cadastroTransacoes.destinatario, escolha);

  if (ehverdade == 0) {
    sinal = '+';
    receita_user += atof(novo_cadastroTransacoes.valor);
    CadastroReceitaUser(receita_user);
    FILE *p_arquivoTransacoes = fopen("arquivos/historico_transacoes.txt", "a");
    fprintf(p_arquivoTransacoes, "\nValor da transacao: %c %s", sinal,
            novo_cadastroTransacoes.valor);
    fprintf(p_arquivoTransacoes, "\nData: %s/%s/%s",
            novo_cadastroTransacoes.dia, novo_cadastroTransacoes.mes,
            novo_cadastroTransacoes.ano);
    fprintf(p_arquivoTransacoes, "\nDescricao: %s",
            novo_cadastroTransacoes.descricao);
    fprintf(p_arquivoTransacoes, "\nDestinatario: %s",
            novo_cadastroTransacoes.destinatario);
    fprintf(p_arquivoTransacoes, "\nSaldo Atual de Sua Conta: R$%.2lf\n",
            receita_user);
    fclose(p_arquivoTransacoes);
  } else {
    if (atof(novo_cadastroTransacoes.valor) > receita_user) {
      printf("Não foi possivel efetuar a trasacao, saldo insuficiente :(\n");
    } else {
      printf("\nDigite o nome do desnatario:");
      setbuf(stdin, NULL);
      scanf("%s[^\n]", novo_cadastroTransacoes.destinatario);
      setbuf(stdin, NULL);
      printf("\n");
      receita_user -= atof(novo_cadastroTransacoes.valor);
      CadastroReceitaUser(receita_user);
      sinal = '-';
      FILE *p_arquivoTransacoes =
          fopen("arquivos/historico_transacoes.txt", "a");
      fprintf(p_arquivoTransacoes, "\nValor da transacao: %c %s", sinal,
              novo_cadastroTransacoes.valor);
      fprintf(p_arquivoTransacoes, "\nData: %s/%s/%s",
              novo_cadastroTransacoes.dia, novo_cadastroTransacoes.mes,
              novo_cadastroTransacoes.ano);
      fprintf(p_arquivoTransacoes, "\nDescricao: %s",
              novo_cadastroTransacoes.descricao);
      fprintf(p_arquivoTransacoes, "\nDestinatario: %s",
              novo_cadastroTransacoes.destinatario);
      fprintf(p_arquivoTransacoes, "\nSaudo Atual de Sua Conta: R$%.2lf\n",
              receita_user);
      fclose(p_arquivoTransacoes);
    }
  }
}

void exibirTransacoes(void) {

  char letra;
  FILE *p_arquivoCadastro = fopen("arquivos/historico_transacoes.txt", "r");
  printf("\n###############################################\n");
  printf("\nRelatorio das Transacoes: \n");
  // enquanto não chegar ao final do arquivo
  while (!feof(p_arquivoCadastro)) {
    letra = fgetc(p_arquivoCadastro);
    if (letra != '\n') {
      printf("%c", letra);
    } else {
      printf("\n");
    }
  }
  printf("\n###############################################\n");
}

void menuTransacoes(void) {

  printf("Ola, seja bem-vindo a aba de transacoes:\n");

  int escolhaFoiSucesso = 0;

  while (escolhaFoiSucesso != 1) {

    int escolhaUsuario;
    printf("\nO que deseja fazer?\n(1) Realizar uma transacao para voce mesmo "
           "ou outra pessoa\n(2) Mostrar relatorio das ultimas transacoes\n");
    printf("Digite aqui sua escolha: ");
    scanf("%d", &escolhaUsuario);

    switch (escolhaUsuario) {
    case 1:
      printf("\nOpcao escolhida: (1) Realizar uma transacao para voce mesmo ou "
             "outra pessoa\n\n");
      Transacoes();
      escolhaFoiSucesso = 1;
      break;

    case 2:
      printf("\nOpcao escolhida: (2) Mostrar relatorio das ultimas "
             "transacoes\n\n");
      exibirTransacoes();
      escolhaFoiSucesso = 1;

      break;

    default:
      printf("Ops... Escolha não encontrada! Por favor digite um número válido "
             ":)\n\n");
    }
  }
}