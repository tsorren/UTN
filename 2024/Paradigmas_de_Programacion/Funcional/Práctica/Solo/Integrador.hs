data Criterio = Estudioso | Boludo {cant :: Int} | Cabala


data Alumno = UnAlumno {
    nombre :: String,
    fechaNacimiento :: (Int,Int,Int),
    legajo :: Int,
    materias :: [String],
    criterio :: Criterio
}

data Parcial = UnParcial {
    horaComienzo :: Int,
    horaFin :: Int,
    profe :: String,
    materia :: String,
    aula :: Int,
    cantAlumnos :: Int,
    cantPreguntas :: Int,
    preguntas :: [String]
}

estudiara :: Alumno -> Parcial -> Bool
estudiara (UnAlumno _ _ _ _ Estudioso) _ = True
estudiara (UnAlumno _ _ _ _ (Boludo cant)) parcial = cantPreguntas parcial <= cant    
estudiara (UnAlumno _ _ _ _ Cabala) parcial = (odd.cantPreguntas) parcial 

cambiarCriterioDeAlumno :: Criterio -> Alumno -> Alumno
cambiarCriterioDeAlumno crit alumno = alumno {criterio = crit}
