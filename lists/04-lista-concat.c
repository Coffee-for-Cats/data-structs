#include <stdio.h>
#include <stdlib.h>

typedef struct node {
  struct node* ant;
  int num;
  struct node* prox;
} Node;

typedef struct lista {
  Node* primeiro;
  Node* ultimo;
  int circular;
} Lista;

void add_inicio(Lista* lista, int num) {
  if(lista->circular) {
    printf("Voce nao pode adicionar no inicio de uma lista circular.\n");
    return;
  }
  Node* novo = malloc(sizeof(Node));
  novo->ant = NULL;
  novo->num = num;
  novo->prox = lista->primeiro;
  // se a lista estiver vazia.
  lista->primeiro = novo;
  if(novo->prox) novo->prox->ant = novo;
  if(!lista->ultimo) lista->ultimo = novo;
}

void add_final(Lista* lista, int num) {
  if(lista->circular) {
    printf("Voce nao pode adicionar no final de uma lista circular.\n");
    return;
  }
  Node* novo = malloc(sizeof(Node));
  novo->ant = lista->ultimo;
  novo->num = num;
  novo->prox = NULL;
  lista->ultimo = novo;
  if(novo->ant) novo->ant->prox = novo;
  if(!lista->primeiro) lista->primeiro = novo;
}

void add_depois_de(Lista* lista, int dps_de, int num) {  
  Node* atual = lista->primeiro;
  if(!atual) {
    add_inicio(lista, num);
    return;
  }
  Node* stop = NULL; if(lista->circular) stop = lista->primeiro;
  while(atual->prox != stop && atual->num != dps_de) atual = atual->prox;
  if(atual->prox == stop) {
    printf("Erro! O numero dps_de nao existe.\n");
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

void deleta_num(Lista* lista, int num) {
  Node* atual = lista->primeiro;
  if(!atual) {
    printf("Erro! O numero nao existe.\n");
  }
  Node* stop = NULL; if(lista->circular) stop = lista->primeiro;
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

void printa_lista(Lista* lista) {
  Node* stop = NULL; if(lista->circular) stop = lista->primeiro; 
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

Lista* nova_lista() {
  Lista* lista = malloc(sizeof(Lista));
  lista->primeiro = NULL;
  lista->ultimo = NULL;
  lista->circular = 0;
  return lista;
}

void tornar_circular(Lista* lista) {
  printf("Circulando a lista!\n");
  lista->primeiro->ant = lista->ultimo;
  lista->ultimo->prox = lista->primeiro;
  lista->circular = 1;
}

void tornar_linear(Lista* lista) {
  printf("Circulando a lista!\n");
  lista->primeiro->ant = NULL;
  lista->ultimo->prox = NULL;
  lista->circular = 0;
}

void busca(Lista* lista, int num) {
  Node* atual = lista->primeiro;
  if(!atual) {
    printf("%d nao encontrado na lista.", num);
    return;
  }
  Node* stop = NULL; if(lista->circular) stop = lista->primeiro;
  while(atual->prox != stop && atual->num != num) atual = atual->prox;
  if(atual->prox == stop) {
    printf("%d nao encontrado na lista.", num);
    return;
  }
  printf("-> %p \t| %p \t| %d \t\t| %p\n", atual, atual->ant, atual->num, atual->prox);
  
}

Lista* criar_concat(Lista* lista1, Lista* lista2) {
  Lista* nova = nova_lista();
  // concatena ambas
  Node* atual = lista1->primeiro;
  while(atual) {
    add_inicio(nova, atual->num);
    atual = atual->prox;
  }
  atual = lista2->primeiro;
  while(atual) {
    add_inicio(nova, atual->num);
    atual = atual->prox;
  }
  return nova;
}

// confuso pra caramba, mas funciona =D
void shuffle_concat(Lista* lista1, Lista* lista2) {
  Node* atual1 = lista1->primeiro;
  Node* atual2 = lista2->primeiro;

  while(atual1 && atual2) {
    Node* temp = atual1->prox;
    atual1->prox = atual2;
    atual2->ant = atual1;

    atual1 = temp;
    temp = atual2->prox;
    atual2->prox = atual1;
    if(atual1) atual1->ant = atual2;
    atual2 = temp;
  }

}

Lista* nova_lista_rapida() {
  printf("\nCrie uma nova lista para poder concatenar com a primeira.");
  printf("\nDigite números a serem adicionados na nova lista.");
  printf("\nDigite 0 quando quiser parar e concatenar alternadamente.");
  Lista* lista2 = nova_lista();
  int num;
  do {
    printf("\n      ## lista2 ##");
    printa_lista(lista2);
    scanf("%d", &num);
    add_final(lista2, num);
  } while(num != 0);
  return lista2;
}

int main() {
  int op;
  Lista* lista = nova_lista();
  do {
    printa_lista(lista);
    printf("\nOque deseja fazer com a lista?\n");
    printf("\n0- Sair.");
    printf("\n1- Add comeco.");
    printf("\n2- Add final.");
    printf("\n3- Add ... depois de ...");
    printf("\n4- Excluir depois de ...");
    printf("\n5- Excluir comeco.");
    printf("\n6- Excluir final.");
    printf("\n7- Tornar circular.");
    printf("\n8- Criar uma nova e alternar com a atual.\n");
    scanf("%d", &op);
    switch(op) {
      case 1: {
        printf("\nQual numero deseja adicionar no comeco? ");
        int num;
        scanf("%d", &num);
        add_inicio(lista, num);
        break;
      }
      case 2: {
        printf("\nQual numero deseja adicionar no final? ");
        int num;
        scanf("%d", &num);
        add_final(lista, num);
        break;
      }
      case 3: {
        printf("\nQual numero deseja adicionar? ");
        int num;
        scanf("%d", &num);
        printf("Depois de qual? ");
        int dps_de;
        scanf("%d", &dps_de);
        add_depois_de(lista, dps_de, num);
        break;
      }
      case 4: {
        printf("\nQual deseja excluir? ");
        int num;
        scanf("%d", &num);
        deleta_num(lista, num);
        break;
      }
      case 5: {
        deleta_num(lista, lista->primeiro->num);
        break;
      }
      case 6: {
        deleta_num(lista, lista->ultimo->num);
        break;
      }
      case 7: {
        tornar_circular(lista);
        break;
      }
      case 8: {
        // cria uma nova lista, pedindo números e retornando o ponteiro para ela.
        Lista* lista2 = nova_lista_rapida();
        if(lista->primeiro == NULL) {
          shuffle_concat(lista2, lista);
          // eu sei q na teoria é trapaça, mas
          // funciona perfeitamente e não desperdiça
          // memória nem tempo de execução.
          lista = lista2;
        }
        else
          shuffle_concat(lista, lista2);

        break;
      };
      default: {
        printf("Opcao invalida!\n");
      }
      }
    } while(op != 0);
}