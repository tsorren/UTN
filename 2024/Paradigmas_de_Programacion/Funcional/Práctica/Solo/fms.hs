type Palabra = String
type Verso = String
type Estrofa = [Verso]
type Artista = String -- Solamente interesa el nombre

-- Auxiliares

esVocal :: Char -> Bool
esVocal = flip elem "aeiou"

tieneTilde :: Char -> Bool
tieneTilde = flip elem "áéíóú"

vocales :: Palabra -> String
vocales = filter (\x -> esVocal x || tieneTilde x)

cumplen :: (a -> b) -> (b -> b -> Bool) -> a -> a -> Bool
cumplen f comp v1 v2 = comp (f v1) (f v2)

tomarUltimasNLetras :: Int -> Palabra -> Palabra
tomarUltimasNLetras n = take n . reverse

primeraPalabra :: Verso -> Palabra
primeraPalabra = head . words

ultimaPalabra :: Verso -> Palabra
ultimaPalabra = last . words

-- Rimas
esRimaAsonante :: Palabra -> Palabra -> Bool
esRimaAsonante palabra1 palabra2 = cumplen (tomarUltimasNLetras 2 . vocales) (==) palabra1 palabra2

esRimaConsonante :: Palabra -> Palabra -> Bool
esRimaConsonante palabra1 palabra2 = cumplen (tomarUltimasNLetras 3) (==) palabra1 palabra2

-- 1.
-- a. 
riman :: Palabra -> Palabra -> Bool
riman palabra1 palabra2 = palabra1 /= palabra2 && esRimaAsonante palabra1 palabra2 || esRimaConsonante palabra1 palabra2

-- b.
-- pa k kieres saber eso jaja salu2

-- 2. Conjugaciones
conjugacionRima :: Verso -> Verso -> Bool
conjugacionRima verso1 verso2 = riman (ultimaPalabra verso1) (ultimaPalabra verso2)

conjugacionAnadiplosis :: Verso -> Verso -> Bool
conjugacionAnadiplosis verso1 verso2 = riman (ultimaPalabra verso1) (primeraPalabra verso2)

-- 3. Patrones
type Patron = Estrofa -> Bool

patronSimple :: Int -> Int -> Patron
patronSimple indice1 indice2 estrofa = riman (estrofa !! indice1) (estrofa !! indice2)

patronEsdrujula :: Patron
patronEsdrujula = all (tieneTilde . (!! 2) . reverse . vocales)

patronAnafora :: Patron
patronAnafora estrofa = all ((== (primeraPalabra.head) estrofa) . primeraPalabra) estrofa

patronCadena :: Patron
patronCadena [x,y] = x == y
patronCadena (x:y:ys) = ultimaPalabra x == primeraPalabra y && patronCadena ys

patronCombinado :: Patron -> Patron -> Patron
patronCombinado patron1 patron2 estrofa = patron1 estrofa && patron2 estrofa

aabb = patronCombinado (patronSimple 1 2) (patronSimple 3 4)
abab = patronCombinado (patronSimple 1 3) (patronSimple 2 4)
abba = patronCombinado (patronSimple 1 4) (patronSimple 2 3)
hardcore = patronCombinado patronCadena patronEsdrujula

-- Puestas en Escena
data PuestaEscena = UnaPuestaEscena {
    publicoExaltado :: Bool,
    potencia :: Float,
    estrofa :: Estrofa,
    artista :: Artista
} deriving (Show)

type Estilo = PuestaEscena -> PuestaEscena

aumentarPotencia :: Float -> Estilo
aumentarPotencia cant puesta = puesta{potencia = potencia puesta * (1 + cant/100)}

exaltar :: Bool -> Estilo
exaltar booleano puesta = puesta{publicoExaltado = booleano}

gritar :: Estilo
gritar = aumentarPotencia 50

responderAcote :: Bool -> Estilo
responderAcote True = aumentarPotencia 20 . exaltar True
responderAcote False = exaltar False

tirarTecnicas :: Patron -> Estilo
tirarTecnicas patron puesta
    | (patron.estrofa) puesta = (aumentarPotencia 10 . exaltar True) puesta
    | otherwise = exaltar False puesta

-- 4.

tirarFree :: Artista -> Estrofa -> Estilo -> PuestaEscena
tirarFree artista estrofa estilo = estilo (UnaPuestaEscena False 1 estrofa artista)

-- Jurados
type Criterio = Bool
type Jurado = PuestaEscena -> [(Criterio, Float)]

alToke :: Jurado
alToke puesta = [
    ( (aabb.estrofa) puesta, 0.5 ),
    ( (patronCombinado patronEsdrujula (patronSimple 1 4). estrofa) puesta, 1 ),
    ( publicoExaltado puesta, 1 )]

sumarPuntos :: Float -> (Criterio, Float) -> Float
sumarPuntos suma (True, cant) = suma + cant
sumarPuntos suma (False, _) = suma

calcularPuntos :: Jurado -> PuestaEscena -> Float
calcularPuntos jurado = min 3 . sum . map snd . filter fst . jurado

calcularPromedio :: [a] -> Float -> Float
calcularPromedio lista num = num / (fromIntegral . length) lista

calcularPuntosBatalla :: [PuestaEscena] -> [Jurado] -> Float
calcularPuntosBatalla puestas jurados = (calcularPromedio puestas.sum.map (\puesta -> (calcularPromedio jurados.foldr (\jurado num -> calcularPuntos jurado puesta + num) 0) jurados)) puestas

batalla :: [PuestaEscena] -> [PuestaEscena] -> [Jurado] -> Artista
batalla puestasArt1 puestasArt2 jurados 
    | calcularPuntosBatalla puestasArt1 jurados > calcularPuntosBatalla puestasArt2 jurados = (artista.head) puestasArt1
    | otherwise = (artista.head) puestasArt2