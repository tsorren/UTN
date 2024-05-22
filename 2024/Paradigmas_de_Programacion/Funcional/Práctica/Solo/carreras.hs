import Data.List

-- 1.
data Auto = UnAuto{
  color :: Color,
  velocidad :: Int,
  distanciaRecorrida :: Int
} deriving (Show, Eq)

type Color = String

type Carrera = [Auto]

type Criterio = Auto -> Carrera -> Bool

-- a.
distanciaEntre :: Auto -> Auto -> Int
distanciaEntre auto1 auto2 = abs (distanciaRecorrida auto1 - distanciaRecorrida auto2)

estanCerca :: Auto -> Auto -> Bool
estanCerca auto1 auto2 = auto1 /= auto2 && distanciaEntre auto1 auto2 < 10

-- b.
vaSolo :: Criterio
vaSolo auto = not . any (estanCerca auto)

vaGanando :: Criterio
vaGanando auto carrera = all (\x -> distanciaRecorrida x <= distanciaRecorrida auto) carrera

vaTranquilo :: Criterio
vaTranquilo auto carrera = vaSolo auto carrera && vaGanando auto carrera

-- c.
distancias :: Carrera -> [Int]
distancias = map distanciaRecorrida

puestos :: Carrera -> Carrera
puestos = sortBy (flip (\x y -> compare (distanciaRecorrida x) (distanciaRecorrida y)))

puestoAuto :: Auto -> Carrera -> Int
puestoAuto auto = (+ 1) . length . takeWhile (/= auto).puestos

vaAtrasDe :: Auto -> Auto -> Bool
vaAtrasDe auto = (< distanciaRecorrida auto).distanciaRecorrida

-- 2.
type Modificador = Auto -> Auto

-- a.
correr :: Int -> Modificador
correr tiempo auto = auto {distanciaRecorrida = distanciaRecorrida auto + tiempo * velocidad auto}
-- b.
piso :: Int -> Int
piso = max 0

-- i.
alterarVelocidad :: (Int -> Int) -> Modificador
alterarVelocidad modificador auto = auto {velocidad = (piso . modificador . velocidad) auto}

-- ii.
bajarVelocidad :: Int -> Modificador
bajarVelocidad cant auto = alterarVelocidad (\x -> x - cant)  auto

-- 3.
type Powerup = Auto -> Carrera -> Carrera

afectarALosQueCumplen :: (Auto -> Bool) -> Modificador -> Carrera -> Carrera
afectarALosQueCumplen criterio efecto carrera = (map efecto . filter criterio) carrera ++ filter (not . criterio) carrera

-- a. 
terremoto :: Powerup
terremoto auto = afectarALosQueCumplen (estanCerca auto) (bajarVelocidad 50)

-- b.
miguelitos :: Int -> Powerup
miguelitos cant auto = afectarALosQueCumplen (vaAtrasDe auto) (bajarVelocidad cant)

-- c.
jetpack :: Int -> Powerup
jetpack tiempo auto = afectarALosQueCumplen (== auto) (alterarVelocidad (`div` 2) . correr tiempo . alterarVelocidad (2*))

-- 4.
type Evento = Carrera -> Carrera

aplicarEventos :: [Evento] -> Evento
aplicarEventos eventos carrera = foldr id carrera eventos

conseguirResultado :: Carrera -> Resultado
conseguirResultado carrera = map (\x -> (puestoAuto x carrera, color x)) carrera
-- a.
type Resultado = [(Int, Color)]

simularCarrera :: [Evento] -> Carrera -> Resultado
simularCarrera eventos = conseguirResultado . puestos . aplicarEventos eventos

-- b.
-- i.
correnTodos :: Int -> Evento
correnTodos tiempo carrera = map (correr tiempo) carrera

hallarAutoColor :: Color -> Carrera -> Auto
hallarAutoColor colorBuscado = head.dropWhile ((/= colorBuscado).color)

-- ii.
usaPowerUp :: Powerup -> Color -> Evento
usaPowerUp powerUp color carrera = powerUp (hallarAutoColor color carrera) carrera

-- c.
auto1 :: Auto
auto1 = UnAuto "rojo" 120 0

auto2 :: Auto
auto2 = UnAuto "blanco" 120 0

auto3 :: Auto
auto3 = UnAuto "azul" 120 0

auto4 :: Auto
auto4 = UnAuto "negro" 120 0 :: Auto

carrera1 :: Carrera
carrera1 = [auto1, auto2, auto3, auto4]

evento1 :: Evento
evento1 = correnTodos 30

evento2 :: Evento
evento2 = usaPowerUp (jetpack 3) "azul"

evento3 :: Evento
evento3 = usaPowerUp terremoto "blanco"

evento4 :: Evento
evento4 = correnTodos 40

evento5 :: Evento
evento5 = usaPowerUp (miguelitos 20) "blanco"

evento6 :: Evento
evento6 = usaPowerUp (jetpack 6) "negro"

evento7 :: Evento
evento7 = correnTodos 10

tablaPuestos :: Resultado
tablaPuestos = simularCarrera [evento1, evento2, evento3, evento4, evento5, evento6, evento7] carrera1

--5.
-- a. Se puede realiza de la siguiente manera (efecto a definir)
-- misilTeledirigido :: Color -> Powerup
-- misilTeledirigido color auto carrera = afectarALosQueCumplen (== hallarAutoColor color carrera) efecto carrera

-- b.
-- (1.b) En el caso de que el auto vaya tranquilo, no se podrá terminar de evaluar ya que debe comparar con los demás. Si va tranquilo si termina de evaluar
-- (1.c) No es posible usar la funcion de encontrar puesto, ya que primero debe ordenar la lista por lo que no se termina de evaluar nunca.