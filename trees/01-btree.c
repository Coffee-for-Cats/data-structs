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

// Node* get(Node* root, int path) {
//   // printf(" %d ", root);
 
//   if(path == 0) {
//     return root->left;
//   }
//   if (path == 1) {
//     return root->right;
//   }

//   if(path % 2 == 0) {
//     return get(root->left, path/2);
//   } else {
//     return get(root->right, path/2);
//   }
// }

// void add(Node* tree, int path, int num) {
//   Node* last = tree;

//   if(path > 1) {
//     last = get(tree, path/2 - 1);
//   }

//   if(path % 2 == 0) {
//     last->left = new_root(num);
//   } else {
//     last->right = new_root(num);
//   }
// }

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
  printf("\nNum: %d  Left: %x  Right: %x", root->num, root->left, root->right);
  printa(root->left);
  printa(root->right);
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

int main() {
  Node* btree = root(4);
  add_bst(btree, root(6));
  add_bst(btree, root(1));
  add_bst(btree, root(3));
  add_bst(btree, root(5));
  add_bst(btree, root(7));
  add_bst(btree, root(2));

  print_ident(btree, 0);
}