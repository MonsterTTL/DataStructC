#include <stdio.h>
#include <stdlib.h>





int main(void)
{

}

int * cal_next(char arr[],int length)
{
    int * ret = (int *)(malloc(sizeof(int) * length));
    ret[0] = 0;
    int end;
    int half ;
    int cnt = 1;
    int i;
    int result;
    while(cnt < length)
    {
        if(cnt == 1)
        {
            ret[cnt] = 1;
        }
        else{
            ret[cnt] = 0;
            half = cnt / 2;
            end = cnt;
            result = 1;
            i = 0;
            while(half <= end)
            {
                if(arr[half] == arr[i])
                {
                    result++;
                    half++;
                    i++;
                    ret[cnt] = ret[cnt] > result ? ret[cnt] : result;
                }
                else
                {
                    half++;
                    result = 1;
                }
            }
            

        }
    }
    

}
