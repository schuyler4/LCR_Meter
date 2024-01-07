#include <stdio.h>


int main(void)
{
    int number = 6969;
    int index = 0;

    while(number > 0)
    {
        if(index == 2)
        {
            index++;
            continue;
        }
        int digit = number % 10;
        printf("%d %d\n", digit, index);   
        number /= 10;
        index ++; 
    }
}
