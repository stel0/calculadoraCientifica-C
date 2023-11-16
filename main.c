#include "main.h"
#include "stack/pila.h"

int main(){
    char expresion_infija[SIZE];
    int op = 0;
    *expresion_infija = '\0';//inicializar la cadena como vacía

    while (op != 3) {
        if (strlen(expresion_infija) != 0) {
            printf("Expresión: %s\n", expresion_infija);
        }

        menu();
        if (scanf("%d", &op) != 1 || op < 1 || op > 3) {
            printf("Opción inválida. Por favor, elige una opción válida (1-3).\n");
            while (getchar() != '\n'); // Limpiar el búfer del teclado
            continue;
        }

        switch(op){
            case 1:
                printf("Ingrese la expresión infija: ");
                scanf("%s", expresion_infija); // Tener en cuenta el posible desbordamiento
                // Controlar sintaxis válida de la expresión
                break;
            case 2:
                // Realiza la conversión y cálculo si se ha ingresado una expresión correcta
                if (strlen(expresion_infija) != 0) {
                    char *expresion_postfija = convertir_a_postfija(expresion_infija);
                    calcular(expresion_postfija);
                } else {
                    printf("No se ha ingresado ninguna expresión.\n");
                }
                break;
            case 3:
                exit(0);
            default:
                printf("Opción inválida\n");
                break;
        }
    }

    return 0;
}