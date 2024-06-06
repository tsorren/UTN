-------------------
-- Primera Parte --
-------------------

---------------
--- Punto 1 ---
---------------
{-# OPTIONS_GHC -Wno-unrecognised-pragmas #-}
{-# HLINT ignore "Use !!" #-}
data Persona = UnaPersona
  { edad :: Int,
    items :: [Item],
    experiencia :: Int
  }

type Item = String

data Criatura = UnaCriatura
  { peligrosidad :: Int,
    condicionParaDeshacerse :: Persona -> Bool
  }

-- Funciones auxiliares
imposibleDeshacerse :: Persona -> Bool
imposibleDeshacerse _ = False

tieneItem :: Item -> Persona -> Bool
tieneItem unItem = elem unItem . items

between :: (Ord a) => a -> a -> a -> Bool
between x min max = x >= min && x <= max

-- Criaturas
siempreDetras :: Criatura
siempreDetras = UnaCriatura 0 imposibleDeshacerse

gnomos :: Int -> Criatura
gnomos cantidadGnomos = UnaCriatura (2 ^ cantidadGnomos) $ tieneItem "Soplador de Hojas"

fantasma :: Int -> (Persona -> Bool) -> Criatura
fantasma categoria condicionACumplir
  | between categoria 1 10 = UnaCriatura (categoria * 20) condicionACumplir

---------------
--- Punto 2 ---
---------------
enfrentar :: Persona -> Criatura -> Persona
enfrentar unaPersona unaCriatura
  | puedeDeshacerse unaCriatura unaPersona = ganarExperiencia (peligrosidad unaCriatura) unaPersona
  | otherwise = escapar unaPersona

-- Funciones auxiliares
puedeDeshacerse :: Criatura -> Persona -> Bool
puedeDeshacerse = condicionParaDeshacerse

ganarExperiencia :: Int -> Persona -> Persona
ganarExperiencia xp unaPersona = unaPersona {experiencia = experiencia unaPersona + xp}

escapar :: Persona -> Persona
escapar = ganarExperiencia 1

---------------
--- Punto 3 ---
---------------
-- a.
experienciaTotal :: Persona -> [Criatura] -> Int
experienciaTotal unaPersona = experiencia . foldl enfrentar unaPersona

-- b.
criaturas :: [Criatura]
criaturas = [siempreDetras, gnomos 10, fantasma 3 (\persona -> tieneMenosDe 13 persona && tieneItem "Disfraz de Oveja" persona), fantasma 1 (tieneMasDeNExperienca 10)]

-- Ejemplo
dipper :: Persona
dipper = UnaPersona 12 ["Diario 3", "Linterna", "Disfraz de Oveja"] 0

-- Consulta
-- ghci> experienciaTotal dipper criaturas
-- ghci> 82

-- Funciones auxiliares
tieneMenosDe :: Int -> Persona -> Bool
tieneMenosDe nAños = (< nAños) . edad

tieneMasDeNExperienca :: Int -> Persona -> Bool
tieneMasDeNExperienca xp = (> xp) . experiencia

-------------------
-- Segunda Parte --
-------------------

---------------
--- Punto 1 ---
---------------
zipWithIf :: (a -> b -> b) -> (b -> Bool) -> [a] -> [b] -> [b]
zipWithIf _ _ [] _ = []
zipWithIf _ _ _ [] = []
zipWithIf funcion condicion (x1:x1s) (x2:x2s)
    | not . condicion $ x2 = x2 : zipWithIf funcion condicion (x1:x1s) x2s
    | otherwise = funcion x1 x2 : zipWithIf funcion condicion x1s x2s

---------------
--- Punto 2 ---
---------------
-- a.
abecedarioDesde :: Char -> [Char]
abecedarioDesde unaLetra = dropWhile (/=unaLetra) abecedario ++ takeWhile (/=unaLetra) abecedario

abecedario :: String
abecedario = ['a' .. 'z']

-- b
desencriptarLetra :: Char -> Char -> Char
desencriptarLetra letraClave letraEncriptada = desencriptarDeluxe (abecedarioDesde letraClave) abecedario letraEncriptada
    where
        desencriptarDeluxe :: [Char] -> [Char] -> Char -> Char
        desencriptarDeluxe (x:xs) (y:ys) letraEncriptada
          | x == letraEncriptada = y
          | otherwise = desencriptarDeluxe xs ys letraEncriptada

desencriptarLetra' :: Char -> Char -> Char
desencriptarLetra' letraClave letraEncriptada = head . drop distanciaEquivalente $ abecedario
  where
    distanciaEquivalente = length . takeWhile (/= letraEncriptada)  . abecedarioDesde $ letraClave

-- c.
cesar :: Char -> String -> String
cesar = zipWithIf desencriptarLetra esLetra . repeat 

esLetra :: Char -> Bool
esLetra =  (`elem` ['a'..'z'])

-- d.
-- ghci> map (`cesar` "jrzel zrfaxal!") abecedario

---------------
--- Punto 3 ---
---------------
vigenere :: String -> String -> String
vigenere textoClave textoEncriptado = zipWithIf desencriptarLetra esLetra (alinear textoClave textoEncriptado) textoEncriptado

-- Función auxiliar
alinear :: String -> String -> String
alinear textoClave textoEncriptado = take (length textoEncriptado) . cycle $ textoClave