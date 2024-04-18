{-
    Definir la función haceFrioF/1,
    indica si una temperatura expresada en grados Fahrenheit es fría.
    Decimos que hace frío si la temperatura es menor a 8 grados Celsius. 
-}

fahrToCelsius::Float->Float
fahrToCelsius f = (f - 32) * 5/9

haceFrio::Float->Bool
haceFrio f = fahrToCelsius f < 8