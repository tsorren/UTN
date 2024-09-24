

#### Ejercicios:

1
``` c
/*
Dada la BNF:
<sentenciaAsignacion> ::= <identificador> OpAsig <expresion> SgPunt

Construir una func C que implemente el PAS de esta producción
*/

void SentenciaAsignacion(void)
{
	Identificador();
	MATCH(OpAsig);
	Expresion();
	MATCH(SgPunt);
}
```

2
```c
/*
Dada la BNF:
<FACTOR> ::= PAREN_IZQ <EXP> PAREN_DER | NRO

Construir una func C que implemente el PAS de esta producción
*/

void Factor(void)
{
	TOKEN tok = ProximoToken();
	switch(tok)
	{
		case PAREN_IZQ:
			MATCH(PAREN_IZQ);
			Expresion();
			MATCH(PAREN_DER);
			break;
		case NRO:
			MATCH(tok);
			break;
		default:
			ErrorSintactico(tok);
			break;
	}
}
```

3
```c
/*
Dada la siguiente BNF:
<Exp> ::= <Operando> {SUM <Operando> | MULT <Operando>}

Construya una func C que implemente el PAS de esta producción
*/

void Exp()
{
	Operando();
	TOKEN tok;
	while(tok == SUM || tok == MULT)
	{
		MATCH(tok);
		Operando();
		tok = ProximoToken();
	}
}
```

4
```c
// Sea el siguiente PAS:

void PS(void)
{
	TOKEN tok = ProximoToken();
	switch(tok)
	{
		case A: MATCH(A); break;
		case B: MATCH(B); break;
		case C: MATCH(C); D(); Match(E); break;
		default: ErrorSintactico(tok); break;
	}
}


// <PS> ::= A | B | C <D> E

```

5
```c

// Sea el siguiente PAS

void Sent1(void)
{
	Sent2();
	while(1)
	{
		switch(ProximoToken())
		{
			case SGNO:
			case OP_ESP:
				Sent2();
				break;
			default:
				return;
		}
	}
}
// <Sent1> ::= <Sent2> {<Sent2>}

// Recursividad a Derecha
// <Sent1> ::= <Sent2> <Sent1> | <Sent2> 

```

6
```c

// Sea el siguiente PAS 

void Y(void)
{
	MATCH(H);
	while(1)
	{
		switch(ProximoToken())
		{
			case J: MATCH(J); break;
			case Z: MATCH(Z); break;
			default: return;
		}
	}
}

// <Y> ::= H {J | Z}

// Recursividad a Derecha
// <Y> ::= H <A>
// <A> ::= J <A> | Z <A> | epsilon


```

7
```c
Dado el PAS, resuelva los siguientes ítems:
void S(){
	switch(GetProximoToken()){
		case A: Match(A); S(); Match(C); return;
		case B: Match(B); return;
		default: // TODO
	}
}
/*
a. El PAS es sintácticamente correcto.
. Verdadero.
. Falso. Justificación si es falsa:.
b. Dibuje el árbol de expresión de la expresión de la sentencia etiquetada con case B:
c. La sentencia etiquetada con default no fue desarrollada por el programador original, por eso
tiene el comentario TODO (para hacer), complétela arriba, en el propio código.
d. Defina el conjunto de las producciones de la gramática asociada al PAS
e. Escriba una regex que represente el Σ asociado al PAS

a) Verdadero (en C23), Falso (en C17)

b) Arbolito Kawaii >.<
         ( )
      /       \
   Match        B

c) ErrorSintactico(GetProximoToken()); return;

d) <S> ::= A <S> C | B

e) {A-C}
*/

```

8
```c
/*
Es un Scanner implementado a mano, con la tabla por switchs

a) 9 tokens
	EOF
	!=
	(
	c
	=
	getchar
	(
	)
	)
	
b) 3
	!= distinto
	= asignacion
	() invocacion

c) c cambia de valor según la asignación, tambien avanza el puntero de stdin

d)
	enum estado {INICIAL, ...};
	enum estado state;

e)
	c es de tipo int, ya que es lo que devuelve getchar() (EOF es -1)

*/
```