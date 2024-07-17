object wollok {

	method howAreYou() {
		return 'I am Wolloktastic!'
	}

}

/**
 * 	Definicion de un método:
 * 		Primero definimos la interfaz (nombre, input / output)
 * 		Luego definimos la implementación (codificamos)
 * 		Polimorfismo -> Permite abstraer la implementacion de cada objeto de un metodo común
 */
object shrek {

	/** 
	 *   	Coleccion -> Conjunto (sin orden ni repetidos) 
	 *   	Constante -> La referencia a la colección no cambia, pero sus contenido es modificable
	 */
	const misiones = #{}

	method agregarMision(_mision) {
		misiones.add(_mision)
	}

	method cantidadDeMisiones() = misiones.size()

	method misionesDificiles() = misiones.filter({ mision => mision.esDificil() })

	method solicitantesDeMisMisiones() = misiones.map({ mision => mision.solicitante() })

	/** objeto.sum suma los elementos de la colección luego de aplicar una transformacion / mapeo */
	method totalPuntosDeRecompensa() = misiones.sum({ mision => mision.puntosRecompensa() })

}

object liberarAFiona {

	var cantidadTrolls = 5

	method esDificil() = cantidadTrolls.between(4, 5)

	method solicitante() = "Lord Farquaad"

	method puntosRecompensa() = cantidadTrolls * 2

}

object buscarPiedraFilosofal {

	var kilometrosDistancia = 40

	method esDificil() = kilometrosDistancia > 100

	method solicitante() = "Mr DumblecofcofDore"

	method puntosRecompensa() = if (kilometrosDistancia > 50) 10 else 5

}

