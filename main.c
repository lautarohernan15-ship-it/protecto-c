#include <stdio.h>
#include "artemis.h"

int main(void)
{
    Mision datos;
    int opcion;
    int tipo;

    cargarDatosNominales(&datos);

    do {
        printf("\n==================================================\n");
        printf("   SIMULADOR ARTEMIS - REINGRESO Y AMERIZAJE\n");
        printf("==================================================\n");
        printf("  1. Jugar mision de reingreso\n");
        printf("  2. Analisis analitico (incisos a, b, c, d)\n");
        printf("  3. Cambiar datos de la mision\n");
        printf("  4. Reglas del juego\n");
        printf("  0. Salir\n");

        opcion = leerEntero("Opcion", 0, 4);

        switch (opcion) {
            case 1:
                jugarMision(&datos);
                break;
            case 2:
                mostrarAnalisis(&datos);
                break;
            case 3:
                mostrarDatos(&datos);
                printf("\n  1. Usar datos del enunciado\n");
                printf("  2. Ingresar datos propios\n");
                printf("  0. Volver\n");
                tipo = leerEntero("Opcion", 0, 2);
                if (tipo == 1) {
                    cargarDatosNominales(&datos);
                    printf("\n  Datos del enunciado cargados.\n");
                } else if (tipo == 2) {
                    ingresarDatosPropios(&datos);
                }
                break;
            case 4:
                mostrarReglas();
                break;
            case 0:
                printf("\n  Fin del programa. Buen viaje, comandante.\n\n");
                break;
        }
    } while (opcion != 0);

    return 0;
}
