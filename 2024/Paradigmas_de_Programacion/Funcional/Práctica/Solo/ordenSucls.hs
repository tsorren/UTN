siempre :: a -> Bool
siempre a = True

totalCaracteres :: [String] -> Int
totalCaracteres lista = contarListaOperando siempre length lista 0

contarListaOperando :: (a -> Bool) -> (a -> Int) -> [a] -> Int -> Int
contarListaOperando condicion operador lista contador
    | null lista = contador
    | (condicion.head) lista= contarListaOperando condicion operador (tail lista) (contador + (operador.head) lista)
    | otherwise = contarListaOperando condicion operador (tail lista) contador

contarLista :: (a -> Bool) -> [a] -> Int -> Int
contarLista condicion lista contador
    | null lista = contador
    | (condicion.head) lista = contarLista condicion (tail lista) (contador + 1)
    | otherwise = contarLista condicion (tail lista) contador

esLarga :: String -> Bool
esLarga = (3 < ) . length

cantPalabrasLargas :: [String] -> Int
cantPalabrasLargas lista = contarLista esLarga lista 0 

