#include "Projeto.h"
#include <stdio.h>
#include <string.h>

//Vinícius de Castro Duarte - 24.123.073-9

void limpa() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) { }
}


void ler(struct Tarefa *armazena) {
    printf("Prioridade: ");
    scanf("%d", &armazena->prioridade);
    limpa();
    printf("Descricao: ");
    scanf("%299[^\n]", armazena->descricao);
    limpa();
    printf("Categoria: ");
    scanf("%99[^\n]", armazena->categoria);
    limpa();
    printf("Estado:\n");
    printf("[1] Completo\n[2] Em andamento\n[3] Nao iniciado\n");
    int opcao_estado;
    scanf("%d", &opcao_estado);
    limpa();

    switch (opcao_estado) {
        case 1:
            strcpy(armazena->estado, "Completo");
            break;
        case 2:
            strcpy(armazena->estado, "Em andamento");
            break;
        case 3:
            strcpy(armazena->estado, "Nao iniciado");
            break;
        default:
            strcpy(armazena->estado, "Estado indefinido");
            break;
    }
}

void excluir_tarefa(struct Tarefa *tarefas, int *cont, int posicao) {
    if (posicao >= 1 && posicao <= *cont) {
        for (int i = posicao - 1; i < *cont - 1; i++) {
            tarefas[i] = tarefas[i + 1];
        }
        (*cont)--;
        printf("Tarefa deletada\n\n");
    }
}

void alterarTarefa(struct Tarefa *tarefas, int cont) {
    int numero_tarefa, opcao;
    printf("Escolha o número da tarefa que deseja alterar: ");
    scanf("%d", &numero_tarefa);
    limpa();

    if (numero_tarefa < 1 || numero_tarefa > cont) {
        printf("Numero de tarefa invalido.\n");
        return;
    }

    printf("Escolha o campo que deseja alterar:\n");
    printf("[1] Prioridade\n[2] Descrição\n[3] Categoria\n[4] Estado\n");
    printf("Digite o número correspondente ao campo: ");
    scanf("%d", &opcao);
    limpa();

    switch (opcao) {
        case 1:
            printf("Nova prioridade: ");
            scanf("%d", &tarefas[numero_tarefa - 1].prioridade);
            limpa();
            break;
        case 2:
            printf("Nova descrição: ");
            scanf("%299[^\n]", tarefas[numero_tarefa - 1].descricao);
            limpa();
            break;
        case 3:
            printf("Nova categoria: ");
            scanf("%99[^\n]", tarefas[numero_tarefa - 1].categoria);
            limpa();
            break;
        case 4:
            printf("Novo estado:\n");
            printf("[1] Completo\n[2] Em andamento\n[3] Nao iniciado\n");
            int opcao_estado;
            scanf("%d", &opcao_estado);
            limpa();

            switch (opcao_estado) {
                case 1:
                    strcpy(tarefas[numero_tarefa - 1].estado, "Completo");
                    break;
                case 2:
                    strcpy(tarefas[numero_tarefa - 1].estado, "Em andamento");
                    break;
                case 3:
                    strcpy(tarefas[numero_tarefa - 1].estado, "Nao iniciado");
                    break;
                default:
                    printf("Opção de estado inválida.\n");
                    break;
            }
            break;
        default:
            printf("Opção inválida.\n");
            break;
    }
    FILE *arquivo_binario = fopen("tarefas.txt", "wb");
    if (arquivo_binario) {
        fwrite(tarefas, sizeof(struct Tarefa), cont, arquivo_binario);
        fclose(arquivo_binario);
    }
  return;
}


void filtrarTarefaPrioridade(struct Tarefa *tarefas, int cont){
  int prioridade;
  int c = 0;
  printf("Digite a prioridade desejada: ");
  scanf("%d", &prioridade);
  printf("\n");
  limpa();
  printf("Tarefas encontradas:\n\n");
  for (int i = 0; i < cont; i++) {
      if (tarefas[i].prioridade == prioridade) {
          printf("Posicao da tarefa: %d\n", i + 1);
          printf("Prioridade: %d\n", tarefas[i].prioridade);
          printf("Categoria: %s\n", tarefas[i].categoria);
          printf("Descricao: %s\n", tarefas[i].descricao);
          printf("Estado: %s\n\n", tarefas[i].estado);
          c++;
      }
  }
  if(c == 0){
    printf("Nenhuma tarefa encontrada para a prioridade escolhida!\n\n");
  }
}

void filtrarTarefaEstado(struct Tarefa *tarefas, int cont){
  int estado;
  char estadoEscrito[30];
  printf("Digite o numero correspondente ao estado da tarefa\n");
  printf("[1] Completo\n[2] Em andamento\n[3] Nao iniciado\n");
  scanf("%d", &estado);
    if (estado < 1 || estado > 3) {
        printf("Opcao invalida!\n");
        return;
    } else if (estado == 1) {
        strcpy(estadoEscrito, "Completo");
    } else if (estado == 2) {
        strcpy(estadoEscrito, "Em andamento");
    } else if (estado == 3) {
        strcpy(estadoEscrito, "Nao iniciado");
    }
    printf("\n");
  limpa();
    int c = 0;
    printf("Tarefas encontradas:\n\n");
    for (int i = 0; i < cont; i++) {
      if (strcmp(tarefas[i].estado, estadoEscrito) == 0) {
        printf("Posicao da tarefa: %d\n", i + 1);
        printf("Prioridade: %d\n", tarefas[i].prioridade);
        printf("Categoria: %s\n", tarefas[i].categoria);
        printf("Descricao: %s\n", tarefas[i].descricao);
        printf("Estado: %s\n\n", tarefas[i].estado);
        c++;
        }
    }
    if(c == 0){
      printf("Nenhuma tarefa encontrada para a prioridade escolhida!\n\n");
  } 
}

void filtrarTarefaCategoria(struct Tarefa *tarefas, int cont) {
    char categoria_desejada[100];
    printf("Digite a categoria desejada: ");
    scanf("%99s", categoria_desejada);
    limpa();

    // Ordena as tarefas por prioridade crescente
    for (int i = 0; i < cont - 1; i++) {
        for (int j = 0; j < cont - i - 1; j++) {
            if (tarefas[j].prioridade > tarefas[j + 1].prioridade) {
                struct Tarefa temp = tarefas[j];
                tarefas[j] = tarefas[j + 1];
                tarefas[j + 1] = temp;
            }
        }
    }

    int c = 0;
    printf("Tarefas encontradas para a categoria '%s':\n\n", categoria_desejada);
    for (int i = 0; i < cont; i++) {
        if (strcmp(tarefas[i].categoria, categoria_desejada) == 0) {
            printf("Posição da tarefa: %d\n", i + 1);
            printf("Prioridade: %d\n", tarefas[i].prioridade);
            printf("Categoria: %s\n", tarefas[i].categoria);
            printf("Descrição: %s\n", tarefas[i].descricao);
            printf("Estado: %s\n\n", tarefas[i].estado);
            c++;
        }
    }

    if (c == 0) {
        printf("Nenhuma tarefa encontrada para a categoria escolhida!\n\n");
    }
}

void filtrarPorPrioridadeECategoria(struct Tarefa *tarefas, int cont) {
    int prioridade;
    char categoria_desejada[100];

    printf("Digite a prioridade desejada: ");
    scanf("%d", &prioridade);
    limpa();

    printf("Digite a categoria desejada: ");
    scanf("%99s", categoria_desejada);
    limpa();

    int c = 0;
    printf("Tarefas encontradas para a prioridade %d e categoria '%s':\n\n", prioridade, categoria_desejada);

    for (int i = 0; i < cont; i++) {
        if (tarefas[i].prioridade == prioridade && strcmp(tarefas[i].categoria, categoria_desejada) == 0) {
            printf("Posição da tarefa: %d\n", i + 1);
            printf("Prioridade: %d\n", tarefas[i].prioridade);
            printf("Categoria: %s\n", tarefas[i].categoria);
            printf("Descrição: %s\n", tarefas[i].descricao);
            printf("Estado: %s\n\n", tarefas[i].estado);
            c++;
        }
    }

    if (c == 0) {
        printf("Nenhuma tarefa encontrada para a prioridade e categoria escolhidas!\n\n");
    }
}

void exportarTarefasPorPrioridade(struct Tarefa *tarefas, int cont) {
    int prioridade_escolhida;

    printf("Digite a prioridade para exportar as tarefas: ");
    scanf("%d", &prioridade_escolhida);
    limpa();

    FILE *arquivo_export = fopen("tarefas_prioridade.txt", "w");
    if (arquivo_export == NULL) {
        printf("Erro ao criar o arquivo para exportar as tarefas.\n");
        return;
    }

    for (int i = 0; i < cont; i++) {
        if (tarefas[i].prioridade == prioridade_escolhida) {
            fprintf(arquivo_export, "Prioridade: %d\nCategoria: %s\nEstado: %s\nDescricao: %s\n\n", tarefas[i].prioridade, tarefas[i].categoria, tarefas[i].estado, tarefas[i].descricao);
        }
    }

    fclose(arquivo_export);
    printf("Tarefas da prioridade %d exportadas para o arquivo 'tarefas_prioridade.txt'.\n", prioridade_escolhida);
}
