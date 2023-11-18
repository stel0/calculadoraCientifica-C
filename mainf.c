#include "main.h"
#include "stack/pila.h"

void menu()
{
  printf("1. Ingresar expresion\n");
  printf("2. Calcular\n");
  printf("3. Salir\n");
}

#ifdef _WIN32
#include <windows.h>
#endif

char * log_or_trigo(char *str)
{
  double res = 0; // Resultado
  float pi = 3.141592653589793;
  static char word[10]; // un auxiliar mas
  memset(word, 0, sizeof(word)); // Inicializa el arreglo word con '\0'
  
  while (*str >= 'a' && *str <= 'z')
  {
    strncat(word, str, 1); // copiamos cada caracter para saber a que función pertenece
    str++;
  }
  str++;

  // convertir de letras a enteros
  while (*str != ')')
  {
    res = (res * 10) + (*str - '0');
    str++;
  }

  if (strcmp(word, "ln") == 0)
    res = log(res);
  else if (strcmp(word, "log") == 0)
    res = log10(res);
  else if (strcmp(word, "sin") == 0)
    res = sin(res * pi / 180.0);
  else if (strcmp(word, "cos") == 0)
    res = cos(res * pi / 180.0);
  else if (strcmp(word, "tan") == 0){
    res = tan(res * pi / 180.0);
  }

  // convertir de enteros a letras y guardamos en word
  sprintf(word,"%.2f",res);
  
  return word; 
}

void limpiar_pantalla()
{
#ifdef _WIN32
  system("cls");
#else
  system("clear");
#endif
}

int is_operator(char c)
{
  char *operadores_algebraicos = "+-*^/(";

  if (strchr(operadores_algebraicos, c) != NULL)
    return 1;

  else
    return 0;
}

// precedencia expresión vs top -> 0 menor o igual;  1 mayor
int comparar(char top, char operando_expresion)
{
  int precedencia_expresion;
  int precedencia_top;

  switch (operando_expresion)
  {
  case '+':
  case '-':
    precedencia_expresion = 0;
    break;
  case '*':
  case '/':
    precedencia_expresion = 1;
    break;
  case '^':
    precedencia_expresion = 2;
    break;
  case '(':
    precedencia_expresion = 3; // siempre meter a la pila el paréntesis abierto
  }

  switch (top)
  {
  case '+':
  case '-':
    precedencia_top = 0;
    break;
  case '*':
  case '/':
    precedencia_top = 1;
    break;
  case '^':
    precedencia_top = 2;
    break;
  case '(':
    precedencia_top = -1; // siempre agregar a la pila operadores a la derecha de parentesis
  }

  if (precedencia_expresion > precedencia_top)
    return 1;

  else
    return 0;
}

char *convertir_a_postfija(char *expresion_infija, char *buffer_postfija)
{
  Stack *p = createS();
  int contador_postfijo = 0; // cantidad de elementos en el buffer

  while (*expresion_infija != '\0')
  {

    while (*expresion_infija >= '0' && *expresion_infija <= '9')
    {                                                             // si es un operando
      buffer_postfija[contador_postfijo++] = *expresion_infija++; // se guarda en el buffer
    }                                                             // fin if

    buffer_postfija[contador_postfijo++] = ' '; // se separan los operandos con espacios

    if (*expresion_infija == ')')
    { // si es un caracter de fin de agrupación

      // este if de acá no estoy seguro de que sea uy útil, para validar la entrada capaz
      if (emptyS(p))
      { // si la pila esta vacia
        exit(1);
      } // fin if

      while (!emptyS(p) && top(p) != '(')
      { // mientras el tope de la pila no sea el inicio de agrupación
        // cargar los operadores al buffer y sacarlos  de la pila
        buffer_postfija[contador_postfijo++] = removeS(&p);
      } // fin while

      removeS(&p); // sacar el '(' de la pila
    }              // fin else if

    else if (is_operator(*expresion_infija))
    { // si es operador algebraico

      if (emptyS(p) && *expresion_infija != '\0')
      {                                // si la pila esta vacia
        insertS(&p, expresion_infija); // meter el primer operador a la pila
      }                                // fin if

      else
      {

        // mientras la pila no esté vacía
        // y el operador leído sea de menor o igual precedencia que el tope de la pila
        while (!emptyS(p) && !(comparar(top(p), *expresion_infija)))
        {
          // sacar el tope de la pila y volver a comparar el operador leido
          buffer_postfija[contador_postfijo++] = removeS(&p);
        } // fin while

        // si la pila esta vacía o el operador leído es de mayor precedencia
        // que el tope de la pila, meter a la pila
        if (emptyS(p) || comparar(top(p), *expresion_infija))
          insertS(&p, expresion_infija);
      } // fin else

    } // fin else if

    //caso de seno, coseno, tangente o logaritmo
    else if (*expresion_infija >= 'a' && *expresion_infija <= 'z') // si en la expresion hay una letra
    {
      char * res = log_or_trigo(expresion_infija); // devuelve el valor de sen, cos, tan,ln o log en una cadena
      while (*res != '\0') // mientras no se haya llegado al final
      {
        buffer_postfija[contador_postfijo++] = *res; // copiamos cada caracter de res al buffer
        res++;                                     // avanzamos el puntero
      }
      while(*expresion_infija != ')'){
        expresion_infija++; // avanzamos el puntero de expresion infija hasta el final de sen, cos, tan, ln o log
      }
    }
    *expresion_infija++; // avanzar la expresión
  }                      // fin while

  // al evaluar toda la expresión, sacar todos los elementos de la pila
  while (!emptyS(p))
  { // mientras la pila no esté vacia
    buffer_postfija[contador_postfijo++] = removeS(&p);
  }

  buffer_postfija[contador_postfijo] = '\0'; // terminar la cadena
  free(p);                                   // liberar memoria asignada a la pila
  return buffer_postfija;
}

void calcular(char *expresion_postfija)
{
}
