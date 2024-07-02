#### Conceptos básicos:
Objeto: Zona contigua de memoria que puede contener un valor de un tipo dado
Tipo: Define un conjunto de valores posibles y un conjunto de operaciones
Valor: Es un conjunto de bits en la memoria interpretados según un tipo

Identificador:
Permite designar
- Objetos: variable
- Funciones
- El nombre (tag) o los miembros de: estructuras, uniones y enumeraciones
- "Alias" de tipos de datos (typedef)
- Una etiqueta (para saltos)
- Una macro o sus parámetros
- Un atributo (C23)
#### Tipos de datos:
El significado de un valor guardado en un objeto o devuelto por una función está determinado por el tipo de expresión usado para accederlo
La expresión más simple es un identificador, y su tipo fue especificado al declararlo
Los tipos se dividen en tipos de **objetos** (variables) y tipos de **funciones** (que describen su firma)
Los tipos de objetos pueden, en un determinado punto de la unidad de traducción, estar incompletos (y ser completados luego).
Cuando esto ocurre, no se puede especificar el tamaño necesario para guardarlo.
Por lo tanto no se puede declarar variables de un tipo incompleto (pero si punteros)
Casos:
- Arreglos sin dimensión
- Estructuras o uniones sin sus miembros

#### Tipos de Objetos (básicos):
Void: Es un tipo especial, ya que tiene un conjunto vacio de valores, se lo considera incompleto y no puede completarse

\_Bool (`bool` en C23): Es considerado de tipo entero sin signo con la capacidad necesaria para almacenar un 0 y un 1 (típicamente un byte)
Si se le asigna el valor de una expresión entera, su valor será 0 si la expresión era igual a cero y 1 en cualquier otro caso

Tipos carácter: `char, unsigned char, signed char`
Se los considera 3 tipos diferentes, `char` termina siendo signed o unsigned dependiendo de la implementación
Tiene espacio necesario para guardar un carácter del juego básico (típicamente un byte)

Tipos enumerados: Cada vez que defino un `enum` tag se lo considera un tipo enumerado
Tipos enteros estándar: `int` y `char` con y sin signo, incluye las varientes de `int` como `short, long, long long` y los tipos de enumeración
Tipos enteros: Los enteros estándar más \_Bool
Tipos reales flotantes: `float, double, long double`
Tipos complejos: Su implementación es optativa `float \_Complex, double \_Complex, long double \_Complex`
Tipos flotantes: La unión de reales flotantes y complejos
Tipos reales: La unión de reales flotantes más los tipos enteros
Tipos aritméticos: La unión de flotantes más los tipos enteros
Tipos básicos: La unión de tipos de carácter, con tipos enteros y tipos flotantes. Son tipos completos (todo lo nombrado excepto void)

#### Tipos Derivados:
A partir de los tipos de objetos y de funciones se pueden derivar otros:
Tipo arreglo: Área contigua de memoria donde hay una cantidad no vacía de miembros que son objetos de un determinado tipo
Tipo estructura: Aloja una secuencia no vacía de miembros objetos que puyeden ser de diferentes tipos
Tipo unión: Similar a la estructura pero memoria asignada a los miembros se solapa (todas comienzan al principio de la unión, solo 1 var viva a la vez)
Tipo función: Las funciones se caracterizan por el tipo que devuelven y, la cantidad y tipo de sus parámetros. Dado un tipo T, la derivación en función es una función que devuelve T
Tipo puntero: Pueden derivar de un tipo objeto o función, llamado genéricamente tipo referenciado
Se pueden derivar tipos recursivamente (Arreglo de estructuras, arreglo de arreglos de punteros a funciones, etc)

#### Otros Tipos de Datos:
Tipos agregados: La unión de tipo estructura y tipo arreglo
Tipos escalares: La unión de tipo aritmético y tipo puntero

ValorL: Es una expresión que permite designar (ubicar) un objeto y recuperar su valor. 
El caso más simple es el identificador de una variable. Por ejemplo, de tipo básico, un elemento de un arreglo, o lo apuntado por un puntero
Un ValorL es modificable si no fue calificado como constante, ni es una estructura o unión con un miembro calificado como constante
Tampoco son ValorL modificables los arreglos (no se refiere a sus elementos) y los tipos incompletos

ValorR: Es el valor en si mismo, es una expresión

#### Otros
Equivalencias: Por ejemplo, `int` es equivalente a `*&int`
Compatibilidad de Tipos: Cuando puedo usar un tipo de datos donde se esperaba otro. Por ejemplo `int` en lugar de `char`, `short` donde se esperaba un `long`
Inferencia de Tipos: Dada una expresión, escoje el tipo de dato que debe usarse.

#### Chequeos de Tipos de Datos:
Chequeo estático: Los tipos se definen en el fuente, en tiempo de compilación
Chequeo dinámico: Los tipos se definen en tiempo de ejecución
Combinación: Hay lenguajes que usan los dos tipos de chequeos

Fuerte/Debilmente tipados: No es una categoría precisa, es más bien de uso informal
Fuertemente tipado exige que el programador haga conversiones explicitas, o bien no permite hacerlas

#### Declaración y Definición:
Declaración: Especifica los atributos y la interpretación del idenficador
Sirve también para que una unidad de traducción referencie a objetos o funciones definidas en otra unidad de traducción

Definición: Es una declaración que además
Si es un objeto causa que se reserve memoria para alojarlo
Si es una función incluye el código de la misma

Para un objeto o función se puede tener varias declaraciones pero solo una definición

#### Ámbito / Alcance (Scope) - General
Dado un identificador, este hace referencia a un objeto, pero solo en ciertas partes del programa esta vinculación está activa
Hablamos de "donde es visible" o donde está vinculado o enlazado (el nombre con el objeto), en inglés: name binding. 
Puede ser interpretado como un Intervalo de lineas \[x, y\].
Los identificadores de mayor alcance pueden ser ocultados en un sub-ámbito al redefinir el identificador en el mismo espacio de nombre.

Léxico (estático, lenguaje C): Definido por el fuente
Dinámico (lenguajes funcionales): Definido por el orden de llamada entre las subrutinas
###### Niveles:
- Expresión: En general lenguajes funcionales
- Bloque: Son declarados dentro de él, viven dentro de este bloque y sus anidados. Los argumentos de una función tienen alcance de bloque (función), viven dentro de ella. 
- Función: Archivo completo (funciones, etiquetas goto).
- Archivo (Fuentes): Tomar C como ejemplo, desde la línea *n* hasta el fin del archivo
- Modulo: Conjunto de archivos
- Global: Todo el sistema

###### Vinculación - Linkage:
Se refiere a que el mismo identificador pueda designar el mismo objeto (o no) en distintas unidades de traducción o solo dentro de una
- Externa: Desde distintas unidades de traducción
- Intera: Desde una unidad de traducción
- Sin vinculación: Solo en su bloque (variables locales y argumentos de la función)

###### Definiciones Tentativas - Predefinido:
En C se admite una mala práctica en la cual se puede definir varias veces un identificador y tomar una sola como definición, el resto son "tentativas" (actuan como declaración)
- En distintas unidades de traducción (fuentes)
- En la misma pero a nivel archivo

Identificador predefinido: En cada función está disponible, sin necesidad de definirlo, el identificador \_\_func\_\_ que es el arreglo de caracteres con el nombre de la función.

##### Ejemplos de identificadores:
```c
extern int var;        // Declaro var, definida en otro fuente
int varex;             // Ámbito de archivo, vinculación externa
static int varin;      // Ámbito de archivo, vinculación interna (no se puede ver desde afuera)

int f1(void)           // Por defecto las funciones tienen vinculación externa
{
	int a;             // Defino a, ámbito de bloque, alcance desde luego de su definición hasta antes de la llave que cierra
	...
}

static int f2(int arg) // Vinculación interna (No se ve desde otros fuentes)
{
	int a;             // Diferente a la de f1, en otro ámbito, sin vinculación (mismo espacio de nombres pero no hay error)
	static int b;      // Ámbito en f2, pero "vive" durante toda la ejecución, se asigna su espacio en memoria al inciar el programa

	int c = 1;
	int d, e = 2, *pi, arr[3]; // Mal estilo en general, pero permitido ( int d = 0 por no ser definido, int e = 2, int *pi, int arr[3] )
}
```

#### Espacios de nombre:
Permiten referirse a objetos distintos con un mismo identificador en el mismo ámbito
En C, los espacios de nombre no pueden ser creados por el programador pero existen predefinidos

Nombres calificados: Utilizar un prefijo para indicar un espacio de nombre del identificador
###### Espacios de nombre de C:
- Etiquetas, para goto `:`
- Tags, el nombre de estructuras, uniones y enumeraciones
- Los miembros de las estructuras y uniones pertenecen al espacio de nombre creado por su tag
- Los atributos (separados en el estándar con sus prefijos y los que siguen a un prefijo, van con doble corchete)
- Los identificadores ordinarios (comunes): Todos los demás, incluyendo variables, funciones, constantes de enumeración y alias de tipos introducidos con `typedef` 

##### Ejemplo de Espacios de nombres:
```c
int fun(void)
{
	return 3;
}
int fun;                             // Error, hay 2 definiciones del identificador fun en el espacio de nombre ordinario y en el mismo ámbito


int main(void)
{
	int nombre                      // Ok
	struct nombre {int campo;};     // Ok, mismo ámbito pero distinto espacio de nombres (ordinario y de tags/nombres)
	struct otra {int campo;};       // Ok, distinto espacio de nombre (espacio de miembros de nombre y espacio de miembros de otra)

	enum otra {UNO, DOS, nombre}    // ID otra ya pertenece al espacio de nombres de tags,
	                                // nombre (dentro del enum) pertenece al espacio de nombres ordinario que ya esta usado
	int fun;                        // Espacio de nombres ordinario pero distinto ámbito, oculta lo declarado a nivel de archivo

nombre:                             // Ok, las etiquetas (para goto) tienen su propio espacio de nombres
	return EXIT_SUCCESS;
}
```
#### Duración (Tiempo de Vida):
Lapso en el cuál hay una zona de memoria reservada para el objeto:

Deterministico: Su creación / destrucción está determinada de antemano, como en C, con las variables automáticas o estáticas
Dinámico: Depende de la ejecución del programa: `malloc(), free(), new, delete`