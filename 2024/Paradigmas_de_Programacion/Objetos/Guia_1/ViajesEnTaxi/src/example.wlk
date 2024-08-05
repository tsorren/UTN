object daniel {

	method llevaA(pasajero) = !pasajero.esJoven()

}

object magali {
	var edad = 19
	
	method cumplirAnios() {
		edad = edad + 1
	}
	
	method esJoven() = edad < 30
}
