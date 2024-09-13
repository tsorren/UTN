object pepita
{
    var energia = 100

    var position = game.at(0.randomUpTo(game.width()), 0.randomUpTo(game.height()))
    
    method volar(distancia, direccion){
        energia -= 10 * distancia

        if(not self.estaCansada())
        {
            if(direccion == "arriba") {
                position = position.up(1)
            }
            else if(direccion == "izquierda"){
                position = position.left(1)
            }
            else if(direccion == "derecha"){
                position = position.right(1)
            }
        }
    }
    method position() = position
    method image(){
        if(self.estaCansada())
        {
            return "pepita_dead.png"
        }
        else
        {
            return "pepita.png"
        }
    }
    method comer(comida){
        energia += comida.energia()
    }

    method estaCansada() = energia <= 20

    /*
    method position() = position // Getter
    method position(newPos) { // Setter
        position = newPos
    } 
    */
    method caer(){
        if(position.y() > 0)
            position = position.down(1)
    }
    method comerDelSuelo(comida){
        self.comer(comida)
        game.removeVisual(comida)

    }
}

object alpiste {
    method energia() = 5

    const position = game.at(0.randomUpTo(game.width()), 0.randomUpTo(game.height()))
    method position() = position
    method image() = "birdseed.png"
    
    method reaccionar(alguien) = {alguien.comerDelSuelo(self)}
}

object manzana 
{
	var madurez = 0
    const energiaInicial = 50
    const position = game.at(0.randomUpTo(game.width()), 0.randomUpTo(game.height()))
    
    method image() = "apple.png"
	method position() = position

	method energia() 
    {
        if(madurez > 150 or madurez < 0)
        {
            return 0
        }
        else if (madurez >= 100)
        {
            return energiaInicial * (200 + (100 - madurez) * 4) / 100
        }
        else
        {
		    return energiaInicial * (100 + madurez) / 100	
        }
	}
    
    method maduracion() = madurez
	
	method madurar() {
		madurez += 10
	}
    method estaPudriendose() = madurez >= 100 && madurez < 150
    method estaPodrida() = madurez >= 150

    method reaccionar(alguien) = {alguien.comerDelSuelo(self)}
}

object nido 
{
    const position = game.at(0.randomUpTo(game.width()), 0.randomUpTo(game.height()))
    method position() = position
    method image() = "neest.png"
    method esComida() = false

    method reaccionar(alguien) 
    {
        game.say(self, "Ganaste!")
        game.removeTickEvent("gravedad")
        game.schedule(3000, {game.stop()})
    }
}