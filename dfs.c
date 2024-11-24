
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define size 100

struct node {
  int vertex;
  struct node* next;
};

struct Graph {
  int numVertices;
  int adjmatrix[size][size];
  struct node** adjLists;
};

// Create a node
struct node* createNode(int v)
{
  struct node* newNode = malloc(sizeof(struct node));
  newNode->vertex = v;
  newNode->next = NULL;
  return newNode;
}

// Create graph
struct Graph* createGraph(int vertices)
{
  struct Graph* graph = malloc(sizeof(struct Graph));
  graph->numVertices = vertices;
  graph->adjLists = malloc(vertices * sizeof(struct node*));

  int i;
  for (i = 0; i < vertices; i++) {
    graph->adjLists[i] = NULL;
  }
  for(int i=0;i<size;i++)
  {
      for(int j=0;j<size;j++)
      {
          graph->adjmatrix[i][j]=0;
      }
  }
  return graph;
}

// Add edge
void addEdge(struct Graph* graph, int src, int dest)
{
  struct node* newNode = createNode(dest);
  newNode->next = graph->adjLists[src];
  graph->adjLists[src] = newNode;
  graph->adjmatrix[src][dest]=1;
  graph->adjmatrix[dest][src]=1;
}

// DFS algo

void DFS_adjlist(struct Graph* graph, int ver)
{
  int visited[size]={0};
  int stack[size];
  int top=-1;
  top++;
  stack[top]=ver;
  visited[ver]=1;
  while(top!=-1)
  {
      int currentvertex=stack[top];
      printf("%d ",currentvertex);
      top--;
      struct node* temp=graph->adjLists[currentvertex];
      while(temp)
      {
          int nextvertex=temp->vertex;
          if(visited[nextvertex]==0)
          {
              visited[nextvertex]=1;
              top++;
              stack[top]=nextvertex;
          }
          temp=temp->next;
      }
  }
}

void DFS_matrix(struct Graph* graph, int ver)
{
  int visited[size]={0};
  int stack[size];
  int top=-1;
  top++;
  stack[top]=ver;
  visited[ver]=1;
  printf("%d ",ver);
  while(top!=-1)
  {
    int nextvertex=stack[top];
    top--;
    for(int i=0;i<graph->numVertices;i++)
    {
      if(graph->adjmatrix[nextvertex][i]==1 && visited[i]==0)
      {
        printf("%d ",i);
        visited[i]=1;
        top++;
        stack[top]=i;
      }
    }
  }
}


int main()
{
  int n, edge, startVertex, src, dest;

  printf("\nEnter the total number of vertices: ");
  scanf("%d", &n);

  struct Graph* graph = createGraph(n);

  printf("\nEnter the number of edges:");
  scanf("%d", &edge);
  for (int i = 0; i < edge; ++i)
  {
    printf("Enter edge %d (source dest):", i + 1);
    scanf("%d %d", &src, &dest);
    addEdge(graph, src, dest);
  }
  startVertex=0;

        printf("\nDFS via Adjancency list: ");
        DFS_adjlist(graph, startVertex);
        printf("\n");

        printf("\nDFS via Adjancency matrix: ");
        DFS_matrix(graph,startVertex);
        printf("\n");

  return 0;
}
