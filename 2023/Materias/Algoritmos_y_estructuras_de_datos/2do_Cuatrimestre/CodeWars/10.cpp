//https://www.codewars.com/kata/544675c6f971f7399a000e79
#include <string>
#include <cmath>
int string_to_number(const std::string& s) {
  std::string str = s;
  int num = 0;
  
  bool negative = str[0] == '-';  
  if(negative)
    str = str.substr(1, str.length() - 1);
  
  int len = str.length() - 1;
  
  for(int i = 0; i <= len; i++)
    num += (str[i] - 48) * pow(10, len-i);
  
  return negative ? -num : num;
}

int main()
{
    string_to_number("123456");
    string_to_number("352605");
    string_to_number("-321405");
    string_to_number("-7");
    string_to_number("0");
    string_to_number("-0");
    return 0;
}