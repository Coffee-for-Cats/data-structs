#include <stdio.h>
#include <stdlib.h>

typedef struct node {
  struct node* ant;
  int num;
  struct node* prox;
} Node;

typedef struct lista {
  Node* primeiro;
  int size;
  Node* ultimo;
} Lista;

void add_inicio(Lista* lista, int num) {
  Node* novo = malloc(sizeof(Node));
  novo->ant = NULL;
  novo->num = num;
  novo->prox = lista->primeiro;
  lista->primeiro = novo;
  if(lista->size == 0) lista->ultimo = novo;
  lista->size++;
}

void add_final(Lista* lista, int num) {
  Node* novo = malloc(sizeof(Node));
  novo->ant = lista->ultimo;
  novo->num = num;
  novo->prox = NULL;
  lista->ultimo->prox = novo;
  lista->ultimo = novo;
  if(lista->size == 0) {
    lista->primeiro = novo;
  }
  lista->size++;
}

void add_depois_de(Lista* lista, int num, int dps_de) {  
  Node* atual = lista->primeiro;
  if(!atual) {
    add_inicio(lista, num);
    return;
  }
  while(atual->prox && atual->num != dps_de) atual = atual->prox;
  if(atual->prox == NULL) {
    printf("\nErro! O numero dps_de nao existe.");
    return;
  }
  Node* novo = malloc(sizeof(Node));
  novo->num = num;
  // não me pergunte
  novo->prox = atual->prox;
  novo->ant = atual;
  atual->prox->ant = novo;
  atual->prox = novo;
}

void remove_indice(Lista* lista, int index) {
  Node* atual = lista->primeiro;

  for(int i = 0; i < index; i++) {
    if(!atual) {
      printf("\nO indice %d nao existe!", index);
      return;
    }
    atual = atual->prox;
  }

  if(atual->ant)
    atual->ant->prox = atual->prox;

  if(atual->prox)
    atual->prox->ant = atual->ant;

  // atualiza os ponteiros de inicio e fim da lista
  if(index == 0) {
    atual->prox->ant == NULL;
    lista->primeiro = atual->prox;
  }
  if(index == lista->size - 1) {
    lista->ultimo = atual->ant;
  }

  lista->size--;
  free(atual);
}

Lista* nova_lista() {
  Lista* lista = malloc(sizeof(Lista));
  lista->primeiro = NULL;
  lista->size = 0;
  lista->ultimo = NULL;
  return lista;
}

void printa_lista(Lista* lista) {
  printf("\n{ Tam: %d, prim: %p, ult: %p }", lista->size, lista->primeiro, lista->ultimo);
  printf("\nindice \t| Ant: \t\t| Numero: \t| Prox:");
  printf("\n==================================================\n");
  int i = 0;
  for(Node* atual = (*lista).primeiro; atual != NULL; atual = atual->prox) {
    printf("%d\t| %p \t| %d \t\t| %p\n", i++, atual->ant, atual->num, atual->prox);
  }
}

int main() {
  int num;
  Lista* lista = nova_lista();
  add_inicio(lista, 4);
  add_inicio(lista, 3);
  add_final(lista, 7);
  add_final(lista, 14);
  add_depois_de(lista, 5, 7);
  printa_lista(lista);
  remove_indice(lista, 4);
  printa_lista(lista);
}