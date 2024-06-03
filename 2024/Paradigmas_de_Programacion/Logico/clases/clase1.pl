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
% FAMILIARES
% Hijos - Padres
padreDe(jorge, daniel).
padreDe(julian, daniel).

padreDe(camila, raul).

% Padres - Abuelos
padreDe(daniel, carlos).
padreDe(raul, carlos).

% Abuelos - Tatarabuelos
padreDe(carlos, pablo).
padreDe(cesar, pablo).

% RELACIONES
hermanos(Persona1, Persona2) :- 
    padreDe(Persona1, Padre),
    padreDe(Persona2, Padre),
    Persona1 \= Persona2.

tioDe(Persona, Tio) :-
    padreDe(Persona, Padre),
    hermanos(Padre, Tio),
    Padre \= Tio.

primos(Persona1, Persona2) :-
    padreDe(Persona1, Padre1),
    padreDe(Persona2, Padre2),
    hermanos(Padre1, Padre2).

abueloDe(Persona, Abuelo) :-
    padreDe(Persona, Padre),
    padreDe(Padre, Abuelo).

tioAbueloDe(Persona, TioAbuelo) :-
    abueloDe(Persona, Abuelo),
    hermanos(Abuelo, TioAbuelo).

tatarabueloDe(Persona, Tatarabuelo) :-
    padreDe(Persona, Padre),
    abueloDe(Padre, Tatarabuelo).
