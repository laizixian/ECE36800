#include <stdio.h>
#include <stdlib.h>
#include <time.h>


typedef struct _edge{
  int dest_V;
  double weight;
  struct _edge *next;
} edge;

typedef struct _stack{
  int info;
  struct _stack *next;
} stack;

typedef struct _Vertex{
  int thisnode;
  double width;
  double height;
  double x_coord;
  double y_coord;
  int visited_H;
  int visited_V;
  struct _edge *HCG_head;
  struct _edge *VCG_head;
} Vertex;

typedef struct _Graph{
  int Verties;
  int *seq;
  struct _Vertex *array;
} Graph;


/////////////////////////////////
/////////////////////////////////
Graph *creatGraph(char *Filename)
{
//open file
  FILE *loadfile = fopen(Filename,"r");
  if(loadfile == NULL)
  {
    fprintf(stderr, "cant open the input file\n");
    return NULL;
  }

  int NumOfBlocks, thisNode;
  double width, height;
//create graph
  Graph *G;
  if(fscanf(loadfile, "%d", &NumOfBlocks) == 1)
  {
    G = (Graph*)malloc(sizeof(Graph));
    G->Verties = NumOfBlocks;
    G->array = (Vertex*)malloc((NumOfBlocks + 2) * sizeof(Vertex));
    //set start and sink
    G->array[0].thisnode = 0;
    G->array[0].width = 0;
    G->array[0].height = 0;
    G->array[0].x_coord = 0;
    G->array[0].y_coord = 0;
    G->array[0].visited_H = 0;
    G->array[0].visited_V = 0;
    G->array[0].HCG_head = NULL;
    G->array[0].VCG_head = NULL;
    G->array[NumOfBlocks+1].thisnode = NumOfBlocks+1;
    G->array[NumOfBlocks+1].width = 0;
    G->array[NumOfBlocks+1].height = 0;
    G->array[NumOfBlocks+1].x_coord = 0;
    G->array[NumOfBlocks+1].y_coord = 0;
    G->array[NumOfBlocks+1].visited_H = 0;
    G->array[NumOfBlocks+1].visited_V = 0;
    G->array[NumOfBlocks+1].HCG_head = NULL;
    G->array[NumOfBlocks+1].VCG_head = NULL;
    //set each vertex
    int i;
    for(i = 1; i < (NumOfBlocks+1); i++)
    {
      if(fscanf(loadfile, "%d %lf %lf", &thisNode, &width, &height) == 3)
      {
        G->array[i].thisnode = thisNode;
        G->array[i].width = width;
        G->array[i].height = height;
        G->array[i].x_coord = 0;
        G->array[i].y_coord = 0;
        G->array[i].visited_H = 0;
        G->array[i].visited_V = 0;
        G->array[i].HCG_head = NULL;
        G->array[i].VCG_head = NULL;
      }
    }
    //set the sequence
    i = 0;
    int sequence;
    G->seq = (int*)malloc( (2*NumOfBlocks) * sizeof(int) );
    while(fscanf(loadfile, "%d", &sequence) == 1)
    {
      G->seq[i] = sequence;
      
      i++;
    }
  }
  else
  {
    fclose(loadfile);
    G = NULL;
  }

  fclose(loadfile);
  return G;
}

edge *make_edge(int to, double weight)
{
  edge *new_edge = (edge*)malloc(sizeof(edge));
  new_edge->dest_V = to;
  new_edge->weight = weight; 
  new_edge->next = NULL;
  return new_edge;
}

edge *HCG_add_new_edge(int from, int to, Graph *G)
{
  edge *HCG_head = make_edge(to, G->array[from].width);
  HCG_head->next = G->array[from].HCG_head;
  return HCG_head;
}

edge *VCG_add_new_edge(int from, int to, Graph *G)
{
  edge *VCG_head = make_edge(to, G->array[from].height);
  VCG_head->next = G->array[from].VCG_head;
  return VCG_head;
}

void make_start_sink(Graph *G)
{
  int i;
  for(i = 1; i < (G->Verties+1); i++)
  {
    G->array[0].HCG_head = HCG_add_new_edge(0, i, G);
    G->array[0].VCG_head = VCG_add_new_edge(0, i, G);
    G->array[i].HCG_head = HCG_add_new_edge(i, (G->Verties+1), G);
    G->array[i].VCG_head = VCG_add_new_edge(i, (G->Verties+1), G);
  }
}

Graph *connect_graph(Graph *G)
{
  int i, j;
  int index_num1, index_num2;
  int key_seq1[2], key_seq2[2];
  int *matrix1, *matrix2;
  matrix1 = (int*)malloc( (G->Verties * G->Verties) * sizeof(int));
  matrix2 = (int*)malloc( (G->Verties * G->Verties) * sizeof(int));
  if(matrix1 == NULL)
  {
    fprintf(stderr,"the NULL\n");
    return NULL;
  }
  if(matrix2 == NULL)
  {
    fprintf(stderr, "the NULL\n");
    return NULL;
  }
  for(i = 0; i < G->Verties; i++)
  {
    for(j = 0; j < G->Verties; j++)
    {
      matrix1[(i * G->Verties) + j] = 0;
    }
  }
  for(i = 0; i < G->Verties; i++)
  {
    for(j = 0; j < G->Verties; j++)
    {
      matrix2[(i * G->Verties) + j] = 0;
    }
  }


  for(i = 1; i < (G->Verties+1); i++)
  {
    //find the index of the seq
    j = 0;
    index_num1 = -1;
    while(index_num1 != 1)
    {
      if(G->seq[j] == i)
      {
        key_seq1[index_num1 + 1] = j;
        j++;
        index_num1++;
      }
      else
      {
	j++;
      }
    }
    //create edge
    int a, b;
    for(a = 1; a < (G->Verties+1); a++)
    {
      if(a != i)
      {
	b = 0;
        index_num2 = -1;
        while(index_num2 != 1)
        {
          if(G->seq[b] == a)
          {
            key_seq2[index_num2 + 1] = b;
            b++;
            index_num2++;
          }
          else
          {
	    b++;
          }
        }
        if((key_seq1[0] > key_seq2[0]) && (key_seq1[1] > key_seq2[1]))
        {
          if(matrix1[((a-1) * G->Verties) + (i-1)] == 0)
	  {
            G->array[a].HCG_head = HCG_add_new_edge(a, i, G);
	    matrix1[((a-1) * G->Verties) + (i-1)] = 1;
	  }
        }
        else if((key_seq1[0] < key_seq2[0]) && (key_seq1[1] < key_seq2[1]))
        {
          if(matrix1[((i-1) * G->Verties) + (a-1)] == 0)
	  {
            G->array[i].HCG_head = HCG_add_new_edge(i, a, G);
	    matrix1[((i-1) * G->Verties) + (a-1)] = 1;
	  }
        }
        else if((key_seq1[0] > key_seq2[0]) && (key_seq1[1] < key_seq2[1]))
        {
          if(matrix2[((i-1) * G->Verties) + (a-1)] == 0)
	  {
	    G->array[i].VCG_head = VCG_add_new_edge(i, a, G);
	    matrix2[((i-1) * G->Verties) + (a-1)] = 1;
	  }
        }
        else if((key_seq1[0] < key_seq2[0]) && (key_seq1[1] > key_seq2[1]))
        {
          if(matrix2[((a-1) * G->Verties) + (i-1)] == 0)
	  {
            G->array[a].VCG_head = VCG_add_new_edge(a, i, G);
	    matrix2[((a-1) * G->Verties) + (i-1)] = 1;
	  }
        }
      }
    }
  }

  make_start_sink(G);

  free(matrix1);
  free(matrix2);
  return G;
}

stack *make_stack(int info)
{
  stack *temp = (stack*)malloc(sizeof(stack));
  temp->info = info;
  temp->next = NULL;
  return temp;
} 

stack *stack_push(stack **sort, int info)
{
  stack *stack_top = NULL;
  if(sort == NULL)
  {
    *sort = make_stack(info);
  }
  else
  {
    stack_top = make_stack(info);
    stack_top->next = *sort;
    *sort = stack_top;
  }
  return stack_top;
}

void toposort_order_VCG(Graph *G, int node_number, stack **stack_top)
{
  edge *temp = G->array[node_number].VCG_head;
  while(temp != NULL)
  {
    if(G->array[temp->dest_V].visited_V == 0)
    { 
      toposort_order_VCG(G, temp->dest_V, stack_top);
    }
    temp = temp->next;
  } 
  G->array[node_number].visited_V = 1;
  stack_push(stack_top, node_number);
  
  return;
}
void toposort_order_HCG(Graph *G, int node_number, stack **stack_top)
{
  edge *temp = G->array[node_number].HCG_head;
  while(temp != NULL)
  {
    if(G->array[temp->dest_V].visited_H == 0)
    { 
      toposort_order_HCG(G, temp->dest_V, stack_top);
    }
    temp = temp->next;
  } 
  G->array[node_number].visited_H = 1;
  stack_push(stack_top, node_number);
  
  return;
}

void find_longest_path_H(Graph *G, stack *sort_order_H)
{
  stack *temp = sort_order_H;
  while(temp != NULL)
  {
    edge *head = G->array[temp->info].HCG_head;
    while(head != NULL)
    {
      if(G->array[head->dest_V].x_coord < (G->array[temp->info].x_coord + head->weight) )
      {
        G->array[head->dest_V].x_coord = (G->array[temp->info].x_coord + head->weight);
      }
      head = head->next;
    }
    temp = temp->next;
  }
}

void find_longest_path_V(Graph *G, stack *sort_order_V)
{
  stack *temp = sort_order_V;
  while(temp != NULL)
  {
    edge *head = G->array[temp->info].VCG_head;
    while(head != NULL)
    {
      if(G->array[head->dest_V].y_coord < (G->array[temp->info].y_coord + head->weight) )
      {
        G->array[head->dest_V].y_coord = (G->array[temp->info].y_coord + head->weight);
      }
      head = head->next;
    }
    temp = temp->next;
  }
}

void make_output(Graph *G, char *Filename)
{
  FILE *output = fopen(Filename, "w");

  fprintf(output, "%d\n", G->Verties);
  
  int i;
  for(i = 1; i < (G->Verties+1); i++)
  {
      fprintf(output,"%d %le %le %le %le\n",G->array[i].thisnode, G->array[i].width, G->array[i].height, G->array[i].x_coord, G->array[i].y_coord);

  }

  fclose(output);
}

void destroy_stack(stack *stack_top)
{
  stack *temp = NULL;
  while(stack_top != NULL)
  {
    temp = stack_top;
    stack_top = stack_top->next;
    free(temp);
  }
}

void destroy_Graph(Graph *G)
{
  int i;
  for(i = 0; i < (G->Verties+2); i++)
  {
    edge *head_H = G->array[i].HCG_head;
    edge *head_V = G->array[i].VCG_head;
    while(head_H != NULL)
    {
      edge *temp = head_H;
      head_H = head_H->next;
      free(temp);
    }
    while(head_V != NULL)
    {
      edge *temp = head_V;
      head_V = head_V->next;
      free(temp);
    }
  }
  free(G->array);
  free(G->seq);
  free(G);
}

int main(int argc, char **argv)
{
  if(argc == 3)
  {
    double time1, time2;
    time1 = clock();
    Graph *G = creatGraph(argv[1]);
    if(G == NULL)
    {
      fprintf(stderr, "fail on creating graph\n");
      return EXIT_FAILURE;
    }

    
    connect_graph(G);
  
    
    stack *stack_top_VCG = NULL;
    stack *stack_top_HCG = NULL;

    toposort_order_HCG(G, 0, &stack_top_HCG); 

    toposort_order_VCG(G, 0, &stack_top_VCG); 
    

    find_longest_path_H(G, stack_top_HCG);
    find_longest_path_V(G, stack_top_VCG);
    
    time2 = clock();
    make_output(G, argv[2]);
    
    fprintf(stdout, "Width: %le\n", G->array[G->Verties+1].x_coord);
    fprintf(stdout, "Height: %le\n", G->array[G->Verties+1].y_coord);
    fprintf(stdout, "X-coordinate: %le\n", G->array[G->Verties].x_coord);
    fprintf(stdout, "Y-coordinate: %le\n", G->array[G->Verties].y_coord);
    fprintf(stdout, "Elapsed time: %le\n", (time2-time1)/CLOCKS_PER_SEC);


    destroy_stack(stack_top_HCG);
    destroy_stack(stack_top_VCG);
    destroy_Graph(G);
  }
	



  else
  {
    fprintf(stderr, "wrong number of argeement\n");
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
