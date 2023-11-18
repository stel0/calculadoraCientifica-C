#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define SIZE 256

void menu();
char* convertir_a_postfija(char * expresion_infija, char * buffer_postfija);
void calcular(char * expresion_postfija);  
int is_operator(char c);
int comparar(char top, char operando_expresion);
void limpiar_pantalla();