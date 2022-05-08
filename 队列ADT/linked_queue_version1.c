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

static Qnode * Linklist_reverse(Qnode * temp);

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

Statue Queue_scanf(Queue * temp,int times)
{   
    int use;
    for(int i = 0;i < times;i++)
    {   
        scanf("%d",&use);
        Queue_Add(temp,use);
    }
    return OK;
}

Statue Queue_showarr(Queue * temp)
{
    Qnode * use = temp -> head;
    if(temp -> head == NULL)
        return Error;
    while(use  != temp -> tail)
    {
        printf("%d ",use  -> data);
        use  = use -> next;
    }
    printf("%d finish",temp -> tail -> data);
    return OK;
}

int Queue_length(Queue * temp)
{
    Qnode * use = temp -> head;
    if(temp -> head == NULL)
        return 0;
    int ret = 1;
    while(use != temp -> tail)
    {
        ret++;
        use = use -> next;
    }
    return ret;

}


Statue Queue_reverse(Queue * temp)
{
    Qnode * newhead = temp -> tail;
    Qnode * newtail = temp -> head;
    Linklist_reverse(temp -> head);
    temp -> head = newhead;
    temp -> tail = newtail;
    return OK;

}


static Qnode * Linklist_reverse(Qnode * temp)
{
    Qnode * node;
    Qnode * newhead = NULL;
    while(temp != NULL )
    {
        node = temp;
        temp = temp -> next;
        node -> next = newhead;
        newhead = node;
    }
    return newhead;
}


int main(void)
{
        Queue * test ;
        Queue_init(&test);
        Queue_Add(test,11);
        Queue_Add(test,28);
        Queue_Add(test,29);
        Queue_showarr(test);
        Queue_scanf(test,3);
        Queue_showarr(test);
        printf("\nlength:%d ",Queue_length(test));
        Queue_reverse(test);
        Queue_showarr(test);
       

}