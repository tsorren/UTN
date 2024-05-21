# Algoritmos



# Detalles
## Biblioteca Estándar
- Implementa funcionalidades habitualmente requeridas.
- Las funciones son declaradas en un header (encabezado), junto con las macro que puedan ser necesarias.
- En C23 hay 31 encabezados que agrupan funciones relacionadas (C23:7.1.2-3).

###### Identificadores reservados (C23:7.1.3 Reserved Identifiers)
- Si comienza con doble guión bajo o guión bajo mayúscula.
- Si comienza con guión bajo en ámbito de archivo.
- Si termina con guión bajo t (ej size_t).
- Si comienza con E seguido de dígito u mayúscula (códigos de errores)

- Reserved words:
	- No se deben utilizar nunca para declarar ni definir
	- Reemplazan los namespaces

- Keywords:
	- while
	- if
	- int

- Funciones comunes: 
	- malloc -> new
	- free -> delete
	- assert

###### No existe la sobrecarga de funciones
###### Las arrays son punteros
## <stdio.h>
Entrada y salida, puede ser contra un archivo, terminal de consola, o otro dispositivo.
##### Flujos de datos (FILE):
No se restringen a archivos aunque sea su uso habitual.
Es una estructura definida en stdio.h, contiene los datos necesarios para el manejo de flujo.
- Buffers
- Posición dentro del archivo para la proxima operación
- Estado, por ejemplo EOF o errores varios
- Administración de concurrencia (lock para hilos)

Declaración.
```c
// nombre_archivo es el "pathname"
// tipo_apertura es la modalidad (r, w, a, b, +, x)
// Devuelve el puntero al FILE creado o NULL si falla
FILE *fopen (const char *nombre_archivo, const char *tipo_apertura);
int fclose(FILE *flujo);

FILE archivo = fopen("datos.dat", "r");
fclose(archivo);
```

| Tipo | Modo          |       Descripción       | Posición inicial |
| :--: | :-----------: | :---------------------: | :--------------: |
| r    | Lectura       | Debe existir el archivo | Al principio     |
| w    | Escritura     |  Crea el archivo, pisa  | Al principio     |
| a    | Agregar       | Debe existir el archivo | Al final         |
| b    | binario       |                         | -                |
| +    | Actualización |                         | -                |
| x    | Exclusivo     |                         | -                |

| Caracteristicas | Modo Binario | Texto |
| :-------------: | :----------: | :---: |
|    Convierte    |      No      |  Si   |
|  Pierde datos   |      No      |  Si   |

###### Flujos estándar:
Hay flujos que ya están abiertos
- stdin (teclado habitualmente)
- stdout (consola habitualmente)
- stderr (consola habitualmente)

|     main     |    header     |
| :----------: | :-----------: |
| Definiciones | Declaraciones |
###### Archivos:
``` c
size_t fwrite(const void *datos, size_t tamaño_individual, size_t cuantos, FILE *flujo);

escritos = fwrite(vector, sizeof(int), 5, archivo);
// fwrite devuelve la cantidad de elementos efectivamente escritos, si no hay error es igual a "cuantos"

size_t fread(void *datos, size_t tamaño_individual, size_t cuantos, FILE *flujo);

leidos = fread(&velocidad, sizeof(double), 1, archivo)

while(leidos) // Leidos == 1
{
	...
}

```
##### Entrada y Salida de Texto con formato:

``` c
printf();
scanf();
```
El primer parámetro de las funciones indica el formato , para intercalar variabls se usa el símbolo % como secuencia de escape, seguido de el indicador de formato.
Cada secuencia de escape se reemplaza por el valor del parámetro adicional

| Secuencia |                                         Uso                                          |
| :-------: | :----------------------------------------------------------------------------------: |
|  d, i, u  | Números enteros en base 10 (en scanf "i" trata de detectar la base), "u" es unsigned |
|     o     |                                Enteros en base octal                                 |
|   x, X    |           Enteros en base hexadecimal, X usa mayúsculas, x usa minúsculas            |
|   b, B    |                     Enteros en binario, con 0b o 0B como prefijo                     |
|     c     |                                       Caracter                                       |
|     s     |                                        String                                        |
|     f     |                           Double en printf, float en scanf                           |
|   e, E    |                           Flotante con notación científica                           |
|     p     |                                       Punteros                                       |
|     %     |                              Mostrar un % en la salida                               |

| Modificador |                  Uso                  |
| :---------: | :-----------------------------------: |
|      l      |               Para long               |
|      L      | Para long double (se usa Lf en scanf) |
##### Lectura y Escritura en modo texto
```c
fprintf();
fscanf();
```
Reciben FILE* como primer parámetro, lo demás es igual, trabajan en un flujo específico. printf es fprintf(stdout, ...)

snprintf tiene seguridad contra ataques de buffer overflow

##### Lectura por línea
``` c
char *fgets(char *string, int cuantos, FILE *flujo);
```
- Lee hasta encontrar un \\n
- Incluye el \\n y agrega un \\0 para terminar la cadena correctamente
- Guarda lo leído en lo apuntado por string
- Si no encuentra un \\n, frena al leer (cuantos - 1) caracteres, ya que reserva lugar para el \\0
- Siempre agrega \\0 al final, eventualmente sobre el \\n
- Si hay un \\0 en medio del flujo, fgets falla
- Si falla devuelve NULL, sino devuelve el puntero de la string
- \\0 es un ward o centinela, no pertenece al alfabeto reconocible, por lo que se deja de leer

``` c
char *gets(char *string);
```
- Similar a fgets pero lee desde stdin. Deprecado en C99, eliminado en C11
- Lee hasta \\n pero NO lo oncluye en lo leído (a diferencia de fgets). Agrega un \\0 para terminar correctamente la cadena
- No hay control de máxima cantidad de caracteres, por lo que es peligroso y se suele usar getline o algo similar

``` c
char *gets_s(char *string, rsize_t n);
```
- Disponible en forma optativa a partir de C11, pero no suele estar implementada en los compiladores
- El estándar recomienda usar fgets en su lugar
- Lee hasta \\n o EOF o error, a lo sumo n-1 caracteres, para agregar \\0 al final

##### Escritura por línea
``` c
int fputs(const char *string, FILE *flujo);
```
- Escribe la cadena string en el archivo flujo
- No añade el \\n
``` c
int puts(const char *string, FILE *flujo);
```
- Escribe la cadena string en el archivo flujo
- Añade un \\n a la cadena

##### Lectura por caracteres
``` c
int fgetc(FILE *flujo);
```
- Lee desde flujo un carácter
- Devuelve un int para poder incluir EOF

``` c
int getc(FILE *flujo);
```
- Lee desde flujo un carácter
- No lee de stdin, sino que es una version optimizada de fgetc
- Se implementa como macro, por lo tanto no podemos pasar parámetros que tengan efectos de lado ni obtener la dirección de la función

``` c
int getchar(void);
```
- Lee desde stdin un caracter
- Es la versión de fgetc que lee de stdin

##### Escritura por caracteres
``` c
int fputc(intc, FILE *flujo);
```
- Convierte c al tipo unsigned char y lo escribe en el flujo
- Si no hubo error devuelve c, sino EOF

```c
int putc(int c, FILE *flujo);
```
- Versión optimizada de fputc

```c
int putchar(int c);
```
- Escribe c a stdout

```c
int ungetc(int c, FILE *flujo);
```
- No es propiamente de escritura
- Se utiliza para devolver un carácter leído al flujo
- Es habitual en algoritmos que deben reconocer patrones

##### Posicionamiento
Indica donde haremos nuestra próxima operación, sea de lectura o escritura, ya que mira al archivo como una cadena de bytes

Consultar posición actual:
```c
long int ftell(FILE *flujo);
off_t ftello(FILE *flujo);
```
- Devuelven -1 si hubo error

Cambiar la posición:
```c
int fseek(FILE *flujo, long int desp, int desde_donde);
int fseeko(FILE *flujo, off_t desp, int desde_donde);
```
- Si hubo exito devuelven 0
- El parametro *desde_donde* puede ser:
	- SEEK_SET (desde el inicio)
	- SEEK_CUR (desde la pos actual)
	- SEEK_END (desde el final)

Cerrar archivos:
```c
int fcloseall(void);
```
- Devuelve 0 si pudo cerrarlos todos, EOF si hubo alguno

Consultar si se llegó al EOF en un archivo:
```c
int feof(FILE *flujo);
```
- Devuelve algo distinto de cero, o sea verdadero, si se llego al final del archivo

Bajar buffers a disco:
```c
int fflush(FILE *flujo);
```
- Devuelve EOF si hubo error
- Si el parametro *flujo* es NULL, lo hace para todos los archivos abiertos

### <ctype.h>
Funciones que devuelven si un carácter pertenece o no a un grupo (las firmas son del tipo `int isXXX(int c)`):
- isalpha, islower, isupper
- isdigit, isxdigit
- isalnum
- isspace (espacio en blanco y en general \\n, \\r, \\t, \\f, \\v)
- ispunct (imprimible y no es espacio o alfanumerico)

Funciones de conversión:
- tolower
- toupper

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