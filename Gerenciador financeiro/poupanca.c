#include <stdio.h>
#include <time.h>

void mostrarRendimentoMinPoupanca(void) {
    printf("###############################################\n");

  printf("\nAqui, iremos mostrar qual sera o rendimento minimo da poupanca a partir de hoje ate "
         "uma data de retirada! Para os calculos, o rendimento sera de 0.5 por "
         "cento ao mes!\n\n");

  // ponteiro para struct que armazena data
  struct tm *data_atual;

  time_t segundos;

  time(&segundos);

  data_atual = localtime(&segundos);
  int diaAtual = (data_atual->tm_mday);
  int mesAtual = (data_atual->tm_mon) + 1;
  int anoAtual = (data_atual->tm_year) + 1900;

  double dinheiroGuardado;
  printf("\nQual o valor do dinheiro que sera guardado na poupanca?\n");
  printf("Digite o valor aqui: ");
  scanf("%lf", &dinheiroGuardado);

  printf("Informe a data que deseja fazer a retirada do dinheiro: \n\n");

  printf("Escolha o dia: \n");
  int diaEscolhido;
  scanf("%d", &diaEscolhido);

  printf("\n\nEscolha o mes:\n");
  printf("01) Janeiro\n");
  printf("02) Fevereiro\n");
  printf("03) Marco\n");
  printf("04) Abril\n");
  printf("05) Maio\n");
  printf("06) Junho\n");
  printf("07) Julho\n");
  printf("08) Agosto\n");
  printf("09) Setembro\n");
  printf("10) Outubro\n");
  printf("11) Novembro\n");
  printf("12) Dezembro\n\n");
  int mesEscolhido;
  printf("Digite aqui: ");
  scanf("%d", &mesEscolhido);

  printf("\n\nEscolha o ano -> (digite na formatacao 'aaaa') : ");
  int anoEscolhido;
  scanf("%d", &anoEscolhido);

  int diferencaAnos = anoEscolhido - anoAtual;
  int diferencaMes = mesEscolhido - mesAtual;
  int diferencaDia = diaEscolhido - diaAtual;
  int mesesTotais = 0;

  if (diferencaDia >= 0) {
    mesesTotais = 0;
  } else {
    mesesTotais = -1;
  }

  if (diferencaAnos >= 0) {
    mesesTotais += (diferencaAnos * 12 + diferencaMes);
  } else {
    if (diferencaMes >= 0) {
      mesesTotais += diferencaMes;
    }
  }

  double jurosTotais = 1;

  for (int meses = 0; meses < mesesTotais; meses++) {
    jurosTotais = jurosTotais * 1.0005;
  }

  double valorRendido = jurosTotais * dinheiroGuardado;

  printf("\n\n#######################################################\n");
  printf("Data de Inicio: %d / %d / %d.\n", diaAtual, mesAtual, anoAtual);
  printf("Data da retirada: %d / %d / %d.\n", diaEscolhido, mesEscolhido,
         anoEscolhido);
  printf("O dinheiro sera guardado por %d mes(es) com rendimento de 0.5 por "
         "cento ao mes.\n\n",
         mesesTotais);
  printf("Valor inicial: R$ %.2lf. \n", dinheiroGuardado);
  printf("Valor total acumulado: R$ %.2lf.\n", valorRendido);
  printf("Havera um rendimento minimo total de : R$ %.2lf.\n",
         (valorRendido - dinheiroGuardado));
  printf("#######################################################\n\n");
}