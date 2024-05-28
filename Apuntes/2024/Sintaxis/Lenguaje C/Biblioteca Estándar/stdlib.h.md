### <stdlib.h>
Utilidades varias, entre ellas:

Manejo de memoria:
- malloc (new)
- free (delete)

Aleatorios: 
- rand
- srand

Conversiones varias de string a numeros:
- strtod
- atof
- etc

Búsqueda y ordenamiento
- bsearch
- qsort

Funciones con enteros
- abs

### <string.h>
El lenguaje C no maneja cadenas como elemento del lenguaje, lo asimila a secuencia de caracteres con un "centinela" o ward (\\0) que indica el fin de la secuencia
Reservar memoria para las cadenas es tarea del programador. Los métodos habituales son declarar un vector de caracteres o usar la funcion `malloc()`
La lógica para manipular cadenas es recorrerlas y operarlas carácter a carácter
La biblioteca estándar **string.h** provee varias funciones para operar con cadenas 

Declaración:
```c
// Como vector
char palabra [10]; // Permite gurdar cadenas de hasta 9 caracteres, ya que debemos contemplar el '\0' final
char frase[] = "Hola mundo"; // El vector fras se dimensiona automáticamente de 11 posiciones (10 caracteres + '\0' final)

char frase[100] = "Hola mundo"; // Las posiciones no inicializadas quedan explicitamente en cero, como cualquier vector

// El estandar no permite inicializar con cadena de más elementos que la dimension del vector
// Si pongo un literal del mismo largo que la dimension del vector, no añade el '\0'

char palabra[5] = "Hola";
char palaba[5] = {'H', 'o', 'l', 'a', '\0'};

char palabra [10];

palabra = "Hola"; // Esto es incorrecto ya que el vector solo se puede usar para inicializar
strcpy(palabra, "Hola") // Esta es la manera correcta, strcpy es parte de string.h

// Puedo simplemente definir un puntero a char, pero eso no reserva memoria para los datos, debo hacerlo aparte
char *cadena;
cadena = malloc(20); // Devuelve puntero, o NULL si no hay memoria disponible
strcpy(cadena, "Hola");

// Si lazona de memoria ya está reservada, puedo apuntarla directamente
char buffer[512];
char *cadena = buffer;

char *saludo = "Hola";
// El tipo de dato de un literal cadena es un arreglo de caracteres constante, que se degrada a const char*. Puede que no sea (fisicamente) modificable

```

Funciones de string.h
```c
size_t strlen(const char *s); // Devuelve el largo de la cadena en bytes (sin incluir el '\0')
char pais[20] = "Argentina";
char *p = malloc(strlen(pais) + 1)
strcpy(p, pais);

char pais[20] = "Argentina";
char *p = strdup(pais) // A partir de C23, string duplicate

char *strdup(const char *s); // Duplica la cadena s, pide memoria con malloy y copia la cadena. Devuelve puntero a la cadena duplicada o NULL

char *strndup(const char *s, size_t n); // Toma hasta caracter n

char *strcpy(char * restrict s1, const char * restrict s2); // Copia la cadena apuntada por s2 en la memoria apuntada por s1

char *strncpy(char * restrict s1, const char * restrict s2, size_t n); // Copia los primeros n caracteres, el resto se llena con '\0'

char *strcat(char * restrict s1, const char * restrict s2) // Agrega una copia de la cadena apuntada por s2 al final de la cadena s1

char *strncat(char * restrict s1, const char * restrict s2, size_t n); // Similar a la anterior pero agrega a lo sumo n caracteres de s2

int strcmp(const char *s1, const char *s2); 
/*
	> 0 si s1 > s2
	< 0 si s1 < s2
	= 0 si s1 == s2
*/

int strncmp(const char *s1, const char *s2, size_t n); 

```