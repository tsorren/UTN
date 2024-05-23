{-
    Definir las funciones fst3, snd3, trd3, que dada una tupla de 3 elementos devuelva el elemento correspondiente, p.ej. 
-}
fst3 :: (a, a, a) -> a
fst3 (x, _, _) = x

snd3 :: (a, a, a) -> a
snd3 (_, y, _) = y

trd3 :: (a, a, a) -> a
trd3 (_, _, z) = z
