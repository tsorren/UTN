data Jugador = UnJugador {
    nombre :: String,
    padre :: String,
    habilidad :: Habilidad
} deriving (Eq, Show)

data Habilidad = Habilidad {
    fuerzaJugador :: Int,
    precisionJugador :: Int
} deriving (Eq, Show)

data Tiro = UnTiro {
    velocidad :: Int,
    precision :: Int,
    altura :: Int
} deriving (Eq, Show)

data Obstaculo = UnObstaculo {
    tiroPost :: PostObstaculo,
    superaObstaculo :: SuperaObstaculo
}

type Puntos = Int
type Palo = Habilidad -> Tiro
type PostObstaculo = Tiro -> Tiro
type SuperaObstaculo = Tiro -> Bool


-- AUXILIARES
between n m x = x `elem` [n .. m]

maximoSegun f = foldl1 (mayorSegun f)
mayorSegun f a b
    | f a > f b = a
    | otherwise = b

doble = (2*)
mitad = ( `div` 2)
noSupera = UnTiro 0 0 0
-- Jugadores de ejemplo
bart :: Jugador
bart = UnJugador "Bart" "Homero" (Habilidad 25 60)

todd :: Jugador
todd = UnJugador "Todd" "Ned" (Habilidad 15 80)

rafa :: Jugador
rafa = UnJugador "Rafa" "Gorgory" (Habilidad 10 1)

-- Punto 1
putter :: Palo
putter habilidadJugador = UnTiro {velocidad = 10, precision = (doble.precisionJugador) habilidadJugador, altura = 0}

madera :: Palo
madera habilidadJugador = UnTiro {velocidad = 100, precision = (mitad.precisionJugador) habilidadJugador, altura = 5}

hierro :: Int -> Palo
hierro num habilidadJugador = UnTiro {
    velocidad = ((num *) . fuerzaJugador) habilidadJugador,
    precision = ((`div` num) . precisionJugador) habilidadJugador,
    altura = max 0 (num - 3)
}

palosHierro :: Int -> Int -> [Palo] -> [Palo]
palosHierro cant n lista
    | n < cant = palosHierro cant (n+1) (hierro n : lista)
    | otherwise = lista

palos :: [Palo]
palos = [putter, madera] ++ palosHierro 10 1 []

golpe :: Palo -> Jugador -> Tiro
golpe palo = palo.habilidad

superaTunelConRampita :: SuperaObstaculo
superaTunelConRampita (UnTiro _ prec alt) = prec > 90 && alt == 0

postTunelConRampita :: PostObstaculo
postTunelConRampita tiro
    | superaTunelConRampita tiro = tiro {velocidad = (doble.velocidad) tiro, precision = 100}
    | otherwise = noSupera

tunelConRampita :: Obstaculo
tunelConRampita = UnObstaculo postTunelConRampita superaTunelConRampita

superaLaguna :: SuperaObstaculo
superaLaguna (UnTiro vel _ alt) = vel > 80 && between 1 5 alt

postLaguna :: Int -> PostObstaculo
postLaguna largo tiro
    | superaLaguna tiro = tiro{altura = div (altura tiro) largo}
    | otherwise = noSupera

laguna :: Int -> Obstaculo
laguna ancho = UnObstaculo (postLaguna ancho) superaLaguna

superaHoyo :: SuperaObstaculo
superaHoyo (UnTiro vel prec _) = between 5 20 vel && prec > 95

postHoyo :: PostObstaculo
postHoyo _ = noSupera

hoyo :: Obstaculo
hoyo = UnObstaculo postHoyo superaHoyo

superaConPalo :: Jugador -> Obstaculo -> Palo -> Bool
superaConPalo persona obstaculo palo = superaObstaculo obstaculo (golpe palo persona)

palosUtiles :: Jugador -> Obstaculo -> [Palo]
palosUtiles persona obstaculo = filter (superaConPalo persona obstaculo) palos

cantidadSuperados :: Tiro -> [Obstaculo] -> Int
cantidadSuperados _ [] = 0
cantidadSuperados tiro (primerObstaculo:obstaculos) 
    | superaObstaculo primerObstaculo tiro = 1 + cantidadSuperados (tiroPost primerObstaculo tiro) obstaculos
    | otherwise = 0

cantSupPorPalo :: Jugador -> [Obstaculo] -> [Int]
cantSupPorPalo persona obstaculos = map (\x -> cantidadSuperados ((x.habilidad) persona) obstaculos) palos

encontrarMaximo :: [Int] -> Int
encontrarMaximo lista = (length.takeWhile (/= maximum lista)) lista

paloMasUtil :: Jugador -> [Obstaculo] -> Palo
paloMasUtil persona obstaculos = palos !! (encontrarMaximo.cantSupPorPalo persona) obstaculos

testTiro = UnTiro 10 96 0
testObstaculos = [tunelConRampita, tunelConRampita, hoyo]

ganador :: [(Jugador, Puntos)] -> (Jugador, Puntos)
ganador lista = lista !! (encontrarMaximo . map snd) lista

padresPerdedores :: [(Jugador, Puntos)] -> [String]
padresPerdedores lista = (map (padre.fst) . filter (/= ganador lista)) lista