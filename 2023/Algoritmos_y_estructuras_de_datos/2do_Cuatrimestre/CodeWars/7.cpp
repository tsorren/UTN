int beeramid(int bonus, double price)
{
  int i = 0;
  int beers = (i+1) * (i+1);
  while(bonus >= price * beers)
  {
    bonus -= price * beers;
    i++;
    beers = (i+1) * (i+1);
  }
  return i;
}
int main()
{
    beeramid(10, 2);
    return 0;
}