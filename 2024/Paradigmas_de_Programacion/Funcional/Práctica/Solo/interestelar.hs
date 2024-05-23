data Planeta = UnPlaneta{
    nombreP :: String,
    posicion :: Posicion,
    distorsionTiempo :: Int -> Int
}

type Posicion = (Float, Float, Float)
coordX, coordY, coordZ :: Posicion -> Float
coordX (x, _, _) = x
coordY (_, y, _) = y
coordZ (_, _, z) = z

data Astronauta = UnAstronauta{
    nombreA :: String,
    edad :: Int,
    planetaActual :: Planeta
}

-- 1.a
calcularHipotenusa :: Posicion -> Float
calcularHipotenusa (x, y, z) = sqrt (x*x + y*y + z*z)

restaPosiciones :: Posicion -> Posicion -> Posicion
restaPosiciones (x1, y1, z1) (x2, y2, z2) = (x1 - x2, y1 - y2, z1 - z2)

distanciaEntrePlanetas :: Planeta -> Planeta -> Float
distanciaEntrePlanetas planeta1 planeta2 = (calcularHipotenusa.restaPosiciones (posicion planeta1)) (posicion planeta2)

-- 1.b
tiempoDeViaje :: Planeta -> Planeta -> Int -> Int
tiempoDeViaje planeta1 planeta2 velocidad = ((`div` velocidad) . round . distanciaEntrePlanetas planeta1) planeta2

-- 2
aumentarEdad :: Int -> Astronauta -> Astronauta
aumentarEdad tiempo astronauta = astronauta{edad = edad astronauta + tiempo}

pasarTiempo :: Int -> Astronauta -> Astronauta
pasarTiempo años astronauta = aumentarEdad ((distorsionTiempo.planetaActual) astronauta años) astronauta

-- 3.a
type Nave = (Planeta -> Planeta -> Int)

naveVieja :: Int -> Nave
naveVieja tanquesDeOxigeno planeta1 planeta2
    | tanquesDeOxigeno < 6 = tiempoDeViaje planeta1 planeta2 7
    | otherwise = tiempoDeViaje planeta1 planeta2 10

-- 3.b
naveFuturista :: Nave
naveFuturista _ _ = 0

-- 4
cambiarPlaneta :: Planeta -> Astronauta -> Astronauta
cambiarPlaneta destino astronauta = astronauta{planetaActual = destino}

tiempoConNave :: Nave -> Planeta -> Astronauta -> Int
tiempoConNave nave destino astronauta = (tiempoDeViaje (planetaActual astronauta) destino . nave (planetaActual astronauta)) destino

viajar :: Nave -> Planeta -> Astronauta -> Astronauta
viajar nave destino astronauta = (cambiarPlaneta destino . aumentarEdad (tiempoConNave nave destino astronauta)) astronauta

grupoViaja :: Nave -> Planeta -> [Astronauta] -> [Astronauta]
grupoViaja nave destino = map (viajar nave destino)

grupoPasaTiempo :: Int -> [Astronauta] -> [Astronauta]
grupoPasaTiempo años = map (pasarTiempo años)

planetaDeInicio :: [Astronauta] -> Planeta
planetaDeInicio = planetaActual.head

-- a
rescate :: Astronauta -> Nave -> Planeta -> [Astronauta] -> [Astronauta]
rescate astronauta nave destino grupo = ((astronauta :) . grupoPasaTiempo (tiempoConNave nave destino (head grupo))) grupo

misionRescate :: [Astronauta] -> Astronauta -> Nave -> Planeta -> [Astronauta]
misionRescate grupo astronauta nave destino = (grupoViaja nave (planetaDeInicio grupo) . rescate astronauta nave destino  . grupoViaja nave destino) grupo

-- b
puedeSerRescatado :: Astronauta -> Nave -> Planeta -> [Astronauta] -> Bool
puedeSerRescatado astronauta nave destino = all ((<= 90).edad) . rescate astronauta nave destino

nombresDeGrupo :: [Astronauta] -> [String]
nombresDeGrupo = map nombreA

quienesPuedenSerRescatados :: Nave -> [Astronauta] -> [Astronauta] ->[Astronauta]
quienesPuedenSerRescatados nave rescatistas = filter (\x -> puedeSerRescatado x nave (planetaActual x) rescatistas)

astronautasRescatables :: [Astronauta] -> Nave -> [Astronauta] -> [String]
astronautasRescatables rescatistas nave = nombresDeGrupo . quienesPuedenSerRescatados nave rescatistas

-- 5 Inferir el tipo de "f a b c = any (( > b).a b).filter (c 10)" 
-- f :: a -> b -> c -> [d] -> Bool 
--              b es Num
--              a es func de Num -> d -> Num
--              c es b -> d -> Bool

-- f :: (Ord -> d -> Ord) -> Ord -> (Num -> d -> Bool) -> d -> Bool
f :: (Ord a, Num b) => (a -> d -> a) -> a -> (b -> d -> Bool) -> [d] -> Bool
f a b c = any (( > b).a b).filter (c 10)
--f a b c listaD = any (a b d > b) (filter (c 10) listaD)