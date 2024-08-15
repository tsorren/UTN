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
