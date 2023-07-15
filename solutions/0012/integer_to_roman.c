#include <stdlib.h>

char * intToRoman(int num){
    char *out = calloc(1, 16);
    size_t i = 0;

    // Hundreds
    while (num >= 1000)
    {
        out[i++] = 'M';
        num -= 1000;
    }
    
    // Thousands
    if (num >= 900)
    {
        out[i++] = 'C';
        out[i++] = 'M';
        num -= 900;
    }
    else if (num >= 500)
    {
        out[i++] = 'D';
        num -= 500;
    }
    else if (num >= 400)
    {
        out[i++] = 'C';
        out[i++] = 'D';
        num -= 400;
    }
    
    while (num >= 100)
    {
        out[i++] = 'C';
        num -= 100;
    }
    
    // Hundreds
    if (num >= 90)
    {
        out[i++] = 'X';
        out[i++] = 'C';
        num -= 90;
    }
    else if (num >= 50)
    {
        out[i++] = 'L';
        num -= 50;
    }
    else if (num >= 40)
    {
        out[i++] = 'X';
        out[i++] = 'L';
        num -= 40;
    }
    
    while (num >= 10)
    {
        out[i++] = 'X';
        num -= 10;
    }

    // Units
    if (num >= 9)
    {
        out[i++] = 'I';
        out[i++] = 'X';
        num -= 9;
    }
    else if (num >= 5)
    {
        out[i++] = 'V';
        num -= 5;
    }
    else if (num >= 4)
    {
        out[i++] = 'I';
        out[i++] = 'V';
        num -= 4;
    }
    
    while (num >= 1)
    {
        out[i++] = 'I';
        num -= 1;
    }

    return out;
}