// a:
object pepita {
	var energia = 100

	method volar(kilometros) {
		energia -= kilometros + 10
	}

	method comer(gramos) {
		energia += 4 * gramos
	}
	
	method energia() = energia
	
	

}

// b:
object pepitaMensajera {
	var lugarActual = buenosAires
	var energia = 300
	
	
	method volarA(lugar) {
		energia -= (lugar.kilometro() - lugarActual.kilometro()).abs() + 10
		lugarActual = lugar
		return self
	}
	
	method energia() = energia
	method lugarActual() = lugarActual
	
	method puedeVolarA(lugar) = self.volarA(lugar).energia() > 0
}

object buenosAires {
	const kilometro = 0
	method kilometro() = kilometro
}

object rosario {
	const kilometro = 255
	method kilometro() = kilometro
}

object cordoba {
	const kilometro = 665
	method kilometro() = kilometro
}