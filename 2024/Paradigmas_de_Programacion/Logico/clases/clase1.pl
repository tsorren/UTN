/*
esHombre(socrates).
esHombe(juanPerez).

esMortal(Alguien) :- esHombre(Alguien).

%---------------------------------------------------

clima(bsas, lluvia, 10).
clima(cordoba, sol, 23).
clima(rosario, lluvia, 100).

ubicacion(pasto, bsas).
ubicacion(vereda, cordoba).
ubicacion(jardin, rosario).

seRego(pasto).
seRego(canchaFutbol).
%seRego(vereda).

alAireLibre(pasto).
alAireLibre(vereda).
alAireLibre(jardin).

llovioMucho(Ciudad) :-
    clima(Ciudad, lluvia, Cantidad),
    Cantidad > 20.

seMojo(Lugar) :- seRego(Lugar).
seMojo(Lugar) :-
    alAireLibre(Lugar),
    ubicacion(Lugar, Ciudad),
    llovioMucho(Ciudad).

%---------------------------------------------------

tieneEntrada(carlos).
tieneEntrada(pedro).

puedeEntrarAlBar(Nombre, Edad, Vestimenta) :-
    Edad >= 18,
    tieneEntrada(Nombre),
    Vestimenta = sport.

*/
%---------------------------------------------------
% FAMILIA

padreDe(jorge, daniel).
padreDe(julian, daniel).

%padreDe(daniel, carlos).
%padreDe(raul, carlos).

hermanos(Hermano1, Hermano2) :- 
    padreDe(Persona1, Padre),
    padreDe(Persona2, Padre),
    Persona1 \= Persona2.
/*
tioDe(Persona, Tio) :-
    padreDe(Persona, Padre),
    hermanos(Padre, Tio).

abueloDe(Persona, Abuelo) :-
    padreDe(Persona, Padre),
    padreDe(Padre, Abuelo).
*/