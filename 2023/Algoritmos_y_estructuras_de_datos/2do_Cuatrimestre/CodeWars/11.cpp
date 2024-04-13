// https://www.codewars.com/kata/54e6533c92449cc251001667
#include <string>
#include <vector>

template <typename T> std::vector<T> uniqueInOrder(const std::vector<T>& iterable){
  if(iterable.size() == 0)
    return {};
  
  std::vector<T> vec = {};
  vec.push_back(iterable[0]);
  
  for(int i = 1; i < iterable.size(); i++) 
    if(iterable[i] != vec[vec.size() - 1])
      vec.push_back(iterable[i]);
  
  return vec;
}

std::vector<char> uniqueInOrder(const std::string& iterable){
  if(iterable.length() == 0)
    return {};
  
  std::vector<char> vec;  
  vec.push_back(iterable[0]);
  
  for(int i = 1; i < iterable.length(); i++)
    if(iterable[i] != vec[vec.size() - 1])
      vec.push_back(iterable[i]);

  return vec;    
}

int main()
{
    uniqueInOrder("");
    uniqueInOrder("AA");
    uniqueInOrder("AAAABBBCCDAABBB");
    return 0;
}