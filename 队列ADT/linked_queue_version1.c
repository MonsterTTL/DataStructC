#include <stdio.h>
#include <stdlib.h>

typedef struct qstruct{
    int data;
    struct qstruct * next;
}Qnode;

typedef struct queue{
    Qnode * head;
    Qnode * tail;
}Queue;

typedef enum statue{
    OK = 1,
    Error = 0
}Statue;

Statue Queue_init(Queue ** temp)
{
    (*temp) = (Queue *)(malloc(sizeof(Queue)));
    if(*temp == NULL)
        return Error;
    (*temp) -> head = NULL;
    (*temp) -> tail = NULL;
    return OK;

}

Statue Queue_Add(Queue * temp,int data)
{
    Qnode * ret = (Qnode *)(malloc(sizeof(Qnode)));
    if(ret == NULL)
        return Error;
   // if(temp -> head == NULL )
    //   {temp -> head = ret;
     //   temp -> tail = ret ;
     //   ret -> data = data;
     //   ret -> next = NULL;
      //  return OK;
     //  } 
    ret -> data = data;
    ret -> next = NULL;
    if(temp -> head == NULL)
    {
        temp -> head = ret;
        temp -> tail = ret ;
        return OK;
    }
    temp -> tail -> next = ret;
    temp -> tail = ret ;
    return OK;
}


Statue Queue_Exit(Queue * temp,int * ret)
{   Qnode * fre = temp -> head;
    (*ret) = temp -> head -> data;
    temp -> head = temp -> head -> next;
    free(fre);
    return OK;

}


int main(void)
{
        Queue * test ;
        Queue_init(&test);
        Queue_Add(test,11);
        Queue_Add(test,28);
        Queue_Add(test,29);
        int ar ;
        Queue_Exit(test,&ar);
        printf("%d \n",ar);
        Queue_Exit(test,&ar);
        printf("%d \n",ar);
        Queue_Exit(test,&ar);
        printf("%d \n",ar);

}