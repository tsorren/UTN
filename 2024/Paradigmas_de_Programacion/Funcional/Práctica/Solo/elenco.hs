data Actuacion = UnaActuacion {
    pelicula :: String,
    valoracion :: Int
}

data Persona = UnaPersona {
    nombre :: String,
    recibioOscar :: Bool,
    actuaciones :: [Actuacion]      -- Orden de mayor a menor con criterio de cuán reciente
}
peliculasPremiadas = ["a, b, c, d, e"]
{-
    PRIMERA FILA:
        1.
        Determinar si el/la actor/actriz tuvo valoración de 3 estrellas o más
        en la útima película en la que actuó, y actuó en más de una película.

        2.
        Saber si el/la actor/actriz recibió un oscar individualmente
        o su primer actuación fue en una película que lo ganó.

        3.
        Actor/actriz con experiencia.
        Dada un número que representa una cantidad de películas,
        averiguar si el/la actor/actriz actuó en más películas que la cantidad indicada.
-}

ultimaActuacion :: Persona -> Actuacion
ultimaActuacion = head . actuaciones

ultimaValoracion :: Persona -> Int
ultimaValoracion = valoracion . ultimaActuacion

exitoEnUltima :: Persona -> Bool
exitoEnUltima = (3 <= ) . ultimaValoracion

cantActuaciones :: Persona -> Int
cantActuaciones = length . actuaciones

actuoTantasVeces :: Persona -> Int -> Bool
actuoTantasVeces actor n = cantActuaciones actor == n

esPeliPremiada :: Actuacion -> Bool
esPeliPremiada act = pelicula act `elem` peliculasPremiadas

primeraPeliEsPremiada :: Persona -> Bool
primeraPeliEsPremiada = esPeliPremiada . last . actuaciones

esExperimentado :: Persona -> Int -> Bool
esExperimentado actor requisito = cantActuaciones actor > requisito

primeraFila :: Persona -> Int -> Bool
primeraFila actor reqExp
    = (exitoEnUltima actor && esExperimentado actor 1) || recibioOscar actor || primeraPeliEsPremiada actor || esExperimentado actor reqExp


{-
    LA ACADEMIA SE RECTIFICA:
        4.
        Cuando un actor que ganó el oscar hace
        declaraciones desafortunadas, la academia se lo quita
-}

laAcademiaSeRectifica :: Persona -> Bool -> Bool
laAcademiaSeRectifica actor hizoDeclaracionesDesafortunadas = recibioOscar actor && hizoDeclaracionesDesafortunadas

{-
    LAS SEGUNDAS PARTES NUNCA FUERON BUENAS
        5.
        Si un actor/actriz tiene éxito en su última actuación
        (una valoración mayor a 3 estrellas)
        lo contratan para la parte 2 de la pelicula,
        pero recibe una valoración 2 unidades menor.
-}

segundaParte :: Persona -> Int
segundaParte actor
    | exitoEnUltima actor = ultimaValoracion actor - 2

{-
    VILLANOS:
        6.
        Determinar si el/la actor/actriz siempre tuvo valoración
        de 3 estrellas o más en todas las películas en las que actuó,
        y actuó en más de una película.
-}

exitoEnTodas :: Persona -> Bool
exitoEnTodas actor
    | (not . exitoEnUltima) actor || actuoTantasVeces actor 0 = False
    | exitoEnUltima actor && actuoTantasVeces actor 1 = True
    | otherwise = exitoEnTodas (UnaPersona (nombre actor) (recibioOscar actor) ((tail . actuaciones) actor))

esVillano :: Persona -> Bool
esVillano actor = exitoEnTodas actor && esExperimentado actor 1

{-
    HEROES Y HEROINAS
    7. 
    Puede ser Saber si el/la actor/actriz
    recibió un oscar individualmente o actuó en una película que lo ganó.
-}

actuoEnPremiada :: Persona -> Bool
actuoEnPremiada actor
    | actuoTantasVeces actor 0 = False
    | (esPeliPremiada . ultimaActuacion) actor = True
    | otherwise = actuoEnPremiada (UnaPersona (nombre actor) (recibioOscar actor) ((tail . actuaciones) actor))

esHeroe :: Persona -> Bool
esHeroe actor = recibioOscar actor || actuoEnPremiada actor

{-
    EXPERIENCIA
        8.
        Dada un número que representa una cantidad de películas,
        averiguar si el/la actor/actriz actuó
        en más películas que la cantidad indicada.
-}

-- esExperimentado 

{-
    ARMANDO EL ELENCO
        9. 
        A partir de una lista de personas, y utilizando las funciones anteriores,
        se quiere resolver estos requerimientos (y otros similares).
        Definir las funciones adicionales necesarias y mostrar cómo se las invocaría para cada caso:
            a. 
                Si la cantidad de actores/actrices
                que podrian ser heroes/heroinas es más que 3.
            b. 
                Si hay al menos 5 actores/actrices
                que no podrían ser villanos.
            c. 
                Si hay más de 2 actores/actrices
                que tengan una experiencia de más de 4 películas.
            d. 
                Si considerando los que
                podrían ser heroes/heroinas o villanos/as,
                se llega a 5 actores/actrices.
            e. 
                Inventar una nueva catalogación posible
                para un actor/actriz y utilizarla
                para hacer una consulta parecida a las anteriores.
-}

{-
cantPosiblesHeroes :: [Persona] -> Int -> Int
cantPosiblesHeroes lista k
    | null lista = k
    | (esHeroe.head) lista = cantPosiblesHeroes (tail lista) (k+1)
    | otherwise = cantPosiblesHeroes (tail lista) k


cantPosiblesVillanos :: [Persona] -> Int -> Int
cantPosiblesVillanos lista k
    | null lista = k
    | (esVillano.head) lista = cantPosiblesVillanos (tail lista) (k+1)
    | otherwise = cantPosiblesVillanos (tail lista) k
-}

muyExperimentado :: Persona -> Bool
muyExperimentado actor = esExperimentado actor 4

esHeroeOVillano :: Persona -> Bool
esHeroeOVillano actor = esHeroe actor || esVillano actor

contadorCondicional :: (Persona -> Bool) -> [Persona] -> Int -> Int
contadorCondicional condicion lista k
    | null lista = k
    | (condicion.head) lista = contadorCondicional condicion (tail lista) (k+1)
    | otherwise = contadorCondicional condicion (tail lista) k

cantPosiblesHeroes :: [Persona] -> Int
cantPosiblesHeroes lista = contadorCondicional esHeroe lista 0

cantPosiblesVillanos :: [Persona] -> Int
cantPosiblesVillanos lista = contadorCondicional esVillano lista 0

cantHeroesOVillanos :: [Persona] -> Int
cantHeroesOVillanos lista = contadorCondicional esHeroeOVillano lista 0

cantMuyExperimentados :: [Persona] -> Int
cantMuyExperimentados lista = contadorCondicional muyExperimentado lista 0

cantActoresEstrella :: [Persona] -> Int
cantActoresEstrella lista = contadorCondicional recibioOscar lista 0

variosPosiblesHeroes :: [Persona] -> Bool
variosPosiblesHeroes lista = cantPosiblesHeroes lista > 3

variosNoVillanos :: [Persona] -> Bool
variosNoVillanos lista = length lista - cantPosiblesVillanos lista >= 5

variosMuyExperimentados :: [Persona] -> Bool
variosMuyExperimentados lista = cantMuyExperimentados lista > 2

personajesSuficientes :: [Persona] -> Bool
personajesSuficientes lista = cantHeroesOVillanos lista >= 5

produccionEstelar :: [Persona] -> Bool
produccionEstelar lista = cantActoresEstrella lista == length lista

{-
    PARA PENSAR
        10.
        Justificar la utilización de 
        composición y aplicación parcial en la solución.
-}

{-
    BONUS TRACK
        11. 
        Peliculas en común. 
        Dado un conjunto de personas,
        obtener el conjunto de todas las películas
        en las que actuaron todas esas personas, sin repeticion
-}
