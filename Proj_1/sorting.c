#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

long *Load_File(char *Filename, int *Size)
{
  FILE *read_file;
  long *array;

//////open file
  read_file = fopen(Filename, "r");
  if(read_file == NULL)
  {
    return NULL;
  }
  rewind(read_file);

//////read the first line as number of integers
  int number = 0;
  if(fscanf(read_file, "%d", &number))
  {
    array = malloc(sizeof(long) * number);
  }
  else
  {
    return NULL;
  }

//////if malloc fails return null
  if(array == NULL)
  {
    return NULL; 
  }

//////read the array
  *Size = 0;
  while(fscanf(read_file, "%ld", &array[*Size]) == 1)
  {
    *Size += 1;
  }
  

  //close the file and return the array
  fclose(read_file);
  return array;
}

////////////////////////////////////////////////////
////////////////////////////////////////////////////
int Save_File(char *Filename, long *Array, int Size)
{
//////open the file
  FILE *write_file;
  write_file = fopen(Filename, "w");
  if(write_file == 0)
  {
    return 0;
  }
  rewind(write_file);

//////write the file
  fprintf(write_file, "%d", Size);
  int i;
  for(i = 0; i < Size; i++)
  {
    fprintf(write_file, "\n%ld", Array[i]);
  }
  fprintf(write_file, "\n");
  
  fclose(write_file);
  return 1;
}

/////////////////////////////////////////////////////////////////////////////////////
void Shell_Insertion_Sort_Seq1(long *Array, int Size, double *N_Comp, double *N_Move)
{
  int T_number;
  T_number = (log(Size + 1)) / (log(2));

  int i,j,k;
  int gap;
  long temp;
  for(i = T_number; i >= 1; i--)
  {
    gap = (int)(pow(2, i) - 1);
    for(j = gap; j < Size; j++)
    {
      temp = Array[j];
      *N_Move += 1;

      for(k = j - gap; ((k >= 0) && (Array[k] > temp)); k -= gap)
      {
        *N_Comp += 1;

        Array[k + gap] = Array[k];
        *N_Move += 1;
      }
      Array[k + gap] = temp;
      *N_Move += 1;
    }
  }
}

//////////////////////////////////////////////////////////////////////////////////
void Shell_Bubble_Sort_Seq1(long *Array, int Size, double *N_Comp, double *N_Move)
{
  int T_number;
  T_number = (log(Size + 1)) / (log(2));

  int i,j,k;
  int gap;
  long temp;
  for(i = T_number; i >= 1; i--)
  {
    gap = (int)(pow(2, i) - 1);
    for(j = 0; j < Size - gap; j++)
    {
      for(k = 0; k < Size - j - gap; k += gap)
      {
        *N_Comp += 1;
        if(Array[k] > Array[k + gap])
        {
          temp = Array[k];
          Array[k] = Array[k + gap];
          Array[k + gap] = temp;
          *N_Move += 3;
        }
      }
    }
  }
}

/////////////////////////////////////////////////////////////////////////////////////
void Shell_Insertion_Sort_Seq2(long *Array, int Size, double *N_Comp, double *N_Move)
{
  int Q_P_number;
  Q_P_number = (log(Size) / log(3));
  
  int p, q; 
  int j,k;
  int gap;
  long temp;
  for(p = Q_P_number; p >= 0; p--)
  {
    for(q = p; q >= 0; q--)
    {
      gap = (int)(pow(2, p - q) * pow(3, q));
      for(j = gap; j < Size; j++)
      {
        temp = Array[j];
        *N_Move += 1;

        for(k = j - gap; ((k >= 0) && (Array[k] > temp)); k -= gap)
        {
          *N_Comp += 1;

          Array[k + gap] = Array[k];
          *N_Move += 1;
        }
        Array[k + gap] = temp;
        *N_Move += 1;
      }
    }
  }
}

//////////////////////////////////////////////////////////////////////////////////
void Shell_Bubble_Sort_Seq2(long *Array, int Size, double *N_Comp, double *N_Move)
{
  int Q_P_number;
  Q_P_number = (log(Size) / log(3));
  
  int p, q; 
  int j,k;
  int gap;
  long temp;
  for(p = Q_P_number; p >= 0; p--)
  {
    for(q = p; q >= 0; q--)
    {
      gap = (int)(pow(2, p - q) * pow(3, q));
      for(j = 0; j < Size - gap; j++)
      {
        for(k = 0; k < Size - j - gap; k += gap)
        {
          *N_Comp += 1;
          if(Array[k] > Array[k + gap])
          {
            temp = Array[k];
            Array[k] = Array[k + gap];
            Array[k + gap] = temp;
            *N_Move += 3;
          }
        }
      }
    }
  }
}
/////////////////////////////////////////
//the Seq_1
int Print_Seq_1(char *Filename, int Size)
{
//open file
  FILE *write_file;
  write_file = fopen(Filename, "w");

/////////////////////
//calculate seq//////
  int T_number;
  T_number = (log(Size + 1)) / (log(2));
  int i;
  fprintf(write_file, "%d", T_number);
  for(i = 1; i <= T_number; i++)
  {
    fprintf(write_file, "\n%d", (int)(pow(2, i) - 1));
  }
  fprintf(write_file, "\n");
/////////////////////
//close the file/////
  fclose(write_file);
  return 1;
}

/////////////////////////////////////////
//the seq_2
int Print_Seq_2(char *Filename, int Size)
{
  //open file
  FILE *write_file;
  write_file = fopen(Filename, "w");

/////////////////////
//calculate seq//////
  int Q_P_number;
  Q_P_number = (log(Size) / log(3));

  int T_number;
  T_number = ((Q_P_number + 2) * (Q_P_number + 1)) / 2;
  fprintf(write_file, "%d\n", T_number);
  
  int p, q; 
  for(p = 0; p <= Q_P_number; p++)
  {

    for(q = 0; q <= p; q++)
    {
      fprintf(write_file, "%d\n", (int)(pow(2, p - q) * pow(3, q)));
    }
  }
  
/////////////////////
//close the file/////
  fclose(write_file);
  return 1;
}
