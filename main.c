#include "Projeto.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Vinícius de Castro Duarte - 24.123.073-9

int main() {
  struct Tarefa t[100];
  FILE *arquivo_binario = fopen("tarefas.txt", "rb");
  int cont = 0;
  if (arquivo_binario) {
    while (fread(&t[cont], sizeof(struct Tarefa), 1, arquivo_binario) == 1) {
      cont++;
    }
    fclose(arquivo_binario);
  }

  int posicao = 0;

  while (1) {
    printf(" 1 - Criar\n");
    printf(" 2 - Excluir\n");
    printf(" 3 - Listar\n");
    printf(" 4 - Editar\n");
    printf(" 5 - Filtros\n");
    printf(" 6 - Exportar\n");
    printf(" 7 - Encerrar\n");
    printf("Escreva apenas o numero da opcao que deseja: ");
    char *p, s_opcao[100];
    char *p_posicao, s_posicao[100];
    int opcao;
    fgets(s_opcao, sizeof(s_opcao), stdin);
    opcao = strtol(s_opcao, &p, 10);

    if (opcao == 1) {
      ler(&t[cont]);
      printf("Tarefa criada!\n\n");
      cont++;
    } else if (opcao == 2) {
      printf("Digite o numero da tarefa que deseja excluir: ");
      fgets(s_posicao, sizeof(s_posicao), stdin);
      posicao = strtol(s_posicao, &p_posicao, 10);
      if (p_posicao == s_posicao || *p_posicao != '\n') {
        printf("Nao foi possivel, tente novamente!\n\n");
      } else {
        excluir_tarefa(t, &cont, posicao);
      }
    } else if (opcao == 3) {
      printf("Lista:\n\n");
      for (int x = 0; x < cont; x++) {
        printf("Posicao da tarefa: %d\n", x + 1);
        printf("Prioridade: %d\n", t[x].prioridade);
        printf("Categoria: %s\n", t[x].categoria);
        printf("Descricao: %s\n", t[x].descricao);
        printf("Estado: %s\n\n", t[x].estado);
      }

    }else if(opcao == 4){
      alterarTarefa(t, cont);
    } else if(opcao == 5){
      printf("Escolha dentre os filtros abaixo o desejado:\n\n");
      printf("1 - Categoria\n2 - Prioridade\n3 - Estado\n4 - Prioridade e Categoria\n");
      int opcaoFiltro;
      scanf("%d", &opcaoFiltro);
      if(opcaoFiltro == 1){
        filtrarTarefaCategoria(t, cont);
      } else if(opcaoFiltro == 2){
        filtrarTarefaPrioridade(t, cont);
      } else if(opcaoFiltro == 3){
        filtrarTarefaEstado(t, cont);
      } else if(opcaoFiltro == 4){
        filtrarPorPrioridadeECategoria(t, cont);
      }
    } else if(opcao == 6){
      exportarTarefasPorPrioridade(t, cont);
    } else if (opcao == 7) {
      arquivo_binario = fopen("tarefas.txt", "wb");
      if (arquivo_binario) {
        fwrite(t, sizeof(struct Tarefa), cont, arquivo_binario);
        fclose(arquivo_binario);
      }
      printf("Ate logo\n");
      break;
    } else {
      printf("Por favor, digite um valor entre 1 - 4.\n");
    }
  }

  return 0;
}
