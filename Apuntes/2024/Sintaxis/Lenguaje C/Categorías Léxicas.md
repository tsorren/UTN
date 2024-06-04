### Categorías Léxicas:
El lenguaje C usa varios LR a los cuales llama categorías léxicas o tokens
Cada palabra de alguno de estos lenguajes se conoce como lexema
Por ejemplo: `75` -> Lexema 75, Token constante

En lenguaje C se reconocen los siguientes tokens:
- Palabras clave (keywords)
- Identificador
- Constante
- LiteralCadena (string-literal)
- CaracterPuntuación (punctuator)
	Incluye a los operadores (dependen del contexto), que en ANSI C se los consideraba una categoría separada

Palabras Reservadas:

|  Col 1   |  Col 2   |  Col 3   |      Col 4       |
|:--------:|:--------:|:--------:|:----------------:|
|   auto   |  extern  |  short   |      while       |
|  break   |  float   |  signed  |    \_Alignas     |
|   case   |   for    |  sizeof  |    \_Alignof     |
|   char   |   goto   |  static  |     \_Atomic     |
|  const   |    if    |  struct  |      \_Bool      |
| continue |  inline  |  switch  |    \_Complex     |
| default  |   int    | typedef  |    \_Generic     |
|    do    |   long   |  union   |   \_Imaginary    |
|  double  | register | unsigned |    \_Noreturn    |
|   else   | restrict |   void   | \_Static\_assert |
|   enum   |  return  | volatile | \_Thread\_local  |
