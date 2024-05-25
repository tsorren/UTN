-- Definir una funcion que sume una lista de números
sumatoria :: Num a => [a] -> a
sumatoria = foldr1 (+)
