% 1h10
% 1:
atiende(dodain, lunes, 9, 15).
atiende(dodain, miercoles, 9, 15).
atiende(dodain, viernes, 9, 15).

atiende(lucas, martes, 10, 20).
atiende(juanC, sabado, 18, 22).
atiende(juanC, domingo, 18, 22).

atiende(juanFdS, jueves, 10, 20).
atiende(juanFdS, viernes, 12, 20).

atiende(leoC, lunes, 14, 18).
atiende(leoC, miercoles, 14, 18).

atiende(martu, miercoles, 23, 24).

atiende(vale, Dia, HoraInicio, HoraFin) :- atiende(dodain, Dia, HoraInicio, HoraFin).
atiende(vale, Dia, HoraInicio, HoraFin) :- atiende(juanC, Dia, HoraInicio, HoraFin).

% 2:
quienAtiende(Persona, Dia, Hora) :- 
    atiende(Persona, Dia, HoraInicio, HoraFin),
    between(HoraInicio, HoraFin, Hora).

% 3:
foreverAlone(Persona, Dia, Hora) :-
    quienAtiende(Persona, Dia, Hora),
    not((quienAtiende(Alguien, Dia, Hora), Alguien \= Persona)).

% 4:
puedenEstarAtendiendo(Dia, PosiblesPersonas) :-
    quienesAtienden(Dia, Personas),
    combinacion(Personas, PosiblesPersonas).

quienesAtienden(Dia, Personas) :-
    atiende(_, Dia, _, _),
    findall(Persona, atiende(Persona, Dia, _, _), Personas).

combinacion([], []).
combinacion([Persona | Personas], [Persona | PosiblesPersonas]) :- combinacion(Personas, PosiblesPersonas).
combinacion([_ | Personas], PosiblesPersonas) :- combinacion(Personas, PosiblesPersonas).


/*
combinacion(Personas, PosiblesPersonas) :-
    separarLista(Personas, _, PosiblesPersonas).

separarLista([], [], []).

separarLista([Cabeza | Cola], [Cabeza | Cola2], ListaSeparada) :-
    separarLista(Cola, Cola2, ListaSeparada).

separarLista([Cabeza | Cola], ListaAuxiliar, [Cabeza | ListaSeparada]) :-
    separarLista(Cola, ListaAuxiliar, ListaSeparada).
*/

/* 5:
    venta(golosinas(Valor)).
    venta(cigarrillo(Marca)).
    venta(bebidas(SonAlcoholicas, Cantidad)).
*/

ventas(dodain, lunes, fecha(10, 8), [golosinas(1200), cigarrillos([jockey]), golosinas(50)]).
ventas(dodain, miercoles, fecha(12, 8), [bebidas(alcoholicas, 8), bebidas(noAlcoholicas, 1), golosinas(10)]).

ventas(martu, miercoles, fecha(12, 8), [golosinas(1000), cigarrillos([chesterfield, colorado, parisiennes])]).

ventas(lucas, martes, fecha(11, 8), [golosinas(600)]).
ventas(lucas, martes, fecha(18, 8), [bebidas(noAlcoholicas, 2), cigarrillos([derby])]).

esSuertudo(Persona) :-
    esVendedor(Persona),
    todasPrimerasVentasImportantes(Persona).

esVendedor(Persona) :- ventas(Persona, _, _, _).

todasPrimerasVentasImportantes(Persona) :-
    forall(ventas(Persona, _, _, [PrimerVenta | _]), esVentaImportante(PrimerVenta)).

esVentaImportante(golosinas(Dinero)) :- Dinero > 100.
esVentaImportante(cigarrillos(Marcas)) :- length(Marcas, CantidadPaquetes), CantidadPaquetes > 2.
esVentaImportante(bebidas(alcoholicas, _)).
esVentaImportante(bebidas(_, Cantidad)) :- Cantidad > 5.

