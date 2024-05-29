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
