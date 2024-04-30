data Elemento = Fuego | Psiquico | Acero deriving (Eq, Show)

data TipoPokemon
  = Unico {primario :: Elemento}
  | Doble {primario :: Elemento, secundario :: Elemento}
  deriving (Show, Eq)

data Pokemon = Pokemon
  { nombre :: String,
    familia :: String,
    tipoPokemon :: TipoPokemon
  }
  deriving (Show)

elementos :: Pokemon -> [Elemento]
elementos (Pokemon _ _ (Unico elemento)) = [elemento]
elementos (Pokemon _ _ (Doble elemento1 elemento2)) = [elemento1, elemento2]

elementosComunes :: Pokemon -> Pokemon -> [Elemento]
elementosComunes pokemon1 pokemon2 = elementos pokemon1 `intersect` elementos pokemon2

sonCompatibles :: Pokemon -> Pokemon -> Bool
sonCompatibles pokemon1 = not . null . elementosComunes pokemon1

poke1 :: Pokemon
poke1 =
  Pokemon
    { nombre = "Charmander",
      familia = "Lagarto",
      tipoPokemon = Unico Fuego
    }
poke2 :: Pokemon
poke2 =
  Pokemon
    { nombre = "Metagross",
      familia = "Acero",
      tipoPokemon = Doble Psiquico Acero
    }

poke3 :: Pokemon
poke3 =
  Pokemon
    { nombre = "Heatran",
      familia = "Fuego",
      tipoPokemon = Unico Acero
    }
