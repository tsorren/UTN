object samsung {
  var bateria = 5

  method perderBateria(duracion){
    bateria -= 0.25
  }

  method estaApagado() = bateria <= 0

  method recargar(){
    bateria = 5
  }
  method bateria() = bateria
}

object iphone {
  var bateria = 5

  method perderBateria(duracion){
    bateria -= duracion / 1000
  }

  method estaApagado() = bateria <= 0

  method recargar(){
    bateria = 5
  }

  method bateria() = bateria
}

object juliana {
  const telefono = samsung
  const servicio = personal
  var plataGastada = 0

  method llamarA(alguien, duracion){
    telefono.perderBateria(duracion)
    alguien.recibirLlamada(duracion)
    plataGastada += servicio.cobrar(duracion)
  }

  method cuantaBateria() = telefono.bateria()

  method recibirLlamada(duracion){
    telefono.perderBateria(duracion)
    plataGastada += servicio.cobrar(duracion)
  }

  method cuantoGasto() = plataGastada

}

object catalina {
  const telefono = iphone
  const servicio = movistar
  var plataGastada = 0

  method llamarA(alguien, duracion){
    telefono.perderBateria(duracion)
    alguien.recibirLlamada(duracion)
    plataGastada += servicio.cobrar(duracion)
  }
  method cuantaBateria() = telefono.bateria()

  method recibirLlamada(duracion){
    telefono.perderBateria(duracion)
    plataGastada += servicio.cobrar(duracion)
  }

  method cuantoGasto() = plataGastada
}

object movistar {
  const costoPorMin = 60
  method cobrar(duracion) = costoPorMin * duracion
}

object claro {
  const costoPorMin = 50
  method cobrar(duracion) = (costoPorMin * duracion) * 1.21
}

object personal {
  const costoPorMinExtra = 40
  const costoFijo = 70
  method cobrar(duracion){
    if(duracion < 10){
      return costoFijo
    }
    else{
      return costoFijo + costoPorMinExtra * (duracion - 10)
    }
  }
}