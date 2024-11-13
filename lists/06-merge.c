#include <stdio.h>
#include <stdlib.h>
#include <math.h>
// #include <time.h>

typedef struct node {
  struct node* ant;
  int num;
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

void add_final(Lista* lista, int num) {
  Node* novo = malloc(sizeof(Node));
  novo->ant = lista->ultimo;
  novo->num = num;
  novo->prox = NULL;
  lista->ultimo = novo;
  if(novo->ant) novo->ant->prox = novo;
  if(!lista->primeiro) lista->primeiro = novo;
  lista->qtd++;
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
    if(i < pivo) add_final(lista1, atual->num);
    else add_final(lista2, atual->num);
    atual = atual->prox;
  }

  lista1 = merge_sort(lista1);
  lista2 = merge_sort(lista2);

  // onde a ordenação acontece
  while(lista1->primeiro && lista2->primeiro) {
    if(lista1->primeiro->num < lista2->primeiro->num) {
      add_final(temp, lista1->primeiro->num);
      deleta_prim(lista1);
    } else {
      add_final(temp, lista2->primeiro->num);
      deleta_prim(lista2);
    }
  }
  // joga oque sobrou na nova lista. Um desses nem vai executar '-'
  while(lista1->primeiro) {
    add_final(temp, lista1->primeiro->num);
    deleta_prim(lista1);
  }
  while(lista2->primeiro) {
    add_final(temp, lista2->primeiro->num);
    deleta_prim(lista2);
  }

  return temp;
}

int main() {
  Lista* lista = nova_lista();
  
  for(int i = 0; i < 100000; i++) {
    add_final(lista, i);
  }

  Lista* ordenada = merge_sort(lista);
}