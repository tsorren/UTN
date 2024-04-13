// https://www.codewars.com/kata/57b06f90e298a7b53d000a86
#include<queue>
long queueTime(std::vector<int> customers,int n){
  long totalTime = 0;
  int index = 0;
  int size = customers.size();
  if(n > customers.size())
    n = size;

  int checkouts[n];
  std::queue<int> freeCheckouts;
  
  for(int i = 0; i < n; i++)
  {
    checkouts[i] = 0;
    freeCheckouts.push(i);    
  }
  
  while(index < size || (index == size && freeCheckouts.size() < n))
  {
    for(int i = freeCheckouts.front(); freeCheckouts.size() > 0 && index < size; i = freeCheckouts.front())
    {
      checkouts[i] = customers[index++];
      freeCheckouts.pop();
    }
    for(int i = 0; i < n; i++)
    {
      if(checkouts[i] > 0)
      {
        checkouts[i]--;
        if(checkouts[i] == 0)
            freeCheckouts.push(i);
      }
    }
    totalTime++;
  }
  return totalTime;
}

int main()
{
    //queueTime(std::vector<int>{}, 1);               // 0
    //queueTime(std::vector<int>{1,2,3,4}, 1);        // 10
    //queueTime(std::vector<int>{2,2,3,3,4,4}, 2);    // 9
    queueTime(std::vector<int>{1,2,3,4,5}, 100);    // 5
    return 0;
}