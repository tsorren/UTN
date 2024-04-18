{-
    Definir la función esMultiploDeTres/1, que devuelve True si un número es múltiplo de 3, p.ej: 
    Main> esMultiploDeTres 9 
    True 
-}

esMultiploDeTres::Int->Bool
esMultiploDeTres n = mod n 3 == 0