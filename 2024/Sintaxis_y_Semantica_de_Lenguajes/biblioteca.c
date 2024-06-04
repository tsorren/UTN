#include <stdio.h>

constexpr int n = 5;

void mostrarNum(double cant) {
  printf("| ");
  printf("%10g", cant);
  printf(" |");
  return;
}

int main() {
  mostrarNum(123456789.12);
  int nums[n];
  return 0;
}
