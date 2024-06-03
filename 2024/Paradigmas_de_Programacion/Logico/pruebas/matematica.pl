bhaskara(A, B, C, Raiz) :- Raiz is (-B + sqrt(B**2 - 4 * A * C)) / 2 * A.
bhaskara(A, B, C, Raiz) :- Raiz is (-B - sqrt(B**2 - 4 * A * C)) / 2 * A.

raiz(M, B, Raiz) :- Raiz is -B / M.