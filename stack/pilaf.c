#include "pila.h"

Stack * createS(){
  Stack * s = (Stack *)malloc(sizeof(Stack));
  s -> count = 0;
  printf("Pila creada\n");
  return s;
}

int fullS(Stack * s){
  return s->count == SIZE;
}

int emptyS(Stack *s){
  return s->count == 0;
}

void insertS(Stack ** s, datatype * x){
  if(fullS(*s)){
    printf("La pila esta llena, no se puede agregar mas (insertS)\n");
    exit(1);
  }
  int i = (*s)->count;
  (*s)->data[i] =  *x;
  (*s)->count++;
  return;
}

datatype removeS(Stack **s)
{
 /*  printf("\npila.lon = %ld\n",sizeS(*s)); */
  if(emptyS(*s)){
    printf("La pila esta vacia, no se puede eliminar nada\n");
    exit(1);
  }
  /* printf("\ncount - 1 = %ld\n",((*s)->count)-1); */
  datatype  res = (*s) ->data[((*s)->count) - 1 ];
  (*s) ->count--;
  return res;
}

void printS(Stack *s){
  int i;
  for(i=0;i<s->count;i++){
    printf("%c->",s->data[i]);
  }
}

int sizeS(Stack *s){
  return  s->count;
}