{-
    Definir la función aplicar, que recibe como argumento
    una tupla de 2 elementos con funciones y un entero,
    me devuelve como resultado una tupla
    con el resultado de aplicar el elemento a cada una de la funciones
-}

aplicar :: (Int -> Int, Int -> Int) -> Int -> (Int, Int)
aplicar (f, g) num = (f num, g num)