data Tactica = Accionista | OferenteSingular | CompradorCompulsivo deriving Show

data Propiedad = UnaPropiedad {
    nombrePropiedad :: String,
    precio :: Float
} deriving Show

data Accion = PasarPorElBanco | Enojarse | Gritar | Subastar{propiedad :: Propiedad} | CobrarAlquileres | PagarAccionistas deriving Show

data Participante = UnParticipante {
    nombre :: String,
    dinero :: Float,
    tactica :: Tactica,
    propiedades :: [Propiedad],
    acciones :: [Accion]
} deriving Show

modificarDinero :: Float -> Participante -> Participante
modificarDinero cantidad participante = participante{dinero = dinero participante + cantidad}

cambiarTactica :: Tactica -> Participante -> Participante
cambiarTactica nuevaTactica participante = participante{tactica = nuevaTactica}

agregarAccion :: Accion -> Participante -> Participante
agregarAccion accion participante = participante{acciones = accion : acciones participante}

adquirirPropiedad :: Propiedad -> Participante -> Participante
adquirirPropiedad propiedad (UnParticipante n d OferenteSingular p a) = modificarDinero (-precio propiedad) (UnParticipante n d OferenteSingular (propiedad : p) a)
adquirirPropiedad propiedad (UnParticipante n d Accionista p a) = modificarDinero (-precio propiedad) (UnParticipante n d Accionista (propiedad : p) a)

propiedadBarata :: Propiedad -> Bool
propiedadBarata = (150 >) . precio

recaudacionBarata :: Participante -> Participante
recaudacionBarata participante = modificarDinero ((sum . map (const 10) . filter propiedadBarata . propiedades) participante) participante

recaudacionCara :: Participante -> Participante
recaudacionCara participante = modificarDinero ((sum . map (const 10) . filter (not . propiedadBarata) . propiedades) participante) participante

pagarAccionistas :: Participante -> Participante
pagarAccionistas (UnParticipante nombre dinero Accionista propiedades acciones) = modificarDinero 200 (UnParticipante nombre dinero Accionista propiedades acciones)
pagarAccionistas (UnParticipante nombre dinero tactica propiedades acciones) = modificarDinero (-100) (UnParticipante nombre dinero tactica propiedades acciones)

realizarAccion :: Accion -> Participante -> Participante
realizarAccion PasarPorElBanco = modificarDinero 40 . cambiarTactica CompradorCompulsivo
realizarAccion Enojarse = modificarDinero 50 . agregarAccion Gritar
realizarAccion (Subastar propiedad) = adquirirPropiedad propiedad 
realizarAccion CobrarAlquileres =  recaudacionBarata.recaudacionCara
realizarAccion PagarAccionistas  = pagarAccionistas 

nuevoParticipante :: String -> Tactica -> Accion -> Participante
nuevoParticipante nombre tactica accion = UnParticipante nombre 500 tactica [] [PasarPorElBanco, accion]

carolina :: Participante
carolina = nuevoParticipante "Carolina" Accionista PagarAccionistas

manuel :: Participante
manuel = nuevoParticipante "Manuel" OferenteSingular Enojarse

listaDePropiedades :: [Propiedad]
listaDePropiedades = [ 
    UnaPropiedad "Avenida 9 de Julio" 200,
    UnaPropiedad "Calle Florida" 220,
    UnaPropiedad "Avenida Corrientes" 240,
    UnaPropiedad "Calle Caminito" 260,
    UnaPropiedad "Avenida de Mayo" 280,
    UnaPropiedad "Calle Lavalle" 300,
    UnaPropiedad "Avenida Santa Fe" 320,
    UnaPropiedad "Calle Reconquista" 340,
    UnaPropiedad "Avenida Belgrano" 360,
    UnaPropiedad "Calle Rivadavia" 380
    ]
