#include <stdio.h>
#include <stdlib.h>     
#include "artemis.h"


// Pide un numero entero entre minimo y maximo
int leerEntero(char mensaje[], int minimo, int maximo)
{
    int valor;
    int leidos;
    int lineaLimpia;
    int c;
    int valido;

    do {
        valido = 0;
        printf("  %s [%d a %d]: ", mensaje, minimo, maximo);
        leidos = scanf("%d", &valor);

        if (leidos == EOF) {
            printf("\n  Se cerro la entrada de datos. Fin del programa.\n");
            exit(1);
        }

        
        lineaLimpia = 1;
        c = getchar();
        while (c != '\n' && c != EOF) {
            lineaLimpia = 0;
            c = getchar();
        }

        if (leidos != 1 || lineaLimpia == 0) {
            printf("  [ERROR] Ingrese solo un numero entero (sin letras ni simbolos).\n");
        } else if (valor < minimo || valor > maximo) {
            printf("  [ERROR] Valor fuera de rango.\n");
        } else {
            valido = 1;
        }
    } while (valido == 0);

    return valor;
}

{
    double valor;
    int leidos;
    int lineaLimpia;
    int c;
    int valido;

    do {
        valido = 0;
        printf("  %s [%.2f a %.2f]: ", mensaje, minimo, maximo);
        leidos = scanf("%lf", &valor);

        if (leidos == EOF) {
            printf("\n  Se cerro la entrada de datos. Fin del programa.\n");
            exit(1);
        }

        lineaLimpia = 1;
        c = getchar();
        while (c != '\n' && c != EOF) {
            lineaLimpia = 0;
            c = getchar();
        }

        if (leidos != 1 || lineaLimpia == 0) {
            printf("  [ERROR] Ingrese solo un numero (use punto decimal, ej: 6.5).\n");
        } else if (!(valor >= minimo && valor <= maximo)) {
            printf("  [ERROR] Valor fuera de rango.\n");
        } else {
            valido = 1;
        }
    } while (valido == 0);

    return valor;
double energiaCinetica(double masa, double velocidad)
{
    return 0.5 * masa * velocidad * velocidad;
}

void calcularResultados(Mision *m)
{
    double desnivel;
    double kImpacto;


    desnivel        = m->altInicial - m->altParacaidas;
    m->kInicial     = energiaCinetica(m->masa, m->velInicial);
    m->kFinal       = energiaCinetica(m->masa, m->velParacaidas);
    m->deltaK       = m->kFinal - m->kInicial;
    m->trabajoPeso  = m->masa * GRAVEDAD * desnivel;
    m->trabajoRoz   = m->deltaK - m->trabajoPeso;

    
    m->aMedia  = (m->velInicial - m->velParacaidas) / m->tiempoFrenado;
    m->aMediaG = m->aMedia / GRAVEDAD;

    
    m->peso       = m->masa * GRAVEDAD;
    kImpacto      = energiaCinetica(m->masa, m->velImpacto);
    m->fProm      = m->peso + kImpacto / m->profundidad;
    m->fPromPesos = m->fProm / m->peso;
}


int clasificarAngulo(double gamma)
{
    int clase;

    if (gamma > GAMMA_MAX) {
        clase = ANGULO_EMPINADO;
    } else if (gamma < GAMMA_MIN) {
        clase = ANGULO_RASANTE;
    } else {
        clase = ANGULO_SEGURO;
    }
    return clase;
}