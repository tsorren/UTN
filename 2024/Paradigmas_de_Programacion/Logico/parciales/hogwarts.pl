% T - 4h 51m -> 1h30

casa(gryffindor).
casa(slytherin).
casa(ravenclaw).
casa(hufflepuff).

tipoSangre(harry, mestiza).
tipoSangre(draco, pura).
tipoSangre(hermione, impura).
tipoSangre(ron, pura).
tipoSangre(luna, pura).

caracteristicas(harry, [coraje, amistoso, orgullo, inteligencia]).
caracteristicas(draco, [inteligencia, orgullo]).
caracteristicas(hermione, [inteligencia, orgullo, responsabilidad]).
caracteristicas(ron, [coraje, amistoso]).
caracteristicas(luna, [amistoso, inteligencia, responsabilidad]).

odiaCasa(harry, slytherin).
odiaCasa(draco, hufflepuff).
odiaCasa(ron, slytherin).

caracteristicasNecesarias(griffindor, [coraje]).
caracteristicasNecesarias(slytherin, [orgullo, inteligencia]).
caracteristicasNecesarias(ravenclaw, [inteligencia, responsabilidad]).
caracteristicasNecesarias(hufflepuff, [amistoso]).

% 1:
casaPermiteEntrarMago(slytherin, Mago) :- tipoSangre(Mago, TipoSangre), TipoSangre \= impura.
casaPermiteEntrarMago(Casa, Mago) :- casa(Casa), caracteristicas(Mago, _), Casa \= slytherin.

% 2:
tieneCaracterAdecuado(Mago, Casa) :-
    caracteristicasNecesarias(Casa, CaracteristicasNecesarias),
    forall(member(Requisito, CaracteristicasNecesarias), tieneCaracteristica(Mago, Requisito)).

tieneCaracteristica(Mago, Caracteristica) :-
    caracteristicas(Mago, CaracteristicasMago),
    member(Caracteristica, CaracteristicasMago).

% 3:
posibleCasa(Mago, Casa) :-
    caracteristicas(Mago, _),
    tieneCaracterAdecuado(Mago, Casa),
    casaPermiteEntrarMago(Casa, Mago),
    not(odiaCasa(Mago, Casa)).

posibleCasa(hermione, griffindor).

% 4:
cadenaDeAmistades(Magos) :-
    todosSonAmistosos(Magos),
    puedenEstarEnMismaCasaQueSiguiente(Magos).

todosSonAmistosos(Magos) :-
    forall(member(Mago, Magos), tieneCaracteristica(Mago, amistoso)).

puedenEstarEnMismaCasaQueSiguiente([_]).
puedenEstarEnMismaCasaQueSiguiente([Mago1 | [Mago2 | Magos]]) :-
    posibleCasa(Mago1, Casa),
    posibleCasa(Mago2, Casa),
    puedenEstarEnMismaCasaQueSiguiente([Mago2 | Magos]).

% PARTE 2

accion(harry, andarFueraDeCama).
accion(hermione, irA(tercerPiso)).
accion(hermione, irA(bibliotecaRestringida)).
accion(harry, irA(bosque)).
accion(harry, irA(tercerPiso)).
accion(draco, irA(mazmorras)).
accion(ron, buenaAccion(ganarAjedrezMagico, 50)).
accion(hermione, buenaAccion(salvarAmigosDeMuerte, 50)).
accion(harry, buenaAccion(vencerVoldemort, 60)).
accion(harry, buenaAccion(ganarTorneoQuiddtich, 60)).
accion(hermione, buenaAccion(vencerOgro, 35)).

% 4:
accion(hermione, responderPregunta(dondeSeEncuentraUnBezoar, 20, snape)).
accion(hermione, responderPregunta(comoHacerLevitarUnaPluma, 25, flitwick)).

accion(harry, responderPregunta(comoVencerDementor, 50, lupin)).
accion(hermione, responderPregunta(comoHacerPocionMultijugos, 50, flitwick)).


malaAccion(andarFueraDeCama, -50).
malaAccion(irA(bosque), -50).
malaAccion(irA(bibliotecaRestringida), -10).
malaAccion(irA(tercerPiso), -75).

esDe(harry, gryffindor).
esDe(hermione, gryffindor).
esDe(ron, gryffindor).
esDe(draco, slytherin).
esDe(luna, ravenclaw).

% 1:
magoEsBuenAlumno(Mago) :-
    accion(Mago, _),
    not((accion(Mago, Accion), malaAccion(Accion, _))).

esAccionRecurrente(Accion) :-
    accion(Mago, Accion),
    accion(OtroMago, Accion),
    Mago \= OtroMago.

% 2:
puntosDeAccion(Accion, Puntos) :- malaAccion(Accion, Puntos).
puntosDeAccion(buenaAccion(_, Puntos), Puntos).
puntosDeAccion(responderPregunta(_, Dificultad, snape), Puntos) :- Puntos is Dificultad / 2.

% 4:
puntosDeAccion(responderPregunta(_, Dificultad, Profesor), Dificultad) :- Profesor \= snape.

puntosParaCasa(Casa, Puntos) :-
    casa(Casa),
    esDe(Mago, Casa),
    accion(Mago, Accion),
    puntosDeAccion(Accion, Puntos).

puntajeTotalDeCasa(Casa, PuntajeTotal) :-
    casa(Casa),
    findall(Puntos, puntosParaCasa(Casa, Puntos), PuntosDeAcciones),
    sum_list(PuntosDeAcciones, PuntajeTotal).

% 3:
esCasaGanadora(Casa) :-
    casa(Casa),
    puntajeTotalDeCasa(Casa, PuntajeMasAlto),
    forall((puntajeTotalDeCasa(OtraCasa, PuntajeOtraCasa), OtraCasa \= Casa), PuntajeMasAlto > PuntajeOtraCasa).

