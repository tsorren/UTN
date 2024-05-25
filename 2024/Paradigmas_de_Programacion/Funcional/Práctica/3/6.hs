{-
    Definir la función esMayorDeEdad, que dada una tupla de 2 elementos (persona, edad)
    me devuelva True si es mayor de 21 años y False en caso contrario. 
    Nota: Definir la función utilizando aplicación parcial y composición.
-}
esMayorDeEdad :: (String, Int) -> Bool
esMayorDeEdad = (> 21).snd