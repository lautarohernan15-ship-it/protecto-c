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
Las inteligencias artificiales utilizadas fueron: Gemini IA y Claude IA

Comprender cómo estructurar el proyecto en C en varios archivos (.h y .c) y el diseño general.

Utilizado: Claude

Prompt:
"Hola, en base al trabajo mencionado nos gustaria tu ayuda. Estamos diseñando un simulador en C para el escenario 4 de Artemis (reingreso y amerizaje). Necesitamos modularizar el programa separando la
lógica.¿Cómo nos sugieres estructurar la cabecera y el paso de punteros?".

Para la revisión de fragmentos de código antes de hacer cada commit al repositorio de GitHub:

Utilizado: Claude

Ejemplos de Prompts utilizados:
"Revisa esta función leerEntero que usa scanf y getchar para limpiar el búfer. ¿Qué pasa si el usuario ingresa un símbolo especial o letras? ¿Hay riesgo de bucle infinito?"

"Verifica si el cálculo del Teorema del Trabajo y la Energía (W_roz = deltaK - W_peso) está expresado correctamente en unidades del SI y si los signos algebraicos de la gravedad y el desnivel son coherentes".

Ordenamiento final del código, redacción clara de los comentarios dentro de las funciones y maquetación de la documentación técnica.

UtilizadO: Gemini.

"Necesitamos que nos ayudes con los comentarios sobre que hace cada estructura y la separacion de las mismas."