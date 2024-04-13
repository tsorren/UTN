sueldoCargo :: String -> Int
sueldoCargo "titular" = 149000
sueldoCargo "adjunto" = 116000
sueldoCargo "ayudante" = 66000

factorHoras :: Int -> Int
factorHoras hs 
    | mod hs 10 >= 5 = div hs 10 + 1
    | otherwise = div hs 10

incAntiguedad :: Int -> Int -> Int
incAntiguedad sueldo antiguedad
    | antiguedad < 3 = sueldo
    | antiguedad <= 5 = div (12 * sueldo) 10
    | antiguedad < 10 = div (13 * sueldo) 10
    | antiguedad < 24 = div (15 * sueldo) 10
    | antiguedad >= 24 = div (22 * sueldo) 10

sueldoTotal :: String -> Int -> Int -> Int
sueldoTotal cargo hs antiguedad = 
    incAntiguedad (sueldoCargo cargo * factorHoras hs) antiguedad