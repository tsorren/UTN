##### Ejercicio 1 - Farmacia
Condiciones:
	Obra social -> Booleana
	Pertenece a lista de descuentos -> Booleana
	Descuento mayor a 30% -> Booleana
	Presenta Carnet -> Booleana
	Pertenece a lista de inhabilitados -> Booleana

Todas las condiciones booleanas -> Tabla Booleana
Al menos 1 reg ext -> Tabla de Registro Extendido

Acciones:
	Realizar Dto -> 20% / 25% / 30% / Segun Lista - (Registro Extendido)
	No realizar Dto -> Booleana


|                                    |      1      |  2  |  3  |  4  |  5  |  6  |   7   |
| :--------------------------------- | :---------: | :-: | :-: | :-: | :-: | :-: | :---: |
| Obra Social                        |     Si      | Si  | Si  | Si  | No  |  -  | Otros |
| Pertenece a lista de descuentos    |     Si      | Si  | No  | No  |  -  |  -  |       |
| Descuento mayor a 30%              |     Si      | No  |  -  |  -  |  -  |  -  |       |
| Presenta Carnet                    |      -      |  -  | Si  | No  |  -  |  -  |       |
| Pertenece a lista de inhabilitados |     No      | No  | No  | No  | No  | Si  |       |
| ---                                |             |     |     |     |     |     |       |
| Realizar Dto                       | Segun Lista | 30% | 25% | 20% | 20% |     |       |
| No realizar Dto                    |             |     |     |     |     |  X  |       |
| Consultar                          |             |     |     |     |     |     |   X   |

