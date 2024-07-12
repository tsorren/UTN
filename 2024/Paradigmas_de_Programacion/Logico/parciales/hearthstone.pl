/*
T-18minutos

carta(Nombre, Tipo)
deCriatura(ataque, vida, costoMana)
deHechizo(curar/herir, cantidad, costoMana)

turno(Nombre, Mana, Accion)
usarCarta(Jugador, Cartas, Carta, Enemigo)
atacar(Jugador, Mesa, Criatura, Enemigo)

*/
/* 
Jugadores
jugador(Nombre).
jugador(Nombre, PuntosVida, PuntosMana, CartasMazo, CartasMano, CartasCampo).
*/

jugador(jugador(grogoroth, 15, 7, 
    [criatura(murloc, 3, 2, 2), criatura(murloc, 2, 1, 2), criatura(esbirro, 1, 2, 1)],
    [criatura(esbirro, 1, 2, 1), criatura(giganteHierro, 5, 7, 6)],
    [criatura(esbirro, 1, 2, 1)])).

jugador(jugador(paladin, 20, 7, 
    [hechizo(bolaFuego, danio(6), 4), criatura(bandido, 2, 1, 1), criatura(murloc, 3, 2, 2), criatura(esbirro, 1, 2, 1)],
    [criatura(esbirro, 1, 2, 1), hechizo(plegaria, curar(3), 3)],
    [criatura(bandido, 2, 1, 1)])).
/* 
Cartas
criatura(Nombre, PuntosDanio, PuntosVida, CostoMana).
hechizo(Nombre, FunctorEfecto, CostoMana).

Efectos
danio(CantidadDanio).
cura(CantidadCura).
*/

criatura(esbirro, 2, 1, 1).
criatura(bandido, 2, 1, 1).
criatura(murloc, 3, 2, 2).
criatura(giganteHierro, 5, 7, 3).

hechizo(bolaFuego, danio(6), 4).
hechizo(plegaria, curar(3), 3).

% Auxiliares: 
nombre(jugador(Nombre, _,  _,  _,  _,  _), Nombre).
nombre(criatura(Nombre, _, _, _), Nombre).
nombre(hechizo(Nombre,_, _), Nombre).

vida(jugador(_, Vida,_, _, _, _), Vida).
vida(criatura(_, _, Vida,_), Vida).
vida(hechizo(_, curar(Vida), _), Vida).

danio(criatura(_, Danio, _, _), Danio).
danio(hechizo(_, danio(Danio), _), Danio).
mana(jugador(_, _, Mana,_, _, _), Mana).
mana(criatura(_, _, _, Mana), Mana).
mana(hechizo(_, _, Mana), Mana).

cartasMazo(jugador(_, _, _, Cartas,_, _), Cartas).
cartasMano(jugador(_, _, _, _, Cartas,_), Cartas).
cartasCampo(jugador(_, _, _, _, _, Cartas), Cartas).

% 1: Relacionar un jugador con una carta que tiene. La carta podría estar en su mano, en el campo o en el mazo.

esCartaDe(Jugador, Carta) :- cartasMazo(Jugador, CartasMazo), member(Carta, CartasMazo).
esCartaDe(Jugador, Carta) :- cartasMano(Jugador, CartasMano), member(Carta, CartasMano).
esCartaDe(Jugador, Carta) :- cartasCampo(Jugador, CartasCampo), member(Carta, CartasCampo).

cartaJugador(Jugador, Carta) :-
    jugador(Jugador),
    esCartaDe(Jugador, Carta).

% 2: Saber si un jugador es un guerrero. Es guerrero cuando todas las cartas que tiene, ya sea en el mazo, la mano o el campo, son criaturas.

esGuerrero(Jugador) :-
    jugador(Jugador),
    todasCartasCriaturas(Jugador).

todasCartasCriaturas(Jugador) :-
    todasLasCartasDe(Jugador, Cartas),
    forall(member(Carta, Cartas), esCriatura(Carta)).

todasLasCartasDe(Jugador, Cartas) :- 
    jugador(Jugador),
    findall(Carta, esCartaDe(Jugador, Carta), Cartas).

esCriatura(criatura(_, _, _, _)).

/* 3:   Relacionar un jugador consigo mismo después de empezar el turno.
        Al empezar el turno, la primera carta del mazo pasa a estar en la mano y el jugador gana un punto de maná.
*/

siguienteTurno(Jugador, jugador(Nombre, PuntosVida, PManaSgte, Mazo, [PrimerCarta | Mano], Campo)) :-
    jugador(Jugador),
    nombre(Jugador, Nombre),
    vida(Jugador, PuntosVida),
    mana(Jugador, PuntosMana),
    cartasMazo(Jugador, [PrimerCarta | Mazo]),
    cartasMano(Jugador, Mano),
    cartasCampo(Jugador, Campo),
    PManaSgte is PuntosMana + 1.

/* 4: Jugar Cartas
    a:  Saber si un jugador tiene la capacidad de jugar una carta,
        esto es verdadero cuando el jugador tiene igual o más maná que el costo de maná de la carta. 
        Este predicado no necesita ser inversible!
*/
puedeJugarCarta(Carta, Jugador) :-
    esCarta(Carta),
    mana(Jugador, PuntosMana),
    mana(Carta, CostoMana),
    PuntosMana >= CostoMana.

esCarta(hechizo(_, _, _)).
esCarta(criatura(_, _, _, _)).

/*
    b:  Relacionar un jugador y las cartas que va a poder jugar en el próximo turno,
        una carta se puede jugar en el próximo turno si tras empezar ese turno
        está en la mano y además se cumplen las condiciones del punto 4.a.
*/

cartasJugablesEnProxTurno(Jugador, CartasJugables) :-
    siguienteTurno(Jugador, SiguienteTurno),
    findall(Carta, puedeJugarEnProxTurno(Carta, SiguienteTurno), CartasJugables).

puedeJugarEnProxTurno(Carta, Jugador) :-
    jugador(Jugador),
    cartasMano(Jugador, Mano),
    member(Carta, Mano),
    puedeJugarCarta(Carta, Jugador).

/* 5:   Conocer, de un jugador, todas las posibles jugadas que puede hacer en el próximo turno, 
        esto es, el conjunto de cartas que podrá jugar al mismo tiempo sin que su maná quede negativo.
        Nota: Se puede asumir que existe el predicado jugar/3 como se indica en el punto 7.b.
        No hace falta implementarlo para resolver este punto. Importante: También hay formas de resolver este punto sin usar jugar/3. 
        Tip: Pensar en explosión combinatoria.
*/

jugadaPosible(Jugador, JugadaPosible) :-
    cartasJugablesEnProxTurno(Jugador, CartasJugables),
    combinacion(CartasJugables, JugadaPosible),
    siguienteTurno(Jugador, SiguienteTurno),
    tieneManaParaJugada(SiguienteTurno, JugadaPosible).

tieneManaParaJugada(Jugador, JugadaPosible) :-
    costeManaDeJugada(JugadaPosible, CosteTotalMana),
    mana(Jugador, Mana),
    Mana >= CosteTotalMana.

costeManaDeJugada(Jugada, CosteTotalMana) :-
    findall(CosteMana, (member(Carta, Jugada), mana(Carta, CosteMana)), Costes),
    sum_list(Costes, CosteTotalMana).

combinacion(Cartas, Combinacion) :-
    separar(Cartas, _, SubLista),
    SubLista = [_|_],
    permutacion(SubLista, Combinacion).

separar([], [], []).
separar([Cabeza | Cola], [Cabeza | Cola2], ListaSeparada) :-
    separar(Cola, Cola2, ListaSeparada).
separar([Cabeza | Cola], ListaAux, [Cabeza | ListaSeparada]) :-
    separar(Cola, ListaAux, ListaSeparada).

permutacion([], []).
permutacion(Lista, [Cabeza | Cola]) :-
    quitar(Cabeza, Lista, ListaAux),
    permutacion(ListaAux, Cola).

quitar(Elem, [Elem | Cola], Cola).
quitar(Elem, [Cabeza | Cola], [Cabeza |ListaAux]) :-
    quitar(Elem, Cola, ListaAux).

% 6:   Relacionar a un jugador con el nombre de su carta más dañina.

cartaMasDanina(Jugador, CartaDanina) :-
    jugador(Jugador),
    %esCarta(CartaDanina),
    todasLasCartasDe(Jugador, Cartas),
    member(CartaDanina, Cartas),
    forall((member(Carta, Cartas), danio(Carta, _)), esMenosPoderosaQue(Carta, CartaDanina)).

esMenosPoderosaQue(Carta, CartaDanina) :-
    danio(Carta, DanioCarta),
    danio(CartaDanina, MayorDanio),
    DanioCarta =< MayorDanio.

/* 7:   Cuando un jugador juega una carta, él mismo y/o su rival son afectados de alguna forma:
    a:  jugarContra/3. Modela la acción de jugar una carta contra un jugador.
        Relaciona a la carta, el jugador antes de que le jueguen la carta y el jugador después de que le jueguen la carta.
        Considerar que únicamente afectan al jugador las cartas de hechizo de daño.

        Este predicado no necesita ser inversible para la carta ni para el jugador antes de que le jueguen la carta.
*/
jugarContra(Carta, Jugador, jugador(Nombre, VidaAfectada, Mana, Mazo, Mano, Campo)) :-
    esCarta(Carta),
    jugador(Jugador),
    nombre(Jugador, Nombre),
    vida(Jugador, PuntosVida),
    mana(Jugador, Mana),
    cartasMazo(Jugador, Mazo),
    cartasMano(Jugador, Mano),
    cartasCampo(Jugador, Campo),
    danio(Carta, Danio),
    VidaAfectada is PuntosVida - Danio.

/*
    b:  BONUS: jugar/3. Modela la acción de parte de un jugador de jugar una carta.
        Relaciona a la carta, el jugador que puede jugarla antes de hacerlo y el mismo jugador después de jugarla.
        En caso de ser un hechizo de cura, se aplicará al jugador y no a sus criaturas.
        No involucra al jugador rival (para eso está el punto a).
*/

jugar(Carta, Jugador, JugadorAfectado) :-
    jugador(Jugador),
    nombre(Jugador, Nombre),
    nombre(JugadorAfectado, Nombre),
    cartasMazo(Jugador, Mazo),
    cartasMazo(JugadorAfectado, Mazo),
    puedeJugarEnProxTurno(Carta, Jugador),
    usarCarta(Carta, Jugador, JugadorAfectado),
    quitarMana(Carta, Jugador, JugadorAfectado),
    quitarCartaDeMano(Carta, Jugador, JugadorAfectado).

usarCarta(Carta, Jugador, JugadorAfectado) :-
    esCriatura(Carta),
    vida(Jugador, Vida),
    vida(JugadorAfectado, Vida),
    ponerCartaEnCampo(Carta, Jugador, JugadorAfectado).
    
usarCarta(Carta, Jugador, JugadorAfectado) :-
    cartasCampo(Jugador, Campo),
    cartasCampo(JugadorAfectado, Campo),
    aplicarCuracion(Carta, Jugador, JugadorAfectado).

ponerCartaEnCampo(Carta, Jugador, JugadorAfectado) :-
    cartasCampo(Jugador, Campo),
    cartasCampo(JugadorAfectado, [Carta | Campo]).

aplicarCuracion(hechizo(_, curar(Curacion), _), Jugador, JugadorAfectado) :-
    vida(Jugador, Vida),
    vida(JugadorAfectado, VidaAfectada),
    VidaAfectada is Vida + Curacion.

quitarMana(Carta, Jugador, JugadorAfectado) :-
    mana(Jugador, Mana),
    mana(Carta, CosteMana),
    mana(JugadorAfectado, ManaAfectado),
    ManaAfectado is Mana - CosteMana.

quitarCartaDeMano(Carta, Jugador, JugadorAfectado) :-
    cartasMano(Jugador, Mano),
    cartasMano(JugadorAfectado, ManoAfectada),
    quitarCarta(Carta, Mano, ManoAfectada).

quitarCarta(Carta, [Carta | Mano], Mano).
quitarCarta(Carta, [Cabeza | ManoAux], [Cabeza | Mano]) :-
    quitarCarta(Carta, ManoAux, Mano).