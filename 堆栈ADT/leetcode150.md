# 根据 逆波兰表示法，求表达式的值。

有效的算符包括 +、-、*、/ 。每个运算对象可以是整数，也可以是另一个逆波兰表达式。

注意 两个整数之间的除法只保留整数部分。

可以保证给定的逆波兰表达式总是有效的。换句话说，表达式总会得出有效数值且不存在除数为 0 的情况。

 

示例 1：

输入：tokens = ["2","1","+","3","*"]
输出：9
解释：该算式转化为常见的中缀算术表达式为：((2 + 1) * 3) = 9
示例 2：

输入：tokens = ["4","13","5","/","+"]
输出：6
解释：该算式转化为常见的中缀算术表达式为：(4 + (13 / 5)) = 6
示例 3：

输入：tokens = ["10","6","9","3","+","-11","*","/","*","17","+","5","+"]
输出：22
解释：该算式转化为常见的中缀算术表达式为：
  ((10 * (6 / ((9 + 3) * -11))) + 17) + 5
= ((10 * (6 / (12 * -11))) + 17) + 5
= ((10 * (6 / -132)) + 17) + 5
= ((10 * 0) + 17) + 5
= (0 + 17) + 5
= 17 + 5
= 22
 

提示：

1 <= tokens.length <= 104
tokens[i] 是一个算符（"+"、"-"、"*" 或 "/"），或是在范围 [-200, 200] 内的一个整数
 

逆波兰表达式：

逆波兰表达式是一种后缀表达式，所谓后缀就是指算符写在后面。

平常使用的算式则是一种中缀表达式，如 ( 1 + 2 ) * ( 3 + 4 ) 。
该算式的逆波兰表达式写法为 ( ( 1 2 + ) ( 3 4 + ) * ) 。
逆波兰表达式主要有以下两个优点：

去掉括号后表达式无歧义，上式即便写成 1 2 + 3 4 + * 也可以依据次序计算出正确结果。
适合用栈操作运算：遇到数字则入栈；遇到算符则取出栈顶两个数字进行计算，并将结果压入栈中

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/evaluate-reverse-polish-notation
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。


思路：运用栈，遇到数字就把数字压入栈中，遇到运算符时则把栈顶的两个数弹出作运算，**后弹出的数注意要作为被运算数**，直到栈中只剩一个数时极为结果。       
**在实际操作时也要注意数字与运算符份额判定**，因为给出的测试用例中还可能包含有负数，因为操作符的字符串长度为一，而数字的长度不一定为一，所以数字的判定可以简化为**首字符在数字域中或整个字符串的长度大于一**。         
## 代码实现：
            
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


本题中也可以把数组当作栈来使用以简化代码。