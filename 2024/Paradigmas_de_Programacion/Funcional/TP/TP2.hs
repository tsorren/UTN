data Intensidad = Baja | Mediana | Alta deriving Show

data Actividad = 
    IrEscuela |
    ComerCheesyP {cant :: Int} |
    Trabajar {trabajo :: String} |
    DobleTurno {trabajo :: String} |
    JugarWOW {amigos :: Int, horas :: Float} |
    SufrirBullying {intensidad :: Intensidad} deriving Show

data Personaje = UnPersonaje {
    nombre :: String,
    dinero :: Float,
    felicidad :: Float 
} deriving Show

data Logro = 
    Millonario {dineroDeCartman :: Float} |
    Contento {nivelDeseado :: Float} |
    VerPrograma |
    ComprarConsola deriving Show

modificarFelicidad :: Float -> Personaje -> Personaje
modificarFelicidad modificador personaje = personaje{felicidad = (max 0 . (modificador +). felicidad) personaje }

modificarDinero :: Float -> Personaje -> Personaje
modificarDinero modificador personaje = personaje{dinero = dinero personaje + modificador}

jornal :: Num a => String -> a
jornal = fromIntegral.length

diversion :: Int -> Float -> Float
diversion amigos horas = 10 * fromIntegral amigos * min 5 horas

realizarActividad :: Actividad -> Personaje -> Personaje
realizarActividad IrEscuela (UnPersonaje "Butters" dinero felicidad) = modificarFelicidad 20 (UnPersonaje "Butters" dinero felicidad)
realizarActividad IrEscuela personaje = modificarFelicidad (-20) personaje
realizarActividad (ComerCheesyP cant) personaje = modificarDinero (-20) personaje
realizarActividad (Trabajar trabajo) personaje = modificarDinero (jornal trabajo) personaje
realizarActividad (DobleTurno trabajo) personaje = (modificarFelicidad (-jornal trabajo) . modificarDinero (2 * jornal trabajo)) personaje
realizarActividad (JugarWOW amigos horas) personaje = (modificarFelicidad (diversion amigos horas) . modificarDinero (-10 * horas)) personaje
realizarActividad (SufrirBullying Baja) personaje = modificarFelicidad (-15) personaje
realizarActividad (SufrirBullying Mediana) personaje = modificarFelicidad (-25) personaje
realizarActividad (SufrirBullying Alta) personaje = modificarFelicidad (-50) personaje

repetirAccion :: Actividad -> Int -> Personaje -> Personaje
repetirAccion actividad cantidad personaje
    | cantidad == 0 = personaje 
    | otherwise = repetirAccion actividad (cantidad - 1) (realizarActividad actividad personaje)

alcanzarLogro :: Logro -> Personaje -> Bool
alcanzarLogro (Millonario dineroCartman) personaje = dinero personaje > dineroCartman
alcanzarLogro (Contento nivel) personaje = felicidad personaje > nivel
alcanzarLogro VerPrograma personaje = dinero personaje >= 10
alcanzarLogro ComprarConsola personaje = dinero personaje >= 50 || felicidad personaje < 10 -- La compran sus padres si esta triste

actividadDecisiva :: Actividad -> Logro -> Personaje -> Bool
actividadDecisiva actividad logro personaje = (not.alcanzarLogro logro) personaje && (alcanzarLogro logro.realizarActividad actividad) personaje

paraQuienesEsDecisiva :: Actividad -> Logro -> [Personaje] -> [Personaje]
paraQuienesEsDecisiva actividad logro = filter (actividadDecisiva actividad logro) 

cartman :: Personaje
cartman = UnPersonaje "Cartman" 20 20

stan :: Personaje
stan = UnPersonaje "Stan" 10 35

butters :: Personaje
butters = UnPersonaje "Butters" 20 50