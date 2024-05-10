# Expresiones Regulares Matemáticas
Una Expresion Regular (ER, RegEx) es un patrón que describe un conjunto de cadenas de un Lenguaje Regular (LR)
Las Expresiones Regulares se forman con:
- Caracteres del alfabeto del LR representado
- ε para representar la cadena vacía
- Operadores:
	- Unión - Conmutativa
	- Concatenación - No conmutativa
	- Estrella de Kleene (loop ó potencia infinita, potencia finita no)
- Paréntesis para agrupar o cambiar presedencias
- Precedencia:
	1. Potenciación (Estrella de Kleene)
	2. Concatenación
	3. Unión
	Los LR son cerrados respecto a estas operaciones
	Por eso podemos aplicarlos sabiendo que lo obtenido sigue siendo un LR

Un cáracter solo es una ER, ε es una ER
- La ER *a* representa el LR {a}
Concatenación:
- La ER a.b o simplemente *ab* representa el LR {ab}
Unión:
- La ER a+b (también a|b en computadora) representa el LR {a,b}
Potenciación: (No es parte de las ER básicas)
- La ER a³ representa el LR {aaa}
Estrella de Kleene
- La ER a* representa el LR {ε, a, aa, aaa, ...}

Maneras de demostrar que un Lenguaje es Regular:
- Generar con Gramática Regular
- Reconocer con Gramática Regular
- Describir con Expresión Regular

#### Operar con Expresiones Regulares
Factorización:
- La Concatenación no es conmutativa, entonces tendremos factorizaciones a izquierda y a derecha
	- a(a+b) = aa + ab
	- aab + abb = a(ab + bb) = a(a+b)b
Clausura Positiva
- Como la de Kleene pero sin potencia cero
	- a* = {ε, a, aa, aaa...}
	- a⁺ = aa* = a\*a
Igualdades Útiles:
- a\*a\* = a*
- ε* = ε
- a* = aa* + ε
- (ab)* = a(ba)*
- (R*)* = R*
- (R* + S*)* = (R\*S\*) = (R+S)*

#### Definición formal de Expresión Regular:
1. Vacio es la ER que representa el conjunto vacío
2. ε es una ER que representa al lenguaje L={ε}
3. x perteneciente a Σ (Alfabeto) es la ER que representa el Lenguaje L = {x}
4. s perteneciente a Σ* es la ER que representa el Lenguaje = {s}. Por ej: *s* = *abf* (palabra)
5. R1 y R2 son ER -> R1 + R2 es también una ER
6. R1 y R2 son Er entonces R1.R2 es también una ER
7. R es ER entonces R* es también una ER
8. R es ER entonces (R) es también una ER

#### Expresión Regular Universal (ERU)
Aquella que representa todas las cadenas que se pueden formar con un alfabeto dado (es Σ*)

#### Ejemplo de ER:
La ER a(b+c)\*a representa todas las cadenas que comienzan y terminan exactamente con una *a* y en el medio puede tener una cantidad arbitraria (puede ser ninguna) de *b* o *c*

# Expresiones Regulares Extendidas (MetaER)
"Buscar por un patrón y reemplazar por otro"
Permite usar otros operadores que hacen más facil armar las ER
Hay distintos tipos de extensiones, pero las más comunes son las siguientes:

| Metacaracter |    Descripción    |                                           Comentario                                            |
| :----------: | :---------------: | :---------------------------------------------------------------------------------------------: |
|      .       |       Punto       | Cualquier caracter (generico), salvo \\n dado que los programas de ER suelen analizar por línea |
|      \|      |       Pipe        |                            Operador de unión (corresponde a + en ER)                            |
|     \[ ]     |     Corchete      |                    Enumera conjunto de caracteres (alternativa a usar unión)                    |
|    \[ ^ ]    |  Con Circunflejo  |                               Complemento del conjunto enumerado                                |
|    \[ - ]    |     Con Guión     |             Da un rango de caracteres \[ 0 - 9 ], es la unión de todos los dígitos              |
|     { }      |      Llaves       |                         Indica potenciación. *b{3}* corresponde a *bbb*                         |
|    { , }     |     Con Coma      |       Unión de todas las potencias entre la primera y la última. *b{2, 3}* es *bb + bbb*        |
|      ?       | Signo de Pregunta |                       Indica opción (cero o una vez). *b?* es (b+ε)                       |
|      *       |     Asterisco     |                                       Clausura de Kleene                                        |
|      +       |        Más        |                                        Clausura Positiva                                        |
|     ( )      |    Paréntesis     |                             Se utiliza para agrupar subexpresiones                              |
|      ^       |    Circunflejo    |        La expresión debe estar al principio de la linea. *\^R* es una regex al principio        |
|      $       |       Pesos       |            La expresión debe estar al final de la linea. *\$R* es una regex al final            |
|     \\w      |  Expresion Perl   |                Matchear palabras (mayúsculas, minúsculas, números y guión bajo)                 |
|      \W      |  Expresion Perl   |                                     Complemento de palabras                                     |
#### Ejemplo:
Regex: \[a-zA-Z]\[a-zA-Z0-9_-]{3, 11} 
- Cadena que comienza con una letra y continúa con letras o dígitos o guión bajo o guión medio en cantidad de 3 a 11

Regex: 0\[xX]\[0-9a-fA-F]+
- Constantes hexadecimales "similares" a las de lenguaje C, + es Clausura Positiva

### Tabla de Clausuras sobre operaciones
|   Operación   | LR  | LIC | LSC | LRE |
| :-----------: | :-: | :-: | :-: | :-: |
|     Unión     | Si  | Si  | Si  | Si  |
| Concatenación | Si  | Si  | Si  | Si  |
|  Intesección  | Si  | No  | Si  | Si  |
|  Complemento  | Si  | No  | Si  | No  |
#### Definición Regular:
ER Auxiliar que simplifica la definición de otra ER más compleja
- Ejemplo para constantes Hexadecimales en lenguaje C:
	- PRE = 0\[xX]
	- DH = \[0-9a-fA-F]
	- SU = \[uU]
	- SL = \[lL]
	- ER = PRE DH+ (SU SL | SL SU | SU | SL)
#### Subexpresiones
