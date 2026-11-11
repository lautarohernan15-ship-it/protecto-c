# Simulador ARTEMIS - Situación-Problema 4
# Reingreso Atmosférico, Frenado Aerodinámico y Amerizaje (Trabajo, Energía e Impacto)

UTN FRRe | Algoritmos y Estructuras de Datos | Ingeniería en Sistemas de Información

# a) Integrantes y comisión
| Integrante | Legajo |
|Guinea, Josias Vicente|29301|
|Gomez Aguer, Lautaro Hernan|29212|
|Sofia, Ortiz|28866|
|Herrmann Benasayag, Mateo Enrique|29278|

**Comisión:**
AED C K1.4

# b) Escenario y reglas
El módulo Orion (10.400 kg) reingresa a 11.000 m/s desde 120 km y debe amerizar en el Pacífico.
El jugador supera 4 fases (25 puntos c/u); si una falla, la misión termina:

1. Ángulo de reingreso: debe estar entre 5,5° y 7,0° (γ > 7° desaceleración excesiva; γ < 5,5° rebote).
2. Frenado: el jugador elige la duración; máx. 5 g y máx. 600 s (escudo térmico).
3. Paracaídas: se simula cuántos paracaídas principales abren (cambia la velocidad de impacto).
4. Amerizaje: la fuerza del agua no debe superar 5 veces el peso.

Los límites 5 g, 600 s y 5 pesos son criterios definidos por el grupo (`artemis.h`).

Física (Teorema Trabajo-Energía, W_total = ΔK):
- a) W_roz = ΔK − m·g·(hi − hf)
- b) a = (vi − vf) / Δt
- c) F = m·g + ½·m·v²/d

# c) Funcionamiento
- `main.c`: función `main()` y menú principal.
- `artemis.h`: constantes, `struct Mision` y prototipos.
- `artemis.c`: lectura validada (`do-while` + `scanf` + `getchar`), cálculos físicos y las 4 fases.
- Arreglos: tabla de velocidades del frenado y factores de paracaídas. Punteros: paso del struct `Mision *` a las funciones.

# d) Compilación y ejecución
```bash
gcc -Wall -Wextra -std=c99 -pedantic main.c artemis.c -o artemis4
./artemis4          # en Windows: artemis4.exe
```
(o simplemente `make`)

# e) Uso de Inteligencia Artificial
proximamente.