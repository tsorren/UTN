pais(america, uruguay).
pais(america, brasil).
pais(america, argentina).

pais(europa, espania).
pais(europa, francia).
pais(europa, italia).
pais(europa, portugal).

paises(america, [uruguay, brasil, argentina]). % -> [Cabeza | Cola], [Elem], []
paises(europa, [espania, francia, italia, portugal]).

cuantosPaises(Continente, Cantidad) :-
	paises(Continente, Paises),
	length(Paises, Cantidad).

tieneMasPaisesQue(C1, C2) :-
    cuantosPaises(C1, Cant1),
    cuantosPaises(C2, Cant2),
    Cant1 > Cant2.

listaPaises(Continente, Lista) :-
    pais(Continente, _),
    findall(X, pais(Continente, X), Lista).

listaTodosPaises(Lista) :-
    findall(Pais, pais(_, Pais), Lista).

listaListas(Lista) :-
    findall(SubLista, listaPaises(_, SubLista), ListaGen),
    list_to_set(ListaGen, Lista).

/*
No son totalmente inversibles!

length(Lista, N).
sumlist(Lista, Suma).
member(Elem, Lista).
append(Lista1, Lista2, Resultado) % Resultado = Lista1 + Lista2
findall(Elem, Condicion, Resultado) % Genera lista por comprensión

*/