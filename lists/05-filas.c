#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
}

void deleta_prim(Lista* lista, int* count) {
  if(!lista->primeiro) {
    printf("A lista esta vazia.\n");
    return;
  }
  Node* aux = lista->primeiro;
  if(lista->primeiro) lista->primeiro = lista->primeiro->prox;
  if(lista->primeiro) lista->primeiro->ant = NULL;
  free(aux);
  lista->qtd--;
  count++;
}

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
  printf("\n   { prim: %p, ult: %p }\n", lista->primeiro, lista->ultimo);
  printf("   Endereco \t| Anterior \t| Numero \t| Proximo\n");
  printf("   -------------+---------------+---------------+---------\n");
  

  Node* atual = lista->primeiro;
  do {
    printf("   %p \t| %p \t| %d \t\t| %p\n", atual, atual->ant, atual->num, atual->prox);
    atual = atual->prox;
  } while(atual != stop);
}

void main() {
  Lista* fila1l = nova_lista();
  Lista* fila2l = nova_lista();
  Lista* fila3l = nova_lista();
  Lista* fila4l = nova_lista();
  Lista* fila1o = nova_lista();
  Lista* fila2o = nova_lista();
  Lista* fila3o = nova_lista();
  Lista* fila4o = nova_lista();

  static int id = 0;
  static int count = 0;
  
  char cmd[20];
  do {
    printf("Fila 1 Leste:\n"); printa_lista(fila1l);
    printf("Fila 2 Leste:\n"); printa_lista(fila2l);
    printf("Fila 3 Leste:\n"); printa_lista(fila3l);
    printf("Fila 4 Leste:\n"); printa_lista(fila4l);
    printf("Fila 1 Oeste:\n"); printa_lista(fila1o);
    printf("Fila 2 Oeste:\n"); printa_lista(fila2o);
    printf("Fila 3 Oeste:\n"); printa_lista(fila3o);
    printf("Fila 4 Oeste:\n"); printa_lista(fila4o);

    printf("\n Pessoas que ja entraram: %d \n", count);
    printf("\n Leste / Oeste");
    printf("\n L1 %02d / %02d", fila1l->qtd, fila1o->qtd);
    printf("\n L2 %02d / %02d", fila2l->qtd, fila2o->qtd);
    printf("\n L3 %02d / %02d", fila3l->qtd, fila3o->qtd);
    printf("\n L4 %02d / %02d", fila4l->qtd, fila4o->qtd);
    printf("\n");
    printf("\nEscreva seu comando em 3 caracteres, nessa ordem: ");
    printf("\n[a/r] - adicionar/remover");
    printf("\n[1-4] - filas");
    printf("\n[l/o] - leste/oeste");
    printf("\nOu digite 'sair' para sair");
    printf("\n");
    gets(cmd);

    Lista* selecionada = NULL;
    switch(cmd[1]) { // char com o numero da lista.
      case '1': {
        if(cmd[2] == 'l') selecionada = fila1l;
        else if(cmd[2] == 'o') selecionada = fila1o;
        else {printf("\nInput mal formatado"); }
        break;
      }
      case '2': {
        if(cmd[2] == 'l') selecionada = fila2l;
        else if(cmd[2] == 'o') selecionada = fila2o;
        else { printf("\nInput mal formatado"); }
        break;
      }
      case '3': {
        if(cmd[2] == 'l') selecionada = fila3l;
        else if(cmd[2] == 'o') selecionada = fila3o;
        else { printf("\nInput mal formatado"); }
        break;
      }
      case '4': {
        if(cmd[2] == 'l') selecionada = fila4l;
        else if(cmd[2] == 'o') selecionada = fila4o;
        else { printf("\nInput mal formatado"); }
        break;
      }
      default: printf("\nInput mal formatado"); break;
    }

    if(selecionada) {
      if(cmd[0] == 'a') {
        add_final(selecionada, id++);
      } else if(cmd[0] == 'r') {
        deleta_prim(selecionada, &count);
      } else {
        printf("\nInput mal formatado.");
      }
    }
  } while(strcmp(cmd, "sair") != 0);
}