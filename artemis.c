/*
 * artemis.c
 * Implementacion del simulador: validacion de datos, calculos fisicos
 * y las 4 fases de la mision.
 *
 * Fisica: Teorema del Trabajo y la Energia
 *         W_total = W_peso + W_rozamiento = variacion de energia cinetica
 */
#include <stdio.h>
#include <stdlib.h>      /* para exit() */
#include "artemis.h"

/* =====================================================================
 *  1) LECTURA DE DATOS CON VALIDACION
 *  Se repite la pregunta (do-while) hasta que el dato sea valido.
 * ===================================================================== */

/* Pide un numero entero entre minimo y maximo */
int leerEntero(char mensaje[], int minimo, int maximo)
{
    int valor;         /* numero que escribe el usuario                  */
    int leidos;        /* scanf devuelve cuantos datos pudo leer (1 o 0) */
    int lineaLimpia;   /* 1 si despues del numero no habia nada mas      */
    int c;             /* caracter que leemos con getchar                */
    int valido;        /* 1 cuando el dato ya es correcto                */

    do {
        valido = 0;
        printf("  %s [%d a %d]: ", mensaje, minimo, maximo);
        leidos = scanf("%d", &valor);

        /* Si se cierra la entrada (EOF) salimos, si no el bucle seria infinito */
        if (leidos == EOF) {
            printf("\n  Se cerro la entrada de datos. Fin del programa.\n");
            exit(1);
        }

        /* Limpiamos el buffer: leemos con getchar hasta el ENTER.
         * Si encontramos algo antes del ENTER (ej: "5abc"), el dato no sirve. */
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

/* Pide un numero real (con punto decimal) entre minimo y maximo */
double leerReal(char mensaje[], double minimo, double maximo)
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
            /* Se escribe asi (con !) para que tambien rechace "nan" */
            printf("  [ERROR] Valor fuera de rango.\n");
        } else {
            valido = 1;
        }
    } while (valido == 0);

    return valor;
}

/* =====================================================================
 *  2) DATOS DE LA MISION
 * ===================================================================== */

/* Carga los valores del enunciado. 'm' es un puntero: modifica la variable original */
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

/* El usuario escribe sus propios datos. Cada dato depende del anterior
 * para que no haya valores absurdos (ej: velocidad de impacto mayor a la inicial). */
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

/* Muestra los datos actuales (no modifica nada, solo lee) */
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

/* =====================================================================
 *  3) CALCULOS FISICOS
 * ===================================================================== */

/* Energia cinetica: K = 1/2 * m * v^2 */
double energiaCinetica(double masa, double velocidad)
{
    return 0.5 * masa * velocidad * velocidad;
}

/*
 * Resuelve los incisos a), b) y c).
 *
 * a) W_total = delta K   y   W_total = W_peso + W_roz
 *    => W_roz = delta K - W_peso
 *    con W_peso = m * g * (hi - hf)   (positivo porque la nave baja)
 *
 * b) a = (vi - vf) / tiempo
 *
 * c) En el agua: (m*g - F) * d = 0 - K_impacto
 *    => F = m*g + K_impacto / d
 */
void calcularResultados(Mision *m)
{
    double desnivel;     /* cuanto baja la nave: hi - hf */
    double kImpacto;     /* energia cinetica al tocar el agua */

    /* a) Trabajo del rozamiento */
    desnivel        = m->altInicial - m->altParacaidas;
    m->kInicial     = energiaCinetica(m->masa, m->velInicial);
    m->kFinal       = energiaCinetica(m->masa, m->velParacaidas);
    m->deltaK       = m->kFinal - m->kInicial;
    m->trabajoPeso  = m->masa * GRAVEDAD * desnivel;
    m->trabajoRoz   = m->deltaK - m->trabajoPeso;

    /* b) Desaceleracion media */
    m->aMedia  = (m->velInicial - m->velParacaidas) / m->tiempoFrenado;
    m->aMediaG = m->aMedia / GRAVEDAD;

    /* c) Fuerza promedio en el amerizaje */
    m->peso       = m->masa * GRAVEDAD;
    kImpacto      = energiaCinetica(m->masa, m->velImpacto);
    m->fProm      = m->peso + kImpacto / m->profundidad;
    m->fPromPesos = m->fProm / m->peso;
}

/* Dice si el angulo esta dentro de la ventana de seguridad */
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

/* Inciso d): consecuencias fisicas segun el angulo */
void explicarAngulo(int clase)
{
    if (clase == ANGULO_EMPINADO) {
        printf("  gamma > %.1f grados: DESACELERACION EXCESIVA\n", GAMMA_MAX);
        printf("   - La capsula entra muy rapido a capas densas de aire.\n");
        printf("   - La fuerza de rozamiento crece mucho y la energia cinetica\n");
        printf("     se disipa en muy poco tiempo.\n");
        printf("   - La tripulacion soportaria demasiados g y el escudo termico\n");
        printf("     podria sobrecalentarse.\n");
    } else if (clase == ANGULO_RASANTE) {
        printf("  gamma < %.1f grados: REBOTE ATMOSFERICO\n", GAMMA_MIN);
        printf("   - La capsula roza la atmosfera sin penetrarla lo suficiente.\n");
        printf("   - El trabajo del rozamiento no alcanza para frenarla.\n");
        printf("   - Rebota hacia el espacio con mucha energia cinetica y no\n");
        printf("     puede volver a la Tierra de forma segura.\n");
    } else {
        printf("  %.1f <= gamma <= %.1f grados: VENTANA SEGURA\n", GAMMA_MIN, GAMMA_MAX);
        printf("   - La desaceleracion es soportable y la capsula no rebota.\n");
    }
}

/* =====================================================================
 *  4) ANALISIS ANALITICO (incisos a, b, c, d)
 * ===================================================================== */

void mostrarAnalisis(Mision *m)
{
    double gamma;
    int clase;

    calcularResultados(m);

    printf("\n=========== ANALISIS ANALITICO ===========\n");

    printf("\na) Trabajo de la fuerza de rozamiento\n");
    printf("   K inicial = 1/2*m*vi^2 = %.4e J\n", m->kInicial);
    printf("   K final   = 1/2*m*vf^2 = %.4e J\n", m->kFinal);
    printf("   delta K   = %.4e J\n", m->deltaK);
    printf("   W peso    = m*g*(hi-hf) = %.4e J\n", m->trabajoPeso);
    printf("   W roz = delta K - W peso = %.4e J\n", m->trabajoRoz);
    printf("   (es negativo: el aire le quita energia a la capsula)\n");

    printf("\nb) Desaceleracion media (fase de %.0f s)\n", m->tiempoFrenado);
    printf("   a = (vi - vf) / t = %.3f m/s^2\n", m->aMedia);
    printf("   a = %.3f veces g\n", m->aMediaG);

    printf("\nc) Fuerza promedio del agua en el amerizaje\n");
    printf("   Peso = m*g = %.1f N\n", m->peso);
    printf("   F = m*g + (1/2*m*v^2)/d = %.1f N\n", m->fProm);
    printf("   F = %.3f veces el peso de la nave\n", m->fPromPesos);

    printf("\nd) Angulo de reingreso\n");
    explicarAngulo(ANGULO_EMPINADO);
    explicarAngulo(ANGULO_RASANTE);
    printf("\n  Pruebe un angulo:\n");
    gamma = leerReal("Angulo gamma (grados)", 0.1, 90.0);
    clase = clasificarAngulo(gamma);
    explicarAngulo(clase);
}

/* =====================================================================
 *  5) LAS 4 FASES DEL JUEGO
 *  Cada fase devuelve 1 si el jugador la supera y 0 si la mision falla.
 * ===================================================================== */

/* FASE 1: el jugador elige el angulo de reingreso */
int faseAngulo(Mision *m)
{
    int clase;
    int superada = 0;

    printf("\n========== FASE 1/4: ENTRADA A LA ATMOSFERA ==========\n");
    printf("  Orion llega a %.0f km de altura a %.0f m/s (%.0f km/h).\n",
           m->altInicial / 1000.0, m->velInicial, m->velInicial * KMH_POR_MS);
    printf("  Ventana segura: entre %.1f y %.1f grados.\n\n", GAMMA_MIN, GAMMA_MAX);

    m->gamma = leerReal("Angulo de reingreso gamma (grados)", 0.1, 90.0);
    clase = clasificarAngulo(m->gamma);
    printf("\n");
    explicarAngulo(clase);

    if (clase == ANGULO_SEGURO) {
        m->puntaje = m->puntaje + PUNTOS_FASE;
        superada = 1;
    } else if (clase == ANGULO_EMPINADO) {
        m->estado = FALLO_EMPINADO;
    } else {
        m->estado = FALLO_REBOTE;
    }
    return superada;
}

/* FASE 2: frenado aerodinamico, se muestra una tabla de 10 turnos */
int faseFrenado(Mision *m)
{
    double velocidad[N_TURNOS];    /* arreglo: velocidad al final de cada turno */
    double tiempoMin;              /* tiempo minimo para no pasar el limite de g */
    double t;
    int i;
    int superada = 0;

    tiempoMin = (m->velInicial - m->velParacaidas) / (LIMITE_G * GRAVEDAD);

    printf("\n========== FASE 2/4: FRENADO AERODINAMICO ==========\n");
    printf("  Usted elige cuanto dura la fase de mayor desaceleracion:\n");
    printf("   - Muy corta: la tripulacion supera los %.1f g.\n", LIMITE_G);
    printf("   - Muy larga: el escudo termico se sobrecarga (max %.0f s).\n", LIMITE_TIEMPO);
    printf("   - Rango util para estos datos: %.0f s a %.0f s.\n\n", tiempoMin, LIMITE_TIEMPO);

    m->tiempoFrenado = leerReal("Duracion del frenado (s)", 10.0, 3600.0);
    calcularResultados(m);

    /* Calculamos la velocidad en cada turno: v = vi - a*t */
    for (i = 0; i < N_TURNOS; i++) {
        t = m->tiempoFrenado * (i + 1) / N_TURNOS;
        velocidad[i] = m->velInicial - m->aMedia * t;
    }

    printf("\n  Desaceleracion media: %.3f m/s^2 = %.3f g\n", m->aMedia, m->aMediaG);
    printf("\n  Turno | t (s)  | v (m/s)  | v (km/h)  | K (J)\n");
    printf("  ------------------------------------------------------\n");
    for (i = 0; i < N_TURNOS; i++) {
        t = m->tiempoFrenado * (i + 1) / N_TURNOS;
        printf("  %4d  | %6.1f | %8.1f | %9.1f | %.3e\n", i + 1, t, velocidad[i],
               velocidad[i] * KMH_POR_MS, energiaCinetica(m->masa, velocidad[i]));
    }

    if (m->aMediaG > LIMITE_G) {
        printf("\n  [!] La desaceleracion supera el limite de la tripulacion.\n");
        m->estado = FALLO_G;
    } else if (m->tiempoFrenado > LIMITE_TIEMPO) {
        printf("\n  [!] El escudo termico no soporta una exposicion tan larga.\n");
        m->estado = FALLO_ESCUDO;
    } else {
        printf("\n  Fase 2 superada.\n");
        m->puntaje = m->puntaje + PUNTOS_FASE;
        superada = 1;
    }
    return superada;
}

/* FASE 3: paracaidas. Se simula cuantos paracaidas principales abren */
int faseParacaidas(Mision *m)
{
    /* Arreglo de factores: el indice es la cantidad de paracaidas que abren.
     * Con menos paracaidas, la nave llega al agua mas rapido. */
    double factor[4] = {0.0, 1.75, 1.25, 1.00};
    int abiertos;

    printf("\n========== FASE 3/4: PARACAIDAS ==========\n");
    printf("  A %.0f m de altura y %.1f m/s se despliegan los paracaidas.\n",
           m->altParacaidas, m->velParacaidas);
    printf("  Contingencia: cuantos paracaidas principales abren bien?\n");
    printf("  (3 = todo normal, menos = emergencia)\n\n");

    abiertos = leerEntero("Paracaidas operativos", 1, 3);
    m->velImpacto = m->velImpacto * factor[abiertos];

    printf("\n  Velocidad de impacto prevista: %.2f m/s (%.1f km/h)\n",
           m->velImpacto, m->velImpacto * KMH_POR_MS);
    printf("  Fase 3 superada.\n");
    m->puntaje = m->puntaje + PUNTOS_FASE;
    return 1;
}

/* FASE 4: amerizaje, se calcula la fuerza que hace el agua */
int faseAmerizaje(Mision *m)
{
    int superada = 0;

    calcularResultados(m);

    printf("\n========== FASE 4/4: AMERIZAJE ==========\n");
    printf("  La capsula toca el agua a %.2f m/s y se hunde %.2f m.\n\n",
           m->velImpacto, m->profundidad);
    printf("  Fuerza promedio del agua: %.1f N\n", m->fProm);
    printf("  Equivale a %.3f veces el peso (limite: %.1f)\n", m->fPromPesos, LIMITE_PESOS);

    if (m->fPromPesos > LIMITE_PESOS) {
        printf("\n  [!] La fuerza del agua rompe la estructura de la capsula.\n");
        m->estado = FALLO_IMPACTO;
    } else {
        printf("\n  Fase 4 superada.\n");
        m->puntaje = m->puntaje + PUNTOS_FASE;
        superada = 1;
    }
    return superada;
}

/* =====================================================================
 *  6) JUEGO COMPLETO Y REPORTE
 * ===================================================================== */

/* Juega las 4 fases en orden. Si una falla, las siguientes no se juegan. */
void jugarMision(Mision *datos)
{
    Mision partida;    /* copia de trabajo: asi no se pisan los datos originales */
    int superada;

    partida = *datos;
    partida.estado  = EXITO;
    partida.puntaje = 0;

    printf("\n############ INICIO DE MISION: REINGRESO DE ORION ############\n");
    printf("  Usted es el director de vuelo. Supere las 4 fases.\n");

    superada = faseAngulo(&partida);
    if (superada == 1) {
        superada = faseFrenado(&partida);
    }
    if (superada == 1) {
        superada = faseParacaidas(&partida);
    }
    if (superada == 1) {
        superada = faseAmerizaje(&partida);
    }

    calcularResultados(&partida);
    mostrarReporte(&partida);
}

/* Reporte final de desempeno */
void mostrarReporte(Mision *m)
{
    printf("\n=========== REPORTE FINAL ===========\n");

    switch (m->estado) {
        case EXITO:          printf("  Resultado: MISION EXITOSA, amerizaje seguro\n"); break;
        case FALLO_EMPINADO: printf("  Resultado: FALLO, reingreso demasiado empinado\n"); break;
        case FALLO_REBOTE:   printf("  Resultado: FALLO, rebote atmosferico\n"); break;
        case FALLO_G:        printf("  Resultado: FALLO, desaceleracion excesiva\n"); break;
        case FALLO_ESCUDO:   printf("  Resultado: FALLO, escudo termico sobrecargado\n"); break;
        case FALLO_IMPACTO:  printf("  Resultado: FALLO, impacto estructural\n"); break;
    }

    printf("  Fases superadas: %d de 4\n", m->puntaje / PUNTOS_FASE);
    printf("  Puntaje: %d / 100\n", m->puntaje);

    if (m->puntaje == 100) {
        printf("  Calificacion: COMANDANTE ARTEMIS\n");
    } else if (m->puntaje >= 75) {
        printf("  Calificacion: Piloto de reingreso\n");
    } else if (m->puntaje >= 50) {
        printf("  Calificacion: Ingeniero de vuelo\n");
    } else if (m->puntaje >= 25) {
        printf("  Calificacion: Cadete\n");
    } else {
        printf("  Calificacion: Aspirante\n");
    }

    printf("\n  Datos usados:\n");
    printf("   - Angulo de reingreso: %.2f grados\n", m->gamma);
    printf("   - Duracion del frenado: %.1f s\n", m->tiempoFrenado);
    printf("   - Velocidad de impacto: %.2f m/s\n", m->velImpacto);
    printf("\n  Resultados fisicos:\n");
    printf("   - Trabajo del rozamiento: %.4e J\n", m->trabajoRoz);
    printf("   - Desaceleracion media: %.3f m/s^2 (%.3f g)\n", m->aMedia, m->aMediaG);
    printf("   - Fuerza promedio del agua: %.1f N (%.3f veces el peso)\n",
           m->fProm, m->fPromPesos);
}

/* Reglas del juego */
void mostrarReglas(void)
{
    printf("\n=========== REGLAS DEL JUEGO ===========\n");
    printf("  El modulo Orion reingresa a la atmosfera a 11000 m/s (Mach 32)\n");
    printf("  desde 120 km de altura y debe amerizar en el Pacifico.\n\n");
    printf("  Son 4 fases de %d puntos. Si una falla, la mision termina.\n", PUNTOS_FASE);
    printf("   1. Angulo: entre %.1f y %.1f grados.\n", GAMMA_MIN, GAMMA_MAX);
    printf("   2. Frenado: maximo %.1f g y no mas de %.0f s.\n", LIMITE_G, LIMITE_TIEMPO);
    printf("   3. Paracaidas: se simula cuantos abren (afecta la velocidad de impacto).\n");
    printf("   4. Amerizaje: la fuerza del agua no debe pasar %.1f veces el peso.\n", LIMITE_PESOS);
    printf("\n  Principio fisico: W_total = delta K (Trabajo y Energia).\n");
}
