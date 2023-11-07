#ifndef PROJETO_H
#define PROJETO_H

//Vinícius de Castro Duarte - 24.123.073-9

struct Tarefa {
    int prioridade;
    char categoria[100];
    char descricao[300];
    char estado[30];
};

void limpa();
void ler(struct Tarefa *armazena);
void excluir_tarefa(struct Tarefa *tarefas, int *cont, int posicao);
void alterarTarefa(struct Tarefa *tarefas, int cont);
void filtrarTarefaPrioridade(struct Tarefa *tarefas, int cont);

#endif//PROJETO_H
