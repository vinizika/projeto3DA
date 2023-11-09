#include "Projeto.h" // Inclui o arquivo de cabeçalho que contém as definições de estrutura e funções
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Vinícius de Castro Duarte - 24.123.073-9

int main() {
  struct Tarefa t[100]; // Declaração de um array de estruturas Tarefa para armazenar as tarefas
  FILE *arquivo_binario = fopen("tarefas.txt", "rb"); // Abre o arquivo no modo de leitura binária
  int cont = 0; // Inicializa um contador para o número de tarefas no arquivo

  // Verifica se o arquivo foi aberto corretamente
  if (arquivo_binario) {
    // Lê as tarefas do arquivo e armazena no array até o final do arquivo
    while (fread(&t[cont], sizeof(struct Tarefa), 1, arquivo_binario) == 1) {
      cont++;
    }
    fclose(arquivo_binario); // Fecha o arquivo após a leitura
  }

  int posicao = 0; // Inicializa a variável para a posição da tarefa

  // Loop principal para apresentar o menu e interagir com o usuário
  while (1) {
    printf(" [1] - Criar\n");
    printf(" [2] - Excluir\n");
    printf(" [3] - Listar\n");
    printf(" [4] - Editar\n");
    printf(" [5] - Filtros\n");
    printf(" [6] - Exportar\n");
    printf(" [7] - Encerrar\n");
    printf("Escreva apenas o numero da opcao que deseja: ");
    char *p, s_opcao[100];
    char *p_posicao, s_posicao[100];
    int opcao;
    fgets(s_opcao, sizeof(s_opcao), stdin);
    opcao = strtol(s_opcao, &p, 10);

    if (opcao == 1) {
      ler(&t[cont]); // Chama a função para criar uma nova tarefa e a armazena no array
      printf("Tarefa criada!\n\n");
      cont++; // Incrementa o contador de tarefas
    } else if (opcao == 2) {
      printf("Digite o numero da tarefa que deseja excluir: ");
      fgets(s_posicao, sizeof(s_posicao), stdin);
      posicao = strtol(s_posicao, &p_posicao, 10);
      if (p_posicao == s_posicao || *p_posicao != '\n') {
        printf("Nao foi possivel, tente novamente!\n\n");
      } else {
        excluir_tarefa(t, &cont, posicao); // Chama a função para excluir a tarefa desejada do array
      }
    } else if (opcao == 3) {
      // Mostra a lista de todas as tarefas armazenadas no array
      printf("Lista:\n\n");
      for (int x = 0; x < cont; x++) {
        printf("Posicao da tarefa: %d\n", x + 1);
        printf("Prioridade: %d\n", t[x].prioridade);
        printf("Categoria: %s\n", t[x].categoria);
        printf("Descricao: %s\n", t[x].descricao);
        printf("Estado: %s\n\n", t[x].estado);
      }
    } else if (opcao == 4) {
      alterarTarefa(t, cont); // Chama a função para editar uma tarefa específica no array
    } else if (opcao == 5) {
      // Apresenta opções de filtros para as tarefas
      printf("Escolha dentre os filtros abaixo o desejado:\n\n");
      printf("1 - Categoria\n2 - Prioridade\n3 - Estado\n4 - Prioridade e Categoria\n");
      int opcaoFiltro;
      scanf("%d", &opcaoFiltro);
      if (opcaoFiltro == 1) {
        filtrarTarefaCategoria(t, cont); // Chama a função para filtrar tarefas por categoria
      } else if (opcaoFiltro == 2) {
        filtrarTarefaPrioridade(t, cont); // Chama a função para filtrar tarefas por prioridade
      } else if (opcaoFiltro == 3) {
        filtrarTarefaEstado(t, cont); // Chama a função para filtrar tarefas por estado
      } else if (opcaoFiltro == 4) {
        filtrarPorPrioridadeECategoria(t, cont); // Chama a função para filtrar tarefas por prioridade e categoria
      }
    } else if (opcao == 6) {
      // Opções para exportar tarefas para um arquivo
      printf("Escolha o modo de exportar:\n\n");
      printf("1 - Prioridade\n2 - Categoria\n3 - Prioridade e Categoria\n");
      int opcaoExportar;
      scanf("%d", &opcaoExportar);
      if (opcaoExportar == 1) {
        exportarTarefasPorPrioridade(t, cont); // Chama a função para exportar tarefas por prioridade
      } else if (opcaoExportar == 2) {
        exportarTarefasPorCategoria(t, cont); // Chama a função para exportar tarefas por categoria
      } else if (opcaoExportar == 3) {
        exportarTarefasPorCategoriaPrioridade(t, cont); // Chama a função para exportar tarefas por categoria e prioridade
      } else {
        printf("Digite uma opcao entre 1 e 3!\n\n");
      }
    } else if (opcao == 7) {
      // Salva as tarefas no arquivo binário e encerra o programa
      arquivo_binario = fopen("tarefas.txt", "wb");
      if (arquivo_binario) {
        fwrite(t, sizeof(struct Tarefa), cont, arquivo_binario);
        fclose(arquivo_binario);
      }
      printf("Ate logo\n");
      break; // Sai do loop para encerrar o programa
    } else {
      printf("Por favor, digite um valor entre 1 - 7.\n");
    }
 
