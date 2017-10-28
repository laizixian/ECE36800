#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _node{
  long value;
// linked-list
  struct _node *next;
  struct _node *print;
// tree
  long balance;
  struct _node *left;
  struct _node *right;
  struct _node *b_left;
  struct _node *b_right;
} Node;
/////////////////////////////////
/////////////////////////////////

Node *Load_File(char *Filename, int *Size);
Node *Construct_BST(Node *list);
long Print_BST_Preorder(char *Filename, Node *tree);
long Print_BST_Inorder(char *Filename, Node *tree);
long Print_BST_Postorder(char *Filename, Node *tree);
long Print_BST_BF(char *Filename, Node *tree);
Node *Balance_BST(Node *list);

int Search_List(Node *List, long key, double *N_Comp);
int Search_Tree(Node *tree, long key, double *N_comp);
int Search_Tree_balanced(Node *tree, long key, double *N_Comp);

void destroy_list(Node *list);

int main(int argc, char **argv)
{
  int size = 0;
  double Comp_list = 0;
  double Comp_tree = 0;
  double Comp_balanced_tree = 0;

  //long depth = 0;
  if(argc == 5)
  {
    Node *list = Load_File(argv[2], &size);
    Node *tree = Construct_BST(list);
    Node *balanced_tree = Balance_BST(tree);
    if(list == NULL)
    {
      return EXIT_FAILURE;
    }

    if(strcmp(argv[1], "e") == 0)
    {
      Print_BST_Preorder(argv[3], tree);
    }
    else if(strcmp(argv[1], "i") == 0)
    {
      Print_BST_Inorder(argv[3], tree);
    }
    else if(strcmp(argv[1], "o") == 0)
    {
      Print_BST_Postorder(argv[3], tree);
    }
    else if(strcmp(argv[1], "b") == 0)
    {
      Print_BST_BF(argv[3], tree);
    }

    FILE *output_file = fopen(argv[4], "w");
    if(output_file == NULL)
    {
      fprintf(stderr, "cant open file\n");
      return EXIT_FAILURE;
    }
    long key;
    fprintf(stdout, "Number of nodes: %d\n", size);
    while((fscanf(stdin, "%ld", &key) == 1) && (key != -1))
    {
      //int check = scanf("%ld", &key);
      int r1, r2, r3;
      r1 = Search_List(list, key, &Comp_list);
      r2 = Search_Tree(tree, key, &Comp_tree);
      r3 = Search_Tree_balanced(balanced_tree, key, &Comp_balanced_tree);
      fprintf(output_file, "the number of comparisons for key %ld:\n", key);
      fprintf(output_file, "searching list: %f\n", Comp_list);
      fprintf(output_file, "searching tree: %f\n", Comp_tree);
      fprintf(output_file, "searching balanced tree: %f\n\n", Comp_balanced_tree);
      if((r1 == 1) && (r2 == 1) && (r3 == 1))
      {
        fprintf(stdout, "found\n");
      }
      else
      {
        fprintf(stdout, "not found\n");
      }
      Comp_list = 0;
      Comp_tree = 0;
      Comp_balanced_tree = 0;
    }

    fclose(output_file);
    destroy_list(list);

  }  
  

  return EXIT_SUCCESS;
}
