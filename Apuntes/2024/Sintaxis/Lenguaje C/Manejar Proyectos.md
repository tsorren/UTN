Al incluir un header, damos direcciones al preprocesador para que lo haga una sola vez
header.h
```c
#ifnded HEADER_H_INCLUDED
#define HEADER_H_INCLUDED

...header

#endif // HEADER_H_INCLUDED
```

Construcción de Software:
	Lento: gcc  -g -Wall -c pedantic-errors -std=c23 \*.c -o imagen.exe
	Eficiente: make

#### Makefile:
La herramienta make facilita la construcción de software
Además de automatizar la construcción, también se gestionan las dependencias, de modo de no volver a construir todo, cuando solo una parte fue modificada
Se compone de reglas y comandos:
	objetivo: dependencias
	comando
	comando
	...
	
El objetivo generalmente es un archivo a construir. También puede ser una acción a realizar, como por ejemplo borrar archivo intermedios o temporales de la construcción.
Las dependencias son los archivos que deben construirse primero. Se controlarán las fechas de modificación, si la fecha del objetivo es posterior a las fechas de las dependencias, implica que está al día y no hace falta volver a construirlo. 
- Si una acción tiene dependencias, se controlará que esta exista y esté actualizada.
Los comandos son las acciones a realizar para construir el objetivo. Pueden ser varios. Deben comenzar con un tabulador ('\\t') para que se interpreten como tales.

##### Sintaxis:
Comentarios: puedo ponerlos comenzando la línea con un #.
Para marcar un objetivo como acción se pone .PHONY objetivo
Se puede asignar valores a variables y luego usarlos. Por ejemplo:
- CFLAGS = -g -Wall -c -pedantic-errors -std=c2x
-  Y luego en un comando
- gcc $(CFLAGS) main.c -o main.o
###### Otros:
Reglas Implícitas, hay varias por ejemplo si tengo una dependencia archivo.o y no tengo regla, make aplicará la siguiente regla implícita a partir de archivo.c:
- $(CC) $(CPPFLAGS) $(CFLAGS) -c
Notar el uso de variables como CFLAGS, que ya mostramos en el ejemplo anterior.
Algunas variables predefinidas:
- $<: es el primer item en la lista de dependencias
-  $@: nombre del objetivo
-  $^: Esta variable representa todas las dependencias de la regla de compilación.
Comando info: se utiliza para que muestre el valor de una variable.
Por ejemplo:
- \$(info CFLAGS=\$(CFLAGS))
##### Invocación:
Si se invoca solo el comando make buscará las especificaciones en el archivo makefile y construirá el primer objetivo que encuentre.
Si quiero un objetivo en particular lo paso como parámetro al comando make, por ejemplo make run o make clean
Si quiero darle valor a una variable, debo agregar como parámetro el nombre de la variable, seguida de un símbolo = y luego el valor que quiero que tome.
Si quiero usar una archivo diferente de makefiel puedo especificarlo con la bandera -f y luego el nombre del archivo.
Ejemplo: en nuestro ejemplo de fuentes múltiples si quiero usar la especificación dada en el archivo makealt y compilar para debug debo invocar:
- make -f makealt BUILD_TYPE=debug