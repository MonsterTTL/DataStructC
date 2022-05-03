#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    int data;
    struct node * next;
}Stack_node;

typedef struct stack{
    Stack_node * top ;
    int count;
}Stack;

typedef enum Status{
    Status_OK = 1,
    Status_Error = 0
}STATUS;

STATUS stack_init(Stack ** head);
STATUS stack_push(Stack * temp,int data);
int stack_pop(Stack * temp);
int stack_leng(Stack * head);
STATUS stack_delete(Stack * head);
STATUS stack_delete_show(Stack * head);


int main(void)
{
    Stack * head ;
    stack_init(&head);
    stack_push(head,98);
    stack_push(head,155);
    stack_push(head,980);
    stack_push(head,1550);
    printf("length:%d \n",head->count);
   // int a = stack_pop(head);
  //  int b = stack_pop(head);
   stack_delete_show(head);
  //  printf("%d %d\n",a,b);
    printf("length:%d \n",head->count);

}

STATUS stack_init(Stack ** head)
{
    (*head) = (Stack *)(malloc(sizeof(Stack)));
    if(*head == NULL)
        return Status_Error;
    (*head) -> top = NULL;
    (*head) -> count = 0;
    return Status_OK;
}

STATUS stack_push(Stack * temp,int data)
{
    Stack_node * p1 = (Stack_node *)(malloc(sizeof(Stack_node)));
    p1 -> data = data;
    p1 -> next = temp -> top;
    temp -> count++;
    temp -> top = p1;
    return Status_OK;
}

int stack_pop(Stack * temp)
{
    if(temp == NULL)
        return -99999;
    int ret = temp -> top -> data ;
    Stack_node * fre = temp -> top;
    temp -> top = temp -> top -> next;
    temp -> count--;
    free(fre);
    return ret;
}

int stack_leng(Stack * head)
{
    return head->count;
}

STATUS stack_delete(Stack * head)
{
    Stack_node * fre;
    while(head -> top != NULL)
    {   
        fre = head -> top;
        head -> top = head -> top -> next;
        free(fre);
    }
    return Status_OK;
}

STATUS stack_delete_show(Stack * head)
{
    Stack_node * fre;
    while(head -> top != NULL)
    {   
        fre = head -> top;
        printf("%d ",fre -> data);
        head -> top = head -> top -> next;
        head -> count--;
        free(fre);
    }
    printf("\n");
  //  head -> count = 0;
    return Status_OK;
}
