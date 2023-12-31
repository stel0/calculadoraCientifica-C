#include "pila.h"

Stack * createS(){
  Stack * s = (Stack *)malloc(sizeof(Stack));
  s -> count = 0;
  return s;
}



int emptyS(Stack *s){
  return s->count == 0;//retorna 1 si la pila esta vacia
}

void insertS(Stack ** s, datatype * x){

  int i = (*s)->count;
  
  //no insertar caracter de fin de línea 
  //(puede solucionarse el problema en el flujo de la función en vez de acá?)
  if (*x != '\0'){
    (*s)->data[i] =  *x;
    (*s)->count++;//incrementa la cantidad de elementos
  }

  return;
}

datatype removeS(Stack **s)
{
 /*  printf("\npila.lon = %ld\n",sizeS(*s)); */
  if(emptyS(*s)){
    printf("La pila esta vacia, no se puede eliminar\n");
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
    printf("%c-> ",s->data[i]);
  }
  printf("\n");
}

int sizeS(Stack *s){
  return  s->count;
}

datatype top(Stack *s)
{
  if(emptyS(s)){
    printf("Pila vacía, no hay cima\n");
    exit(1);
  }
  int i = (s) ->count;
  datatype top = (s) -> data[i-1];
  return top;
}
