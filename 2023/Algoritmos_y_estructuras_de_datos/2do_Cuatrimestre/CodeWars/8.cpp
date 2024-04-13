#include <vector>

using namespace std;
vector<vector<int>> matrix_multiplication(vector<vector<int>> &a, vector<vector<int>> &b, size_t n){
  // TODO: Return the result of A × B in the form of an n × n matrix
  // NOTE: Please allocate and return matrix C
  
  vector<vector<int>> c;
  for(int i = 0; i < n; i++)
  {
    c.push_back({});
    for(int j = 0; j < n; j++)
      c[i].push_back(0);
  }
  for(int i = 0; i < n; i++)
    for(int j = 0; j < n; j++)
      for(int k = 0; k < n; k++)
        c[i][j] += a[i][k] * b[k][j];
      
  return c;
  
}
int main()
{
    vector<vector<int>> a = {{1,2},{3,2}};
    vector<vector<int>> b = {{3,2},{1,1}};
    vector<vector<int>> c = matrix_multiplication(a, b, 2);
    return 0;
}