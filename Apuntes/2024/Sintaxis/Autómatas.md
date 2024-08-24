Son mecanismos abstractos que permiten *reconocer* lenguajes formales
Reconocer:  
	Aceptar toda cadena que pertenezca al lenguaje
	Rechazar toda cadena que no pertenezca al lenguaje

### Jerarquía de Chomsky

| Jerarquía | Tipo de lenguaje formal          | Grámatica que lo genera          | Autómata mínimo que reconoce               |
| :-------: | :------------------------------- | :------------------------------- | :----------------------------------------- |
|  Tipo 0   | Recursivamente Enumerable (LRE)  | Irrestricta (GIR)                | Máquina de Turing                          |
|  Tipo 1   | Sensible al Contexto (LSC)       | Sensible al Contexto (GSC)       | Autómata Linealmente Acotado (MT)          |
|  Tipo 2   | Independiente del Contexto (LIC) | Independiente del Contexto (GIC) | Autómata Finito con pila NO DETERMINISTICO |
|  Tipo 3   | Regular (LR)                     | Regular (GR)                     | Autómata Finito                            |
Estos problemas son computables
#### Definición formal:
Está formado por:
- Un conjunto de Estados
- Un Estado Inicial, que es único. Comienza a analizar las cadenas en este Estado
- Un Alfabeto sobre el cuál se escribe el Lenguaje que recibe el Autómata
- Una Función de Transición que recibe el Estado Actual del Autómata y el Próximo Carácter de la Cadena a analizar. Cómo salida, pasa a otro Estado
- Un conjunto de Estados Finales. Si al finalizar el análisis de la Cadena queda en alguno de estos Estados, la cadena es aceptada, sino es rechazada.

El término Finito se refiere a la cantidad de Estados

##### Ejemplo:
![[Ejemplo - Autómatas 2024-04-30 09.40.35.excalidraw|200]]
0 → c → 1 → a → 7 ACEPTA
#### Definición Matemática:
Un Autómata es una 5-upla:
M = (Q, Σ, T, q0, F)
Donde:
- Q es el conjunto de Estados
- Σ es el Alfabeto del lenguaje a reconocer
- T: Q 𝑥 Σ → Q, es la Función de Transición
- q₀ ∈ Q, es el Estado Inicial
- F incluído en Q, es el conjunto de Estados Finales o Aceptores
- Se muestra con Tabla de Transición, Filas = Estados, Columnas = Caracteres

### Autómata Finito Determinístico (ADF)
- La Función de Transición, recibiendo un estado y carácter, determina unívocamente el nuevo estado al que pasa el autómata
- La Función de Transición no tiene por que estar definida para todo par de QxΣ
- Si durante el análisis de una cadena, el par a aplicar resulta no estar definido, se detiene el análisis y se rechaza la cadena
- Los Estados suelen identificarse con números y letras
- T(2, c) = 4 Significa que si el Autómata está en el Estado *2* y el próximo carácter es *c*, entonces el Autómata pasará al Estado *4*
- Se agrega un nuevo Estado, llamado Estado de Error, y se completa la Función de Transición con este Estado, el cual vuelve a si mismo con cualquier carácter de Σ (Asigna un Estado Error para los pares que no estaban definidos)

|  TT   |   a   |   b   |
| :---: | :---: | :---: |
|  0-   |   1   |   3   |
|   1   | **4** |   2   |
|  2+   | **4** | **4** |
|  3+   | **4** | **4** |
| **4** | **4** | **4** |

### Autómata Finito No Determinístico (AFN)
- No determinístico indica que ante un par Q 𝑥 Σ en la entrada, para la cual la Función está definida, la salida puede ser más de un Estado (La salida es un conjunto de Estados)
- Son más lentos que los AFD, ocupan menos memoria

Matemáticamente es una 5-upla
M = (Q, Σ, T, q0, F)
Donde:
- T: Q 𝑥 Σ → P(Q), la Función de Transición cambia su imagen al Conjunto de Partes de Q (todos los posibles subconjuntos de Q)
- Lo demás es igual que en ADF

| TT  |   a    |   b    |
| :-: | :----: | :----: |
| 0-  |  {0}   | {0, 1} |
|  1  | {1, 2} |  {2}   |
| 2+  |  {3}   | {0, 1} |
| 3+  |  {3}   |   -    |

### Autómata Finito No Determinístico con ε (AFN-ε)
- Permite cambiar de Estado sin consumir ningún Carácter de la cadena que se analiza
- Permite comenzar de otro Carácter (Salto desde el inicio, con ε, al Estado Deseado)
- Estos cambios se etiquetan con ε
- A la Tabla de Transición se le agrega una columna más, etiquetada con ε
- La mayoria de las veces se utiliza este AFN
La Función de Transición pasa a ser:
- T: Q 𝑥 (Σ u {ε}) → P(Q)

| TT  |  a  |  b  |   ε    |
| :-: | :-: | :-: | :----: |
| 0-  | {0} | {0} |  {1}   |
|  1  | {1} |  -  | {2, 3} |
| 2+  | {3} | {3} |   -    |
| 3+  |  -  | {3} |   -    |

### Autómata Finito con Pila:
La diferencia fundamental con un AF es justamente la pila, que es una pila abstracta de capacidad infinita.
En la pila se almacenan caracteres de un alfabeto distinto al del lenguaje que reconoce el autómata.

Por convención al escribir la secuencia de caracteres almacenados en la pila, lo hago comenzando por el tope de la misma. 
Si digo que en la pila tengo ABC significa que A está al tope y C en el fondo de la misma

Las transiciones tienen en cuenta el estado del autómata, el carácter siguiente de la cadena a reconocer y el carácter en el tope de la pila
Para que el autómata "vea" el tope de la pila, debe hacer pop.
Luego se puede volver a hacer push con el mismo caracter, dejando sin alterar la pila, o hacer push de epsilon (nada)

##### Definicion Formal:
Un AFP es una 7-upla
M = (Q, Σ, Γ, T, e₀, p₀, F)

Donde:
- Q es el conjunto de estados
- Σ es el alfabeto de entrada
- Γ es el alfabeto de π la (Algunos enfatizan: Σ ∩ Γ = ∅)
- T función: Q 𝑥 (Σ {ε}) 𝑥 Γ → P(Q 𝑥 Γ*),  describe la Tabla de Movimientos
- e₀ perteneciente a  Q, estado inicial
- p₀ perteneciente a Γ, Símbolo inicial en pila que indica pila vacía, suele ser el símbolo $
- F conjunto de estados finales

Nota, el libro de la cátedra usa como notación M = (E, A, A', T, e0, p0, F)

##### Función de Transición:
Notar que la función de transición toma como entrada una terna dada por:
– El estado en que se encuentra el autómata
– Un carácter de Σ o ε
	Esto significa que puede haber un cambio de estado sin necesidad de consumir un carácter de la cadena analizada
– Un carácter de Γ

Y como salida
– Un nuevo estado del autómata
– Un cadena sobre el alfabeto Γ (eventualmente vacía)
	Se considera que en cada transición se elimina el carácter que estaba al tope de pila, por tanto, si quiero conservarlo debo volver a introducirlo

Un modo de explicar cada transición es pensarla a cada una con los siguientes pasos:
1. Pop: se saca (siempre) del tope de pila el elemento que allí se encuentre
2. Push: se insertan en la pila los elementos que indique la transición
3. Cambio al estado que indique la transición 
4. Si el carácter que indica la transición no es ε, entonces avanzar al próximo en la cadena que está siendo analizada

###### Para que un AFP sea determinístico (AFPD) es necesario que se cumplan 2 condiciones:
Para cualquier terna de entrada el conjunto de salida de tiene a lo sumo un elemento
∀ e ∊ Q, a ∊ (Σ U {ε}), 𝑥 ∊ Γ: |T(e,a,x)| ≤ 1

Si está definida la función para ε entonces no debe	estar definida para ningún elemento de Σ y viceversa
∀ e ∊ Q, 𝑥 ∊ Γ:
T(e, ε, x) ≠ ∅ ⇒ T(e, a, x) = ∅( ∀a ∊ Σ)

∀ e ∊ Q, 𝑥 ∊ Γ:
Si ∃ a ∊ Σ tq: T(e, a, x) ≠ ∅ ⇒ T(e, ε, x) = ∅

##### Notacion Alternativa:

### Máquina de Turing:
Dado un problema, responde si se puede resolver o no, reconoce los lenguajes de tipo 0

Es un autómata que se define como una 7-upla
(Q, Σ, Γ, T, q₀, B, F) Donde:
- Q: Conjunto de estados
- Σ: Alfabeto terminal
- Γ: Alfabeto de cinta (array infinita)
	Γ = Σ ∪ B ∪ Alfabeto auxiliar (“no terminal”)
	Alfabeto auxiliar ∩ Σ = ∅
- T: Q 𝑥 Γ → Q 𝑥 Γ 𝑥 {I,D}
- Q₀: Estado Inicial
- B: Caracter Blanco ∈ Γ
- F: Conjunto de estados aceptores

##### Descripción del programa
Tipo actividad (como en el libro de la cátedra):
- Estado actual – carácter leído, carácter escrito, dirección – Nuevo estado
- Ejemplo: e0 – a,X,R - e1

Tipo tabla:
- Una fila por cada estado
- Un elemento de Γ por cada columna (carácter leído)
- En la intersección:
	El nuevo estado
	El carácter a escribir
	El movimiento

Descripción Instantanea:
Se hace mostrando el estado a la izquierda del próximo carácter a leer
