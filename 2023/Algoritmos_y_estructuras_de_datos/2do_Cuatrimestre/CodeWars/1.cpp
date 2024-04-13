#include <vector>
#include <iostream>
using namespace std;
void AddWithoutRepeating(int vec[][2], int& logicSize, int val)
{
  for(int i = 0; i < logicSize; i++)
  {
    if(vec[i][0] == val)
    {
      vec[i][1]++;
      return;
    }
  }
  vec[logicSize][0] = val;
  vec[logicSize][1]++;
  logicSize++;
  return;
}
int findOdd(const vector<int>& numbers){
  int tam = numbers.size();
  int counter[tam][2];
  int logicSize = 0;
  for(int i = 0; i < tam; i++)
  {
    counter[i][0] = 0;  
    counter[i][1] = 0;  
  }
  for(int i = 0; i < tam; i++)
  {
    AddWithoutRepeating(counter, logicSize, numbers[i]);
  }
  for(int i = 0; i < logicSize; i++)
  {
    if(counter[i][1] % 2 == 1)
        return counter[i][0];
  }
  return 1;
}

int main()
{
    vector<int> numbers = {20,1,-1,2,-2,3,3,5,5,1,2,4,20,4,-1,-2,5};
    cout << findOdd(numbers);
    return 0;
}