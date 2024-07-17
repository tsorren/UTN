-- Paradigmas de Programacion - Parcial Funcional
-- Autor: Tadeo Sorrentino
-- Fecha: 24/05/2024

data Fremen = UnFremen{
    nombre :: String,
    toleranciaEspecia :: Int,
    titulos :: [Titulo],
    cantReconocimientos :: Int
} deriving (Eq, Show)

type Titulo = String
type Tribu = [Fremen]
type EfectoFremen = Fremen -> Fremen

-- PUNTO 1

{- 
Ejemplo Fremen:
stilgar :: Fremen
stilgar = UnFremen{nombre = "Stilgar", toleranciaEspecia = 150, titulos = ["Guia"], cantReconocimientos = 3}
-}

-- Auxiliares

anterior :: Int -> Int
anterior num = num - 1

consultaReconocimientos :: Tribu -> [Int]
consultaReconocimientos = map cantReconocimientos

tieneTitulo :: Titulo -> Fremen -> Bool
tieneTitulo titulo = (titulo `elem`) . titulos

esCandidato :: Fremen -> Bool
esCandidato fremen = tieneTitulo "Domador" fremen && toleranciaEspecia fremen > 100

candidatos :: Tribu -> Tribu
candidatos = filter esCandidato

-- Calcula la cantidad de elementos hasta encontrar el maximo de la lista (indice de maximo)
encontrarIndiceDeMaximo :: [Int] -> Int 
encontrarIndiceDeMaximo lista = (length . takeWhile ( /= maximum lista)) lista

-- Funciones Principales

recibirReconocimiento :: EfectoFremen
recibirReconocimiento fremen = fremen{cantReconocimientos = cantReconocimientos fremen + 1}

hayCandidatos :: Tribu -> Bool
hayCandidatos = not . null . candidatos

-- Encuentra indice de freman candidato de maximo reconocimiento, accede a candidatos tribu con ese indice
hallarElegido :: Tribu -> Fremen
hallarElegido tribu = ((candidatos tribu !!) . encontrarIndiceDeMaximo . consultaReconocimientos . candidatos) tribu

-- PUNTO 2

data Gusano = UnGusano{ -- Gusanos de arena
    longitud :: Int,
    nivelHidratacion :: Int,
    descripcion :: String
} deriving (Show)

-- Auxiliares

longitudCria :: Gusano -> Gusano -> Int -- Reducir 10% = Calcular 90%
longitudCria gusano1  = porciento 90 . max (longitud gusano1) . longitud

descripcionCria :: Gusano -> Gusano -> String
descripcionCria gusano1 gusano2 = descripcion gusano1 ++ " - " ++ descripcion gusano2

reproducirDosGusanos :: Gusano -> Gusano -> Gusano
reproducirDosGusanos gus1 gus2 = UnGusano{longitud = longitudCria gus1 gus2, nivelHidratacion = 0, descripcion = descripcionCria gus1 gus2}

-- Funciones Principales

-- Añade recursivamente crias mientras las listas tengan ambas al menos un elemento, cuando esto no se cumple retorna la lista vacia
-- Esto finaliza la recursividad y devuelve la lista completa de crias
aparearListasGusanos :: [Gusano] -> [Gusano] -> [Gusano]
aparearListasGusanos [] _ = []
aparearListasGusanos _ [] = []
aparearListasGusanos (x:xs) (y:ys) = reproducirDosGusanos x y : aparearListasGusanos xs ys

-- PUNTO 3

type Mision = Gusano -> Fremen -> Fremen
type Condicion = Gusano -> Fremen -> Bool

-- Auxiliares

mitad :: Int -> Int
mitad = (`div` 2)

porciento :: Int -> Int -> Int
porciento cant = (`div` 100 ) . (* cant)

esElElegido :: Tribu -> Fremen -> Bool
esElElegido tribu =  ( == hallarElegido tribu)

-- Solo recibe titulo si no lo tenia previamente
recibirTitulo :: Titulo -> EfectoFremen
recibirTitulo nuevoTitulo fremen
    | (not . tieneTitulo nuevoTitulo) fremen = fremen{titulos = nuevoTitulo : titulos fremen}
    | otherwise = fremen

modificarCantidadTolerancia :: Int -> EfectoFremen
modificarCantidadTolerancia cant fremen = fremen{toleranciaEspecia = toleranciaEspecia fremen + cant}

aumentoNormalTolerancia :: EfectoFremen
aumentoNormalTolerancia = modificarCantidadTolerancia 100

modificarPorcentajeTolerancia :: Int -> EfectoFremen
modificarPorcentajeTolerancia cant fremen = modificarCantidadTolerancia (porciento cant . toleranciaEspecia $ fremen) fremen

-- Mision generica ya que todas cumplen el formato de Condicion, Efecto Positivo, Efecto Negativo
realizarMision :: Condicion -> EfectoFremen -> EfectoFremen -> Mision
realizarMision condicion efectoLograr efectoFallar gusano fremen
    | condicion gusano fremen = efectoLograr fremen
    | otherwise = efectoFallar fremen

-- DOMAR
puedeDomarGusano :: Condicion
puedeDomarGusano gusano = ( >= (mitad . longitud) gusano) . toleranciaEspecia

efectoDomarGusano :: EfectoFremen
efectoDomarGusano = aumentoNormalTolerancia . recibirTitulo "Domador"

efectoNoDomarGusano :: EfectoFremen
efectoNoDomarGusano = modificarPorcentajeTolerancia (-10)

domarGusano :: Mision
domarGusano = realizarMision puedeDomarGusano efectoDomarGusano efectoNoDomarGusano

-- DESTRUIR
puedeDestruirGusano :: Condicion -- not . puedeDomarGusano => tolerancia menor a mitad de longitud del gusano
puedeDestruirGusano gusano fremen = (not . puedeDomarGusano gusano) fremen && tieneTitulo "Domador" fremen

efectoDestruirGusano :: EfectoFremen
efectoDestruirGusano = recibirReconocimiento . aumentoNormalTolerancia

efectoNoDestruirGusano :: EfectoFremen
efectoNoDestruirGusano = modificarPorcentajeTolerancia (-20)

destruirGusano :: Mision
destruirGusano = realizarMision puedeDestruirGusano efectoDestruirGusano efectoNoDestruirGusano

-- MISION INVENTADA
puedeVencerGusanoGigante :: Tribu -> Condicion
puedeVencerGusanoGigante tribu gusano fremen = esElElegido tribu fremen && toleranciaEspecia fremen >= longitud gusano

efectoVencerGusanoGigante :: EfectoFremen
efectoVencerGusanoGigante = recibirReconocimiento . recibirTitulo "Elegido" . modificarPorcentajeTolerancia 50

efectoNoVencerGusanoGigante :: EfectoFremen
efectoNoVencerGusanoGigante = recibirTitulo "Veterano" . modificarPorcentajeTolerancia (-50)

vencerGusanoGigante :: Tribu -> Mision
vencerGusanoGigante tribu = realizarMision (puedeVencerGusanoGigante tribu) efectoVencerGusanoGigante efectoNoVencerGusanoGigante

-- Funciones Principales

misionColectiva :: Mision -> Gusano -> Tribu -> Tribu
misionColectiva mision gusano = map (mision gusano)

-- Evalua si el nombre elegido de la tribu original es distino del elegido luego de la mision, se utiliza el nombre como identificador
cambioElElegido :: Mision -> Gusano -> Tribu -> Bool
cambioElElegido mision gusano tribu = (nombre . hallarElegido) tribu /= (nombre . hallarElegido . misionColectiva mision gusano) tribu

-- Simulacion
simulacionGusano :: Gusano
simulacionGusano = UnGusano 120 21 "Gigante"

simulacionTribu :: Tribu
simulacionTribu = [UnFremen "Pepe" 20 ["Guia"] 1, UnFremen "Fulanito" 150 ["Domador"] 3]

simulacionMisionColectiva :: Tribu -> Tribu -- Se puede utilizar simulacionTribu o una tribu infinita
simulacionMisionColectiva tribu = misionColectiva (vencerGusanoGigante tribu) simulacionGusano simulacionTribu

-- PUNTO 4  (Enunciado : Al entrenarlos -> Simular mision colectivamente)
{-

Tribu de infinitos Fremen y gusano:

    a)      Al realizar una mision, distanta de vencerGusanoGigante, colectivamente con la tribu infinita y el gusano,
        se aplicará evaluacion diferida para calcular el efecto que recibe cada fremen individualmente,
        y se mostrará uno por uno hasta el infinito.
            En el caso de que se utilice vencerGusanoGigante, haskell necesita la tribu completa para hallar el elegido, por lo que
        busca infinitamente quien tiene la mayor cantidad de reconocimientos y no termina.

        Consulta 1:     misionColectiva domarGusano simulacionGusano (cycle simulacionTribu)
            Salida:     Lista infinita de fremen evaluados diferidamente

        Consulta 2:     misionColectiva (vencerGusanoGigante (cycle simulacionTribu)) simulacionGusano (cycle simulacionTribu)
            Salida:     Haskell se cuelga
        
    b)      Al consultar si hay candidatos con la tribu infinita, pueden suceder dos cosas:
                Existe un posible candidato     ->   Haskell evalua hasta encontrarlo y devuelve True
                No existe un posible candidato  ->   Haskell se cuelga

        Consulta 1:     hayCandidatos (cycle simulacionTribu)
            Salida:     True
        
        Consulta 2:     hayCandidatos (repeat (UnFremen "Pepe" 20 ["Guia"] 1))
            Salida:     Haskell se cuelga

    c)      Al buscar al elegido con la tribu infinita, haskell necesita encontrar el Fremen con mayor de reconocimientos de la tribu,
        esto implica evaluar todos los elementos de la tribu, por lo que no termina de evaluar nunca y Haskell se cuelga.

        Consulta 1:     hallarElegido (cycle simulacionTribu)
            Salida:     Haskell se cuelga
        
        Consulta 2:     hallarElegido (repeat (UnCandidato "Pepe" 20 ["Guia"] 1))
            Salida:     Haskell se cuelga
-}