#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define peso_de_prioridade 10
#define tam_fila 4

typedef struct node {
  struct node* ant;
  int num;
  char descricao[20];
  struct node* prox;
} Node;

typedef struct lista {
  Node* primeiro;
  Node* ultimo;
  int qtd;
} Lista;

Lista* nova_lista() {
  Lista* lista = malloc(sizeof(Lista));
  lista->primeiro = NULL;
  lista->ultimo = NULL;
  lista->qtd = 0;
  return lista;
}

void printa_lista(Lista* lista) {
  Node* stop = NULL;
  if(lista->primeiro == NULL) {
    printf("<Lista vazia>\n");
    return;
  }
  printf("\n   { prim: %p, ult: %p, qtd: %d }\n", lista->primeiro, lista->ultimo, lista->qtd);
  printf("   Endereco \t| Anterior \t| Numero \t| Proximo\n");
  printf("   -------------+---------------+---------------+---------\n");
  

  Node* atual = lista->primeiro;
  do {
    printf("   %p \t| %p \t| %d \t\t| %p\n", atual, atual->ant, atual->num, atual->prox);
    atual = atual->prox;
  } while(atual != stop);
}


void deleta_prim(Lista* lista) {
  if(!lista->primeiro) {
    printf("A lista esta vazia.\n");
    return;
  }
  Node* aux = lista->primeiro;
  if(lista->primeiro) lista->primeiro = lista->primeiro->prox;
  if(lista->primeiro) lista->primeiro->ant = NULL;
  free(aux);
  lista->qtd--;
}

void add_final(Lista* lista, int num, char descricao[20]) {
  Node* novo = malloc(sizeof(Node));
  novo->ant = lista->ultimo;
  novo->num = num;
  novo->prox = NULL;
  strcpy(novo->descricao, descricao);
  lista->ultimo = novo;
  if(novo->ant) novo->ant->prox = novo;
  if(!lista->primeiro) lista->primeiro = novo;
  lista->qtd++;
}

void del_rec(Node* atual) {
  if(atual) {
    del_rec(atual->prox);
    free(atual);
  }
}

Lista* merge_sort(Lista* lista) {
  if(lista->qtd == 1) {
    return lista;
  }

  Lista* temp = nova_lista();
  Lista* lista1 = nova_lista();
  Lista* lista2 = nova_lista();
  
  // divide a lista em 2 listas menores.
  // sim, aloca espaço extra para ambas; esse é o ruim do merge_sort.
  int pivo = floor((lista->qtd)/2);
  Node* atual = lista->primeiro;
  for(int i = 0; i < lista->qtd; i++) {
    if(i < pivo) add_final(lista1, atual->num, atual->descricao);
    else add_final(lista2, atual->num, atual->descricao);
    atual = atual->prox;
  }

  lista1 = merge_sort(lista1);
  lista2 = merge_sort(lista2);

  // onde a ordenação acontece
  while(lista1->primeiro && lista2->primeiro) {
    if(lista1->primeiro->num < lista2->primeiro->num) {
      add_final(temp, lista1->primeiro->num, lista1->primeiro->descricao);
      deleta_prim(lista1);
    } else {
      add_final(temp, lista2->primeiro->num, lista2->primeiro->descricao);
      deleta_prim(lista2);
    }
  }
  // joga oque sobrou na nova lista. Um desses nem vai executar '-'
  while(lista1->primeiro) {
    add_final(temp, lista1->primeiro->num, lista1->primeiro->descricao);
    deleta_prim(lista1);
  }
  while(lista2->primeiro) {
    add_final(temp, lista2->primeiro->num, lista2->primeiro->descricao);
    deleta_prim(lista2);
  }

  del_rec(lista1->primeiro); free(lista1);
  del_rec(lista2->primeiro); free(lista2);

  return temp;
}

// tasks precisa estar ordenado
void completar(Lista* tasks, Lista* doing) {
  del_rec(doing->primeiro);
  doing->primeiro = NULL;
  doing->ultimo = NULL;
  doing->qtd = 0;
  Node* atual = tasks->ultimo;
  while(atual && doing->qtd < tam_fila) {
    add_final(doing, atual->num, atual->descricao);
    atual = atual->ant;
  }
}

void deleta_num(Lista* lista, int num) {
  Node* atual = lista->primeiro;
  if(!atual) {
    printf("Erro! O numero nao existe.\n");
  }
  Node* stop = NULL;
  while(atual->prox != stop && atual->num != num) atual = atual->prox;
  if(atual == stop) {
    printf("Erro! O numero nao existe.\n");
  }
  // atualiza os ponteiros de partida
  if(atual == lista->primeiro) {
    lista->primeiro = atual->prox;
  }
  if(atual == lista->ultimo) {
    lista->ultimo = atual->ant;
  }
  // atualiza e remove o item da lista
  if(atual->ant) {
    atual->ant->prox = atual->prox;
  }
  if(atual->prox) {
    atual->prox->ant = atual->ant;
  }
  free(atual);
  lista->qtd--;
}

int main() {
  int id = 0;
  Lista* tasks = nova_lista();
  Lista* doing = nova_lista();

  int op;
  do {
    printf("\n<TAREFAS>\n");
    printa_lista(tasks);

    printf("\n<FILA PRIORITARIA>\n");
    printa_lista(doing);

    printf("\nEscolha a opcao: ");
    printf("\n0- Sair");
    printf("\n1- Adicionar Tarefa");
    printf("\n2- Resolver Proxima Tarefa");
    printf("\n > ");
    scanf("%d", &op);

    switch(op) {
      case 0: { printf("\nsaindo..."); break;}
      case 1: {
        char descricao[20] = "";
        int prioridade;
        printf("\nDescreva a tarefa: ");
        fflush(stdin);
        gets(descricao);
        printf("\nQual a prioridade? (> para antes): ");
        scanf("%d", &prioridade);

        add_final(tasks, (prioridade * peso_de_prioridade) + id++, descricao);
        Lista* prioridades = merge_sort(tasks);
        completar(prioridades, doing);
        break;
      }
      case 2: {
        int id = doing->primeiro->num;
        Lista* prioridades = merge_sort(tasks);
        deleta_num(tasks, id);
        deleta_num(doing, id);

        break;
      }
    }
  } while(op != 0);
}