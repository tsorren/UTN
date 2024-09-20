Armas:
    De Filo: -> filo * long
        espadas
        dagas
        hachas
    Contundentes: -> pesoArma
        maza
        martillo
Pueden cambiar

Armadura:
    Casco -> +10
    Escudo -> 5 + 10% destreza

Gladiadores:
    atacar() -> poderAtaque - defensaEnemigo
    defender()
    vida -> 100 inicial


    Mirmillones:
        poderAtaque -> poderArma + fuerza
        espada
        escudo o casco -> puede cambiar
        defensa -> armadura + destreza
        destreza -> 15
        fuerza variable
        crearGrupo() -> mirmillolandia

    Dimachaerus:
        poderAtaque -> fuerza + sumatoriaPoderArmas
        atacar aumenta 1 destreza
        varias Armas
        sin Armadura
        fuerza -> 10
        destreza variable
        defensa -> destreza / 2
        crearGrupo() -> D-poderAtaqueSumado

Pelea:
    Ataque y Contraataque

Grupos:
    Combate entre Grupos()
    nombre
    cantPeleasDelGrupo
    modificarMiembrosDeGrupo

Combates:
    3 rounds
    Se elige campeon (el mas fuerte y vivo) para pelear contra campeon adversario

Coliseo
    Combates entre grupos, o contra un solo gladiador
    Dueño de Coliseo

Dueño
    curarGladiador()
