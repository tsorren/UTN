#include <vector>

std::vector<int> snail(const std::vector<std::vector<int>> &snail_map) {
  std::vector<int> sorted;
  int n = snail_map.size();
  if (snail_map[0].size() == 0)
    return {};
  
  int x = 0, y = 0;
  int loops = 2 * n - 1;
  int i, j, k;
  for(i = 0; i <= loops; i++)
  {
    k = (n-1) - (i / 4);
    for(j = 0; j < k; j++)
    {
      sorted.push_back(snail_map[y][x]);
      switch (i%4)
      {
        case 0:
          x++;
          break;
        case 1:
          y++;
          break;
        case 2:
          x--;
          break;
        case 3:
          y--;
          break;
      }
    }
  }
  return sorted;
}
int main()
{
    snail({{1,2}, {4,3}});
    snail({{1,2,3}, {8,9,4}, {7,6,5}});
    return 0;
}