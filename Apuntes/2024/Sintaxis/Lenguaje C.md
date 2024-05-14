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

### <stdio.h>
Entrada y salida, puede ser contra un archivo, terminal de consola, o otro dispositivo.

###### Flujos de datos (FILE):
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

| Tipo | Modo          | Descripción             | Posición inicial |
| :--: | :-----------: | :---------------------: | :--------------: |
| r    | Lectura       | Debe existir el archivo | Al principio     |
| w    | Escritura     | Crea el archivo, pisa   | Al principio     |
| a    | Agregar       | Debe existir el archio  | Al final         |
| b    | binario       |                         | -                |
| +    | Actualización |                         | -                |
| x    | Exclusivo     |                         | -                |

###### Flujos estándar:
Hay flujos que ya están abiertos
- stdin (teclado habitualmente)
- stdout (consola habitualmente)
- stderr (consola habitualmente)
##### Archivos

|     main     |    header     |
| :----------: | :-----------: |
| Definiciones | Declaraciones |
