#ifdef _WIN32 // solo para SO windows
#include <windows.h>
#endif
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#define SIZE 256

extern int bandera_sistema_trigonometrico;

void menu();
void menu_angulos();
char *convertir_a_postfija(char *expresion_infija, char *buffer_postfija);
double calcular(char *expresion_postfija);
int is_operator(char c);
int comparar(char top, char operando_expresion);
void limpiar_pantalla();
char *log_or_trigo(char *str);