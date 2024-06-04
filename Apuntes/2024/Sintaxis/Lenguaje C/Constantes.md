### Constantes numéricas Enteras

| Tipo        | Rango     | Descripción             |
| ----------- | --------- | ----------------------- |
| Decimales   | 0-9       | No puede comenzar con 0 |
| Octales     | 0-7       | Comienza con 0          |
| Hexadecimal | 0-9a-zA-Z | Comienza con 0x         |
Sufijos: 

### Constantes numéricas Reales
Decimales:
- Debe tener la parte fraccionaria o el exponente obligatoriamente
 - El exponente comienza con e o E, signo optativo
 Hexadecimales:
 

| Tipo          | Descripción                                                                                                                                                                    |
| ------------- | ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ |
| Decimales     | <br>                                                                                                                                                                           |
| Hexadecimales | Comienza con 0x, se escribe en hexa<br>Debe tener la parte fraccionaria o el exponente obligatoriamente<br>El exponente comienza con p o P y se escribe en decimal, con base 2 |
| Ambos         | El punto de la parte fraccionaria no puede tener digitos adelante o atrás                                                                                                      |
Sufijos: l, L, f, F (F es float, L es long double, sin sufijo es double)

### Constantes de Carácter:
Delimitadas entre comillas simples `' '`
Se declaran de tipo `char`, pero son de tipo `int`
El tipo `char` es tomado como `unsigned char` o `signed char` 

| Caracter Ancho      | Biblioteca | Prefijo |
| ------------------- | ---------- | ------- |
| wchar_t             | stddef.h   | L       |
| char16_t            | uchar.h    | u       |
| char32_T            | uchar.h    | U       |
| char8_t (largo var) | uchar.h    | u8      |

### Constantes de Enumeración:
Se definen con `enum`
```c
enum colores {ROJO, AMARILLO = 3, VERDE};
enum colores : short int {ROJO, AMARILLO = 3, VERDE}; // Tipo de dato explicito en C23
enum colores col = VERDE; // asigna 4 a "int col"
```
Son constantes simples de tipo int, node finen un nuevo tipo de dato

### Literales de Cadena:
Se encierran entre comillas dobles `" "`
El final está delimitado por `'\0'`
Se puede aplicar `\` para poder incluir secuencias de escape
El tipo de dato es `char[]` y es usado como `char*` que es a lo que degrada
Cadenas adyacentes se concatenan
Se pueden agregar prefijos:
- Los típicos de char
- UTF-8: u8

### Puntuación:
Dependen del contexto
Pueden indicar operación
```  
[ ] ( ) { } ,  ->  ++  --  &  *  +  -  ~  !  /  %  <<  >>  <  >  <=  =>  ==  !=  ^  |  &&  ||
?  :  ::  ;  ...  =  *=  /=  %=  +=  -=  <<=  >>=  &=  ^=  |=  ,  #  ##
```
