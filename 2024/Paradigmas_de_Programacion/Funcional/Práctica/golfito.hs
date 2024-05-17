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

type Puntos = Int
type Palo = Habilidad -> Tiro
type Obstaculo = Tiro -> Tiro


-- AUXILIARES
between n m x = elem x [n .. m]

maximoSegun f = foldl1 (mayorSegun f)
mayorSegun f a b
    | f a > f b = a
    | otherwise = b

doble = (2*)
mitad = ( `div` 2)
noSupera = UnTiro 0 0 0 

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

palos = [putter, madera] ++ palosHierro 10 0 []

golpe :: Palo -> Jugador -> Tiro
golpe palo = palo.habilidad

tunel :: Obstaculo
tunel tiro 
    | precision tiro > 90 && altura tiro == 0 = tiro {velocidad = (doble.velocidad) tiro, precision = 100}
    | otherwise = noSupera

laguna :: Int -> Obstaculo
laguna largo tiro
    | velocidad tiro > 80 && 1 < altura tiro && altura tiro < 5 = tiro{altura = div (altura tiro) largo}
    | otherwise = noSupera

hoyo :: Obstaculo
hoyo tiro
    | 5 < velocidad tiro && velocidad tiro  < 20 && precision tiro > 95 = tiro{velocidad = 0, precision = 0, altura = 0}
    | otherwise = noSupera

palosUtiles :: Jugador -> Obstaculo -> [Palo]
palosUtiles persona obstaculo = filter (\x -> (not . (== noSupera) . golpe x) persona) palos 


