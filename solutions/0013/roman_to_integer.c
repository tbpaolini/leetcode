// Problem 13 - Roman to Integer
// https://leetcode.com/problems/roman-to-integer/

#include <stddef.h>

static inline int get_value(char c) {
  switch (c) {
      case '\0': return 0;
      case 'I': return 1;
      case 'V': return 5;
      case 'X': return 10;
      case 'L': return 50;
      case 'C': return 100;
      case 'D': return 500;
      case 'M': return 1000;
      default: __builtin_unreachable();
  }
}

int romanToInt(char * s){
    
    int num = 0;
    size_t i = 0;
    
    while (s[i])
    {
    	int val  = get_value(s[i]);
    	int next_val = get_value(s[i+1]);
    	
    	if (val < next_val)
    	{
    		num -= val;
    	}
    	else
    	{
    		num += val;
    	}
    	
    	i++;
    }
    
    return num;
}