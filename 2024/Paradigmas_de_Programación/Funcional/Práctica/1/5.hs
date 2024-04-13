{-
    Definir la función esBisiesto/1, indica si un año es bisiesto. 
    (Un año es bisiesto si es divisible por 400 o es divisible por 4 pero no es divisible por 100)
    Nota: Resolverlo reutilizando la función esMultiploDe/2
-}

{-

esMultiploDe::Int->Int->Bool
esMultiploDe x y = mod y x == 0

esBisiesto::Int->Bool
esBisiesto a = (esMultiploDe 4 a || esMultiploDe 400 a) && not(esMultiploDe 100 a)

-}

noEsMultiploDe :: Int -> Int -> Int
noEsMultiploDe x y
    | mod y x /= 0 = x
    | otherwise = 0

esMultiploDe::Int->Int->Int
esMultiploDe x y 
    | mod y x == 0 = x
    | otherwise = 0

esBisiesto::Int->Bool
esBisiesto = (0 == ) . esMultiploDe 100 . noEsMultiploDe 400 . noEsMultiploDe 4
