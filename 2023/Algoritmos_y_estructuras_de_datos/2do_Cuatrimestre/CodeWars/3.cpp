#include <iostream>
#include <string>
#include<cmath>
std::string seriesSum(int n)
{  
  float sum = 0;
  std::string str;

  for(int i = 0; i < n; i++)
    sum += 1.0 / (3*i+1);
  
  sum = std::round(sum*100)/100.0;
  str = std::to_string(sum); 
  return std::string(str.begin(), str.begin() + 4);
}
int main()
{
    std::cout << seriesSum(0) << std::endl;
    std::cout << seriesSum(1) << std::endl;
    std::cout << seriesSum(2) << std::endl;
    std::cout << seriesSum(5) << std::endl;
    return 0;
}