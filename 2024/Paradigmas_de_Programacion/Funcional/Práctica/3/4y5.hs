{- 4
    Representamos las notas que se sacó un alumno en dos parciales mediante un par (nota1,nota2),
    p.ej. un patito en el 1ro y un 7 en el 2do se representan mediante el par (2,7). 
    A partir de esto: 
    Definir la función esNotaBochazo, recibe un número y devuelve True si no llega a 6, False en caso contrario. No vale usar guardas. 
    Definir la función aprobo, recibe un par e indica si una persona que se sacó esas notas aprueba. Usar esNotaBochazo. 
    Definir la función promociono, que indica si promocionó,
    para eso tiene las dos notas tienen que sumar al menos 15 y además haberse sacado al menos 7 en cada parcial. 
    Escribir una consulta que dado un par indica si aprobó el primer parcial,
    usando esNotaBochazo y composición. La consulta tiene que tener esta forma (p.ej. para el par de notas (5,8)) 
-}

type Notas = (Int, Int)

esNotaBochazo :: Int -> Bool
esNotaBochazo = (< 6)

aprobo :: Notas -> Bool
aprobo (x, y) = (not. (esNotaBochazo x ||). esNotaBochazo) y

promociono :: Notas -> Bool
promociono (x, y) = x + y > 15 && x > 6 && y > 6

aproboPrimerParcial :: Notas -> Bool
aproboPrimerParcial = not.esNotaBochazo.fst

{- 5
    Siguiendo con el dominio del ejercicio anterior, tenemos ahora dos parciales con dos recuperatorios,
    lo representamos mediante un par de pares ((parc1,parc2),(recup1,recup2)). 
    Si una persona no rindió un recuperatorio, entonces ponemos un "-1" en el lugar correspondiente.
    Observamos que con la codificación elegida, siempre la mejor nota es el máximo entre nota del parcial y nota del recuperatorio. 
    Considerar que vale recuperar para promocionar. En este ejercicio vale usar las funciones que se definieron para el anterior. 

    Definir la función notasFinales que recibe un par de pares y
    devuelve el par que corresponde a las notas finales del alumno para el 1er y el 2do parcial.

    Escribir la consulta que indica si un alumno cuyas notas son ((2,7),(6,-1)) recursa o no.
    O sea, la respuesta debe ser True si recursa, y False si no recursa.
    Usar las funciones definidas en este punto y el anterior, y composición.

    Escribir la consulta que indica si un alumno cuyas notas son ((2,7),(6,-1)) recuperó el primer parcial.
    Usar composición. La consulta debe tener esta forma

    Definir la función recuperoDeGusto que dado el par de pares que representa a un alumno,
    devuelve True si el alumno, pudiendo promocionar con los parciales (o sea sin recup.),
    igual rindió al menos un recup.
    Vale definir funciones auxiliares.
    Hacer una definición que no use pattern matching, 
    en las eventuales funciones auxiliares tampoco; o sea, manejarse siempre con fst y snd.
-}

type Parciales = (Notas, Notas)

mejorNota :: Int -> Int -> Int
mejorNota parcial recuperatorio = max parcial recuperatorio

notasFinales :: Parciales -> Notas
notasFinales ((parc1, parc2), (recup1, recup2)) = (mejorNota parc1 recup1, mejorNota parc2 recup2)

recursa :: Parciales -> Bool
recursa = not.aprobo.notasFinales

recuperoPrimerParcial :: Parciales -> Bool
recuperoPrimerParcial ((_, _), (-1, _)) = False
recuperoPrimerParcial parciales = True


recuperoAlgunParcial :: Parciales -> Bool
recuperoAlgunParcial parciales = (fst.snd) parciales == -1 || (snd.snd) parciales == -1

recuperoDeGusto :: Parciales -> Bool
recuperoDeGusto parciales = (promociono.fst) parciales && recuperoAlgunParcial parciales