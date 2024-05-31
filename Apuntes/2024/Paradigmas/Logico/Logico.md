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
Le ocurrió tal cosa a pepito?
	cosa(pepito).
	
Le ocurrió tal cosa a alguién?
	cosa(\_).
	
Le ocurrió tal cosa a alguién? A quién?
	cosa(Generico).

###### Predicado is
