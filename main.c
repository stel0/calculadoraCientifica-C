#include "main.h"
#include "stack/pila.h"

int bandera_sistema_trigonometrico = 3; // 3 radianes 6 sexagesimales
int main()
{
    double result = 0.0;
    char expresion_infija[SIZE];
    char expresion_postfija[SIZE];
    *expresion_infija = '\0'; // inicializar la cadena como vacía
    memset(expresion_postfija, '\0', SIZE); // vaciar la cadena

    int op = 0;               // opción del menu
    int op_trig = 0;          // opción de sistema trigonometrico

    while (op != 4)
    {

        printf("\nCalculando en ");
        if (bandera_sistema_trigonometrico == 3)
        {
            printf("radianes\n");
        }
        else
        {
            printf("grados\n");
        }

        if (strlen(expresion_infija) != 0)
        {
            printf("Expresión ingresada: %s\n", expresion_infija);
        }

        menu();
        if (scanf("%d", &op) != 1 || op < 1 || op > 4)
        {
            limpiar_pantalla(); // limpiar terminal para no tener operaciones acumuladas
            printf("Opción elegida --> %d inválida. Por favor, elige una opción válida (1-4).\n", op);
            while (getchar() != '\n')
                ; // Limpiar el búfer del teclado
            continue;
        }

        switch (op)
        {
        case 1:
            limpiar_pantalla();  // limpiar terminal para no tener operaciones acumuladas
            printf("Ingrese la expresión infija: ");
            scanf("%255s", expresion_infija); //limite de 255 caracteres
            break;
        case 2:
            limpiar_pantalla(); // limpiar terminal para no tener operaciones acumuladas
            // Realiza la conversión y cálculo si se ha ingresado una expresión correcta
            if (strlen(expresion_infija) != 0)
            {
                char *response = convertir_a_postfija(expresion_infija, expresion_postfija);

                if (strcmp(response, "ERROR1") == 0){
                    printf("\n\nError de sintaxis\n\n");
                    memset(expresion_postfija, '\0', SIZE); // vaciar la cadena
                }
                else if (strcmp(response, "ERROR2") == 0){
                    printf("\n\nError de cálculo\n\n");
                    memset(expresion_postfija, '\0', SIZE); // vaciar la cadena
                }
                else if (response != NULL ){
                    result = calcular(expresion_postfija);
                    if (result){
                        imprimir_digitos_significativos(result); // imprime el resultado
                    }
                    else{
                        printf("\n\nError de cálculo\n\n");
                        memset(expresion_postfija, '\0', SIZE); // vaciar la cadena
                    }
                    
                } 
                else{
                    memset(expresion_postfija, '\0', SIZE); // vaciar la cadena
                }
                    
            }

            else
            {
                printf("\nNo se ha ingresado una expresión.\n");
            }
            
            break;
        case 3:
            limpiar_pantalla(); // limpiar terminal para no tener operaciones acumuladas
            menu_angulos();

            if (scanf("%d", &op_trig) != 1 || op_trig < 1 || op_trig > 3)
            {
                limpiar_pantalla(); // limpiar terminal para no tener operaciones acumuladas
                printf("Opción elegida --> %d inválida. Por favor, elige una opción válida (1-3).\n", op_trig);
                while (getchar() != '\n')
                    ; // Limpiar el búfer del teclado
            }

            switch (op_trig)
            {
            case 1:
                bandera_sistema_trigonometrico = 6;
                break;
            case 2:
                bandera_sistema_trigonometrico = 3;
                break;
            case 3:
                break; // salir de la función sin cambios
            default:
                printf("Opción inválida, se mantendrá el sistema del ángulo\n");
                break;
            }
            limpiar_pantalla();  // limpiar terminal para no tener operaciones acumuladas
            break;
        case 4:
            exit(0);
        default:
            printf("Opción inválida\n");
            break;
        }

    } // fin while

    return 0;
}

