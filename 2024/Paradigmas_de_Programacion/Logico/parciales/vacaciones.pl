vacaciones(dodain, pehuenia).
vacaciones(dodain, sanMartin).
vacaciones(dodain, esquel).
vacaciones(dodain, sarmiento).
vacaciones(dodain, camarones).
vacaciones(dodain, playasDoradas).

vacaciones(alf, bariloche).
vacaciones(alf, sanMartin).
vacaciones(alf, elBolson).
vacaciones(nico, marDelPlata).

vacaciones(vale, calafate).
vacaciones(vale, elBolson).

vacaciones(martu, Lugar) :- vacaciones(nico, Lugar).
vacaciones(martu, Lugar) :- vacaciones(alf, Lugar).

vacaciones(juan, villaGesell).
vacaciones(juan, federacion).

/*
parqueNacional(Nombre)
cerro(Nombre, Altura)
cuerpoAgua(Nombre, SePuedePescar, TempPromedio)
playa(Nombre, DiferenciaPromedioMarea)
*/

vacaciones(carlitos, esquel).

atraccion(esquel, parqueNacional(losAlerces)).
atraccion(esquel, excursion("trochita")).
atraccion(esquel, excursion("trevelin")).

atraccion(pehuenia, cerro(bateaMahuida, 2000)).
atraccion(pehuenia, cuerpoAgua(moquehue, sePuedePescar, 19)).

atraccion(marDelPlata, playa(3)).

costoDeVida(sarmiento, 100).
costoDeVida(esquel, 150).
costoDeVida(pehuenia, 180).
costoDeVida(sanMartin, 150).
costoDeVida(camarones, 135).
costoDeVida(playasDoradas, 170).
costoDeVida(bariloche, 140).
costoDeVida(calafate, 240).
costoDeVida(elBolson, 145).
costoDeVida(marDelPlata, 140).

fueVacacionCopada(Persona) :-
    vacaciones(Persona, _),
    forall(vacaciones(Persona, Lugar), tieneAtraccionCopada(Lugar)).

tieneAtraccionCopada(Lugar) :-
    atraccion(Lugar, Atraccion),
    esAtraccionCopada(Atraccion).

esAtraccionCopada(cerro(Altura)) :- Altura >= 2000.
esAtraccionCopada(cuerpoAgua(_, sePuedePescar, _)).
esAtraccionCopada(cuerpoAgua(_, _, TempPromedio)) :- TempPromedio > 20.
esAtraccionCopada(playa(DiferenciaMareas)) :- DiferenciaMareas < 5.
esAtraccionCopada(excursion(Nombre)) :- atom_length(Nombre, CantLetras), CantLetras > 7.
esAtraccionCopada(parqueNacional(_)).

noSeCruzaron(Persona1, Persona2) :-
    vacaciones(Persona1, _),
    vacaciones(Persona2, _),
    forall(vacaciones(Persona1, Lugar), not(vacaciones(Persona2, Lugar))).

fueronVacacionesGasoleras(Persona) :-
    vacaciones(Persona, _),
    forall(vacaciones(Persona, Lugar), esDestinoGasolero(Lugar)).

esDestinoGasolero(Lugar) :-
    costoDeVida(Lugar, Costo),
    Costo < 160.

itinerarioPosible(Persona, Itinerario) :-
    vacaciones(Persona, _),
    findall(Lugar, vacaciones(Persona, Lugar), Lugares),
    permutation(Lugares, Itinerario).