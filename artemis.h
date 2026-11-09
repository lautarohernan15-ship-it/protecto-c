/*ESTRUCTURA*/

#ifndef ARTEMIS_H
#define ARTEMIS_H

#define GRAVEDAD       9.80      
#define KMH_POR_MS     3.6       

#define MASA_NOM       10400.0   
#define VI_NOM         11000.0  
#define HI_NOM         120000.0  
#define VF_NOM         25.0      
#define HF_NOM         2500.0    
#define VIMPACTO_NOM   8.0       
#define DT_NOM         400.0    
#define PROF_NOM       1.50      

#define GAMMA_MIN      5.5       
#define GAMMA_MAX      7.0       

#define LIMITE_G       5.0       
#define LIMITE_TIEMPO  600.0     
#define LIMITE_PESOS   5.0       

#define N_TURNOS       10        
#define PUNTOS_FASE    25        

#define ANGULO_SEGURO    0
#define ANGULO_EMPINADO  1       
#define ANGULO_RASANTE   2       

#define EXITO            0
#define FALLO_EMPINADO   1
#define FALLO_REBOTE     2
#define FALLO_G          3
#define FALLO_ESCUDO     4
#define FALLO_IMPACTO    5


typedef struct {
    double masa;                                                
    double velInicial;      
    double altInicial;      
    double velParacaidas;  
    double altParacaidas;   
    double velImpacto;     
    double tiempoFrenado;  
    double profundidad;     
    double gamma;           

    double kInicial;       
    double kFinal;          
    double deltaK;
    double trabajoPeso;    
    double trabajoRoz;      
    double aMedia;          
    double aMediaG;        
    double peso;           
    double fProm;           
    double fPromPesos;     

    int estado;             
    int puntaje;            
} Mision;

int    leerEntero(char mensaje[], int minimo, int maximo);
double leerReal(char mensaje[], double minimo, double maximo);

void cargarDatosNominales(Mision *m);
void ingresarDatosPropios(Mision *m);
void mostrarDatos(Mision *m);

double energiaCinetica(double masa, double velocidad);
void   calcularResultados(Mision *m);
int    clasificarAngulo(double gamma);
void   explicarAngulo(int clase);

void mostrarAnalisis(Mision *m);
void jugarMision(Mision *datos);
void mostrarReglas(void);

int faseAngulo(Mision *m);
int faseFrenado(Mision *m);
int faseParacaidas(Mision *m);
int faseAmerizaje(Mision *m);

void mostrarReporte(Mision *m);

#endif
