#include <stdio.h>
#include <stdlib.h>

struct vertex;
struct edge;

typedef struct vertex {
  char codeName;
  struct edge* edges;
  struct vertex* nextVertex;
} Vertex;

typedef struct edge {
  struct vertex* ref;
  struct edge* or;
} Edge;

char codeName = 'a';
Vertex* newVertex() {
  Vertex* vertex = malloc(sizeof(Vertex));

  vertex->codeName = codeName++;
  vertex->edges = NULL;
  vertex->nextVertex = NULL;

  return vertex;
}

Edge* newEdge(Vertex* ref) {
  Edge* edge = malloc(sizeof(Edge));
  edge->or = NULL;
  edge->ref = ref;
  return edge;
}

// the edge goes from "on" towards "to".
// it's saved in "on"'s list of edges.
void saveEdge(Vertex* on, Vertex* to) {
  // if the list is empty, save as the first item
  if(on->edges == NULL) {
    on->edges = newEdge(to); // first edge on said vertex
    return;
  }
  // gets the last item of the list of edges, said that there is at least 1 edge.
  Edge* actual = on->edges;
  while(actual->or != NULL) actual = actual->or;
  actual->or = newEdge(to);
}

void printVertex(Vertex* vertex) {
  printf("\nVertice: %c | end: %x", vertex->codeName, vertex);
  printf("\nArrestas: ");
  Edge* actual = vertex->edges;
  while(actual != NULL) {
    printf("%c ", actual->ref->codeName);
    actual = actual->or;
  };
  printf("\n");
}

void printMap(Vertex* first) {
  while(first != NULL) {
    printVertex(first);
    first = first->nextVertex;
  }
}

Vertex* find(Vertex* first, char codeName) {
  printf("\n ??? Searching for code %c ???\n", codeName);
  if(first->codeName == codeName) return first;
  while(first->nextVertex != NULL && first->codeName != codeName) first = first->nextVertex;
  if(first->codeName == codeName) return first;
  printf("\nVertex nao encontrado na funcao find!");
  return NULL;
}

int main() {
  Vertex* mapa = NULL;
  int op;
  int bidirecional = 0;

  do {
    printMap(mapa);

    printf("\nSelecione: ");
    printf("\n1- Adicionar vertice");
    printf("\n2- Adicionar arresta");

    printf("\n3- ");
    if(bidirecional) printf("Desativar");
    else printf("Ativar");
    printf(" bidirecionalidade");

    printf("\n4- Printar matriz");

    printf("\n");
    scanf("%d", &op);

    switch (op) {
    case 0: {
      printf("\nsaindo");
    }
    case 1: {
      if(mapa == NULL) {
        mapa = newVertex();
      } else {
        // gets to the last saved vertex and saves the new vertex as next;
        Vertex* actual = mapa;
        while(actual->nextVertex != NULL) actual = actual->nextVertex;
        actual->nextVertex = newVertex();
      }
      break;
    }
    case 2: {
      char fromCode;
      printf("\nDe? ");
      scanf(" %c", &fromCode);
      printf("\nPara? ");
      char toCode;
      scanf(" %c", &toCode);
      saveEdge(find(mapa, fromCode), find(mapa, toCode));
      if(bidirecional) {
        saveEdge(find(mapa, toCode), find(mapa, fromCode));
      }
      break;
    }
    case 3: {
      if(bidirecional == 0) bidirecional = 1;
      else bidirecional = 0;
    }
    case 4: {
      int tam = codeName - 'a';
      int mat[tam][tam];
      
      for(int i = 0; i < tam; i++) for(int j = 0; j < tam; j++) mat[i][j] = 0;

      // hell yeah, first try baby
      for(Vertex* first = mapa; first != NULL; first = first->nextVertex) {
        for(Edge* fEdge = first->edges; fEdge != NULL; fEdge = fEdge->or) {
          mat[first->codeName - 'a'][fEdge->ref->codeName - 'a'] = 1;
        }
      }

      // pretty print the matrix
      printf("  ");
      for(int i = 'A'; i < tam + 'A'; i++) printf("%c ", i);
      printf("\n");

      for(int i = 0; i < tam; i++) {
        printf("%c ", 'A' + i);
        for(int j = 0; j < tam; j++) {
          if(mat[i][j]) printf("X ");
          else printf("  ");
        }
        printf("\n");
      }
    }

    default:
      break;
    }
  } while(op != 0);
}