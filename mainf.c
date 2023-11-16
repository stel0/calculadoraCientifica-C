#include "main.h"
#include "stack/pila.h"

void menu(){
    printf("1. Ingresar expresion\n");
    printf("2. Calcular\n");
    printf("3. Salir\n");
}

int is_operator(char c){
  char *operadores_algebraicos = "+-*^/";

  if (strchr(operadores_algebraicos, c) != NULL)
    return 1;

  else
    return 0;

}

// precedencia expresión vs top -> 0 menor o igual;  1 mayor
int comparar(char top, char operando_expresion){
  int precedencia_expresion;
  int precedencia_top;

  switch (operando_expresion){
    case '+': case '-':
      precedencia_expresion = 0;
      break;
    case '*': case '/':
      precedencia_expresion = 1;
      break;
    case '^':
      precedencia_expresion = 2;
      break;
  }

  switch (top){
    case '+': case '-':
      precedencia_top = 0;
      break;
    case '*': case '/':
      precedencia_top = 1;
      break;
    case '^':
      precedencia_top = 2;
      break;
  } 

  if (precedencia_expresion > precedencia_top)
    return 1;
  
  else
    return 0;

}

char* convertir_a_postfija(char * expresion_infija){
  Stack * p = createS();
  char buffer_postfija [SIZE];
  int contador_postfijo = 0;//cantidad de elementos en el buffer

  while (*expresion_infija != '\0'){

    if (*expresion_infija >= '0' && *expresion_infija <= '9'){//si es un operando
      buffer_postfija[contador_postfijo++] = *expresion_infija;//se guarda en el buffer
    }//fin if

    else if ( is_operator(*expresion_infija) ){//si es operador algebraico

      if (emptyS(p)){//si la pila esta vacia
        insertS(&p, expresion_infija);//meter el primer operador a la pila
      }//fin if

      else{

        //mientras la pila no esté vacía
        //y el operador leído sea de menor o igual precedencia que el tope de la pila
        while(!emptyS(p) && !(comparar(top(p), *expresion_infija))){
          //sacar el tope de la pila y volver a comparar el operador leido
          buffer_postfija[contador_postfijo++] = removeS(&p);
        }//fin while
        
        //si la pila esta vacía o el operador leído es de mayor precedencia
        //que el tope de la pila, meter a la pila 
        if (emptyS(p) || comparar(top(p), *expresion_infija))
          insertS(&p, expresion_infija);

      }//fin else

    }//fin else if

      *expresion_infija++;//avanzar la expresión
    }//fin while 

    //al evaluar toda la expresión, sacar todos los elementos de la pila
    while (!emptyS(p)){//mientras la pila no esté vacia
      buffer_postfija[contador_postfijo++] = removeS(&p);
    }

    buffer_postfija[contador_postfijo]='\0';//terminar la cadena
    printf("Expresion Postfija: %s\n", buffer_postfija);
}

void calcular (char * expresion_postfija){

}

