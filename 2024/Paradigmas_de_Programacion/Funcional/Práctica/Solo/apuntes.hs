{-
Funcion de Orden Superior:
    Recibe funciones como parámetros
    Puede devolver funciones

    Ej: Filter, Map, Any, All, Composición

Aplicación Parcial:
    Función que no recibió la totalidad de sus parametros, por lo que devuelve una función (espera más parametros
    para reducirse a un valor)

Expresion Lambda o Clausuras:
    \x -> x * 3
    
    Pasar como argumento Lógica
    Orden Superior para lenguajes no funcionales

-}

doble x = 2 * x
triplicarLista = map (\x -> 3 * x)

orLista val lista = any (\criterio -> criterio val) lista

logicaInfinita :: Foldable t => a -> ((a->Bool) -> t a -> Bool)  -> [a->Bool] -> Bool
logicaInfinita val operador = operador (\criterio -> criterio val) 

orInfinito :: a -> [(a -> Bool)] -> Bool
orInfinito val criterios = logicaInfinita (val any criterios)
