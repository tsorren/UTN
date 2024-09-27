class ArmaFilosa 
{
    const filo
    const longitud
    method poder() = filo * longitud
}

class ArmaContundente 
{
    const peso
    method poder() = peso
}

class Casco 
{
    method proteccion() = 10
}

class Escudo
{
    const portador
    method proteccion() = 5 + portador.destreza() / 10
}

class Gladiador
{
    var vida = 100

    method estaVivo() = vida > 0
    method recibirCura(cantidad) {vida = vida + cantidad}

    method defensa()
    method atacar()
    method recibirAtaque(enemigo) {vida = vida - (enemigo.poderAtaque() - self.defensa())}
    method pelear(enemigo)
    {
        self.atacar(enemigo)
        enemigo.atacar(self)
    }
    method registrarPelea() {}
}

class Mirmillon inherits Gladiador
{
    const arma
    var armadura
    var fuerza
    const destreza = 15

    method cambiarArmadura(armaduraNueva) {armadura = armaduraNueva}
    method poderAtaque() = arma.poder() + fuerza
    override method defensa() = defensa + armadura.proteccion()
    override method atacar(enemigo) {enemigo.recibirAtaque(self)}

    method crearGrupo(otroGladiador) = new Grupo(nombre = "Mirmillolandia", #{self, otroGladiador})
}

class Dimachaerus inherits Gladiador
{
    const armas = #{}

    const fuerza = 10
    var destreza

    method poderAtaque() = fuerza + armas.sum({arma => arma.poder()})
    override method defensa() = destreza / 2
    override method atacar(enemigo) 
    {
        enemigo.recibirAtaque(self)
        destreza = destreza + 1
    }
    method crearGrupo(otroGladiador) = new Grupo(
        nombre = "D"+(self.poderAtaque()+otroGladiador.poderAtaque()).toString(),
        #{self, otroGladiador}
    )
}

class Grupo
{
    const nombre
    var cantPeleas = 0

    const miembros #{}

    method reclutarMiembro(nuevoMiembro) {miembros.add(nuevoMiembro)}

    method expulsarMiembro(miembros).remove(miembro)

    method campeon() = miembros.filter({miembro => miembro.estaVivo()}).max({miembro => miembro.poderAtaque()})

    method atacar(enemigo) {enemigo.recibirAtaque(self.campeon())}

    method recibirAtaque(enemigo) {self.campeon().recibirAtaque(enemigo)}

    method combatir(grupoEnemigo)
    {
        self.atacar(grupoEnemigo.campeon())
        self.recibirAtaque(grupoEnemigo.campeon())

    }

    method poderAtaque() = self.campeon().poderAtaque()
    method registrarPelea() {cantPeleas = cantPeleas + 1}
    method recibirCura(cantidad) = {miembros.forEach({miembro => miembro.recibirCura(cantidad)})}
}

class Coliseo
{
    method organizarCombate(grupo1, grupo2)
    {
        3.times({grupo1.combatir(grupo2)})
        grupo1.registrarPelea()
        grupo2.registrarPelea()
    }

    method curar(receptor, cantidad) {receptor.recibirCura(cantidad)}
}