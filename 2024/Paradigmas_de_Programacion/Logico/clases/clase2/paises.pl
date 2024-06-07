:- module(paises, [pais/2, limita/2]).

% Continentes
pais(alaska, america_del_norte).
pais(yukon, america_del_norte).
pais(territorio_del_noroeste, america_del_norte).
pais(groenlandia, america_del_norte).
pais(alberta, america_del_norte).
pais(ontario, america_del_norte).
pais(quebec, america_del_norte).
pais(nueva_york, america_del_norte).
pais(estados_unidos, america_del_norte).
pais(california, america_del_norte).
pais(mexico, america_del_norte).

pais(venezuela, america_del_sur).
pais(peru, america_del_sur).
pais(brasil, america_del_sur).
pais(argentina, america_del_sur).

pais(islandia, europa).
pais(escandinavia, europa).
pais(gran_bretana, europa).
pais(europa_del_norte, europa).
pais(europa_occidental, europa).
pais(europa_del_este, europa).

pais(africa_del_norte, africa).
pais(egipto, africa).
pais(africa_central, africa).
pais(africa_del_sur, africa).
pais(madagascar, africa).

pais(rusia, asia).
pais(oriente_medio, asia).
pais(afganistan, asia).
pais(india, asia).
pais(china, asia).
pais(mongolia, asia).
pais(siberia, asia).
pais(kamchatka, asia).
pais(japon, asia).
pais(sudeste_asiatico, asia).

pais(indonesia, oceania).
pais(nueva_guinea, oceania).
pais(australia, oceania).

% Conexiones
limita(alaska, yukon).
limita(alaska, kamchatka).
limita(alaska, territorio_del_noroeste).

limita(yukon, territorio_del_noroeste).
limita(yukon, alberta).

limita(territorio_del_noroeste, alberta).
limita(territorio_del_noroeste, groenlandia).

limita(groenlandia, quebec).
limita(groenlandia, islandia).

limita(alberta, ontario).
limita(alberta, estados_unidos).

limita(ontario, quebec).
limita(ontario, estados_unidos).
limita(ontario, nueva_york).

limita(quebec, nueva_york).

limita(nueva_york, estados_unidos).
limita(nueva_york, california).

limita(estados_unidos, california).
limita(estados_unidos, mexico).

limita(california, mexico).

limita(mexico, venezuela).

limita(venezuela, brasil).
limita(venezuela, peru).

limita(peru, brasil).
limita(peru, argentina).

limita(brasil, argentina).
limita(brasil, africa_del_norte).

limita(argentina, sudafrica).

limita(islandia, escandinavia).
limita(islandia, gran_bretana).

limita(escandinavia, gran_bretana).
limita(escandinavia, rusia).
limita(escandinavia, europa_del_norte).

limita(gran_bretana, europa_del_norte).
limita(gran_bretana, europa_occidental).

limita(europa_del_norte, europa_occidental).
limita(europa_del_norte, europa_del_este).

limita(europa_occidental, europa_del_este).
limita(europa_occidental, africa_del_norte).

limita(europa_del_este, rusia).
limita(europa_del_este, oriente_medio).

limita(africa_del_norte, egipto).
limita(africa_del_norte, africa_central).

limita(egipto, africa_central).
limita(egipto, oriente_medio).

limita(africa_central, africa_del_sur).

limita(africa_del_sur, madagascar).

limita(rusia, afganistan).
limita(rusia, china).
limita(rusia, mongolia).
limita(rusia, siberia).

limita(oriente_medio, afganistan).
limita(oriente_medio, india).

limita(afganistan, india).
limita(afganistan, china).

limita(india, china).
limita(india, sudeste_asiatico).

limita(china, mongolia).
limita(china, siberia).
limita(china, japon).
limita(china, sudeste_asiatico).

limita(mongolia, siberia).
limita(mongolia, japon).

limita(siberia, kamchatka).

limita(kamchatka, japon).

limita(sudeste_asiatico, indonesia).

limita(indonesia, nueva_guinea).
limita(indonesia, australia).

limita(nueva_guinea, australia).
