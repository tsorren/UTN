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
