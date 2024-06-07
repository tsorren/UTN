A partir de premisas, evaluamos la validez de un razonamiento
Se realizan consultas sobre la base de conocimiento
Al describir bien el problema se define la solución
###### Base de conocimiento:
Hechos y reglas lógicas definidas en el código

###### Universo Cerrado:
Todo lo que no pertenezca a la base de conocimiento es falso

### Sintaxis
Todo predicado termina con punto
###### Variables:
Genericas:
	- Comienzan con mayúscula

Individuos:
	- Comienzan con minúscula

###### Operadores:
Entonces:
	a entonces b
	b :- a
	
Conjunción:
	a y b
	a, b
###### Consultas:
Particularización Existencial
Le ocurrió tal cosa a pepito?
	cosa(pepito).

Cuantificacion Existencial
Le ocurrió tal cosa a alguién?
	cosa(\_).

Inversibilidad - Cuantificación Existencial
Le ocurrió tal cosa a alguién? A quién? 
	cosa(Generico).

###### Aridad:
Cantidad de parámetros que tiene un predicado

###### Backtracking:
Prolog prueba todas las combinaciones posibles para hallar las soluciones

###### Predicados Inversibles:
Se puede consultar con una variable

###### Declaratividad:
Separacion entre el código y los algoritmos que se aplican
El orden no importa