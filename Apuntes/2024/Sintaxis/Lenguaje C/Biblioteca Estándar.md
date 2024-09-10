 Implementa funcionalidades habitualmente requeridas.
 Las funciones son declaradas en un header (encabezado), junto con las macro que puedan ser necesarias.
 En C23 hay 31 encabezados que agrupan funciones relacionadas (C23:7.1.2-3).

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

El header math.h es el único que de la biblioteca estándar no se añade por si sola al compilar
Hay que usar la opción -lm al compilar

###### No existe la sobrecarga de funciones
###### Las arrays son punteros

### Headers:

![[stdio.h]]

![[ctype.h]]

![[stdlib.h]]