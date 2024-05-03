Son mecanismos abstractos que permiten *reconocer* lenguajes formales
Reconocer:  
	Aceptar toda cadena que pertenezca al lenguaje
	Rechazar toda cadena que no pertenezca al lenguaje

### Jerarquía de Chomsky

| Jerarquía |     Tipo de lenguaje formal      |     Grámatica que lo genera      |        Autómata mínimo que reconoce        |
| :-------: | :------------------------------: | :------------------------------: | :----------------------------------------: |
|  Tipo 0   | Recursivamente Enumerable (LRE)  |        Irrestricta (GIR)         |             Máquina de Turing              |
|  Tipo 1   |    Sensible al Contexto (LSC)    |    Sensible al Contexto (GSC)    |        Autómata Linealmente Acotado        |
|  Tipo 2   | Independiente del Contexto (LIC) | Independiente del Contexto (GIC) | Autómata Finito con Pila NO DETERMINISTICO |
|  Tipo 3   |           Regular (LR)           |           Regular (GR)           |              Autómata Finito               |
Estos problemas son computables
### Definición formal:
Está formado por:
- Un conjunto de Estados
- Un Estado Inicial, que es único. Comienza a analizar las cadenas en este Estado
- Un Alfabeto sobre el cuál se escribe el Lenguaje que recibe el Autómata
- Una Función de Transición que recibe el Estado Actual del Autómata y el Próximo Carácter de la Cadena a analizar. Cómo salida, pasa a otro Estado
- Un conjunto de Estados Finales. Si al finalizar el análisis de la Cadena queda en alguno de estos Estados, la cadena es aceptada, sino es rechazada.

El término Finito se refiere a la cantidad de Estados

#### Ejemplo:
![[Ejemplo - Autómatas 2024-04-30 09.40.35.excalidraw|200]]
0 -> c -> 1 -> a -> 7 ACEPTA
### Definición Matemática:
Un Autómata es una 5-upla:
M = (Q, Sigma, T, q0, F)
Donde:
- Q es el conjunto de Estados
- Sigma es el Alfabeto del lenguaje a reconocer
- T: Q x Sigma -> Q, es la Función de Transición
- q0 perteneciente a Q, es el Estado Inicial
- F incluído en Q, es el conjunto de Estados Finales o Aceptores
- Se muestra con Tabla de Transición, Filas = Estados, Columnas = Caracteres

### Autómata Finito Determinístico (ADF)
- La Función de Transición, recibiendo un estado y carácter, determina unívocamente el nuevo estado al que pasa el autómata
- La Función de Transición no tiene por que estar definida para todo par de QxSigma
- Si durante el análisis de una cadena, el par a aplicar resulta no estar definido, se detiene el análisis y se rechaza la cadena
- Los Estados suelen identificarse con números y letras
- T(2, c) = 4 Significa que si el Autómata está en el Estado *2* y el próximo carácter es *c*, entonces el Autómata pasará al Estado *4*
- Se agrega un nuevo Estado, llamado Estado de Error, y se completa la Función de Transición con este Estado, el cual vuelve a si mismo con cualquier carácter de Sigma (Asigna un Estado Error para los pares que no estaban definidos)

|  TT   |   a   |   b   |
| :---: | :---: | :---: |
|  0-   |   1   |   3   |
|   1   | **4** |   2   |
|  2+   | **4** | **4** |
|  3+   | **4** | **4** |
| **4** | **4** | **4** |

### Autómata Finito No Determinístico (AFN)
- No determinístico indica que ante un par Q x Sigma en la entrada, para la cual la Función está definida, la salida puede ser más de un Estado (La salida es un conjunto de Estados)
- Son más lentos que los AFD, ocupan menos memoria

Matemáticamente es una 5-upla
M = (Q, Sigma, T, q0, F)
Donde:
- T: Q x Sigma -> P(Q), la Función de Transición cambia su imagen al Conjunto de Partes de Q (todos los posibles subconjuntos de Q)
- Lo demás es igual que en ADF

| TT  |   a    |   b    |
| :-: | :----: | :----: |
| 0-  |  {0}   | {0, 1} |
|  1  | {1, 2} |  {2}   |
| 2+  |  {3}   | {0, 1} |
| 3+  |  {3}   |   -    |

### Autómata Finito No Determinístico con Epsilon (AFN-Epsilon)
- Permite cambiar de Estado sin consumir ningún Carácter de la cadena que se analiza
- Permite comenzar de otro Carácter (Salto desde el inicio, con Epsilon, al Estado Deseado)
- Estos cambios se etiquetan con Epsilon
- A la Tabla de Transición se le agrega una columna más, etiquetada con Epsilon
- La mayoria de las veces se utiliza este AFN
La Función de Transición pasa a ser:
- T: Q x (Sigma u {Epsilon}) -> P(Q)

| TT  |  a  |  b  | Epsilon |
| :-: | :-: | :-: | :-----: |
| 0-  | {0} | {0} |   {1}   |
|  1  | {1} |  -  | {2, 3}  |
| 2+  | {3} | {3} |    -    |
| 3+  |  -  | {3} |    -    |

---
### Ejercicios: 
- Sigma = {a, b} y L = {ab, bb, ba}. Expresar TT del AFD correspondiente

| TT  |  a  |  b  |
| :-: | :-: | :-: |
| 0-  |  1  |  2  |
|  1  |  -  |  3  |
|  2  |  3  |  3  |
| 3+  |  -  |  -  |
| 4+  |  -  |  -  |
- De el automata correspondiente. Armar Función de Transicion para cada par ordenado y luego la TT
M = ({0, 1, 2, 3}, {a, b}, T, 0, {2, 3})
Función de Transición:
- T(0, a) = 1
- T(1, a) = 2
- T(1, b) = 3
- T(3, a) = 3

| TT  |  a  |  b  |
| :-: | :-: | :-: |
| 0-  |  1  |  -  |
|  1  |  2  |  3  |
| 2+  |  -  |  -  |
| 3+  |  3  |  -  |
- Mostrar la Actividad para las siguientes cadenas:
1. ab: 0 -> a -> 1 -> b -> 3 ACEPTA
2. a: 0 -> a -> 1 RECHAZA
3. aba: 0 -> a -> 1 -> b -> 3 -> b RECHAZA
4. aab: 0 -> 1 -> 2 -> b RECHAZA

- Armar TT y TTC:

| TT  |  a  |  b  |
| :-: | :-: | :-: |
| 0-  |  1  |  2  |
|  1  |  -  |  2  |
| 2+  |  2  |  -  |

| TTC |  a  |  b  |
| :-: | :-: | :-: |
| 0-  |  1  |  2  |
|  1  |  3  |  2  |
| 2+  |  2  |  3  |
|  3  |  3  |  3  |
