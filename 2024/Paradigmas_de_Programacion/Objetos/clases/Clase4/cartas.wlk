object pikachu 
{
    method valor() = 10
    method revalorizar() {} // La carta pikachu no se revaloriza, pero debe ser polimórfica
}

object exodia
{
    var valor = 100
    method valor() = valor
    method revaluar(valorNuevo)
    {
        valor = valorNuevo
    }
    method revalorizar() {valor *= 1.1}
}

object anchoDeEspadas
{
    var antiguedad = 100
    method valor() = antiguedad * 7
    method revalorizar() {antiguedad += 1}
}

object carlitos
{
    const cartas =  []
    var dinero = 0

    method conseguirCarta(unaCarta) 
    {
        cartas.add(unaCarta)
    }

    method tieneCarta(unaCarta) = cartas.contains(unaCarta)

    method vender()
    {
        dinero += cartas.first().valor()
        cartas.remove(cartas.first())
    }
    
    method cuantoDinero() = dinero

    method cuantasCartas() = cartas.size() 

    method cotizacion() = cartas.sum({carta => carta.valor()})

    method tieneCartaValiosa() = cartas.any({carta => carta.valor() > 200})

    method cartasBaratas() = cartas.filter({carta => carta.valor() < 50})

    method visitarExperto() = cartas.forEach({carta => carta.revalorizar()})
}