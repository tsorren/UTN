### Constantes numéricas Enteras

| Tipo        | Rango     | Descripción             |
| ----------- | --------- | ----------------------- |
| Decimales   | 0-9       | No puede comenzar con 0 |
| Octales     | 0-7       | Comienza con 0          |
| Hexadecimal | 0-9a-zA-Z | Comienza con 0x ó 0X    |
Sufijos: l, L, u, U, ll, LL. Pueden combinarse en cualquier orden, salvo L con LL, pueden ser mayúsculas o minúsculas

### Constantes numéricas Reales

| Tipo          | Descripción                                                                                                                                                                    |
| ------------- | ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ |
| Decimales     | Debe tener la parte fraccionaria (1. ó 1.2 ó .2) o el exponente (7E0) obligatoriamente<br>El exponente comienza con e o E<br>El signo es optativo, no es parte de la constante |
| Hexadecimales | Comienza con 0x, se escribe en hexa<br>Debe tener la parte fraccionaria o el exponente obligatoriamente<br>El exponente comienza con p o P y se escribe en decimal, con base 2 |
| Ambos         | El punto de la parte fraccionaria puede no tener digitos adelante o atrás                                                                                                      |
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
El final está delimitado por  \\0
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

|  Precedencia  |                              Operador                              |          Asociatividad          |                                                                                             Descripción                                                                                              |
| :-----------: | :----------------------------------------------------------------: | :-----------------------------: | :--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------: |
|   <br><br>1   |          ++  --<br>( )<br>\[ ]<br>.<br>-><br>(type){list}          |   <br><br>Izquierda a Derecha   |   Prefijo o Sufijo de Incremento y Decremento<br>Llamada a función<br>Subíndice de vector<br>Acceso a miembro de struct y union<br>Acceso a miembro de struct y union por puntero<br>Cast a struct   |
| <br><br><br>2 | ++  --<br>+  -<br>!  ~<br>(type)<br>\*<br>&<br>sizeof<br>\_Alignof | <br><br><br>Derecha a Izquierda | Prefijo de incremento y decremento<br>Suma y resta unaria<br>NOT lógico y NOT binario<br>Cast a tipo<br>Desreferenciación<br>Dirección en memoria<br>Tamaño de tipo de dato<br>Alineación en memoria |
|       3       |                              *  /  %                               |       Izquierda a Derecha       |                                                                                   Multiplicación, división y resto                                                                                   |
|       4       |                                +  -                                |       Izquierda a Derecha       |                                                                                             Suma y resta                                                                                             |
|       5       |                               <<  >>                               |       Izquierda a Derecha       |                                                                                   Shift Left y Shift Right Binario                                                                                   |
|       6       |                            <  <=  >  >=                            |       Izquierda a Derecha       |                                                                                      Operadores de comparación                                                                                       |
|       7       |                               ==  !=                               |       Izquierda a Derecha       |                                                                                      Operadores de comparación                                                                                       |
|       8       |                                 &                                  |       Izquierda a Derecha       |                                                                                             AND Binario                                                                                              |
|       9       |                                 ^                                  |       Izquierda a Derecha       |                                                                                             XOR Binario                                                                                              |
|      10       |                                 \|                                 |       Izquierda a Derecha       |                                                                                              OR Binario                                                                                              |
|      11       |                                 &&                                 |       Izquierda a Derecha       |                                                                                              AND Lógico                                                                                              |
|      12       |                                \|\|                                |       Izquierda a Derecha       |                                                                                              OR Lógico                                                                                               |
|      13       |                                ?  :                                |       Izquierda a Derecha       |                                                                                         Condicional ternario                                                                                         |
|  <br><br>14   |        =<br>+=  -=<br>*=  /=  %=<br><<=  >>=<br>&= ^=  \|=         |   <br><br>Izquierda a Derecha   |      Asignación simple<br>Asignación por suma y resta<br>Asignación por producto, división y módulo<br>Asignación por Shift Left y Shift Right Binario<br>Asignación por AND, XOR y OR Binario       |
|      15       |                                 ,                                  |       Izquierda a Derecha       |                                                                                           Coma, separador                                                                                            |
##### Otros casos:
- `{ }`delimitan bloques
- `;` transforma una expresión en una sentencia o separa expresiones dentro de `for`
- `,` se utiliza para separar variables en su declaración o definicion y para separar argumentos de una función
- `:` se utiliza en etiquetas, ya sea para `goto` o para los distintos casos dentro de un `switch`
- `...` se utilizan para declarar o definir funciones con cantidad variable de argumentos
- `#` directiva de preprocesador u operador para convertir a cadena
- `##` operador de pegar tokens

