#include "main.h"
#include "stack/pila.h"

void menu()
{
  printf("\nMenu\n");
  printf("1. Ingresar expresion\n");
  printf("2. Calcular\n");
  printf("3. Cambiar sistema angular\n");
  printf("4. Salir\n");
}

void menu_angulos()
{
  printf("Sistema angular\n");
  printf("1. Grados\n");
  printf("2. Radianes\n");
  printf("3. No realizar cambios\n");
}

char *log_or_trigo(char *str)
{
  double res = 0; // Resultado
  double pi = 3.141592653589793;
  static char aux[20];         // un auxiliar mas
  memset(aux, 0, sizeof(aux)); // Inicializa el arreglo aux con '\0'

  while (*str >= 'a' && *str <= 'z')
  {
    strncat(aux, str, 1); // copiamos cada caracter para saber a que función pertenece i.e. log, sin o sqrt
    str++;
  }      // sale del while al encontrar el primer paréntesis '('

  if (*str != '(') // si no hay paréntesis '(' antes del valor a operar i.e. log10) o tan87)
  {
    static char error[] = "ERROR1\0";
    return error;
  }
  else
    str++; // se avanza al primer número en la expresión

  // convertir de letras a enteros
  while (*str != ')')
  {
    //(res*10) define el orden del entero a convertir
    //(*str - '0') convierte un caracter numérico ASCII a un entero
    res = (res * 10) + (*str - '0');
    str++;
    if (*str == '('){
      static char error[] = "ERROR1\0";
      return error;
    }
  }

  if (strcmp(aux, "sqrt") == 0){
    if (res < 0){
      static char error[] = "ERROR2\0";
      return error;
    }
    else
      res = sqrt(res);
  }
  

  else if (strcmp(aux, "ln") == 0){
    res = log(res);
  }

  else if (strcmp(aux, "log") == 0)
    res = log10(res);

  // la precisión de los números en los cálculos varía
  else if (bandera_sistema_trigonometrico == 6){ // para cálculos en grados

    // [res * pi / 180.0] convierte 'res' grados sexagesimales a radianes
    // las funciones trigonométricas de math.h operan en ese sistema
    if (strcmp(aux, "sin") == 0){
      res = sin(res * pi / 180.0);
    }

    else if (strcmp(aux, "cos") == 0){
      res = cos(res * pi / 180.0);
    }

    else if (strcmp(aux, "tan") == 0){

      if (res == 90 || res == 270){
        static char error[] = "ERROR2\0";
        return error;
      }
      
      else
        res = tan(res * pi / 180.0);
    }
    else{
      static char error[] = "ERROR1\0";
      return error;
    }

  } // fin de if

  else if (bandera_sistema_trigonometrico == 3)
  { // para cálculos en radianes

    if (strcmp(aux, "sin") == 0)
      res = sin(res);
    else if (strcmp(aux, "cos") == 0)
      res = cos(res);
    else if (strcmp(aux, "tan") == 0)
      res = tan(res);
    else{
      static char error[] = "ERROR1\0";
      return error;
    }

  } // fin de else if



  // convertir de enteros a letras y guardamos en aux
  sprintf(aux, "%.14f", res); // precisión aproximada de tipo de dato double
  return aux;
}

void limpiar_pantalla()
{
#ifdef _WIN32 // solo para SO windows
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
    // si es un operando copia el operando al buffer o si es un numero con coma
    while (*expresion_infija >= '0' && *expresion_infija <= '9' || *expresion_infija == '.')
    {                                                             // si es un operando
      buffer_postfija[contador_postfijo++] = *expresion_infija++; // se guarda en el buffer
    }                                                             // fin if

    buffer_postfija[contador_postfijo++] = ' '; // se separan los operandos con espacios

    // si es un caracter de agrupación
    if (*expresion_infija == ')')
    {

      while (!emptyS(p) && top(p) != '(') // mientras el tope de la pila no sea el inicio de agrupación
      {
        buffer_postfija[contador_postfijo++] = removeS(&p); // cargar los operadores al buffer y sacarlos  de la pila
        buffer_postfija[contador_postfijo++] = ' ';
      } // fin while

      // para validar la entrada
      if (emptyS(p)){ // si la pila esta vacia
        static char error[] = "ERROR1\0";
        return error;
      } // fin if

      else
        removeS(&p); // sacar el '(' de la pila

    }              // fin else 

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
          buffer_postfija[contador_postfijo++] = ' ';
        } // fin while

        // si la pila esta vacía o el operador leído es de mayor precedencia
        // que el tope de la pila, meter a la pila
        if (emptyS(p) || comparar(top(p), *expresion_infija))
          insertS(&p, expresion_infija);
      } // fin else

    } // fin else if

    // caso de seno, coseno, tangente o logaritmo
    else if (*expresion_infija >= 'a' && *expresion_infija <= 'z') // si en la expresion hay una letra
    {
      char *res = log_or_trigo(expresion_infija); // devuelve el valor de sen, cos, tan,ln o log en una cadena
      if (strcmp(res, "ERROR1") == 0){
        static char error[] = "ERROR1\0";
        return error; 
      }
      else if (strcmp(res, "ERROR2") == 0){
        static char error[] = "ERROR2\0";
        return error; 
      }
      while (*res != '\0')                        // mientras no se haya llegado al final
      {
        buffer_postfija[contador_postfijo++] = *res; // copiamos cada caracter de res al buffer
        res++;                                       // avanzamos el puntero
      }
      buffer_postfija[contador_postfijo++] = ' ';

      while (*expresion_infija != ')')
      {
        expresion_infija++; // avanzamos el puntero de expresion infija hasta el final de sen(), cos(), tan(), ln() o log()
      }
    }
    *expresion_infija++; // avanzar la expresión
  }                      // fin while

  // al evaluar toda la expresión, sacar todos los elementos de la pila
  while (!emptyS(p))
  { // mientras la pila no esté vacia

    if(top(p) == '('){//si son parentesis
      removeS(&p);//sacar de la pila
    }
      buffer_postfija[contador_postfijo++] = removeS(&p);
      buffer_postfija[contador_postfijo++] = ' ';

  }

  buffer_postfija[contador_postfijo] = '\0'; // terminar la cadena
  free(p);                                   // liberar memoria asignada a la pila

  return buffer_postfija;
}

void calcular(char *expresion_postfija)
{
  double operandos[strlen(expresion_postfija)]; // lista de operandos
  operandos[strlen(expresion_postfija)] = '\0';//inicializar la pila vacía
  int b; // bandera para saber si hay un numero negativo
  int i = 0; // contador de operandos
  char *eValue; // puntero que apunta al valor de la expresión
  eValue = strtok(expresion_postfija, " "); // apunta al primer valor de la expresion postfija
  /* strtok() coloca un NULL despues de la primera palabra, seguido del NULL le sigue la siguiente palabra que viene despues de la primera palabra  */

  while (eValue != NULL ) // eValue no es NULL
  {
    b = 0;
    if (!is_operator(*eValue)) // si no es un operador 
    {
      operandos[i] = atof(eValue); // cargar en la lista
      i++; // incrementar el contador
    }
    else 
    {
      // si es un operador hacer los calculos con la lista
      switch (*eValue)
      {
      case '+':
        operandos[i - 2] = operandos[i - 2] + operandos[i - 1];
        break;

      case '-':
        if ((i-1) == 0) // si hay un solo elemento en la lista quiere decir que ese numero es negativo
        {
          operandos[i-1] = operandos[i-1] * (-1); // asignamos a ese numero el valor negativo
          b = 1;
        }else{
          operandos[i - 2] = operandos[i - 2] - operandos[i - 1];
        }
        break;

      case '*':
        operandos[i - 2] = operandos[i - 2] * operandos[i - 1];
        break;

      case '/':
        
        operandos[i - 2] = operandos[i - 2] / operandos[i - 1];
        break;

      case '^':
        operandos[i - 2] = pow(operandos[i - 2], operandos[i - 1]);
        break;

      default:
        break;
      }
      // si no se ingreso un numero negativo
      if(b != 1){
        i = i - 1; // el indice se ubica despues del ultimo valor para poder ingresar en esa posicion el nuevo elemento
      }
    }
    eValue = strtok(NULL, " "); //avanzamos el puntero al siguiente valor de expresion postfija
    /* strtok(NULL," ") busca la siguiente palabra en este caso al final de la primera palabra */
  }
  printf("\n");
  printf("El resultado es: %lf\n", operandos[0]); // imprime el resultado
  //printf("\n");
}
