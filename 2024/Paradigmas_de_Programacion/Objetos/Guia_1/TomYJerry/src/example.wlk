object tom {

	var energia = 100
	var velocidad = 5 + energia / 10

	method velocidad() = velocidad

	method energia() = velocidad

	method comerRaton(raton) {
		energia += self.energiaQueBrindaComerRaton(raton)
		self.actualizarVelocidad()
		
		return self
	}
	
	method energiaQueBrindaComerRaton(raton) = 12 + raton.peso()

	method correr(distancia) {
		energia -= self.energiaQueCuestaCorrerDistancia(distancia)
		self.actualizarVelocidad()
		
		return self
	}
	method energiaQueCuestaCorrerDistancia(distancia) = distancia / 2

	method meConvieneComerRatonA(raton, distancia) {
		return self.energiaQueBrindaComerRaton(raton) > self.energiaQueCuestaCorrerDistancia(distancia)
	}

	method actualizarVelocidad() {
		velocidad = 5 + energia / 10
	}

}

object ratonBlanco {

	const peso = 150

	method peso() = peso

}

object rataDeAlcantarilla {

	const peso = 375

	method peso() = peso

}

object reyRata {

	const peso = 750

	method peso() = peso

}

object persona {

	const ratonesComidosPorGato = #{}
	var cantidadDeTiempoCorriendo = 0
	const gato = tom

	method ratonesComidosPorGato() = ratonesComidosPorGato

	method cantidadDeTiempoCorrido() = cantidadDeTiempoCorriendo

	method gato() = gato

	method gatoComeRaton(raton) {
		gato.comerRaton(raton)
		ratonesComidosPorGato.add(raton)
	}

	method gatoCorre(segundos) {
		gato.correr(segundos * gato.velocidad())
		cantidadDeTiempoCorriendo += segundos
	}

}

