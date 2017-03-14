//Includes
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Macros/Constants
#ifndef MAX_BUFFER_SIZE
#define MAX_BUFFER_SIZE 256
#endif

#ifndef MAX_STRING_SIZE
#define MAX_STRING_SIZE 2048
#endif

//Global variables
char** matrix;
static char string[MAX_STRING_SIZE];

//Functions
static int read_file(const char*, int*, int*);
static void fill_matrix(int, int);
static void print_matrix(int, int);

int main(int argc, const char* argv[])
{
  int rows, colums;

  if(read_file(argv[1], &rows, &colums) == -1)
  {
    printf("No se pudo abrir el archivo o el mismo no existe.\n");
    return 0;
  }

  fill_matrix(rows, colums);
  print_matrix(rows, colums);

  return 0;
}

static int read_file(const char* file_name, int* rows, int* colums)
{
  FILE* file = fopen(file_name, "r");
  char buffer[MAX_BUFFER_SIZE];

  if (!file)
    return -1;

  while(!feof(file))
  {
    fgets(buffer, sizeof(buffer), file);
    strcat(string, buffer);
    *rows += 1;
  }

  *colums = strlen(buffer);

  fclose(file);
  return 0;
}

static void fill_matrix(int rows, int colums)
{
  unsigned int i, j, string_index = 0;
  matrix = (char**) malloc(sizeof(char*) * rows);

  for(i = 0; i < rows; i++)
    matrix[i] = (char*) malloc(sizeof(char) * colums);

  for(i = 0; i < rows; i++)
  {
    for(j = 0; j < colums; j++)
    {
      if(string[string_index] != '\n')
        matrix[i][j] = string[string_index];

      string_index++;
    }
  }
}

static void print_matrix(int rows, int colums)
{
  unsigned int i, j;

  for(i = 0; i < rows; i++)
  {
    for(j = 0; j < colums; j++)
      printf("%c", matrix[i][j]);

    printf("\n");
  }
}
