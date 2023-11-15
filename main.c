#include "main.h"
#include "stack/pila.h"

int main(){
  char exp[SIZE - 1];
  int op = 0;

  while (1)
  {
    if (strlen(exp) != 0)
      printf("Expresion: %s\n", exp);
    menu();
    scanf("%d", &op);
    switch(op){
      case 1:
        scanf("%s", exp);
        break;
      case 2:
        calcular(&exp);
        break;
      case 3:
        exit(0);
    }
  }  
}