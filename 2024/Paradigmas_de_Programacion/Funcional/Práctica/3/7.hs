{-
    Definir la función calcular, que recibe una tupla de 2 elementos, 
    si el primer elemento es par lo duplica, 
    sino lo deja como está y con el segundo elemento en caso de ser impar,
    le suma 1 y si no deja esté último como esta. 
    Nota: Resolverlo utilizando aplicación parcial y composición. 
-}

calcularX :: Bool -> Int -> Int
calcularX True = (2*)
calcularX False = id

calcularY :: Bool -> Int -> Int
calcularY True = (1+)
calcularY False = id

calcular ::  (Int, Int) -> (Int, Int)
calcular (x, y) = (calcularX (even x) x, calcularY (odd y) y)