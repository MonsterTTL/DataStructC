#include <stdio.h>
#include <stdlib.h>

void int_printf(int a);

int main(void)
{
    int_printf(626779);
}

void int_printf(int a)
{
    if(a <= 0)
        return ;
    int use = a%10;
    int_printf(a/10);
    printf("%d",use);
    return ;
}