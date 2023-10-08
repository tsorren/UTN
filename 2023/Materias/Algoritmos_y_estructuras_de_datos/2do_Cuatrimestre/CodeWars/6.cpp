#include <iostream>
#include <string>
bool is_merge(const std::string& s, const std::string& part1, const std::string& part2) {
  if(s.length() != part1.length() + part2.length())
    return false;
  
  int i = 0, j = 0, k, l;
  char c, p1, p2;
  for(k = 0; k < s.length(); k++)
  {
    p1 = part1[i];
    p2 = part2[j];
    c = s[k];
    
    if(c == p1 && c == p2)
    {
      l = 0;
      while(c == p1 && c == p2)
      {
        l++;
        p1 = part1[i+l];
        p2 = part2[j+l];
        c = s[k+l];
      }
      if(p1 == c)
        i++;
      else
        j++;
    }
    else if (c == p1)
      i++;
    else if (c == p2)
      j++;
    else
      return false;
  }
  return true;
}

int main()
{
    is_merge("bnfppvuxomglmcwidgitojga", "bfpvomdgiga", "npuxmglcwitoj");
    return 0;
}