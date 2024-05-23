{-
    Definir la función cuentaBizarra, que recibe un par y:
    si el primer elemento es mayor al segundo devuelve la suma,
    si el segundo le lleva más de 10 al primero devuelve la resta 2do – 1ro,
    y si el segundo es más grande que el 1ro pero no llega a llevarle 10, devuelve el producto
-}

cuentaBizarra :: (Ord a, Num a) => (a, a) -> a
cuentaBizarra  (x, y)
    | x > y = x + y
    | y - 10 > x = y - x
    | otherwise = x * y