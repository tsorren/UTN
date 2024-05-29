### Recursión
``` haskell
-- Factorial
f :: Integer -> Integer
f 0 = 1
f n = n * f(n-1)

data Persona {cansancio :: Float, nombre :: String} deriving Show

-- foldr
aplicarR :: (a -> b -> a) -> a -> [b] -> a
aplicarR operador elemento [] = elemento
aplicarR operador elemento [x:xs] = aplicarR operador (operador elemento x) xs

--foldl 

--foldr1 (+) [1..10] es sum

```

### Lista Infinita
Sirven para ser acotadas en algún momento por otra función
``` haskell
f :: Integer -> [Integer]
f n = n : f (n-1)
```

### Evaluación diferida
Evalúa de los argumentos solo cuando es absolutamente necesario

``` haskell
elemento = head f 10
-- Output = 10
```
