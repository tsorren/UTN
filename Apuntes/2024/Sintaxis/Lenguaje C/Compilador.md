#### Análisis (Front End)
Depende del Lenguaje de Programación
Scanner:
	Analizador léxico (GSC)
	Recibe secuencia de caracteres (fuente)
	Reconoce lexemas de las distintas categorías léxicas (LR)
	Genera como salida una secuencia de tokens

Parser:
	Analizador Sintáctico (GIC)
	Recibe los tokens generados por el scanner
	Verifica que cumplan la GIC del Lenguaje

Analizador Semántico:
	Realiza comprobaciones de contexto (vars, def duplicadas, etc)
	Genera un primer código intermedio

#### Síntesis (Back End)
Depende del Entorno
Optimiza el código intermedio
Genera el código para la máquina concreta donde se debe ejecutar


![[Etapas - Compilador.excalidraw | 500]]

Tabla de Símbolos:
	Diccionario

Generador de Código Intermedio:
	AST: 
		Abstract Syntax Tree
	Generic:
		Abstract Syntax Tree de gcc
	Drivers:
		gcc
		clang

Middle End:
	IR:
		Intermediate Representation
	SSA: 
		Static Single Assignment
		Para hacer optimizaciones
	RTL:
		Register Transfer Language


### Entorno de Traducción:
Compilación por partes + vinculador (linker)
Unidad de traducción (translation unit): Cada fuente luego del preprocesador
##### Fases de Traducción (C23:5.1.1.2):
Preprocesador:
- Convertir caracteres a caracteres usados por la implementación (target)
- Unir las lineas que terminan en una barra invertida \\
- Dividir el fuente en tokens de preprocesamiento, reemplazar comentarios y espacios en blanco por un caracter de espacio en blanco -- SCANNER 
- Ejecutar directivas de preprocesamiento
- Expandir las macros al achivo de código fuente
- Convertir secuencias de escape en sus equivalentes
- Concatenar los literales adyacentes

Compilador:
- Analizar tokens sintáctica y semánticamente
- Generar el código de objeto

Vinculador:
- Resolver todas las referenciase externas
- Crear un ejecutable o una biblioteca de vínculos dinámicos (dll)

### Entorno de Ejecución Independiente (Freestanding)
Sin Sistema Operativo, típicamente un embebido
El nombre y la firma de la función principal donde inicia el programa) puede ser cualquiera, es definido por la implementación
La manera en que el programa termina está definido por la implementación
Solo está obligado a dar soporte a un subconjunto de la biblioteca estándar

### Entorno de Ejecución Alojado (Hosted)
El programa comienza en la funcion main, devuelve 0 para exito y distino de 0 para error.
```c
int main(void) // El programa no recibe parámetros al ejecutarse
int main(int argc, char *argv[]) // Recibe un int cantidad y un vector de parametros
// argc debe ser positivo
// argv[0] incluye el nombre del programa
// argv[argc] es un puntero nulo, para poder recorrer el vector
// argc y argv viven durante toda la ejecución del programa, pueden ser modificados
```
Si no hay sentencia return, devuelve 0
En main, llamar `return (exp)` es lo mismo que llamar `exit (exp)`
#### Lenguaje Micro:
- El único tipo de dato es entero.
- Todos los identificadores son declarados implícitamente y con una longitud máxima de 32 caracteres.
- Los identificadores deben comenzar con una letra y están compuestos de letras y dígitos.
- Las constantes son secuencias de dígitos (números enteros).
- Hay dos tipos de sentencias
- Asignación
	- ID := Expresión;
	- Expresión es infija y se construye con identificadores, constantes y los operadores + y -; los paréntesis están permitidos.
- Entrada/Salida
	- leer (lista de IDs);
	- escribir (lista de Expresiones);
- Cada sentencia termina con un "punto y coma" (;). El cuerpo de un programa está delimitado por inicio y fin.
- inicio, fin, leer y escribir son palabras reservadas y deben escribirse en minúscula.

###### Gramática Léxica:
```
<token> → uno de <identificador> <constante>
<palabraReservada> <operadorAditivo>
<asignación> <carácterPuntuación>
<identificador> → <letra> {<letra o dígito>}
<constante> → <dígito> {<dígito>}
<letra o dígito> → uno de <letra> <dígito>
<letra> → una de a-z A-Z
<dígito> → uno de 0-9
<palabraReservada> → una de inicio fin leer escribir
<operadorAditivo> → uno de + -
<asignación> → :=
<carácterPuntuación> → uno de ( ) , ;
```
###### Tabla de Símbolos:
Estructura de datos compleja que sirve durante toda la fase de análisis para guardar y procesar información.
- Aporta el contexto, elimina la necesidad de un algoritmo para GSC.
El diseño depende de cada implementación
Básicamente contiene cada identificador (como clave) y sus atributos
Los atributos dependerán de que tipo de identificador sea, por ejemplo (lista no exhaustiva)
- Variable: Tipo, ámbito, Lugar de almacenamiento, etc.
- Función: Tipo, cantidad de parámetros (para cada parámetro el tipo de pasaje)
- Tipo de dato: Por ejemplo estructuras, arreglos, alias de tipos de datos
- Palabras reservadas (si el escáner es elemental)
- Literales cadena.
En el fondo son una base de tipo clave - valor, se puede implementar como
- Arreglos
- Listas encadenada
- Tablas de Hashing.
Auxiliares:
- Buffers
	Todos los literales cadenas seguidos en un buffer y se guardan punteros a ellos.
- Pilas de TS
	En lugar de un solo diccionario, uno por cada ámbito y se van apilando. En el caso de un único diccionario, el ámbito forma parte de la “clave”

```c
// EJEMPLO:
función int fx(int x, double y)
// - (fx, funcion, int, 2, int, double)
int vdatos[20][40];
// - (vdatos, arreglo, int, 2, 20, 40)
// Caso typedef
typedef double velocidad;
// Inicialmente el escáner ingresa en la TS a velocidad como un identificador
// Debe cambiar el atributo identificador a algo que indique “tipo de dato” y su valor sea double
// La modificación la realiza una rutina semántica

// Devoluciones (caso constante numérica)
// Token, índice/puntero
// Token, valor
```

###### Centinelas:
En centinela es un carácter “espurio” que indica el final del lexema que se está reconociendo. Es decir, es un carácter que NO puede formar parte de ese lexema
- Por ejemplo, si está reconociendo un identificador y encuentra un espacio en blanco
- En general: si encuentra un carácter que no es parte de token que se está reconociendo

Los LR infinitos SIEMPRE necesitan de un centinela.
Los LR finitos pueden necesitar o no un centinela
- No necesitan si los lexemas del LR no comparten prefijos
- Si hay prefijos iguales el lexema más corto necesita de centinela: P.ej: + puede seguir como ++ o encontrar una letra que forma parte de un identificador, esa letra sería el centinela
- Si bien las palabras reservadas son finitas igual necesitan centinela porque pueden ser prefijo de un identificador. P.ej: for es prefijo de forense
### Sintaxis y BNF
Motivación: Lenguajes de programación usan LR para
- Identificadores
- Constantes
- Palabras reservadas
Lenguajes independientes del contexto para:
- Expresiones
- Sentencias
- Estructuras de control
BNF (Backus Naur Form) se usa para describir un Lenguaje de programación en esos dos niveles
- Léxico: Categorías léxicas o Tokens (LR)
- Sintáctico: Categorías sintácticas (LIC)
- Con notación similar a gramática
Por ahora cambiaremos:
- Solo escribimos las producciones
- El axioma es el no terminal a izquierda de la primer producción
- Los no terminales los representaremos con nombres significativos en lugar de con un único símbolo
Los metasímbolos siguen siendo → y |

Identificadores:
Suponga que los identificadores en un determinado lenguaje se forman con letras mayúsculas y guiones bajos.
Los guiones bajos solo se permiten de a uno entre dos letras.

Identificador →
	Letra |
	Identificador Letra |
	Identificador GuionBajo Letra
GuionBajo → _
Letra → A|B|C|D|E|F|G|H|I|J|K|L|M|N|O|P|Q|R|S|T|U|V|W|X|Y|Z

Recursivas a Izquierda
Notar que en la gramática anterior el identificador se va formando de derecha a izquierda
Se dice que la gramática es recursiva a izquierda porque el no terminal de la izquierda aparece a la izquierda de lo producido (la parte derecha)
Es Lineal a Izquierda
Se puede construir una gramática equivalente recursiva a derecha

Recursiva a derecha
Identificador → 
	Letra |
	Letra Resto
	Resto → Letra Resto |
	GuionBajo Letra Resto |
	Epsilon
###### Expresiones y Sintaxis:
Una GIC es apropiada para balancear símbolos, por ejemplo, paréntesis
Nos permite establecer precedencia de operadores, los más cercanos al axioma serán los de menor precedencia.
Reducción es el proceso de evaluación y es inverso paso a paso al de la derivación
Si intento “nivelar” precedencias puedo terminar con una gramática ambigua
Nos permite establecer la asociatividad de los operadores (izquierda a derecha o al revés)
###### Gramática para expresiones:

| Regla | Producción                                              |
| :---: | :------------------------------------------------------ |
|   1   | Expresión → Expresión + Término                         |
|   2   | Expresión → Término                                     |
|   3   | Término → Término * Factor                              |
|   4   | Término → Factor                                        |
|   5   | Factor → Número                                         |
|   6   | Factor → (Expresión)                                    |
|   7   | Número → 0 \| 1 \| 2 \| 3 \| 4 \| 5 \| 6 \| 7 \| 8 \| 9 |

###### Ejemplo de derivación
Para la expresión 2 + 4 * 5. Siempre se toma el No Terminal más a la izquierda

| Paso | Regla         | Derivación               |
| :--: | ------------- | ------------------------ |
|  0   | Axioma        | **Expresión**            |
|  1   | 1 (E → E + T) | **Expresión** + Término  |
|  2   | 2 (E → T)     | **Término** + Término    |
|  3   | 4 (T → F)     | **Factor** + Término     |
|  4   | 5 (F → N)     | **Número** + Término     |
|  5   | 7 (N → 2)     | 2 + **Término**          |
|  6   | 3 (T → T * F) | 2 + **Término** * Factor |
|  7   | 4 (T → F)     | 2 + **Factor** * Factor  |
|  8   | 5 (F → N)     | 2 + **Número** * Factor  |
|  9   | 7 (N → 4)     | 2 + 4 * **Factor**       |
|  10  | 5 (F → N)     | 2 + 4 * **Número**       |
|  11  | 7 (N → 5)     | 2 + 4 * 5                |

###### Reducción:

| Corresponde a Paso | Derivación a Reducir       | Producción    | Operación   |
| :----------------: | -------------------------- | ------------- | ----------- |
|         11         | 2 + 4 * **5**              | 7 (N → 5)     |             |
|         10         | 2 + 4 * **Número5**        | 5 (F → N)     |             |
|         9          | 2 + **4** * Factor5        | 7 (N → 4)     |             |
|         8          | 2 + **Número4** * Factor5  | 5 (F → N)     |             |
|         7          | 2 + **Factor4** * Factor5  | 4 (T → F)     |             |
|         6          | 2 + **Término4 \* Factor** | 3 (T → T * F) |             |
|         5          | **2** + Término20          | 7 (N → 2)     | 4 * 5 = 20  |
|         4          | **Número2** + Término20    | 5 (F → N)     |             |
|         3          | **Factor2** + Término20    | 4 (T → F)     |             |
|         2          | **Término2** + Término20   | 2 (E → T)     |             |
|         1          | **Expresión2** + Término20 | 1 (E → E + T) | 2 + 20 = 22 |
|         0          | Expresión22                | Axioma        |             |

##### Árbol Sintáctico Abstracto (AST):
Se produce realizando la Derivación, se lee mediante la Reducción
De la sintaxis del lenguaje, se produce la precedencia de los operadores. La recursividad a derecha o izquierda define la asociatividad a derecha o a izquierda
De la semántica del lenguaje se ... los operandos

Una gramática es ambigua, si puedo armar al menos dos árboles sintácticos abstractos distintos de una misma cadena de entrada

#### BNF:
Descripción:
Usar nombres representativos (Naur)
Los no terminales se escriben entre < y > (Backus)
El metasímbolo de producción es ::= (Naur)
- Se suele leer ::= como “es un/a”
Se separan opciones (Backus) con el metasímbolo | (Naur)

Ejemplo (tomado de Algol)
```
<identificador> ::= <letra> |
					<identificador> <letra> |
					<identificador> <dígito>
					<letra> ::= A | B | C | … | Z | a | b | c | …… | z
					<dígito> ::= 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9
```

#### EBNF:
Muchas variantes
En 1974 Niklaus Wirth junto a Kathleen Jensen escriben “Pascal User Manual Report” y hacen las siguientes extensiones:
- Las palabras reservadas del lenguaje las distingue subrayándolas
- Usa { } para indicar la repetición de cero o más veces de lo esté entre las llaves (clausura de Kleene)
Además ofrece una notación alternativa, el diagrama de sintaxis

###### Identificador:
Vimos en BNF
```
<identificador> ::= <letra> |
					<identificador> <letra> |
					<identificador> <dígito>
```
Ahora podemos escribir lo mismo como
```
<identificador> ::= <letra> {<letra o dígito>}
<letra o dígito> ::= <letra> | <dígito>
```

#### BNF Lenguaje C:
Cambia la notación, según el estándar
- Los no terminales van en cursiva (italic)
- El metasímbolo de producción es :
- Para indicar opciones pone una por renglón (en lugar de usar | )
- Puede poner varias opciones en un renglón si se precede del metasímbolo one of, usado generalmente para conjuntos de caracteres
- Los terminales van en negrita (en K&R van en tipografía monoespaciada)
- Si un término es opcional se lo indica con el subíndice opt
- No hay equivalente al cero o más repeticiones de la BNF usada en Pascal

###### Ejemplo:
identifier :
	identifier-nondigit
	identifier identifier-nondigit
	identifier digit

identifier-nondigit: one of
	_ a b c d e f g h i j k l m
	n o p q r s t u v w x y z
	A B C D E F G H I J K L M
	N O P Q R S T U V W X Y Z

digit: one of
	0 1 2 3 4 5 6 7 8 9
	
Según el estándar las implementaciones deben distinguir los identificadores al menos hasta el carácter 31 (external)

#### Otras BNF:
● Hay muchas variantes, algunas de ellas son
- = como metasímbolo de producción
-  Corchetes para indicar cero o una vez (opción)
- Indicar los strings terminales con comillas, simples o dobles
- (* \*) como comentarios
- Distintas modificaciones caligráficas para terminales y/o no terminales (negrita, cursiva, etc)
#### BNF otros usos:
Por ejemplo para describir el formato de datos:
- JSON (JavaScript Object Notation)
- W3C (World Wide Consortium) define a XML con una EBNF

### Semántica:
###### Conceptos previos:
Al usar una notación BNF para documentar un Lenguaje de programación, podemos:
- Determinar con precisión las categorías léxicas (tokens) que lo componen
- Determinar las categorías sintácticas del lenguaje, pero con algunas restricciones.
Las restricciones se deben a:
- No complicar la gramática demasiado
- Limitaciones de las GIC, ya que hay reglas que en realidad corresponden a una GSC

#### Semántica estática:
Son las restricciones no representadas en la BNF pero aclaradas en la documentación del lenguaje.
Si se incumplen, pueden ser detectados al compilar.
Los errores de este tipo, reportados por el compilador, se clasifican como errores semánticos.

Casos:
- Compatibilidad de tipos entre operadores y operandos
- Que los identificadores hayan sido declarados (ámbito y alcance)
- Que no se declare más de una vez un identificador (redeclaración) dentro de un mismo espacio de nombre
- Que las funciones se llamen con la cantidad y tipo correcto de parámetros

#### Semántica o Semántica Dinámica:
La semántica (significado) de un constructo sintáctico es "que hace".
Implica lo que ocurre en la ejecución del programa
Este enfoque se llama semántica operacional.
Otros pueden ser la semántica denotacional (funciones) o la semántica axiomática (relaciones).

Guía el código que se va a generar
Se puede hablar de la semántica de sentencias, o por ejemplo de la definición de variables:
- Zona de memoria donde se alojará
- Valor inicial por defecto
- Interpretación del patrón de bits
El estándar de C define la semántica y habla de comportamiento para definirla operacionalmente, pero hay casos donde no queda totalmente definido.

#### Comportamiento:
Apariencia externa de la acción

###### Comportamiento no especificado:
El estándar da un conjunto de posibilidades (todas intercambiables), y la implementación (el compilador) elige una o varias de ellas en diferentes partes del programa.
- Por ejemplo: El orden de evaluación de los argumentos de una función
Esta "omisión" por parte del estándar tiene por objetivo permitir hacer optimizaciones al compilador

###### Comportamiento dependiente de la implementación:
Comportamiento no especificado en el estándar que cada implementación debe decidir y documentar, haciendo luego siempre lo mismo.
- Por ejemplo: el tamaño de un int, desplazamiento de bits a derecha en enteros con signo

###### Comportamiento específico local (o regional):
Depende de la configuración regional
- Por ejemplo: islower puede devolver verdadero para algunos caracteres no pertenecientes al ascii básico

###### Comportamiento no definido:
El estándar no lo define, y puede ocurrir que el compilador lo resuelva de alguna manera, compilando y dando una advertencia.
Es algo que no debería ocurrir.

#### Sintaxis y Semántica (estática):
Error sintáctico: Cuando la cadena analizada no puede ser derivada de la BNF
Error semántico: Cuando es derivable (sintácticamente correcta), pero no cumple con las restricciones del lenguaje (semántica estática)

Ejemplo en C:
```c
if (var) i++;
// Es sintácticamente correcto
// Semánticamente correcto si var fue definida como un tipo escalar (numérico o puntero)
```
##### Distinta Sintaxis e Igual Semántica:
La misma temántica se puede implementar en diferentes lenguajes con sintáxis distintas.
Por ejemplo la asignación, en todos los ejemplos siguientes se asigna el valor 15 a la variable nro
```c
nro = 15; // En lenguajes C, C++, Java y otros
```

```pascal
nro := 15; // Pascal, Algol y otros
```

```R
nro <- 15 # En R, S, y quizas otros
```
C y C++ divergieron con el tiempo, por ejemplo:
```c
sizeof('a'); 
// El valor numérico en C++ es 1, y en C depende de la implementación
// En C++ el tipo de dato de una constante de carácter es tipo char
// En C es de tipo int, y el tamaño de int depende de la implementación

++a;
// En C devuelve un valorR (algo constante)
// En C++ un valorL (referencia)
```

#### Categorías Gramaticales:
Son los Lenguajes Independientes del Contexto que se usan en la sintaxis del lenguajes
Se dividen en:
- Expresiones
- Declaraciones y Definiciones
- Sentencias
Todas se completan con restricciones, sean sintácticas o semánticas
Por ejemplo: El if se engancha con el else más cercano

#### Expresiones
Son secuencias de operadores y operandos que:
- Producen un valor
- Designan un objeto o función
- Generan un efecto lateral
- Combinan los anteriores
Las constantes, variables y llamados a funciones forman parte de las expresiones primarias o elementales

##### Tipos de datos de una expresión
Booleanos:
	No forman parte del lenguaje C en el sentido estricto
	Forman parte de los tipos enteros (standard unsigned integer types)
	Se considera 0 como falso, distinto de 0 como verdadero
	Las operaciones booleanas retornan 0 ó 1
	Para conveniencia de uso se definen en el encabezado stdbool.h bool como alias de \_Bool y los valores true y false
	Desde C23 si hay tipo bool

Operadores aritméticos:
	Necesitan tipos iguales
	Si no lo son se aplican "conversiones aritméticas habituales" 
	Hacen un casting implicito para llevar al tipo con mayor capacidad de representación de valores

##### Evaluación de expresiones
Las precedencias quedan definidas en la gramática (por la cercanía o lejanía del operador con respecto al axioma)
La asociatividad está dada por la recursividad (a izquierda o a derecha) de la producción
El agrupamiento es la precedencia junto con la asociatividad

##### Efecto lateral o secundario (side effect)
Las funciones o expresiones deberían solo calcular un valor e idealmente no hacer nada más.
Un efecto lateral es todo cambio adicional al entorno de ejecución. Por ejemplo:
- Modificación de una variable estática (global) o cualquier otra variable
- Modificar un argumento real de una función
- Leer o Escribir en un archivo

Estos efectos son comunes en el paradigma imperativo
Hay que tener en cuenta como ocurren en el tiempo.
El estándar de C define la secuenciación como el orden de los efectos secundarios

#### Secuenciación
Establece una línea de tiempo (en qué orden suceden los eventos)
Tomando en cuenta un solo hilo de ejecución tenemos:
- A está secuenciada antes que B si la ejecución de A ocurre antes que la de B
- A y B no están secuenciados significa que puede ejecutarse primero A y luego B o al revés, pero no se especifica

Punto de secuencia:
- Es un instante estable que divide dos ejecuciones 
##### Secuenciación de operandos
La ejecución de operandos (los efectos laterales y los cálculos de valores de subexpresiones) salvo en algunos casos, no está secuenciada.

Hay cuatro operadores que te garantizan secuenciación, mediante puntos de secuencia:
- Los operadores && y || aseguran la evaluación de izquierda a derecha. Detienen la evaluación en cuanto el resultado esté definido
- El operador ternario ? asegura evaluar el primer operando, luego el segundo o tercero según corresponda
- El operador , (coma) garantiza que las expresiones (operandos de coma) se evalúan de izquierda a derecha. Todas menos la ultima son evaluadas como void, el resultado es del tipo al que evalúe la última expresión
Ejemplo de operador coma:
```c
a++, b = c + 2;
//Es igual a
a++;
b = c + 2;

for(int a = 0, b = 1; a < 10; a++); // En el estado inical setea a = 0 y b = 1
```
##### Puntos de secuencia
Divide dos ejecuciones y define secuenciación
- El punto y coma ;
- Luego de evaluar todos los argumentos reales, antes de invocar a la función
- Luego de evaluar la expresión de un return, antes de resumir la ejecución de la función invocante
- Luego de cada expresión completa (full expression)
	La expresión que controla un if, switch, while, do-while
	Cualquiera de las expresiones de un for
	Una sentencia expresión

#### ValorL y ValorR
Objeto: Zona de memoria que contiene un valor de un tipo dado
Valor: Significado preciso del contenido de un objeto, según su tipo
ValorL (Left value or Locator value):
- Expresión (no void) que potencialmente designa un objeto (comportamiento no definido si no lo hace)
- El modo más habitual es el identificador de una variable, pero puede ser una expresión como vector\[i\] o ptr->miembro
- Aparece a izquierda de una asignación
ValorL Modificable: ValorL que no está calificado como constante, no es de tipo arreglo y no es incompleto (struct incompleto)
ValorR: Es un valor, según nuestra definición anterior, surgido de una expresión (tira de bits que forman el valor)

#### Operadores de incremento y decremento
Postfijo:
- El operando debe ser un valorL modificable
- El resultado es el valor (valorR)
- Como efecto lateral se suma o resta 1 al operando
- Se obtiene el valor, previo a el efecto lateral (Primero se usa luego se modifica)
```c
b = 2; c = 3;
a = b++ * c; // a vale 6 y b vale 3
```
Prefijo:
- Primero se aplica el efecto lateral
- Luego se obtiene el valor modificado

#### Expresiones BNF
En el estándar, en lugar de comenzar con el axioma e ir alejándose, lo hace en orden inverso.
Comienza con:
```
primary-expression:
	identifier
	constant
	string-literal
	( expression )
	generic-selection

```
Luego introduce los operadores de más alta precedencia, baja a primary expression:
```
postfix-expression:
	primary-expression
	postfix-expression [ expression ]
	postfix-expression ( argument-expression )
	postfix-expression . identifier
	postfix-expression -> identifier
	postfix-expression ++
	postfix-expression --
	( type-name ) { initializer-list }
	( type-name ) {initializer-list , }
```
```
multiplicative-expression:
	cast-expression
	multiplicative-expression * cast-expression
	multiplicative-expression / cast-expression
	multiplicative-expression % cast-expression
	
```
###### multiplicative-expression:
Restricciones:
- Los operandos deben ser de tipo aritmético
- Pero para el operador % deben ser de tipo entero

Semántica:
- Se aplican a los operandos las conversiones aritméticas usuales
- Para los operadores / y % si el segundo operando es cero, el comportamiento es no definido

```
assignment-expression:
	conditional-expression
	unary-expression assig-operator assignment-expression

assig-operator:
 = *= /= etc
```

#### Declaraciones y Definiciones
Declarar es dar a conocer, especificando la interpretación y atributos, un  identificador
Definir es un declarar y:
- Si es un objeto, reservar espacio en memoria
- Si es una función, dar el código de la misma
Para los typedef y las constantes de enumeración, la declaración es definición
Decimos que los tag los declaramos, pero en estructuras y uniones definimos su contenido (sus miembros)

#### Modificadores:
Storage Class: Altera donde se almacena
- extern: Nada, se resuelve en otra unidad de traducción
- static: En heap en lugar de en stack
- register: Si se puede, en registro del CPU

Type-qualifier: Califican un comportamiento particular
- const: No puede alterarse su valor
- restrict: Es el único puntero para acceder a la memoria apuntada
- volatile: Otro programa o hilo puede modificar su valor

Function-specifier:
- inline: Se incrusta su lógica en cada lugar que es invocada
- _ Noreturn: No se genera código para resumir al ejecución de la función que la invoque

#### Nombres de Tipos
Referencia adicional: https://cdecl.org
Se lee de derecha a izquierda
```c
int id // int -> entero
int *id // int * -> puntero a entero
int *id[3] // int *[3] -> arreglo de 3 punteros a entero
int (*id)[3] // int (*)[3] -> puntero a arreglo de 3 enteros
int *id(void) // int *(void) -> funcion sin parámetros que devuelve puntero a entero
int (*id)(void) // int (*)(void) -> puntero a función sin parámetros que devuelve entero
int (*id[])(double) // int (*[])(double) -> arreglo de punteros a funciónes con un parámetro double que devuelven enteros
```

#### Sentencias
BNF de Sentencias (C17)
```
statement:
	labeled-statement
	compound-statement
	expression-statement
	selection-statement
	iteration-statement
	jump-statement
```
En C23 se complica un poco por los atributos, pero conceptualmente es lo mismo

Sentencia etiquetada:
- identifier : statement
- case constant-expression : statement
- default : statement
Los casos de case y default deben estar dentro de un switch. No es obligatorio que switch contenga algún case o default
El primer modo es para usar en goto

Sentencia compuesta:
- Entre { }, puede que solo estén las llaves
- Define un nuevo ámbito

Sentencia expresión:
- Expresión con ; al final. En general de una asignación
- El ; marca un punto de secuencia
- Puede ser nula ( solo ; )
- Si ponés algo como a+b; compila, pero da warning unused value
