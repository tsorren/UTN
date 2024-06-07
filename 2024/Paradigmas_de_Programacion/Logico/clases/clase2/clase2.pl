:- use_module(paises).
:- use_module(ocupacion).

sonLimitrofes(Pais1, Pais2) :- limita(Pais1, Pais2).
sonLimitrofes(Pais1, Pais2) :- limita(Pais2, Pais1).

% predicado que diga que país limita con un pais de otro continente

limitrofesDeDistintoCont(Pais1, Pais2) :-
    sonLimitrofes(Pais1, Pais2),
    pais(Pais1, Continente1),
    pais(Pais2, Continente2),
    Continente1 \= Continente2.

enemigoDe(Pais1, Pais2) :-
    sonLimitrofes(Pais1, Pais2),
    ocupa(Color1, Pais1, _),
    ocupa(Color2, Pais2, _),
    Color1 \= Color2.

estaComplicado(Pais) :-
    enemigoDe(Pais, Enemigo1),
    enemigoDe(Pais, Enemigo2),
    ocupa(Color, Enemigo1, Cant1),
    ocupa(Color, Enemigo2, Cant2),
    Enemigo1 \= Enemigo2,
    Cant1 + Cant2 > 5.

puedeAtacar(Pais) :-
    enemigoDe(Pais, Enemigo),
    ocupa(_, Pais, CantPais),
    ocupa(_, Enemigo, CantEnemigo),
    CantPais > CantEnemigo.

esFuerte(Ejercito) :-
    ocupa(Ejercito, Pais, _),
    not(estaComplicado(Pais)).
