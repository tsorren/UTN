| Instrucción | MSB | LSB | CF  |      Tipo      |                      Descripción                      |
|:-----------:|:---:|:---:|:---:|:--------------:|:-----------------------------------------------------:|
|     SHL     |  -  |  0  | MSB | Desplazamiento |                 Der <- Izq, 0 -> LSB                  |
|     SAL     |  -  |  0  | MSB | Desplazamiento |             Igual a SHL, multiplica por 2             |
|     SHR     |  0  |  -  | LSB | Desplazamiento |                 Der -> Izq, 0 -> MSB                  |
|     SAR     | MSB |  -  | LSB | Desplazamiento | Der -> Izq, MSB -> MSB (Duplica el MSB), Divide por 2 |
|     RCL     |  -  | CF  | MSB |    Rotación    |                      Der <- Izq                       |
|     RCR     | CF  |  -  | LSB |    Rotación    |                      Der -> Izq                       |
|     ROL     |  -  | MSB | MSB |    Rotación    |                      Der <- Izq                       |
|     ROR     | LSB |  -  | LSB |    Rotación    |                      Der -> Izq                       |
