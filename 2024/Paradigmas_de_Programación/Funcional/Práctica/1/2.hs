{-
    Definir la función esMultiploDe/2, que devuelve True si el segundo es múltiplo del primero, p.ej. 
    Main> esMultiploDe 3 12
    True
-}
esMultiploDe::Int->Int->Bool
esMultiploDe x y = mod y x == 0