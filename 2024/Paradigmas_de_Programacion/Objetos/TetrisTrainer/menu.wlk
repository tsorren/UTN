// image = "TetrisTrainerBackground.png"
import wollok.game.*
import gameMaster.*

object interfaz
{
    var pantalla = menuPrincipal

    method setearPantalla(nuevaPantalla) {pantalla = nuevaPantalla}
    
    method cambiarPantalla(nuevaPantalla)
    {
        game.allVisuals().forEach({visual => game.removeVisual(visual)})
        game.schedule(150, {
            pantalla = nuevaPantalla
            pantalla.iniciar()
        })
    }
    method iniciar()
    {
        self.cambiarPantalla(pantalla)
    }

    method teclaSpace() {pantalla.teclaSpace()}
    method teclaShift() {pantalla.teclaShift()}
    
    method teclaRight() {pantalla.teclaRight()}
    method teclaLeft() {pantalla.teclaLeft()}
    method teclaUp() {pantalla.teclaUp()}
    method teclaDown() {pantalla.teclaDown()}
    
    method teclaC() {pantalla.teclaC()}
    method teclaX() {pantalla.teclaX()}
    method teclaZ() {pantalla.teclaZ()}

    method teclaP() {pantalla.teclaP()}
    method teclaBack() {pantalla.teclaBack()}

    method aplicarTick() {pantalla.aplicarTick()}

}

class Pantalla
{   var property image
    var property position = game.origin()
    const property opciones

    method iniciar()
    {
        if(not game.hasVisual(self)) game.addVisual(self)
    }
    
    method teclaSpace() {}
    method teclaShift() {}
    
    method teclaRight() {}
    method teclaLeft() {}
    method teclaUp() {}
    method teclaDown() {}
    
    method teclaC() {}
    method teclaX() {}
    method teclaZ() {}

    method teclaP() {}
    method teclaBack() {interfaz.cambiarPantalla(menuPrincipal)}

    method aplicarTick() {}

    method aplicarGravedad() {}
}


object menuPrincipal inherits Pantalla (
    image = "menu_spr.png",
    opciones = [jugarSprint, jugarDigRace, instrucciones])
{
    var indice = 0
    const imagenes = ["menu_spr.png", "menu_dig.png", "menu_instr.png"]
    method indice() = indice % 3
    override method image() = imagenes.get(self.indice())

    override method teclaSpace() {interfaz.cambiarPantalla(opciones.get(self.indice()))}
    override method teclaUp() {indice += 2}
    override method teclaDown() {indice += 1}
    
}

class PantallaJuego inherits Pantalla
{
    override method teclaSpace() {juego.ponerPieza()}
    override method teclaShift() {juego.intentarHold()}
    
    override method teclaRight() {juego.moverPieza("derecha")}
    override method teclaLeft() {juego.moverPieza("izquierda")}
    override method teclaDown() {juego.moverPieza("abajo")}

    override method teclaC() {juego.rotarPieza("derecha")}
    override method teclaX() {juego.rotarPieza("opuesto")}
    override method teclaZ() {juego.rotarPieza("izquierda")}

    override method teclaP() {self.pausar()}
    //override method teclaBack() {interfaz.cambiarPantalla(opciones.get(0))}

    override method aplicarTick()
    {
        juego.aplicarGravedad()
    }
    
    const esDigRace

    override method iniciar()
    {
        game.addVisual(self)
        if(esDigRace) juego.digRace()
        else juego.sprint()
        juego.iniciarJuego()
    }
    method pausar() {}
}
class PantallaPausa inherits Pantalla(image = "paused.png", opciones = [menuPrincipal, continuar])
{
    const property continuar
    
    override method teclaSpace() {}
    override method teclaShift() {}
    
    override method teclaRight() {}
    override method teclaLeft() {}
    override method teclaDown() {}

    override method teclaC() {}
    override method teclaX() {}
    override method teclaZ() {}

    override method teclaP() {
        game.removeVisual(self)
        interfaz.setearPantalla(opciones.get(1))
    }

    override method teclaBack() {interfaz.cambiarPantalla(opciones.get(0))}

    override method aplicarTick() {}
}

const pausarSprint = new PantallaPausa(continuar = jugarSprint)
const pausarDigRace = new PantallaPausa(continuar = jugarDigRace)

object jugarSprint inherits PantallaJuego(
    image = "sprintBkg.png",
    opciones = [menuPrincipal],
    //(pantallaPausa = pausarSprint,
    esDigRace = false
)
{
    override method pausar(){
        interfaz.setearPantalla(pausarSprint)
        pausarSprint.iniciar()
    }
}
object jugarDigRace inherits PantallaJuego(
    image = "digRaceBkg.png",
    opciones = [menuPrincipal],
    //pantallaPausa = pausarDigRace,
    esDigRace = true
)
{
    override method pausar(){
        interfaz.setearPantalla(pausarDigRace)
        pausarDigRace.iniciar()
    }
}
const instrucciones = new Pantalla (
    image = "instructions.png",
    opciones = [menuPrincipal]
)

const estadisticas = new Pantalla(image = "stats.png", opciones = [menuPrincipal])
