#include <stdio.h>
#include <stdlib.h>

int main() {
  printf("Quantos pontos voce quer ter? ");
  int pointCount = 0;
  scanf(" %d", &pointCount);
  int adjacency[pointCount][pointCount];
  int maxPointLetter = 'a' + pointCount - 1;
  char from, to;
  do {
    printf("Nova conexao (0 p/ cancelar, a-%c para os nomes dos pontos)\n", maxPointLetter);
    printf("Do ponto: ");
    scanf(" %c", &from);
    printf("Para o ponto: ");
    scanf(" %c", &to);

    adjacency[from - 'a'][to - 'a'] = 1;
  } while(from != '0' && to != '0');

  // # print the adjacency table
  
  // prints the columns "names"
  printf("  "); // the first is idented
  for(int i = 0; i < pointCount; ++i) {
    printf(" %c", 'A' + i);
  }
  printf("\n");
  // prints the table itself
  for(int i = 0; i < pointCount; i++) {
    printf(" %c", 'A' + i); // prints the lines "names"
    for(int j = 0; j < pointCount; j++) {
      if(adjacency[i][j] == 1) printf(" T");
      else printf(" F");
    }
    printf("\n");
  }
}