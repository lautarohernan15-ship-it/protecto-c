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
void cargarDatosNominales(Mision *m)
{
    m->masa          = MASA_NOM;
    m->velInicial    = VI_NOM;
    m->altInicial    = HI_NOM;
    m->velParacaidas = VF_NOM;
    m->altParacaidas = HF_NOM;
    m->velImpacto    = VIMPACTO_NOM;
    m->tiempoFrenado = DT_NOM;
    m->profundidad   = PROF_NOM;
    m->gamma         = 6.0;
    m->estado        = EXITO;
    m->puntaje       = 0;
}

void ingresarDatosPropios(Mision *m)
{
    printf("\n--- INGRESO DE DATOS PROPIOS (unidades del SI) ---\n");
    m->masa          = leerReal("Masa (kg)", 1000.0, 100000.0);
    m->velInicial    = leerReal("Velocidad de reingreso vi (m/s)", 1000.0, 15000.0);
    m->altInicial    = leerReal("Altura de reingreso hi (m)", 10000.0, 200000.0);
    m->altParacaidas = leerReal("Altura de paracaidas hf (m)", 100.0, m->altInicial - 1);
    m->velParacaidas = leerReal("Velocidad al abrir paracaidas vf (m/s)", 1.0, m->velInicial - 1);
    m->velImpacto    = leerReal("Velocidad de impacto (m/s)", 0.1, m->velParacaidas);
    m->tiempoFrenado = leerReal("Duracion del frenado (s)", 10.0, 3600.0);
    m->profundidad   = leerReal("Hundimiento en el agua d (m)", 0.1, 10.0);
    printf("\n  Datos cargados correctamente.\n");
}

void mostrarDatos(Mision *m)
{
    printf("\n--- DATOS ACTUALES DE LA MISION ---\n");
    printf("  Masa ..................... %.1f kg\n", m->masa);
    printf("  Velocidad de reingreso ... %.1f m/s (%.0f km/h)\n",
           m->velInicial, m->velInicial * KMH_POR_MS);
    printf("  Altura de reingreso ...... %.1f m\n", m->altInicial);
    printf("  Velocidad paracaidas ..... %.1f m/s\n", m->velParacaidas);
    printf("  Altura paracaidas ........ %.1f m\n", m->altParacaidas);
    printf("  Velocidad de impacto ..... %.1f m/s\n", m->velImpacto);
    printf("  Duracion del frenado ..... %.1f s\n", m->tiempoFrenado);
    printf("  Hundimiento en el agua ... %.2f m\n", m->profundidad);
}
