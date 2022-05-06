#include <stdio.h>
#include <stdlib.h>

#define MAX 100

typedef struct queue{
    int data[MAX];
    int head;
    int tail;
}Queue;

typedef enum statue{
    OK = 1,
    Error = 0
}Statue ;

Statue queue_init(Queue * temp)
{
    temp -> head = 0;
    temp -> tail = 0;
    return OK;
}

Statue queue_add(Queue * temp , int data)
{
    if((temp -> tail + 1) % MAX == (temp -> head))
    {
        return Error;
    }
    temp -> data[temp -> tail] = data;
    temp -> tail = ((temp -> tail + 1) % MAX);
    return OK;
}

Statue queue_exit(Queue * temp,int * ret)
{
    if(temp -> head == temp -> tail)
        return Error;
    (*ret) = temp -> data[temp -> head] ;
    temp -> head = ((temp -> head + 1) % MAX);
    return OK;
}



int main(void)
{
    Queue test;
    int ar ;
    queue_init(&test);
    queue_add(&test,11);
    queue_add(&test,22);
    queue_add(&test,33);
    queue_exit(&test,&ar);
    printf("%d \n",ar);
    queue_exit(&test,&ar);
    printf("%d \n",ar);
    queue_exit(&test,&ar);
    printf("%d \n",ar);

    
}