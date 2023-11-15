#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SIZE 256
typedef char datatype;

typedef struct
{
  datatype data[SIZE];
  int count;
}Stack;

void insertS(Stack **s, datatype * x);
datatype removeS(Stack **s);
void printS(Stack *s);
int emptyS(Stack *s);
int fullS(Stack *s);
int sizeS(Stack *s);
Stack *createS();
