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
puedeConstruirObj  materiales personaje = intersect (inventario personaje) materiales == materiales

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

ordenNormalEsMayor :: [Material] -> Personaje -> Bool
ordenNormalEsMayor recetas personaje = puntaje (crafteosSucesivos recetas personaje) > puntaje (crafteosSucesivos (reverse recetas) personaje)

-- Pruebas
steve = UnPersonaje "Steve Stevenson" 1000 [sueter, fogata, fogata, pollo, pollo]

listaObjetos = [fogata, polloAsado, sueter]

madera = Material "Madera"
fosforo = Material "Fosforo"
pollo = Material "Pollo"
lana = Material "Lana"
agujas = Material "Agujas"
tintura = Material "Tintura"
hielo = Material "Hielo"
iglu = Material "Iglu"
lobo = Material "Lobo"
creeper = Material "Creeper"
zombie = Material "Zombie"
araña = Material "Araña"

fogata = Objeto "Fogata" ([madera, fosforo], 10)
polloAsado = Objeto "Pollo Asado" ([fogata, pollo], 300)
sueter = Objeto "Sueter" ([lana, agujas, tintura], 600)

artico = UnBioma [hielo, iglu, lobo] sueter

mobs = [creeper, zombie, araña]
animales = [pollo, lobo]

hacha :: Herramienta
hacha = last.materiales

espada :: Herramienta
espada = head.materiales

picoDePrecision :: Int -> Herramienta
picoDePrecision indice = (!! indice) . materiales

pala :: Herramienta
pala bioma = picoDePrecision ((`div` 2).length.materiales $ bioma) bioma

arco :: Herramienta
arco = head . filter (\x -> x `elem` mobs || x `elem` animales) . materiales 

-- Mine
data Bioma = UnBioma {materiales :: [Material], requisito :: Material}

type Herramienta = Bioma -> Material

puedeMinar :: Bioma -> Personaje -> Bool
puedeMinar bioma personaje = requisito bioma `elem` inventario personaje

minar :: Bioma -> Herramienta -> Personaje -> Personaje
minar bioma herramienta personaje
    | puedeMinar bioma personaje = (modificarPuntos 50 . añadirObjeto (herramienta bioma)) personaje
    | otherwise = personaje

{-
Si se intenta minar un bioma con infinitos materiales, se plantean los siguientes casos:
    Posee el requisito del bioma:
        Usa el hacha:
            Al utilizar last, se debe recorrer la lista infinita, pero esta no tiene un ultimo elemento por lo que no se puede determinar el material a obtener.

        Usa la espada:
            Al utilizar head, no importa que el bioma tenga infinitos materiales, por lo que obtiene el primer material.

        Usa el pico de precisión:
            Al utilizar un indice, este es finito por lo que la lista siempre podrá determinar el material de esa posición y se obtendra el mismo.

        Usa el arco:
            Al utilizar filter y head, haskell hace una evaluación diferida por cada elemento, si hay alguno que cumpla la condicion lo devuelve y no existe corre infinitamente

    No posee el requisito del bioma:
        La evaluación diferida hace que se ignore la lista infinita de materiales y simplemente no pueda minar, por lo que devuelve al personaje como estaba



-}