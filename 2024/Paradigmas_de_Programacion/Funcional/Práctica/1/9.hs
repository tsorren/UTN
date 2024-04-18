{-
    Definir la función mcm/2 que devuelva el mínimo común múltiplo entre dos números, de acuerdo a esta fórmula. 
    m.c.m.(a, b) = {a * b} / {m.c.d.(a, b)} 
    Nota: Se puede utilizar gcd.
-}
mcm::Int->Int->Int
mcm a b = div (a*b) (gcd a b)