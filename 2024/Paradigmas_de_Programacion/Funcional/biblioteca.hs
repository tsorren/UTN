func :: [a] -> a
func (x:xs) = x

func2 :: [a] -> a
func2 lista = lista !! 0

sinPrimerElem :: [a]->[a]
sinPrimerElem (x:xs)= xs

-- odd
esImpar :: (Integral a) => a -> Bool
esImpar numero = mod numero 2 /= 0

-- even
esPar :: (Integral a) => a -> Bool
esPar numero = mod numero 2 == 0

-- id
identificacion :: a -> a
identificacion x = x

-- const
constante :: a -> b -> a
constante x y = x

-- null
nulo :: String -> Bool
nulo palabra = palabra == ""

-- max
maximo :: (Ord a) => a -> a -> a
maximo x y
  | x > y = x
  | y > x = y
  | otherwise = x

-- min
minimo :: (Ord a) => a -> a -> a
minimo x y
  | x > y = y
  | y > x = x
  | otherwise = x

-- ($)
peso :: (a -> b) -> a -> b
peso x = x

-- mod
resto :: (Integral a) => a -> a -> a
resto dividendo divisor = dividendo - divisor * div dividendo divisor

-- div
divisionEntera :: (Integral a) => a -> a -> a
divisionEntera x y = fromInteger (toInteger x `Prelude.quot` toInteger y)

-- flip
voltear :: (a -> b -> c) -> b -> a -> c
voltear f x y = f y x

-- length
cantidadDeElementos :: [a] -> Int
cantidadDeElementos = contadorAuxiliar 0

contadorAuxiliar :: (Num t) => t -> [a] -> t
contadorAuxiliar acumulador lista
  | null lista = acumulador
  | otherwise = contadorAuxiliar (acumulador + 1) (tail lista)

-- head
primerElemento :: [a] -> a
primerElemento = (!! 0)

-- last
ultimoElemento :: [a] -> a
ultimoElemento lista = ((lista !!) . anterior . length) lista

anterior :: (Num a) => a -> a
anterior num = num - 1

-- tail
eliminarPrimerElemento :: [a] -> [a]
eliminarPrimerElemento (x : xs) = xs

-- null
esVacia :: [a] -> Bool
esVacia = (0 ==) . length

-- ++
concatenacion :: [a] -> [a] -> [a]
concatenacion lista1 = agregarRecursiva (reverse lista1)

agregarRecursiva :: [a] -> [a] -> [a]
agregarRecursiva lista1 lista2
  | null lista1 = lista2
  | otherwise = agregarRecursiva (tail lista1) ((:) (head lista1) lista2)

-- reverse
invertirLista :: [a] -> [a]
invertirLista lista = agregarRecursiva lista []

operar :: (Num t) => (t -> t -> t) -> [t] -> t -> t
operar operador lista numero
  | null lista = numero
  | otherwise = operar operador (tail lista) (operador numero (head lista))

-- sum
sumatoria :: (Num t) => [t] -> t
sumatoria lista = operar (+) lista 0

-- product
producto :: (Num t) => [t] -> t
producto lista = operar (*) lista 1


listaNatural :: Int -> [Int]
listaNatural val = [1..val]

factorial :: Int -> Int
factorial = producto . listaNatural

-- elem
perteneceA :: (Foldable ((->) p), Eq p) => p -> (Bool -> Bool) -> Bool
perteneceA elemento lista = lista `any` (== elemento)

-- !!
posicionLista :: [a] -> Int -> a
posicionLista  = recorrerHasta 

recorrerHasta :: [a] -> Int -> a
recorrerHasta lista indice
    | ((+1) . length) lista == indice = head lista
    | otherwise = recorrerHasta ((tail . reverse) lista) indice

-- filter
filtrar :: (a -> Bool) -> [a] -> [a]
filtrar criterio lista = reverse (agregarConCriterio criterio lista [])

agregarConCriterio :: (a -> Bool) -> [a] -> [a] -> [a]
agregarConCriterio criterio lista1 lista2
  | null lista1 = lista2
  | (criterio . head) lista1 = agregarConCriterio criterio (tail lista1) (head lista1 : lista2)
  | otherwise = agregarConCriterio criterio (tail lista1) lista2


-- map
mapa :: (a -> b) -> [a] -> [b]
mapa transformacion lista =  transformacionRecursiva transformacion lista []

transformacionRecursiva :: (a -> b) -> [a] -> [b] -> [b]
transformacionRecursiva transformacion entrada salida
    | null entrada = reverse salida
    | otherwise = transformacionRecursiva transformacion (tail entrada) ((transformacion.head) entrada : salida)

-- all
todosCumplen :: (Eq a) => (a -> Bool) -> [a] -> Bool
todosCumplen criterio lista = filter criterio lista == lista

-- any
algunoCumple :: (Eq a) => (a -> Bool) -> [a] -> Bool
algunoCumple criterio  = not . null . filter criterio
