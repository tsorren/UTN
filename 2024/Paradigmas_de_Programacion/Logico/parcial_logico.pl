% Sorrentino Tadeo - Solución en Prolog

% BASE DE CONOCIMIENTO
% Personas
genero(nina, femenino).
genero(marcos, masculino).
genero(osvaldo, masculino).
genero(maria, femenino).
genero(carlos, masculino).

edad(nina, 22).
edad(marcos, 8).
edad(osvaldo, 13).
edad(maria, 32).
edad(carlos, 75).

altura(nina, 1.6).
altura(marcos, 1.32).
altura(osvaldo, 1.29).
altura(maria, 1.78).
altura(carlos, 1.8).

pasaporte(nina, flex(35, montaniaRusa)).
pasaporte(marcos, basico(50)).
pasaporte(osvaldo, flex(50, toboganGiganteOlaAzul)).
pasaporte(maria, premium).
pasaporte(carlos, premium).

% Atracciones 
atraccion(parqueDeLaCosta, trenFantasma).
atraccion(parqueDeLaCosta, montaniaRusa).
atraccion(parqueDeLaCosta, maquinaTiquetera).

atraccion(parqueAcuatico, toboganGiganteOlaAzul).
atraccion(parqueAcuatico, rioLentoCorrienteSerpeante).
atraccion(parqueAcuatico, piscinaDeOlasMaremoto).

atraccion(parqueDelTerror, caminoDelInfierno).
atraccion(parqueDelTerror, hotelEmbrujado).
atraccion(parqueDelTerror, penduloRoto).

requisitoFisico(trenFantasma, edad(12)).
requisitoFisico(montaniaRusa, altura(1.3)).

requisitoFisico(toboganGiganteOlaAzul, altura(1.5)).
requisitoFisico(piscinaDeOlasMaremoto, edad(5)).

requisitoFisico(caminoDelInfierno, edad(18)).
requisitoFisico(hotelEmbrujado, altura(1.7)).
requisitoFisico(penduloRoto, edad(18)).

pasaporteRequerido(trenFantasma, comun(20)).
pasaporteRequerido(montaniaRusa, premium).
pasaporteRequerido(maquinaTiquetera, comun(10)).

pasaporteRequerido(toboganGiganteOlaAzul, premium).
pasaporteRequerido(rioLentoCorrienteSerpeante, comun(15)).
pasaporteRequerido(piscinaDeOlasMaremoto, comun(30)).

pasaporteRequerido(caminoDelInfierno, premium).
pasaporteRequerido(hotelEmbrujado, comun(20)).
pasaporteRequerido(penduloRoto, comun(30)).

esParque(Parque) :- atraccion(Parque, _).

esPersona(Persona) :- edad(Persona, _).

% Creditos
creditosDePersona(Persona, Creditos) :-
    pasaporte(Persona, comun(Creditos)).

creditosDePersona(Persona, Creditos) :-
    pasaporte(Persona, flex(Creditos, _)).

% infante, ninio, adolescente, joven, adulto, anciano
grupoEtarioDePersona(Persona, GrupoEtario) :-
    edad(Persona, Edad),
    grupoEtario(Edad, GrupoEtario).

grupoEtario(Edad, infante) :-
    between(1, 5, Edad).

grupoEtario(Edad, ninio) :-
    between(6, 11, Edad).

grupoEtario(Edad, adolescente) :-
    between(12, 17, Edad).

grupoEtario(Edad, joven) :-
    between(18, 30, Edad).

grupoEtario(Edad, adulto) :-
    between(30, 70, Edad).

grupoEtario(Edad, anciano) :-
    between(70, 125, Edad). % Record mundial de edad

% Punto 1 y 6
puedeSubir(Persona, Atraccion) :- 
    esPersona(Persona),
    atraccion(_, Atraccion),
    cumpleConRequisitoFisico(Persona, Atraccion), % Cumple requisitos fisicoss
    tienePasaporteNecesario(Persona, Atraccion). % Debe tener el pasaporte correcto

cumpleConRequisitoFisico(Persona, Atraccion) :- % Requisito de Edad
    requisitoFisico(Atraccion, edad(EdadMinima)),
    edad(Persona, Edad),
    Edad >= EdadMinima.

cumpleConRequisitoFisico(Persona, Atraccion) :- % Requisito de Altura
    requisitoFisico(Atraccion, altura(AlturaMinima)),
    altura(Persona, Altura),
    Altura >= AlturaMinima.

cumpleConRequisitoFisico(_, Atraccion) :- % Cuando la atraccion no tiene requisito fisico
    not(requisitoFisico(Atraccion, _)).

tienePasaporteNecesario(Persona, Atraccion) :- % Atraccion comun
    pasaporteRequerido(Atraccion, comun(Costo)),
    creditosDePersona(Persona, Creditos),
    Creditos > Costo.

tienePasaporteNecesario(Persona, Atraccion) :- % Atraccion premium, pasaporte flex
    pasaporteRequerido(Atraccion, premium),
    pasaporte(Persona, flex(_, Atraccion)).

tienePasaporteNecesario(Persona, _) :- % Tiene pasaporte para cualquier atraccion
    pasaporte(Persona, premium).

% Punto 2
esParaElle(Parque, Persona) :- % Cuando persona puede subir a todas las atracciones del parque
    esPersona(Persona),
    esParque(Parque),
    puedeSubirATodasLasAtracciones(Persona, Parque).

puedeSubirATodasLasAtracciones(Persona, Parque) :-
    atraccionesDelParque(Parque, Atracciones),
    forall(member(Atraccion, Atracciones), puedeSubir(Persona, Atraccion)).

atraccionesDelParque(Parque, Atracciones) :-
    findall(Atraccion, atraccion(Parque, Atraccion), Atracciones).

% Punto 3:
malaIdea(GrupoEtario, Parque) :-
    grupoEtario(_, GrupoEtario),
    esParque(Parque),
    atraccionesDelParque(Parque, AtraccionesDelParque),
    grupoEtarioNoPuedeSubirANinguna(AtraccionesDelParque, GrupoEtario).

% Cuando no existe atraccion del parque al que puedan subir
grupoEtarioNoPuedeSubirANinguna(AtraccionesDelParque, GrupoEtario) :- 
    forall(member(Atraccion, AtraccionesDelParque), not(grupoEtarioPuedeSubir(GrupoEtario, Atraccion))). 

grupoEtarioPuedeSubir(GrupoEtario, Atraccion) :- % Requisito por edad
    requisitoFisico(Atraccion, edad(EdadMinima)),
    grupoEtario(Edad, GrupoEtario),
    Edad > EdadMinima.

grupoEtarioPuedeSubir(infante, Atraccion) :- % Requisitos por altura
    requisitoFisico(Atraccion, altura(AlturaMinima)),
    AlturaMinima < 1.1.

grupoEtarioPuedeSubir(nino, Atraccion) :-
    requisitoFisico(Atraccion, altura(AlturaMinima)),
    AlturaMinima < 1.4.

% De adolescente en adelante puede cumplir cualquier requisito de altura
grupoEtarioPuedeSubir(GrupoEtario, Atraccion) :- 
    requisitoFisico(Atraccion, altura(_)),
    GrupoEtario \= infante,
    GrupoEtario \= ninio.

grupoEtarioPuedeSubir(_, Atraccion) :-
    not(requisitoFisico(Atraccion, _)).

% Punto 4
programaLogico(Parque, Programa) :-
    esParque(Parque),
    atraccionesDelParque(Parque, Atracciones),
    combinacion(Atracciones, PosiblePrograma), % Todas las maneras de tomar atracciones
    permutation(PosiblePrograma, Programa), % Todas las maneras y ordenes de atracciones
    Programa = [_ | _]. % El programa debe tener al menos una atraccion

combinacion([], []). % Caso Base

combinacion([_ | Atracciones], PosiblePrograma) :- % Cabeza no pertenece
    combinacion(Atracciones, PosiblePrograma).

combinacion([Atraccion | Atracciones], [Atraccion | PosiblePrograma]) :- % Cabeza pertenece
    combinacion(Atracciones, PosiblePrograma). 

% Punto 5
% Relaciona las atracciones hasta que no pueda subir
hastaAca(Persona, Programa, SubPrograma) :-
    esPersona(Persona),
    programaLogico(Parque, Programa),
    programaLogico(Parque, SubPrograma),
    programaHastaQueNoPuedaSubir(Persona, Programa, SubPrograma). 

programaHastaQueNoPuedaSubir(_, [], []). % Caso Base

programaHastaQueNoPuedaSubir(Persona, [Atraccion | _], []) :- % Caso Base
    not(puedeSubir(Persona,Atraccion)). 

programaHastaQueNoPuedaSubir(Persona, [Atraccion | Programa], [Atraccion | SubPrograma]) :- % La atraccion pertenece al SubPrograma
    puedeSubir(Persona, Atraccion), % Cuando puede subir
    programaHastaQueNoPuedaSubir(Persona, Programa, SubPrograma). % Recursion mientras que pueda subir
