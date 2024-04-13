{-
    Definir una función siguiente,
    que al invocarla con un número cualquiera
    me devuelve el resultado de sumar a ese número el 1. 
-}

siguiente :: Num a => a -> a
siguiente = (1 +)