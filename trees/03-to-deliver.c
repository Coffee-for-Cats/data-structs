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

void printa_pre_ordem(Node* root) {
  if(root == NULL) return;
  printf("\t%d ", root->num);
  printa_pre_ordem(root->left);
  printa_pre_ordem(root->right);
}

void printa_simetric(Node* root) {
  if(root == NULL) return;
  printa_simetric(root->left);
  printf("\t%d ", root->num);
  printa_simetric(root->right);
}

void printa_pos_ordem(Node* root) {
  if(root == NULL) return;
  printa_pos_ordem(root->left);
  printa_pos_ordem(root->right);
  printf("\t%d ", root->num);
}

int max_height(Node* root) {
  if(root == NULL) return 0;

  int height_right = max_height(root->right);
  int height_left = max_height(root->left);

  if(height_left > height_right)
    return height_left + 1;
  else
    return height_right + 1;
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
    "6- print height of tree\n"
    "7- print pre-order\n"
    "8- print simetric\n"
    "9- print pos-order\n"
    );
    fflush(stdin);
    scanf("%d", &op);
    // printf("op: %d", op);

    switch(op) {
      // quit
      case 0: {break;}
      // batch insert by string
      case 1: {
        char input[60];
        fflush(stdin);
        printf("numbers: ");
        fgets(input, sizeof(input), stdin);
        // printf("String: %s", input);
        
        char* next = strtok(input, " ");
        while(next != NULL) {
          int num = atoi(next);
          add_bst(btree, root(num));
          next = strtok(NULL, " ");
        }
        break;
      }
      // batch insert sequential. pretty bad to be honest.
      case 2: {
        printf("\nInserting a lot!\n");
        for(int i = 0; i < 16; i++) add_bst(btree, root(i));
        break;
      }
      // print idented
      case 3: {
        printf("\n<Idented Tree>\n");
        print_ident(btree, 0);
        printf("\n");
        break;
      }
      // table-like print
      case 4: {
        printf("\n<Non-Idented Tree>\n");
        printa(btree);
        break;
      }
      // print by level
      case 5: {
        printf("\nDesired level: ");
        int wanted = 0;
        scanf("%d", &wanted);
        printf("\n<By Level>\n");
        print_level(btree, wanted);
        break;
      }
      // mas heigth of tree
      case 6: {
        int height = max_height(btree);
        printf("\nHeight of tree: %d", height);
        break;
      }
      // pre-order
      case 7: {
        printf("\n<Pre-ordem>\n");
        printa_pre_ordem(btree);
        break;
      }
      // simetric
      case 8: {
        printf("\n<Simetrico>\n");
        printa_simetric(btree);
        break;
      }
      // pos-order
      case 9: {
        printf("\n<Pos-ordem>\n");
        printa_pos_ordem(btree);
        break;
      }
    }
    // end loop
  } while(op != 0);
}