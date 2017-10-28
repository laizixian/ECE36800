#include <stdio.h>
#include <stdlib.h>

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
Node *node_construct(long number)
{
  Node *ret_node = (Node *)malloc(sizeof(Node));
  if (ret_node == NULL)
  {
     return NULL;
  }
  ret_node->value = number;
  ret_node->balance = 0;
  ret_node->next = NULL;
  ret_node->print = NULL;
  ret_node->left = NULL;
  ret_node->right = NULL;
  ret_node->b_left = NULL;
  ret_node->b_right = NULL;
  return ret_node;
}
//////////////////////////////////////////
//////////////////////////////////////////
Node *Load_File(char *Filename, int *Size)
{
  FILE *read_file;
  read_file = fopen(Filename, "r");
  if(read_file == NULL)
  {
    fprintf(stderr, "cant open file\n");
    return NULL;
  }
  rewind(read_file);
  
  long number;
  int i;
  i = 0;
  
  Node *head_node = NULL;
  while(fscanf(read_file, "%ld", &number) == 1)
  {
    if(i == 0)
    {
      head_node = node_construct(number);
    }
    else
    {
      Node *new_node = node_construct(number);
      new_node->next = head_node;
      head_node = new_node;
    }
    i++;
  }
  *Size = i;
  fclose(read_file);
  return head_node; 
}
///////////////////////////////
///////////////////////////////
Node *Construct_BST(Node *list)
{
  Node *tree_root = list;
  list = list->next; 
  Node *curr = NULL;

  while(list != NULL)
  {
    curr = tree_root;
    while(1)
    {

      if( (list->value) >= (curr->value) )
      {
        if(curr->right == NULL)
	{
	  curr->right = list;
	  break;
	}
	else
	{
  	  curr = curr->right;
	}
      }
      else if( (list->value) < (curr->value) )
      {
        if(curr->left == NULL)
	{
	  curr->left = list;
	  break;
	}
	else
	{
  	  curr = curr->left;
	}
      }
    }

    list = list->next;
  }

  return tree_root;
}
//////////////////////////////////////////////
//////////////////////////////////////////////
Node *stack_push(Node **stack, Node *new_node)
{
  if (new_node != NULL)
  {
    new_node->print = *stack;
    *stack = new_node;
  }
  return new_node;
}
Node *stack_pop(Node **stack)
{
  if(*stack == NULL)
  {
    return NULL;
  }
  Node *ret_node = *stack;  
  *stack = ret_node->print;   
  ret_node->print = NULL;  
  return ret_node;
}
Node *enqueue(Node **stack, Node **end, Node *new_node)
{
  if(new_node != NULL)
  {
    if(*stack == NULL)
    {
      new_node->print = *stack;
      *stack = new_node;
      *end = *stack;
    }
    else
    {
      (*end)->print = new_node;
      *end = new_node;
    }
  }
  return new_node; 
}
long find_size_stack(Node *stack)
{
  Node *temp = stack;
  long count = 0;
  while(temp != NULL)
  {
    temp = temp->print;
    count++;
  }
  return count;
}
void clean_stack(Node *list)
{
  while(list != NULL)
  {
    list->print = NULL;
    list = list->next;
  }
}
///////////////////////////////////////////////////
///////////////////////////////////////////////////
long Print_BST_Preorder(char *Filename, Node *tree)
{
  FILE *write_file;
  write_file = fopen(Filename, "w");
  if(write_file == NULL)
  {
    return 0;
  }
  rewind(write_file);

  Node *stack = NULL;
  Node *tree_node = NULL;
  long max_depth = 0;

  stack_push(&stack, tree); 
  while(stack != NULL)
  {
    tree_node = stack_pop(&stack);
    if(tree_node != NULL)
    {
      
      fprintf(write_file, "%ld\n", tree_node->value);
      stack_push(&stack, tree_node->right);
      stack_push(&stack, tree_node->left);
      if(find_size_stack(stack) > max_depth)
      {
        max_depth = find_size_stack(stack);
      }
    }

  }

  clean_stack(tree);
  fclose(write_file);
  return max_depth;
}
///////////////////////////////////////////////////
///////////////////////////////////////////////////
long Print_BST_Inorder(char *Filename, Node *tree)
{
  FILE *write_file;
  write_file = fopen(Filename, "w");
  if(write_file == NULL)
  {
    return 0;
  }
  rewind(write_file);
  
  long max_depth = 0;
  Node *p = tree;
  Node *Stack = NULL;
  do{
    while(p != NULL)
    {
      stack_push(&Stack, p);
      p = p->left;
    }  
    if(Stack != NULL)
    {
      if(find_size_stack(Stack) > max_depth)
      {
        max_depth = find_size_stack(Stack);
      }
      p = stack_pop(&Stack);
      fprintf(write_file, "%ld\n", p->value);
      p = p->right;
    }
  }while(Stack != NULL || p != NULL);

  clean_stack(tree);
  fclose(write_file);
  return max_depth;
}


long Print_BST_Postorder(char *Filename, Node *tree)
{
  FILE *write_file;
  write_file = fopen(Filename, "w");
  if(write_file == NULL)
  {
    return 0;
  }
  rewind(write_file);

  long max_depth = 0;
  Node *Stack = NULL; 

  stack_push(&Stack, tree);
  Node *prev = NULL;
  while(Stack != NULL)
  {
    Node *curr = Stack;
    if(!prev || prev->left == curr || prev->right == curr)
    {
      if(curr->left != NULL)
      {
        stack_push(&Stack, curr->left);
      }
      else if(curr->right != NULL)
      {
        stack_push(&Stack, curr->right);
      }
    }
    else if(curr->left == prev)
    {
      if(curr->right != NULL)
      {
        stack_push(&Stack, curr->right);
      }
    }
    else 
    {
      fprintf(write_file, "%ld\n", curr->value);
      if(find_size_stack(Stack) > max_depth)
      {
        max_depth = find_size_stack(Stack);
      }
      stack_pop(&Stack);
    }
    prev = curr; 
  }

  clean_stack(tree);
  fclose(write_file);
  return max_depth;
}

long Print_BST_BF(char *Filename, Node *tree)
{
  FILE *write_file;
  write_file = fopen(Filename, "w");
  if(write_file == NULL)
  {
    return 0;
  }
  rewind(write_file);
  
  long max_depth = 0;
  Node *Queue = NULL;
  Node *tree_node = NULL;
  Node *end = NULL;
  enqueue(&Queue,&end, tree);
  while(Queue != NULL)
  {
    tree_node = stack_pop(&Queue);
    if(tree_node != NULL)
    {
      
      fprintf(write_file, "%ld\n", tree_node->value);
      enqueue(&Queue, &end, tree_node->left);
      max_depth++;
      enqueue(&Queue, &end, tree_node->right);
    } 
  }

  clean_stack(tree);
  fclose(write_file);
  return max_depth; 
}

///////////////////////////
///////////////////////////
long height(Node *sub_root)
{
  if(sub_root == NULL)
  {
    return -1;
  }
  else
  {
    return sub_root->balance;
  }
}

long find_max_height(long a, long b)
{
  return a>b ? a:b;
}

void set_balance(Node *sub_root)
{
  sub_root->balance = find_max_height(height(sub_root->b_left), height(sub_root->b_right)) + 1;
}

Node *rotate_left(Node *sub_root)
{
  Node *new_node = sub_root->b_left;
  sub_root->b_left = new_node->b_right;
  new_node->b_right = sub_root;
  set_balance(new_node);
  set_balance(sub_root);
  return new_node;
}

Node *rotate_right(Node *sub_root)
{
  Node *new_node = sub_root->b_right;
  sub_root->b_right = new_node->b_left;
  new_node->b_left = sub_root;
  set_balance(new_node);
  set_balance(sub_root);
  return new_node;
}

Node *insert(Node *sub_root, Node *new_node)
{
  if(sub_root == NULL)
  {
    sub_root = new_node;
  }

  else if(new_node->value < sub_root->value)
  {
    sub_root->b_left = insert(sub_root->b_left, new_node);
    if((height(sub_root->b_left) - height(sub_root->b_right)) == 2)
    {
      if(new_node->value < sub_root->b_left->value)
      {
        sub_root = rotate_left(sub_root);
      }
      else
      {
        sub_root->b_left = rotate_right(sub_root->b_left);
        sub_root = rotate_left(sub_root);
      }
    }
  }

  else if(new_node->value >= sub_root->value)
  {
    sub_root->b_right = insert(sub_root->b_right, new_node);
    if((height(sub_root->b_right) - height(sub_root->b_left)) == 2)
    {
      if(new_node->value >= sub_root->b_right->value)
      {
        sub_root = rotate_right(sub_root);
      }
      else
      {
        sub_root->b_right = rotate_left(sub_root->b_right);
        sub_root = rotate_right(sub_root);
      }
    }
  }
  set_balance(sub_root);
  return sub_root;
}

Node *Balance_BST(Node *list)
{
  Node *tree_root = list;
  list = list->next; 

  while(list != NULL)
  {
    tree_root = insert(tree_root, list);
    list = list->next;
  }
  return tree_root;
}


/////////////////////////////////////////////////////
/////////////////////////////////////////////////////
int Search_List(Node *List, long key, double *N_Comp)
{
  int result = 0;
  while(List != NULL)
  {
    *N_Comp += 1;
    if(List->value == key)
    {
      result = 1;
      break;
    }
    List = List->next;
  }
  return result;
}
////////////////////////////////////////////////////
////////////////////////////////////////////////////
int Search_Tree(Node *tree, long key, double *N_Comp)
{
  int result = 0; 
  while(tree != NULL)
  {
    if(key > tree->value)
    {
      *N_Comp += 1;
      tree = tree->right;
    }
    else if(key < tree->value)
    {
      *N_Comp += 1;
      tree = tree->left;
    }
    else if(key == tree->value)
    {
      *N_Comp += 1;
      result = 1;
      break;
    }
  }
  return result;
}
//////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////
int Search_Tree_balanced(Node *tree, long key, double *N_Comp)
{
  int result = 0; 
  while(tree != NULL)
  {
    if(key > tree->value)
    {
      *N_Comp += 1;
      tree = tree->b_right;
    }
    else if(key < tree->value)
    {
      *N_Comp += 1;
      tree = tree->b_left;
    }
    else if(key == tree->value)
    {
      *N_Comp += 1;
      result = 1;
      break;
    }
  }
  return result;
}
///////
void destroy_list(Node *list)
{
  while(list != NULL)
  {
    Node *tmp = list->next;
    //free(list->ptr);
    free(list);
    list = tmp;
  }
} 


