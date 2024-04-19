esLarga :: String -> Bool
esLarga = (3 < ).length

cuantasPalabrasLargas = (length.filter esLarga)
