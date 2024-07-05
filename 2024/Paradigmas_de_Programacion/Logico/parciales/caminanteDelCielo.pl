
%apareceEn( Personaje, Episodio, Lado de la luz).
apareceEn(luke, elImperioContrataca, luminoso).
apareceEn(luke, unaNuevaEsperanza, luminoso).
apareceEn(vader, unaNuevaEsperanza, oscuro).
apareceEn(vader, laVenganzaDeLosSith, luminoso).
apareceEn(vader, laAmenazaFantasma, luminoso).
apareceEn(c3po, laAmenazaFantasma, luminoso).
apareceEn(c3po, unaNuevaEsperanza, luminoso).
apareceEn(c3po, elImperioContrataca, luminoso).
apareceEn(chewbacca, elImperioContrataca, luminoso).
apareceEn(yoda, elAtaqueDeLosClones, luminoso).
apareceEn(yoda, laAmenazaFantasma, luminoso).

%Maestro(Personaje)
maestro(luke).
maestro(leia).
maestro(vader).
maestro(yoda).
maestro(rey).
maestro(duku).

%caracterizacion(Personaje,Aspecto).
%aspectos:
% ser(Especie,Tamaño)
% humano
% robot(Forma)
caracterizacion(chewbacca,ser(wookiee,10)).
caracterizacion(luke,humano).
caracterizacion(vader,humano).
caracterizacion(yoda,ser(desconocido,5)).
caracterizacion(jabba,ser(hutt,20)).
caracterizacion(c3po,robot(humanoide)).
caracterizacion(bb8,robot(esfera)).
caracterizacion(r2d2,robot(secarropas)).

%elementosPresentes(Episodio, Dispositivos)
elementosPresentes(laAmenazaFantasma, [sableLaser]).
elementosPresentes(elAtaqueDeLosClones, [sableLaser, clon]).
elementosPresentes(laVenganzaDeLosSith, [sableLaser, mascara, estrellaMuerte]).
elementosPresentes(unaNuevaEsperanza, [estrellaMuerte, sableLaser, halconMilenario]).
elementosPresentes(elImperioContrataca, [mapaEstelar, estrellaMuerte] ).

%El orden de los episodios se representa de la siguiente manera:
%precede(EpisodioAnterior,EpisodioSiguiente)
precedeA(laAmenazaFantasma,elAtaqueDeLosClones).
precedeA(elAtaqueDeLosClones,laVenganzaDeLosSith).
precedeA(laVenganzaDeLosSith,unaNuevaEsperanza).
precedeA(unaNuevaEsperanza,elImperioContrataca).

nuevoEpisodio(Heroe, Villano, Extra, Dispositivo) :-
    aparecioPreviamente(Heroe),
    aparecioEnVariosEpisodios(Villano),
    aparecioPreviamente(Extra),
    Heroe \= Villano,
    Villano \= Extra,
    Extra \= Heroe,
    esJediLeal(Heroe),
    esAmbiguo(Villano),
    esExotico(Extra),
    tieneVinculoConProtagonistas(Extra, Heroe, Villano),
    esReconocible(Dispositivo).

/*
episodios(ListaEpisodios) :-
    findall(Episodio, apareceEn(_, Episodio, _), EpisodiosConRepetidos),
    list_to_set(EpisodiosConRepetidos, ListaEpisodios).

episodioEsOrdenado(Episodio, [Episodio]).
episodioEsOrdenado(Episodio, [Episodio | _]) :- not(precedeA(_, Episodio)).
episodioEsOrdenado(Episodio, [Cabeza | [Episodio | _]]) :- precedeA(Cabeza, Episodio).
episodioEsOrdenado(Episodio, [Cabeza | Cola]) :- episodioEsOrdenado(Episodio, Cola).

episodiosOrdenados(EpisodiosConOrden) :-
    episodios(ListaEpisodios),
    permutation(ListaEpisodios, EpisodiosConOrden),
    forall(member(Episodio, EpisodiosConOrden), episodioEsOrdenado(Episodio, EpisodiosConOrden)).
*/

esPosteriorA(EpisodioPosterior, EpisodioAnterior) :- precedeA(EpisodioAnterior, EpisodioPosterior).
esPosteriorA(EpisodioPosterior, EpisodioAnterior) :-
    precedeA(EpisodioAnterior, EpisodioIntermedio),
    esPosteriorA(EpisodioPosterior, EpisodioIntermedio).

aparecioPreviamente(Personaje) :-
   apareceEn(Personaje, _, _).

aparecioEnVariosEpisodios(Personaje) :-
    apareceEn(Personaje, Ep1, _),
    apareceEn(Personaje, Ep2, _),
    Ep1 \= Ep2.

esJediLeal(Personaje) :-
    maestro(Personaje),
    not(apareceEn(Personaje, _, oscuro)).

esAmbiguo(Villano) :- 
    apareceEn(Villano, Episodio, luminoso),
    apareceEn(Villano, Episodio, oscuro).

esAmbiguo(Villano) :-
    apareceEn(Villano, Episodio, luminoso),
    apareceEn(Villano, OtroEpisodio, oscuro),
    esPosteriorA(OtroEpisodio, Episodio).

esExotico(Personaje) :-
    caracterizacion(Personaje, robot(TipoRobot)),
    TipoRobot \= esfera.

esExotico(Personaje) :-
    caracterizacion(Personaje, ser(_, Tamanio)),
    Tamanio > 15.

esExotico(Personaje) :- caracterizacion(Personaje, ser(desconocido, _)).

apareceAlgunoEn(Episodio, Personaje, _) :- apareceEn(Personaje, Episodio, _).
apareceAlgunoEn(Episodio, _, Personaje) :- apareceEn(Personaje, Episodio, _).

tieneVinculoConProtagonistas(Extra, Heroe, Villano) :- 
    apareceEn(Extra, _, _),
    apareceEn(Heroe, _, _),
    apareceEn(Villano, _, _),
    forall(apareceEn(Extra, Episodio, _), apareceAlgunoEn(Episodio, Heroe, Villano)).

esReconocible(Dispositivo) :-
    elementosPresentes(_, Elementos),
    member(Dispositivo, Elementos),
    findall(Dispositivo, (elementosPresentes(_, ElementosEpisodio), member(Dispositivo, ElementosEpisodio)), Apariciones),
    length(Apariciones, CantApariciones),
    CantApariciones >= 3.