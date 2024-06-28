bhaskara(A, B, C, Raiz) :- Raiz is (-B + sqrt(B**2 - 4 * A * C)) / 2 * A.
bhaskara(A, B, C, Raiz) :- Raiz is (-B - sqrt(B**2 - 4 * A * C)) / 2 * A.

raiz(M, B, Raiz) :- Raiz is -B / M.

esTriangulo(A, B, C) :-
    A+B > C,
    B+C > A,
    A+C > B.

hipotenusa(A, B, H) :- H is sqrt(A*A + B*B).
