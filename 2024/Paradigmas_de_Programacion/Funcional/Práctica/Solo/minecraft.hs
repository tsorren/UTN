data Personaje = UnPersonaje {
    nombre :: String,
    puntaje :: Int,
    inventario :: [Material]
} deriving (Show, Eq)

data Material = Material {nombreM :: String} | Objeto {nombreO :: String, receta :: Receta} deriving (Show, Eq)

type Receta = ([Material], Int)

-- Auxiliares
quitar :: Eq a => a -> [a] -> [a]
quitar _ [] = []
quitar x (y:ys)
    | x == y = ys
    | otherwise = y : quitar x ys

intersect :: [Material] -> [Material] -> [Material]
intersect _ [] = []
intersect [] _ = []
intersect xs (y:ys)
    | y `elem` xs = y : intersect xs ys
    | otherwise = intersect xs ys

puedeConstruirObj :: [Material] -> Personaje -> Bool
puedeConstruirObj  materiales personaje = (intersect (inventario personaje) materiales) == materiales

quitarObjetos ::  [Material] -> Personaje -> Personaje
quitarObjetos materiales personaje = personaje{inventario = foldr quitar (inventario personaje) materiales}

añadirObjeto :: Material -> Personaje -> Personaje
añadirObjeto material personaje = personaje{inventario = material : inventario personaje}

modificarPuntos :: Int -> Personaje -> Personaje
modificarPuntos puntos personaje = personaje{puntaje = puntaje personaje + puntos}

-- Funciones Principales
-- 1.1
construirObjeto :: Material -> Personaje -> Personaje
construirObjeto (Objeto nombre (materiales, tiempo)) personaje 
    | puedeConstruirObj materiales personaje = (quitarObjetos materiales . añadirObjeto (Objeto nombre (materiales, tiempo)) . modificarPuntos (10 * tiempo)) personaje
    | otherwise = modificarPuntos (-100) personaje

-- 1.2
elMaterialDuplica :: Material -> Personaje -> Bool
elMaterialDuplica material personaje = (puntaje . construirObjeto material) personaje > 2 * puntaje personaje

objetosCrafteables :: [Material] -> Personaje -> [Material]
objetosCrafteables objetos personaje = filter (\x -> puedeConstruirObj ((fst.receta) x)  personaje ) (filter (`elMaterialDuplica` personaje) objetos) 

crafteosSucesivos :: [Material] -> Personaje -> Personaje
crafteosSucesivos recetas personaje = foldr construirObjeto personaje recetas

mayorPuntaje :: [Material] -> Personaje -> String
mayorPuntaje recetas personaje
    | puntaje (crafteosSucesivos recetas personaje) > puntaje (crafteosSucesivos (reverse recetas) personaje) = "Es mayor con orden normal"
    | puntaje (crafteosSucesivos recetas personaje) == puntaje (crafteosSucesivos (reverse recetas) personaje) = "Es lo mismo con los dos ordenes"
    | otherwise = "Es mayor con orden inverso"

-- Pruebas
steve = UnPersonaje "Steve Stevenson" 1000 [sueter, fogata, fogata, pollo, pollo]

listaObjetos = [fogata, polloAsado, sueter]


madera = Material "Madera"
fosforo = Material "Fosforo"
pollo = Material "Pollo"
lana = Material "Lana"
agujas = Material "Agujas"
tintura = Material "Tintura"

fogata = Objeto "Fogata" ([madera, fosforo], 10)
polloAsado = Objeto "Pollo Asado" ([fogata, pollo], 300)
sueter = Objeto "Sueter" ([lana, agujas, tintura], 600)
