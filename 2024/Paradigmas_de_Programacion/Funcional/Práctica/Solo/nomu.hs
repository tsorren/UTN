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
-}

data Poder = UnPoder {
    cCuracion :: Int,
    cDaño :: Int,
    rangoAtk :: Int,
    probCrit :: Float
}   

data Nomus = UnNomus {
    alas :: Bool,
    brazos :: Int,
    ojos :: Int,
    cPiel :: String,
    vida :: Int,
    fuerza :: Int,
    poderes :: [Poder]
}

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