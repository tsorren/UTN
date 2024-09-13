### Paradigma de Objetos - Visión Purista:
Posibilidad de reunir, en una unidad computacional, datos y comportamientos.
Empaquetar estructuras de datos y funciones.

El objetivo es cerrar / encapsular cada parte del sistema para que pueda ser escalado facilmente.
Dividir y Conquistar: Partir el problema en distintas partes para facilitar la resolución de tareas grandes

Una parte del objeto se "muestra" a los demás, mientras que la otra se "oculta", y se mantiene encapsulado

Todo lo que se quiera representar, se trabajará como un objeto.
Lo más importante es definir cómo comunicarse con el objeto.

Alan Kay define el paradigma de objetos en los 70'

La diferencia entre aprender el paradigma de objetos y saber programar en objetos, es como  la diferencia entre aprender las reglas de ajedrez y ser buen jugador de ajedrez.

##### Wollok:
Lenguaje especificamente orientado al paradigma de objetos (purista). Nació en la UTN

Pepita: Golondrina que come y vuela

Correr en REPL:
wollok repl --darkMode archivo.wlk

### Conceptos:
#### Objetos:
Conjuntos computacionales que se comunican entre ellos a través de mensajes
Objetos bien conocidos (WKO): Tienen referencias globales
Los objetos que no son referenciados por nadie son 
#### Mensajes:
Todo mensaje tiene un emisor, un receptor, puede tener parámetros, y puede tener un valor de retorno.

###### Preguntas / Consultas:
No producen ningún efecto en el objeto.

###### Acciones / Ordenes:
Producen un efecto en el objeto, que perdura.

###### Ejemplos:
Los objetos de tipo booleano reciben los mensajes "not obj", "!obj", "obj.negate()"

Objetos de tipo numero:
- a + b
- a - b
- a \* b
- a / b
- numero.times { val => obj.mensaje(val) } // Repetir lambda

Objetos de tipo booleano:
- not obj
- !obj
- obj.negate()

Objetos de tipo lista:
- lista.add()
- lista.get()
- lista.size()
- lista.contains(elem)
- lista1 + lista2

#### Ambiente:

#### Referencias:
Permiten que los objetos se comuniquen.
Pueden ser variables o constantes

#### Atributos:

#### Métodos:

#### Diagrama Dinámico / Diagrama de Clases:
Permite ver los objetos que pertenecen a nuestro ambiente
Los objetos se representan con circulos
Las referencias se representan con flechas (parecido a punteros de alto nivel)

#### Interfaz / Contrato:
Información sobre entrada y salida de los mensajes.
Permite la creación de software a gran escala

#### Implementación:
Se oculta de los demás objetos

#### Polimorfismo:
Todos los objetos que pasen por un proceso deben ser polimorficos, es decir que cumplen con el mismo contrato

#### Maleabilidad:
Capacidad de cambiar de forma sin que se pierda la funcionalidad y sus propiedades.

## Buenas Prácticas:
- No usar Pre-Cálculo para los estados internos de un objeto


Tarea:
- Entorno
- Programar pepita
- Programar comida
- Polimorficamente

## Testeo Unitario y Automático:
Extensión de archivo: .wtest

Es importante pensar en la calidad del programa, aunque ande
Make it work -> Make it right -> Make it fast

Filosofía:
	En Sistemas, el cliente no pide que se haga bien a la primera. El cliente necesita que el Sistema pueda cambiar y adaptarse.
	La idea es construir herramientas partiendo de la premisa de que la gente se equivoca y no sabe lo que quiere.
	Ser un buen ingeniero en sistemas implica permitirle al cliente añadir funcionalidades y probarlas, manteniendo la continuidad del sistema.
	El sistema debe ser modular para que los testeos no lleven la mayor parte del tiempo del ingeniero
#### Fases de test:
Preparación:
	Definir un escenario de testeo
	Reiniciar el universo

Ejercitación:
	Realizar las acciones que se deberán testear

Verificación:
	Comprobar los resultados

Tipos de assert:
- equals(esperado, testear)
- that(testear)
- notThat(testear)

Ejemplo:
```python
import codigo.*
test "nombre de test" {
	assert.that(obj.mensaje()) # Verificar que obj.mensaje() devuelva true
}

# wollok test nombre_test_sin_extension
```

#### Bloques
Se parecen a las lambdas de funcional, yo decido que hacer, otro objeto decide cuando se hace

```python
{pepita.position(pepita.position().right(1))}
```

## Wollok Game
Permite observar nuestro código, brindando una representación de los objetos en una interfaz gráfica

Par poder hacer un juego, debe haber un programa. Se ejecuta usando "wollok run -g nombreArchivo.nombreProgram"
```python
program juego { # Se parece al main de c, se ejecuta al inicial el programa
	
}
```

Para que el juego pueda interactuar con los objetos, se deben respetar los contratos
Game procesa la entrada y salida del usuario, 

Los objetos deben entender los siguientes mensajes:
	position() 
	image() -> Pueden sobrepasar el cellSize,

#### Ciclos de Juego:
Procesamiento de Eventos

Rendering
	Consulta cuál es la imagen de cada objeto cada vez

#### Objeto Game
Entiende los mensajes:
	game.title(str)
	game.height(celdas)
	game.width(celdas)
	game.boardGround(imagen)
	game.start()
	game.stop()
	game.position()
	game.addVisual(objeto)
	game.addVisualCharacter(objeto) - Permite los movimientos para los costados
	game.say(objeto, texto)
	game.onTick(milisegundos, nombreDeEvento, accion)
	game.schedule(milisegundos, accion)
	
#### Objeto Position
Se crean usando game.at(x, y)

var property position crea una referencia que entiende los mensajes position

Entiende los mensajes:
	position.x()
	position.y()
	position.right(cant)
	position.left(cant)
	position.down(cant)
	position.up(cant)
#### Objeto Keyboard
Entiende los mensajes:
	keyboard.right().onPressDo(action)
	keyboard.left()
	keyboard.space()

No entiende los mensajes:
	mantener apretado -> al recibir ctrl, el siguiente movimiento es con DAS

#### Objeto Colección

Entiende los mensajes:
	objeto.add(elemento)
	objeto.contains(elemento)
	objeto.first()
	objeto.remove(elemento) 
	objeto.size()
	objeto.sum(action)
	objeto.any(action)
	objeto.map(action)
	objeto.max(action)
	objeto.forEach(action)