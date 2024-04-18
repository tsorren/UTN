-- Definir la función fahrToCelsius/1, la inversa de la anterior.
{-
    y = x * 9 / 5 + 32
    x = y * 9/5 + 32
    x - 32 = y * 9/5
    (x - 32) * 5/9 = y
-}

fahrToCelsius::Float->Float
fahrToCelsius f = (f - 32) * 5/9
