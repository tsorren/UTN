| Instrucción | MSB | LSB | CF  |               Descripción               |      Tipo      |
| :---------: | :-: | :-: | :-: | :-------------------------------------: | :------------: |
|     SHL     |  -  |  0  | MSB |          Der <- Izq, 0 -> LSB           | Desplazamiento |
|     SAL     |  -  |  0  | MSB |               Igual a SHL               | Desplazamiento |
|     SHR     |  0  |  -  | LSB |          Der -> Izq, 0 -> MSB           | Desplazamiento |
|     SAR     | MSB |  -  | LSB | Der -> Izq, MSB -> MSB (Duplica el MSB) | Desplazamiento |
|     RCL     |  -  | CF  | MSB |               Der <- Izq                |    Rotación    |
|     RCR     | CF  |  -  | LSB |               Der -> Izq                |    Rotación    |
|     ROL     |  -  | MSB | MSB |               Der <- Izq                |    Rotación    |
|     ROR     | LSB |  -  | LSB |               Der -> Izq                |    Rotación    |
