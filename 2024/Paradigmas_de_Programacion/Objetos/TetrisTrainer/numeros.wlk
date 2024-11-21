
class Numero
{
    var cuantoCarry = 0
    var carry = false
    var property position
    var property num = 0
    var property image = "n" + num + ".png"

    method aplicarGravedad() {}

    method imagenSegunNum() = "n" + num + ".png"
        
    method huboCarry() = carry
    method cuantoCarry() = cuantoCarry
    method aumentar(cantidad) {self.cambiarNumero(num + cantidad)}
    method cambiarNumero(nuevoNum)
    {
        if(nuevoNum > 9) 
        {
            num = nuevoNum % 10
            cuantoCarry = (nuevoNum / 10).truncate(0)
            carry = true
        }
        else
        {
            num = nuevoNum
            cuantoCarry = 0
            carry = false
        }
        image = self.imagenSegunNum()
    }
}
