data Turista = UnTurista{
    cansancio :: Int,    
    estres :: Int,
    viajaSolo :: Bool,
    idiomasHablados :: [Idioma] 
} deriving (Show)

type Idioma = String
type Excursion = Turista -> Turista
data Marea = Fuerte | Moderada | Tranquila
-- Auxiliares

modificCansancio :: Int -> Turista -> Turista
modificCansancio cant turista = turista{cansancio = cansancio turista + cant}

modificEstres :: Int -> Turista -> Turista
modificEstres cant turista = turista{estres = estres turista + cant}

aprenderIdioma :: Idioma -> Turista -> Turista
aprenderIdioma idioma turista 
    | (notElem idioma . idiomasHablados) turista = turista{idiomasHablados = idioma : idiomasHablados turista}
    | otherwise = turista

modificAcompañado :: Bool -> Turista -> Turista
modificAcompañado valor turista = turista{viajaSolo = valor} 

intensidad :: Int -> Int
intensidad = (`div` 4)

-- 1.
-- Excursiones
irPlaya :: Excursion
irPlaya (UnTurista cans estr True idiomas) = modificCansancio (-5) (UnTurista cans estr True idiomas)
irPlaya turista = modificEstres (-1) turista

apreciarPaisaje :: String -> Excursion
apreciarPaisaje cosa = modificEstres ((negate.length) cosa)

hablarIdioma :: Idioma -> Excursion
hablarIdioma idioma = modificAcompañado True . aprenderIdioma idioma

caminar :: Int -> Excursion
caminar tiempo = modificCansancio (intensidad tiempo) . modificEstres (negate.intensidad $ tiempo)

paseoEnBarco :: Marea -> Excursion
paseoEnBarco Fuerte = modificEstres 6 . modificCansancio 10
paseoEnBarco Moderada = id 
paseoEnBarco Tranquila = hablarIdioma "Aleman" . apreciarPaisaje "mar" . caminar 10 

-- Ejemplos
ana, beto, cathi :: Turista
ana = UnTurista {cansancio = 0, estres = 21, viajaSolo = False, idiomasHablados = ["Español"]}
beto = UnTurista {cansancio = 15, estres = 15, viajaSolo = True, idiomasHablados = ["Aleman"]}
cathi = UnTurista {cansancio = 15, estres = 15, viajaSolo = True, idiomasHablados = ["Aleman", "Catalan"]}

-- 2
-- Auxiliares
deltaSegun :: (a -> Int) -> a -> a -> Int
deltaSegun f algo1 algo2 = f algo1 - f algo2 

calcularPorcentaje :: Int -> Int -> Int
calcularPorcentaje cant = (`div` 100) . ((100 + cant) * )

modificEstresPorcentual :: Int -> Turista -> Turista
modificEstresPorcentual cant turista = turista{estres = calcularPorcentaje 10 (estres turista)}

cantIdiomasHablados :: Turista -> Int
cantIdiomasHablados = length . idiomasHablados

esExcursionDesestresante :: Turista -> Excursion -> Bool
esExcursionDesestresante turista excursion = deltaExcursionSegun estres turista excursion <= -3

-- Funciones 

hacerExcursion :: Excursion -> Excursion
hacerExcursion excursion = modificEstresPorcentual (-10) . excursion

deltaExcursionSegun :: (Turista -> Int) -> Turista -> Excursion -> Int
deltaExcursionSegun indice turista excursion = deltaSegun indice (hacerExcursion excursion turista) turista

esExcursionEducativa :: Excursion -> Turista -> Bool
esExcursionEducativa excursion turista = deltaExcursionSegun cantIdiomasHablados turista excursion >= 1 

excursionesDesestresantes :: Turista -> [Excursion] -> [Excursion]
excursionesDesestresantes turista = filter (esExcursionDesestresante turista)