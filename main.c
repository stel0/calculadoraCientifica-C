#include "main.h"
#include "stack/pila.h"

int main(){
  char expresion_infija[SIZE - 1];
  int op = 0;
  *expresion_infija = '\0';//vaciar residuos en memoria

  while (op != 3)
  {

    if (strlen(expresion_infija) != 0)
      printf("Expresión: %s\n", expresion_infija);

    menu();
    scanf("%d", &op);

    switch(op){
      case 1:
        scanf("%s", expresion_infija);
        //controlar que la sintaxis sea válida
        break;
      case 2:
        char * expresion_postfija = convertir_a_postfija(expresion_infija);
        calcular(expresion_postfija);
        break;
      case 3:
        exit(0);
      default:
        printf("Opción inválida\n");
        op = 0;
        break;
    }//fin switch

  }//fin while

  return 0;
}//fin main