{-
    Nomus
    alas, brazos, ojos, cPiel, vida, fuerza
    
    f1 Tiene ojos y categoría

    categoria:
        Comunes
        Fuertes
        High end
        Pichi
 
    Poderes:
        cantCuracion
        cantDaño
        rangoAtk
        rngCrit

    f2 Averiguar proba crit ultimo poder
    f3 Saber si rango de atk cuerpoAcuerpo es < 100
    f4 Saber si poder solo cura (0 dmg)

    f5 funcion irAlGimnasio hace lo mismo que entrenar durante 15 minutos. (Aumenta la fuerza del nomu por minuto entrenado)
    f6 dada una lista de nomus, se quiere hacer que todos vayan al gimnasio

    f7 dada una lista de nomus, queremos saber quienes tienen alas

    f8 dada una lista de nomus, queremos saber si todos son poderosos    
    un nomus es poderoso cuando su fuerza es mayor a 35

    f9 dada una lista de nomus se quiere saber si los que tienen mas de un
    brazo son poderosos

    f10 dada una de lista se quiere saber si despues de ir al gimnasio
    quienes son poderosos
-}

data Poder = UnPoder {
    cCuracion :: Int,
    cDaño :: Int,
    rangoAtk :: Int,
    probCrit :: Float
} deriving Show

data Nomus = UnNomus {
    alas :: Bool,
    brazos :: Int,
    ojos :: Int,
    cPiel :: String,
    vida :: Int,
    fuerza :: Int,
    poderes :: [Poder]
} deriving Show

nomuPrueba :: Nomus
nomuPrueba = UnNomus False 3 4 "Azul" 100 20 []

categorizarNomu :: Int -> String
categorizarNomu fuerza
    | fuerza < 1000 = "Pichi"
    | fuerza < 3000 = "Comun"
    | fuerza < 10000 = "Fuerte"
    | otherwise = "High-end"

tieneOjos :: Int -> Bool
tieneOjos n = n > 0

consultaVistaCategoria :: Nomus -> (Bool, String)
consultaVistaCategoria (UnNomus _ _ o _ _ f _) = (tieneOjos o, categorizarNomu f)

consultaCrit :: Poder -> Float
consultaCrit (UnPoder _ _ _ proba) = proba

critUltimoP :: Nomus -> Float
critUltimoP (UnNomus _ _ _ _ _ _ p) = (consultaCrit . last) p

esCuerpoACuerpo :: Poder -> Bool
esCuerpoACuerpo (UnPoder _ _ r _) = r < 100

esCuracion :: Poder -> Bool
esCuracion (UnPoder c d _ _) = c > 0 && d == 0

irAlGimnasio :: Int -> Nomus -> Nomus
irAlGimnasio tiempo nomus = nomus {fuerza = fuerza nomus + tiempo}

entrenarGrupo :: Int -> [Nomus] -> [Nomus]
entrenarGrupo tiempo grupo = map (irAlGimnasio tiempo) grupo

tienenAlas :: [Nomus] -> [Nomus]
tienenAlas = filter alas

esPoderoso :: Nomus -> Bool
esPoderoso = (35 <=) . fuerza

todosSonPoderosos :: [Nomus] -> Bool
todosSonPoderosos = all ((35 <=).fuerza)

losQueTienenBrazosSonPoderosos :: [Nomus] -> Bool
losQueTienenBrazosSonPoderosos = all esPoderoso . filter ((1 <=) . brazos)

poderososDespuesDelGimnasio :: Int -> [Nomus] -> [Nomus]
poderososDespuesDelGimnasio tiempo = filter esPoderoso . entrenarGrupo tiempo