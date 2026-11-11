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