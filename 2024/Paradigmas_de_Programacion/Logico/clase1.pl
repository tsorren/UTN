esHombre(socrates).
esHombe(juanPerez).

esMortal(Alguien) :- esHombre(Alguien).

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
