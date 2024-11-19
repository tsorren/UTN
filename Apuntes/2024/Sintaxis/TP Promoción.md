finales en jose maria sola 

Es en grupo
Entrega aprox: 31 de diciembre
El scanner hecho con flex, acoplado con parser en bison
Acciones semánticas que hacen printf deben ser cambiadas

Hay que hacer un transpiler de lenguaje mini a lenguaje c

Las rutinas que hay que generar se asemejan a lo que plantea el libro

hay que declarar variables primero
leer son scanf (uno para cada argumento)

programa total -> include e int main(void) {\\n

entero var; -> int var;
leer(args); -> scanf("%d", &arg);
calcular expresiones -> genera variables temporales para realizar las operaciones segun precedencia
asignacion -> solo se hace luego de calcular la expresión
escribir -> printf("%d", arg)
fin -> return 0; y }

symbol.h

hay que crear diccionario
hay que añadir errores semánticos (falta declaración o ya fue declarada)
solo hay tipo de dato entero

ejemplo:
buscar
colocar
definir -> generaba el codigo
verificar

estructura de datos para almacenar las variables, esto es libre
Lista enlazada

semantic.h
rutinas semánticas para generar código:
contador de temporales

void comenzar(programa)
void terminar()
void asignar(vizq, vder) - Qué lleno y con qué
void leer_id(id) - scanf
void escribir_exp(exp) - printf
char \*gen_infijo(pizq, op, pder) - genera y devuelve temporales, recorre arbol de la expresión
char \*invertir(id)

main 
scaner.l
parser.
symbol.c
semantic.c
diccionario.c ?
makefile -> Supermake que compile a exe y ejecuta (compilar a lenguaje c, compilar de c a exe)
readme.md ?

apuntes teoricos para este tp:
procesos de compilador:
general no hace falta
parte lexica
parte sintactica y semanticaes el importante
principalmente parte semántica
