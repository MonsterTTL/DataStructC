#include <stdio.h>
#include <stdlib.h>

#define MAX 200

typedef struct static_stack_plus
{
    int data[MAX];
    int cur1 ;
    int cur2 ;
}NEW_STACK;

typedef enum new_status{
    STATUS_OK = 1,
    STATUS_ERROR = 0
}NEW_STATUS;

NEW_STATUS stack_init(NEW_STACK ** botton);
NEW_STATUS stack_push(NEW_STACK * temp,int location,int number);
int stack_pop(NEW_STACK * temp,int location);
NEW_STATUS stack_showall(NEW_STACK * use);

int main(void)
{
    NEW_STACK * p1 ;
    stack_init(&p1);
    stack_push(p1,1,99);
    stack_push(p1,1,89);
    stack_push(p1,2,79);
    stack_push(p1,2,69);
    stack_showall(p1);
}


NEW_STATUS stack_init(NEW_STACK ** botton) //得传指针的地址
{
    (*botton) = (NEW_STACK *)(malloc(sizeof(NEW_STACK)));
    (*botton) -> cur1 = -1;
    (*botton) -> cur2 = MAX;
    if(*botton != NULL)
        return STATUS_OK;
    else
        return STATUS_ERROR;
}

NEW_STATUS stack_push(NEW_STACK * temp,int location,int number)
{   
    if(temp -> cur1 >= temp -> cur2)
        {
            return STATUS_ERROR;
        }
    else if(location == 1)
        {
            temp -> cur1++;
            temp -> data[temp -> cur1] = number;
            return STATUS_OK;
        }
    else if(location == 2)
        {
            temp -> cur2--;
            temp -> data[temp -> cur2] = number;
            return STATUS_OK;
        }
  
    else
        return STATUS_ERROR;
}

int stack_pop(NEW_STACK * temp,int location)
{
    int ret;
    if(location == 1)
        {
            if(temp -> cur1 <= -1)
                return -99999;
            ret = temp -> data[temp -> cur1];
            temp -> cur1--;
            return ret;
        }
    else if(location == 2)
        {
            if(temp -> cur2 >= MAX)
                return 99999;
            ret = temp -> data[temp -> cur2];
            temp -> cur2++;
            return ret;
        }
    return 666666;
}

NEW_STATUS stack_showall(NEW_STACK * use)
{   
    printf("cur1: ");
    while(use -> cur1 >= 0)
    {
        printf("%d ",use -> data[use -> cur1]);
        use -> cur1 --;

    }
    printf("\n cur2: ");
    while(use -> cur2 <= MAX-1)
    {
        printf("%d ",use -> data[use -> cur2]);
        use -> cur2++;
    }
    return STATUS_OK;
}

