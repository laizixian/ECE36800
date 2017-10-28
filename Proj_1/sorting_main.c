#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <time.h>


long *Load_File(char *Filename, int *Size);
int Save_File(char *Filename, long *Array, int Size);
void Shell_Insertion_Sort_Seq1(long *Array, int Size, double *N_Comp, double *N_Move);
void Shell_Insertion_Sort_Seq2(long *Array, int Size, double *N_Comp, double *N_Move);

void Shell_Bubble_Sort_Seq1(long *Array, int Size, double *N_Comp, double *N_Move);
void Shell_Bubble_Sort_Seq2(long *Array, int Size, double *N_Comp, double *N_Move);

int Print_Seq_1(char *Filename, int Size);
int Print_Seq_2(char *Filename, int Size);

int main(int argc, char **argv)
{
  if(argc != 6)
  {
    fprintf(stderr, "Wrong number of arguments\n");
    return EXIT_FAILURE;
  }

  long *Array;
  int Size;

  double N_Comp = 0;
  double N_Move = 0;

  double time_1 = 0;
  double time_2 = 0;

  double I_O_time = 0;

  double Sorting_time = 0;

  time_1 = clock();
  Array = Load_File(argv[3], &Size);
  time_2 = clock();
  
  I_O_time += (time_2 - time_1);
  

  if(strcmp(argv[1],"1") == 0)
  {
    time_1 = clock();
    Print_Seq_1(argv[4], Size);
    time_2 = clock();
    I_O_time += (time_2 - time_1);

    if(strcmp(argv[2],"i") == 0)
    {
      time_1 = clock();
      Shell_Insertion_Sort_Seq1(Array, Size, &N_Comp, &N_Move);
      time_2 = clock();
      Sorting_time += (time_2 - time_1);
    }
    else if(strcmp(argv[2],"b") == 0)
    {
      time_1 = clock();
      Shell_Bubble_Sort_Seq1(Array, Size, &N_Comp, &N_Move);
      time_2 = clock();
      Sorting_time += (time_2 - time_1);
    }
  }

  else if(strcmp(argv[1],"2") == 0)
  {
    time_1 = clock();
    Print_Seq_2(argv[4], Size);
    time_2 = clock();
    I_O_time += (time_2 - time_1);

    if(strcmp(argv[2],"i") == 0)
    {
      time_1 = clock();
      Shell_Insertion_Sort_Seq2(Array, Size, &N_Comp, &N_Move);
      time_2 = clock();
      Sorting_time += (time_2 - time_1);

    }
    else if(strcmp(argv[2],"b") == 0)
    {
      time_1 = clock();
      Shell_Bubble_Sort_Seq2(Array, Size, &N_Comp, &N_Move);
      time_2 = clock();
      Sorting_time += (time_2 - time_1);
    }
  }


  else
  {
    fprintf(stderr, "invalid Seq\n");
  }

  time_1 = clock();
  Save_File(argv[5], Array, Size);
  time_2 = clock();
  I_O_time += (time_2 - time_1);

  fprintf(stdout, "Number of comparisons: %le\n", N_Comp);
  fprintf(stdout, "Number of moves: %le\n", N_Move);
  fprintf(stdout, "I/O time [sec]: %le\n", (I_O_time / CLOCKS_PER_SEC));
  fprintf(stdout, "Sorting time [sec]: %le\n", (Sorting_time / CLOCKS_PER_SEC));

  free(Array);
  return EXIT_SUCCESS;
}
