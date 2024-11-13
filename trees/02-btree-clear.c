#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node {
  struct node* left;
  int num;
  struct node* right;
} Node;

Node* root(int a) {
  Node* p = malloc(sizeof(Node));
  p->right = NULL;
  p->left = NULL;
  p->num = a;
  return p;
}

void add_bst(Node* root, Node* new) {
  if(root == NULL) {
    printf("\n Erro, cheguei em um NULL\n");
    return;
  }
  if(new->num > root->num) {
    if(root->right == NULL) root->right = new;
    else add_bst(root->right, new);
  } else {
    if(root->left == NULL) root->left = new;
    else add_bst(root->left, new);
  }
}

void print_ident(Node* root, int ident) {
  // em pré-ordem
  if(root == NULL) return;
  for(int i = 0; i < ident; i++) printf("   ");
  printf("number: %d \n", root->num);

  if(root->left) {
    for(int i = 0; i < ident; i++) printf("   ");
    printf("left: \n");
    print_ident(root->left, ident + 1);
  }

  if(root->right) {
    for(int i = 0; i < ident; i++) printf("   ");
    printf("right: \n");
    print_ident(root->right, ident + 1);
  }
}

void printa(Node* root) {
  if(root == NULL) return;
  printf("\nNum: %d\tEnd: %p \tLeft: %p \tRight: %p", root->num, root, root->left, root->right);
  printa(root->left);
  printa(root->right);
}

void print_level(Node* root, int wanted) {
  if(wanted == 0) {
    printf("%d ", root->num);
  } else {
    if(root->right) print_level(root->right, --wanted);
    if(root->left) print_level(root->left, --wanted);
  }
}

int main() {
  int root_num = 0;
  printf("Digite o root: ");
  scanf(" %d", &root_num);
  Node* btree = root(root_num);

  int op = 0;
  do {
    fflush(stdin);
    printf("\n"
    "0- quit\n"
    "1- batch insert as BST\n"
    "2- batch insert\n"
    "3- print ident\n"
    "4- print table-like\n"
    "5- print by level\n"
    );
    fflush(stdin);
    scanf("%d", &op);
    // printf("op: %d", op);

    switch(op) {
      case 0: {break;}
      case 1: {
        char input[60];
        fflush(stdin);
        printf("Numeros: ");
        fgets(input, sizeof(input), stdin);
        printf("String: %s", input);
        
        char* next = strtok(input, " ");
        while(next != NULL) {
          int num = atoi(next);
          add_bst(btree, root(num));
          next = strtok(NULL, " ");
        }
        break;
      }
      case 2: {
        printf("\nInserting a lot!\n");
        for(int i = 0; i < 16; i++) add_bst(btree, root(i));
        break;
      }
      case 3: {
        printf("\n<Idented Tree>\n");
        print_ident(btree, 0);
        printf("\n");
        break;
      }
      case 4: {
        printf("\n<Non-Idented Tree>\n");
        printa(btree);
        break;
      }
      case 5: {
        printf("\nDigite o nivel desejado: ");
        int wanted = 0;
        scanf("%d", &wanted);
        printf("\n<By Level>\n");
        print_level(btree, wanted);
        break;
      }
      case 6: {

      }
    }
    // end loop
  } while(op != 0);
}