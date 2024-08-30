object pepita {
    var energia = 100
    
    method volar(distancia){
        energia -= 10 * distancia
    }

    method comer(comida){
        energia += comida.energia()
    }

    method estaCansada() = energia <= 20
}

object alpiste {
    method energia() = 5
}

object manzana {
	var madurez = 0
    const energiaInicial = 50
	
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
}