
sueldoPorCargo :: String -> Int
sueldoPorCargo "titular" = 149000
sueldoPorCargo "adjunto" = 116000
sueldoPorCargo "ayudante" = 66000

factorHoras :: Int -> Int
factorHoras hs 
    | mod hs 10 >= 5 = div hs 10 + 1
    | otherwise = div hs 10

incrementoAntiguedad :: Int -> Int -> Int
incrementoAntiguedad sueldo antiguedad
    | antiguedad < 3 = sueldo
    | antiguedad <= 5 = div (12 * sueldo) 10
    | antiguedad < 10 = div (13 * sueldo) 10
    | antiguedad < 24 = div (15 * sueldo) 10
    | antiguedad >= 24 = div (22 * sueldo) 10

sueldoTotal :: String -> Int -> Int -> Int
sueldoTotal cargo hs antiguedad = incrementoAntiguedad (sueldoPorCargo cargo * factorHoras hs) antiguedad