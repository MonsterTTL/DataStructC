#include <stdio.h>
#include <stdlib.h>


typedef struct node {
    int data ;
    struct node * next;
}Node;

typedef struct stack{
    struct node * top;
    int count;
}Stack;

void stack_init(Stack ** head)
{
    *head = (Stack *)(malloc(sizeof(Stack)));
    (*head) -> top = NULL   ;
    (*head) -> count = 0;
    return ;
}

void stack_push(Stack * head,int data)
{
    Node * ret = (Node *)(malloc(sizeof(Node)));
    ret -> data = data;
    ret -> next = head -> top;
    head -> top = ret;

}

int stack_pop(Stack * head)
{
    int ret = head -> top -> data;
    Node * fre = head -> top;
    head -> top = head -> top -> next;
    free(fre);
    return ret;
}

bool isNumber(char* token) {
    return ('0' <= token[0] && token[0] <= '9') || strlen(token) > 1;
}




int evalRPN(char ** tokens, int tokensSize){
    char * token;
    Stack * use ;
    stack_init(&use);
    int yunsuan[3];
    for(int i = 0; i < tokensSize ; i++)
    {
        token = tokens[i];
        if(isNumber(token))
        {
            stack_push(use,atoi(token));
        }
        else
        {   yunsuan[0] = stack_pop(use);
            yunsuan[1] = stack_pop(use);
            switch(*token)
            {
                case '+' : 
                yunsuan[2] = yunsuan[1] + yunsuan[0];
                stack_push(use,yunsuan[2]);
                break;
                case '-' : 
                yunsuan[2] = yunsuan[1] - yunsuan[0];
                stack_push(use,yunsuan[2]);
                break;
                case '*' : 
                yunsuan[2] = yunsuan[1] * yunsuan[0];
                stack_push(use,yunsuan[2]);
                break;
                case '/' : 
                yunsuan[2] = yunsuan[1] / yunsuan[0];
                stack_push(use,yunsuan[2]);
                break;
                
            }
        }
    }
    return stack_pop(use);

}