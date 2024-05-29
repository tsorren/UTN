Al incluir un header, damos direcciones al preprocesador para que lo haga una sola vez
header.h
```c
#ifnded HEADER_H_INCLUDED
#define HEADER_H_INCLUDED

...header

#endif // HEADER_H_INCLUDED
```

Construcción de Software:
	Lento: gcc  -g -Wall -c pedantic-errors -std=c23 \*.c -o imagen.exe
	Eficiente: make