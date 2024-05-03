Una Expresion Regular (ER, RegEx) es un patrón que describe un conjunto de cadenas de un Lenguaje Regular (LR)
Las Expresiones Regulares se forman con:
- Caracteres del alfabeto del LR representado
- Epsilon para representar la cadena vacía
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

Un cáracter solo es una ER, Epsilon es una ER
- La ER *a* representa el LR {a}
Concatenación:
- La ER a.b o simplemente *ab* representa el LR {ab}
Unión:
- La ER a+b (también a|b en computadora) representa el LR {a,b}
Potenciación: (No es parte de las ER básicas)
- La ER a³ representa el LR {aaa}
Estrella de Kleene
- La ER a* representa el LR {Epsilon, a, aa, aaa, ...}

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
	- a* = {Epsilon, a, aa, aaa...}
	- a⁺ = aa* = a\*a
Igualdades Útiles:
- a\*a\* = a*
- Epsilon* = Epsilon
- a* = aa* + Epsilon
- (ab)* = a(ba)*
- (R*)* = R*
- (R* + S*)* = (R\*S\*) = (R+S)*

### Definición formal de Expresión Regular:
1. Vacio es la ER que representa el conjunto vacío
2. Epsilon es una ER que representa al lenguaje L={Epsilon}
3. x perteneciente a Sigma (Alfabeto) es la ER que representa el Lenguaje L = {x}
4. s perteneciente a Sigma* es la ER que representa el Lenguaje = {s}. Por ej: *s* = *abf* (palabra)
5. R1 y R2 son ER -> R1 + R2 es también una ER
6. R1 y R2 son Er entonces R1.R2 es también una ER
7. R es ER entonces R* es también una ER
8. R es ER entonces (R) es también una ER

### Expresión Regular Universal (ERU)
Aquella que representa todas las cadenas que se pueden formar con un alfabeto dado (es Sigma*)

### Ejemplo de ER:
La ER a(b+c)\*a representa todas las cadenas que comienzan y terminan exactamente con una *a* y en el medio puede tener una cantidad arbitraria (puede ser ninguna) de *b* o *c*
