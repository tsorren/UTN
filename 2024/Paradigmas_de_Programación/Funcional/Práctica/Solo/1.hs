{-
“El costo de estacionamiento es de 50 pesos la hora, con un mínimo de 2 horas”, esto significa que
si estamos 1 hora, nos cobrarán por 2 horas
si estamos 3 horas, nos cobrarán por 3 horas

Independientemente de eso siempre nos cobran 50 pesos la hora.
-}
costo :: Int -> Int
costo h = 50 * max 2 h

popList :: [Int] -> Int -> Int
popList [] k = k
popList (x:xs) k = popList xs (k+x)

capicua :: String -> Bool
capicua str = str == reverse str