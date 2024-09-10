# Reconocimiento:
Juego: Teris Trainer

Requisitos:
	Tetris singleplayer
	Modos: 40l (9-1, 6-3), dig race. Opcional: Modos de práctica
	Handling options como tetrio -> Controles modernos
	7 bag randomizer
	Seeded - Opcional
	Super rotation system
	Controles: Hold, Clockwise, CounterClockwise, 180°, Drop, HardDrop
	Stats: Timer, PPS, Lines cleared, Finesse
	Ghost Pieces
	Menu -> Opciones, Modos -> Gameplay -> Estadisticas

#### Grid
Como delimitar el juego a 10x20?
Como escalar el tamaño de las imágenes a la pantalla?
Como centrar el juego en la pantalla?
Que puede ir a los costados?

#### Animaciones:
Investigar si wollok tiene cosas como:
	Escalar imágenes
	Realizar animaciones (puede ser implementado a mano)
	
Números: 
    Countdown en cada inicio
    Timer
    Lineas limpiadas / borradas
    Lineas enviadas
    Piezas por segundo 
    Porcentaje de Finesse 
    Score - Opcional
    
Eventos:
    Imágenes que digan T-Spin Triple / Doble / Single
    Imágenes que digan Quad, B2B?
    Imágenes que indiquen el combo actual

#### Piezas:
Podría tener una pieza que va cayendo y una ghost piece proyectada al suelo.
Al poner la pieza o cuando caiga se crea una pieza estática y la del jugador se cambia por la siguiente, moviéndose hacia el spawn
Al intentar hacer Hold se debe verificar que este disponible.
Usar hold intercambia la pieza actual con el Hold o la Bag
Se deshabilita el Hold hasta que se ponga la pieza 
Si el lugar de spawn está ocupado, finalizar juego

#### Lineas:
  Cada frame se evalúan las líneas (o los cambios)
  Contar cuántas líneas se completaron en el frame
  Chequear si se realizó un T-Spin
  Borrar todos los bloques de la línea (modificar piezas estáticas)
  Mover todos los bloques n veces hacia abajo
  Modificar Estadísticas
  Si la altura máxima alcanzada supera 20+n, finalizar juego

#### SRS:
Como funciona? Como se implementa? 
Como puedo aplicar el SRS a los controles?

#### Handling:
Qué es el ARR?
Qué es el DAS?
Detectar colisiones y prevenir movimientos ilegales

#### 7-Bag Randomizer:
Se puede utilizar una Seed para el Randomizer? Opcional
Que estructura de dato se podría utilizar, colas?
Podría tener una cola de 5 piezas usables y una bag que la va llenando

#### Finesse:
Calcular la cantidad de acciones realizados
Si es igual a la cantidad mínima requerida para ese movimiento, el finesse counter aumenta
El porcentaje se define como finesse counter dividido por cantidad de piezas puestas multiplicado por 100


#### Modos de juego:
Sprint
Dig Race
Finesse Practice - Niveles
T-Spin Practice - Opcional 
Attack Survival Practice
Zen Practice
Opener Practice / Sandbox Mode - Opcional 
 
#### Sprint:
Se deben limpiar 40 líneas
La gravedad es constante?
Se evalúa el tiempo que llevó
Se compara contra el Personal Best
Se guardan las estadísticas

#### Dig Race:
Se deben limpiar 10 / 20 Líneas de Garbage
La dificultad es la messiness (dispersión) de la Garbage 
La gravedad es constante?
Se evalúa el tiempo que llevó 
Se compara contra el Personal Best 
Se guardan las estadísticas

# Relevamiento:

#### Grid:
Existe el objeto "mapa"
Sus atributos son:

margenX
	Constante

margenY
	Constante

Entiende los siguientes mensajes:

esEspacioLibre(pos)
	Consulta - REPETIDO

chequearLinea(y)
	Acción - DELEGAR

borrarLinea(linea)
	Acción

Las imágenes no se pueden escalar, son representadas en su tamaño de pixeles
Para centrar el juego utilizamos los margenes de X e Y
Costados de la grid:
- En la esquina superior izquierda está el hold para piezas
- En la esquina superior derecha está la preview de 5 piezas de la bag
- Etc

#### Animaciones:
- Evaluar el costo / beneficio de las animaciones, debido al bajo rendimiento
- Se podría implementar un efecto al limpiar lineas
- Se podría implementar un efecto al hacer combo

#### Números:
Utilizar el texto de wollok, las imágenes son muy ineficientes

#### Piezas:
Existe una clase "Pieza" que contiene todos los mensajes comunes de las piezas.

Sus atributos son:
- estadoRotacion -> variable
- position -> variable
- matKicksJLSTZ -> constante, wallkicks para las piezas J, L, O, S, T, Z
- matKicksI -> constante, wallkicks para la pieza I
- margenX -> BORRAR
- margenY -> BORRAR

Entiende los siguientes mensajes:

estadoRotacion()
	Consulta
	Devuelve el estado de rotacion actual
	
position()
	Consulta
	Devuelve la posicion actual del "centro" de la pieza

mostrar(bloques)
	Acción
	
esconder(bloques)
	Acción
	
crear(bloques, matRot)
	Acción
	
poner(bloques, matRot)
	Acción
	
actualizarPos(bloques, matRot, rotacion)
	Acción
	
aplicarRotacion(matRot, rotacion, id)
	Acción
	
nuevoEstadoRotacion(sentido)
	Consulta
	
calcularIndiceKick(estadoActual, estadoSiguiente)
	Consulta
	
aplicarKick(bloques, matRot, matKicks, nuevoEstado)
	Consulta y Acción???
	
rotar(bloques, matRot, matKicks, sentido)
	Acción
	
esEspacioLibre(pos)
	Consulta
	
esPosValida(pos)
	Consulta
	
esMovimientoValido(bloques, matRot, nuevaPos, rotacion)
	Consulta
	
movete(bliques, matRot, nuevaPos)
	Acción
	
bajar(bloques, matRot)
	Acción
	
randomPos(bloques, matRot)
	Acción

##### Clases para las piezas
Existen las siguientes clases, que heredan de la clase "Pieza". Estas son las 7 piezas usables en el juego:
- PiezaI
- PiezaJ
- PiezaL
- PiezaO
- PiezaS
- PiezaT
- PiezaZ

Cada una define los siguientes atributos:
- img -> Imagen que deben tener los bloques que la conforman
- bloques -> Colección de bloques que la conforman
- matRot -> Lista de Tests de rotación para cada estado de rotación

Cada una entiende los siguientes mensajes:
bloques()
	Consulta
	Devuelve la colección de bloques
	
matRot()
	Consulta
	Devueve matRot
	
matKicks()
	Consulta
	Devuelve la Lista de Tests de kicks correspondiente a la pieza
