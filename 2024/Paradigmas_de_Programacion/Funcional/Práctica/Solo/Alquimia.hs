{-# OPTIONS_GHC -Wno-overlapping-patterns #-}

data Elemento = Elemento
  { nombreE :: String,
    simboloQuimicoE :: String,
    numeroAtomico :: Int,
    especieE :: Grupo
  }
  deriving (Eq, Show)

type Componente = (Elemento, Int)

data Sustancia
  = EsSencilla
      { elemento :: Elemento
      }
  | EsCompuesta
      { componentes :: [Componente],
        nombreC :: String,
        -- simboloQuimicoC :: String,
        especieC :: Grupo
      }
  deriving (Eq, Show)

data Grupo = Metal | NoMetal | Halogeno | GasNoble | Alcaloide deriving (Eq, Show)

data Criterio = Calor | Electricidad deriving (Eq, Show)

-- 1)
-- a)
carbono :: Sustancia
carbono = EsSencilla (Elemento "Carbono" "C" 6 NoMetal)

nitrogeno :: Sustancia
nitrogeno = EsSencilla (Elemento "Nitrogeno" "N" 7 NoMetal)

hidrogeno :: Sustancia
hidrogeno = EsSencilla (Elemento "Hidrogeno" "H" 1 NoMetal)

oxigeno :: Sustancia
oxigeno = EsSencilla (Elemento "Oxigeno" "O" 8 NoMetal)

dietilamidaDeÁcidoLisérgico :: Sustancia
dietilamidaDeÁcidoLisérgico = EsCompuesta [(elemento carbono, 20), (elemento hidrogeno, 25), (elemento nitrogeno, 3), (elemento oxigeno, 1)] "Dietilamida de Ácido Lisérgico" Alcaloide

-- b)
agua :: Sustancia
agua = EsCompuesta [(elemento hidrogeno, 2), (elemento oxigeno, 1)] "Agua" NoMetal

-- 2)
grupo :: Sustancia -> Grupo
grupo (EsSencilla (Elemento _ _ _ grupo)) = grupo
grupo (EsCompuesta _ _ grupo) = grupo

conduceBien :: Criterio -> Sustancia -> Bool
conduceBien _ sustancia = grupo sustancia == Metal
conduceBien Electricidad (EsSencilla (Elemento _ _ _ GasNoble)) = True
conduceBien Calor (EsCompuesta _ _ Halogeno) = True
conduceBien _ _ = False

-- 3

esVocal :: Char -> Bool
esVocal a = a `elem` "aeiouáéíóú"

nombre :: Sustancia -> String
nombre (EsSencilla (Elemento nombreE _ _ _)) = nombreE
nombre (EsCompuesta _ nombreC _) = nombreC

-- agarra el nombre, lo da vuelta, le zapatea, le quita las vocales, lo vuelve a dar vuelta, lo marea y le suma uro
nombreUnion :: Sustancia -> String
nombreUnion sustancia
  | (not . esVocal . last . nombre) sustancia = nombre sustancia ++ "uro"
  | otherwise = ((++ "uro") . reverse . dropWhile esVocal . reverse . nombre) sustancia

-- 4
combinar :: Sustancia -> Sustancia -> String
combinar primera segunda = nombreUnion primera ++ " de " ++ nombre segunda

componente :: Componente -> Sustancia
componente componente = EsSencilla (fst componente)

-- 5
mezclar :: Componente -> Componente -> Sustancia
mezclar primero segundo = EsCompuesta [primero, segundo] (combinar (componente primero) (componente segundo)) NoMetal

-- 6
formula :: Sustancia -> String
formula (EsSencilla (Elemento _ simbolo _ _)) = simbolo
formula (EsCompuesta componentes _ _) = "("++ concatMap representacion componentes ++ ")"

representacion :: Componente -> String
representacion componenteX
  | snd componenteX == 1 = (formula . componente) componenteX
  | otherwise = (formula . componente)  componenteX ++ (show . snd) componenteX