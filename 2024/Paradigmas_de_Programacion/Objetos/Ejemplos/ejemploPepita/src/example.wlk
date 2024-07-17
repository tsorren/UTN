object pepita {

	var energia = 100

	method volar() {
		energia = energia - 10
	}

	method comer(cantidad) {
		energia = energia + 2 * cantidad
	}

	method energia() {
		return energia
	}

	method energia(_energia) {
		energia = _energia
	}

}

