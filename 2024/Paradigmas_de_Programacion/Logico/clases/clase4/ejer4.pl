/*
Punto 1: accion del partido
Conocemos el nombre de cada jugador y las accion que fueron pasando en el partido.
Las cuales son:
    el dibu hizo una atajada en el minuto 122. También, en la tanda de penales atajó 2 de ellos.
    messi metió 2 goles, uno en el minuto 108 de jugada y otro en el minuto 23 de penal. A su vez, también metió el primer penal de la tanda.
    montiel metió el último penal de la tanda de penales.

Se pide modelar la base de conocimientos con las accion y quienes las realizaron.

Extra: Accion Tarjeta
    Color, Minutouto
*/

jugador(elDibu).
jugador(messi).
jugador(montiel).
jugador(otamendi).

accion(elDibu, atajada(122)).
accion(elDibu, atajarPenal(2)).

accion(messi, gol(108)).
accion(messi, gol(23)).
accion(messi, penal(1)).

accion(montiel, penal(5)).

accion(otamendi, tarjeta(amarilla, 80)).

/*
Punto 2: Puntajes de las acciones
Queremos saber cuantos puntos suma cada acción. Los cuales son calculados de la siguiente forma:
    Para las atajadas tanda de penales, suman 15 * la cantidad que se hayan atajado
    Para las otras atajadas, el puntaje se calcula como el minuto en el que ocurrió más 10
    Para los goles, se calcula como el minuto en el que se metió más 20
    Por último, para los penales que se metieron, en caso de que sea el primero suma  45 puntos mientras que si es el último suma 80 puntos

También, queremos saber cuantos puntos suma cada jugador. Es necesario que este predicado sea inversible.
*/

puntaje(atajadaPenal(Cantidad), Puntos) :-
    Puntos is Cantidad * 15.

puntaje(atajada(Minuto), Puntos) :- 
    Puntos is Minuto + 10.

puntaje(gol(Minuto), Puntos) :- 
    Puntos is Minuto + 10.

puntaje(penal(1), 45).
puntaje(penal(5), 80).
puntaje(penal(Numero), Puntos) :- 
    between(2, 4, Numero), Puntos is 30.

puntaje(tarjeta(amarilla, Minuto), Puntaje) :- 
    Puntaje is -25 - Minuto / 2.

puntaje(tarjeta(roja, Minuto), Puntaje) :- 
    Puntaje is -50 - Minuto.

puntajeJugador(Jugador, Puntaje) :-
    jugador(Jugador),
    findall(P, (accion(Jugador, Accion), puntaje(Accion, P)), Puntos),
    sumlist(Puntos, Puntaje).

/*
Punto 3: Puntaje total
    Dada una lista de jugadores, queremos saber cuantos puntos sumaron todos. 
*/

puntajeTotal(ListaJugadores, PuntajeTotal) :-
    findall(Puntos, (member(Jugador, ListaJugadores), puntajeJugador(Jugador, Puntos)), ListaPuntos),
    sumlist(ListaPuntos, PuntajeTotal).

puntosDeEquipo(Equipo, Puntaje) :-
    findall(JugadorEquipo, jugador(Jugador), juegaEn(Jugador, Equipo), Jugadores),
    puntajeTotal(Jugadores, Puntaje).

puntosTodosJugadores(PuntajeTotal) :-
    findall(Puntos, puntajeJugador(_, Puntos), ListaPuntos),
    sumlist(ListaPuntos, PuntajeTotal).