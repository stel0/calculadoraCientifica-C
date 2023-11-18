#include "main.h"
#include "stack/pila.h"

int main(){
    char expresion_infija[SIZE];
    char expresion_postfija[SIZE];
    int op = 0;
    *expresion_infija = '\0';//inicializar la cadena como vacía

    while (op != 3) {
        if (strlen(expresion_infija) != 0) {
            printf("Expresión ingresada: %s\n", expresion_infija);
            printf("Expresión Postfija: %s\n", expresion_postfija);//borrar después 
        }

        menu();
        if (scanf("%d", &op) != 1 || op < 1 || op > 3) {
            limpiar_pantalla();//limpiar terminal para no tener operaciones acumuladas
            printf("Opción elegida --> %d inválida. Por favor, elige una opción válida (1-3).\n", op);
            while (getchar() != '\n'); // Limpiar el búfer del teclado
            continue;
        }

        switch(op){
            case 1:
                limpiar_pantalla() ;//limpiar terminal para no tener operaciones acumuladas
                printf("Ingrese la expresión infija: ");
                scanf("%s", expresion_infija); // Tener en cuenta el posible desbordamiento
                memset(expresion_postfija, '\0', SIZE);//vaciar la cadena
                // Controlar sintaxis válida de la expresión
                break;
            case 2:
                // Realiza la conversión y cálculo si se ha ingresado una expresión correcta
                limpiar_pantalla();//limpiar terminal para no tener operaciones acumuladas
                if (strlen(expresion_infija) != 0) {
                    convertir_a_postfija(expresion_infija, expresion_postfija);
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
        
    }//fin while

    return 0;
}