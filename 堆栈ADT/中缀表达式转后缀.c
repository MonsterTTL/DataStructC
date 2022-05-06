#include <stdio.h>
#include <stdlib.h>
#include <strings.h>

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
void stack_pop_plus(Stack * temp);
void zhuan(char * arr);
int bijiao(char a,char b);
void porer(char * arr);


int main(void)
{
    char math[20] = {"9+(3-1)*3+10/2"};
    porer(math);
    printf("\n");
    zhuan(math);

}

int bijiao(char a,char b)
{
    if(a == '+' || a == '-')
    {
        if(b == '*' || b == '/' )
            return 0;
        else 
            return 1;
    }
    else if(a == '*' || a == '/')
    {
        if(b == '+' || b == '-')
            return 1;
    }
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

void stack_pop_plus(Stack * temp)
{
    if(temp == NULL)
        return ;
    char ret = temp -> top -> data ;
    Stack_node * fre = temp -> top;
    temp -> top = temp -> top -> next;
    temp -> count--;
    free(fre);
    printf("%c ",ret);
    return ;
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

void zhuan(char * arr)
{
    Stack * use ;
    stack_init(&use);
    char * p = arr;
    while(*p != '\0')
    {
        if(*p >= 48 && *p <= 57)
            printf("%d ",*p-48);
        else if(*p <= 47 && *p >=40)
            {   
                if(use -> count == 0)
                    stack_push(use,*p);
                else if(*p == ')')
                    {
                        while(use -> top -> data != '(')
                            stack_pop_plus(use);
                        stack_pop(use);
                    }
                else if(bijiao(*p,use -> top -> data) == 0)
                    {
                        while(use -> top != NULL)
                            {
                                stack_pop_plus(use);
                            }
                        stack_push(use,*p);
                    }
                else 
                    {
                        stack_push(use,*p);
                    }
            }
        p++;
    }
    while(use -> top != NULL)
        {
            stack_pop_plus(use);
        }
    return ;
}

void porer(char * arr)
{
    char * use = arr;
    Stack * p ;
    stack_init(&p);
    int temp = 0;
    int try = 0;
    int flag = 0;
    while(*use != '\0')
    {
        if(*use >= 48 && *use <=57)
            {
                temp = temp * try * 10;
                temp += *use - 48;
                try++;
                flag = 1;

            }
        else if(*use <= 47 && *use >=40)
            {   if(flag != 0) 
                  {printf("%d  ",temp);
                   temp = 0;try = 0;
                   flag = 0;
                  }
                if(p -> count == 0)
                    {
                        stack_push(p,*use);
                    }
                else if(*use == ')')
                    {
                        while(p -> top -> data != '(')
                            stack_pop_plus(p);
                        stack_pop(p);
                    }
                else if(bijiao(*use,p -> top -> data) == 0)
                    {
                        while(p -> top != NULL)
                            {
                                stack_pop_plus(p);
                            }
                        stack_push(p,*use);
                    }
                else 
                    {
                        stack_push(p,*use);
                    }
            }
        use++;

    }
     if(temp != 0)
        printf("%d ",temp);
     while(p -> top != NULL)
        {
            stack_pop_plus(p);
        }
    return ;
}

