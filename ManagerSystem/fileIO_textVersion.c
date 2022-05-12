#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

#define MAX 100
#define ACCOUNT_MAX 20
#define FILE_MAX 50
#define READ_MAX 256
#define SYS_ACCOUNT "system_accountlist.txt"
typedef enum statue{
    OK = 1,
    Error = 0
}Statue;

typedef enum searchstate{
    Yes = 1,
    No = 0
}SearchStatue;

typedef enum movetype{
    Forward = 1,
    Backward = 0
}Movetype;

//file Structure
//typedef struct file_list{
//    char cur_name[FILE_MAX];
//    char next_name[FILE_MAX];
//}FILE_NA;

typedef enum authority{
    System_priorty = 1,
    User_priorty = 0
}Authority_Priorty;

typedef struct user{
    
    char account[ACCOUNT_MAX]; // �˺�
    char password[ACCOUNT_MAX]; //����
    Authority_Priorty priorty; // ���ȼ�
    long money; // ���
}User;

typedef struct list{
     User * cur ;
     struct list * next;
}List;


typedef enum login_statue{
    Successful = 1,
    Fail = 0
}Login_Statue;


//This is my ManagerSystem function
User System;//ϵͳר�ñ���
    // ע�Ჿ��
Statue User_register(void) ;// �û�ע��
Statue Account_Init(User * temp,char name[ACCOUNT_MAX],char password[ACCOUNT_MAX]) ;//�����û�ʱ���˻���ʼ��
Statue Register_process(char usename[],char password[]); //�Ӻ��������ں����ڲ���ʵ��
    // ��¼����
Statue User_login(User * cur);//�û���¼
Login_Statue Account_Login(char usename[],char password[]);//�Ӻ��������ڵ�¼�ڲ���ʵ��
Statue Read_User_Information(char * usename,User * cur);
    //ϵͳ��
void System_Menu(void);//��ʾ�˵�
void UserLoginMenu(void);//�û��ɹ���¼֮��Ľ���
void ManagerMenu(void);//����Ա�˵�
Statue System_ShowInformation(User * name);  //��ʾһ���˻���������Ϣ
Statue System_ShowAllUser(void);//��ʾ�����û�
Statue System_ShowAllDetail(void);//��ʾ�����û�����ϸ��Ϣ
Statue System_ChangeMoney_process(char * usename,int number);//�޸�һ���û������,�ڲ�����
Statue System_ChangeMoney(void);//�޸�һ���û������

Statue System_RerangeProcess(void);//���ս����û���������
Statue ShowListData(List * test);//�������������ʾ
Statue System_ChangeAuthority(void);//�ı�һ���û���Ȩ��
Statue System_ChangeAuthority_process(char * usename,int n);//�ı��û�Ȩ�ޣ��������
List * merge(List * head1,List * head2);//�鲢����
List * mergesort(List * head,List * end);//�鲢����
List * List_sort(List * exam);//�����ݽ�������
List * reverse(List * head);//��ת����
List * List_init(char * filename);//���ļ��е����ݶ���������ת����һ������
//This is my FileIO function
Statue Show_A_File_version1(char * FileName);//��ʾһ���ı��ļ�����������
Statue Create_A_File_version1(char * FileName);//����һ���ı��ļ�����Ҫ����׺
SearchStatue IsFileExist(char * FileName);//����һ���ļ��Ƿ����
Statue Write_A_File_version1(char * FileName,char * target);//��ĩβд����
Statue FilePointSetEnd(FILE * fp);//����ǰ�ļ�ָ��λ��������ĩβ
Statue FilePointSetHead(FILE * fp);//����ǰ�ļ�ָ��λ�������ڿ�ͷ
Statue FilePointMoveForward(FILE * fp,long offset);//��ǰ�ļ�ָ��������
Statue FilePointMoveBackward(FILE * fp,long offset);//��ǰ�ļ�ָ����ǰ��
Statue Write_A_File_version2(char * FileName,char * target,int offset,Movetype flag);//�ھ࿪ͷoffset��д�ļ���β��д�ļ�
Statue Write_A_File_version3(char * FileName,char * target,int length); //���ļ�β��д�̶����ȵ�����
Statue Write_A_File_version4(char * FileName,char * target,int m,int max); //�ھ��ļ���ͷm��дmax���ȵ�����
Statue Read_All_Data(char * FileName,char * target); //��һ���ļ�������ȫ��ȡ������target�У���󳤶�Ϊ256
Statue Read_All_Data_version2(char * FileName,char * target,int m,int max); //��һ���ļ��ӿ�ͷm��������ȡmax������target��
Statue Delete_AendLetter(char * name,int n);//ɾ��������������


//This is my IO function
char * s_gets(char * st,int n);

int main(void)
{   
  
  
  while(1) 
   { 
       System_Menu();
   }
   return 0;
}
Statue Create_A_File_version1(char * FileName)
{
    FILE * fp;
    fp = fopen(FileName,"r");
    if(fp != NULL)
    {
        printf("This File has been created!");
        return Error;
    }
    fclose(fp);
    fp = fopen(FileName,"a");
    fclose(fp);
    return OK;


}

Statue Show_A_File_version1(char * FileName)
{   
    int ch;
    FILE * fp;
    fp = fopen(FileName,"r");
    ch = getc(fp);
    while(ch != EOF)
    {
        putchar(ch);
        ch = getc(fp);
    }
    fclose(fp);
    return OK;
}
Statue Write_A_File_version1(char * FileName,char * target)//��ĩβд����
{   
    if(IsFileExist(FileName) == No )
    {
        printf("This File is not exist !!");
        return Error;
    }
    FILE * fp = fopen(FileName,"a");
    int ch = target[0];
    int i = 0;
    while(ch != '\0')
    {
        putc(ch,fp);
        i++;
        ch = target[i];
    }
    fclose(fp);
    return OK;

}

Statue Write_A_File_version2(char * FileName,char * target,int offset,Movetype flag)//�ھ࿪ͷoffset��д�ļ�����βoffset..
{   
    if(IsFileExist(FileName) == No )
    {
        printf("This File is not exist !!");
        return Error;
    }
    FILE * fp = fopen(FileName,"r+");
    if(flag == Forward)
    {
        FilePointSetHead(fp);
        FilePointMoveForward(fp,offset);
    }
    else if (flag == Backward)
    {
        FilePointSetEnd(fp);
        FilePointMoveBackward(fp,offset);
    }
    else
    {
        printf("This is not a avaliable move ");
    }
    int ch = target[0];
    int i = 0;
    while(ch != '\0')
    {
        putc(ch,fp);
        i++;
        ch = target[i];
    }
    fclose(fp);
    return OK;

}

Statue Write_A_File_version3(char * FileName,char * target,int length)//��ĩβд�̶����ȵ�����
{   
    if(IsFileExist(FileName) == No )
    {
        printf("This File is not exist !!");
        return Error;
    }
    FILE * fp = fopen(FileName,"a");
    int ch = target[0];
    int i = 0;
    while(ch != '\0'&& i <= length)
    {
        putc(ch,fp);
        i++;
        ch = target[i];
    }
    
    while(i < length)
    {
        putc(' ',fp);
        i++;
    }
    fclose(fp);
    return OK;

}

Statue Write_A_File_version4(char * FileName,char * target,int m,int max)
{
    if(IsFileExist(FileName) == No )
    {
        printf("This File is not exist !!");
        return Error;
    }
    FILE * fp = fopen(FileName,"r+");
    FilePointSetHead(fp);
    FilePointMoveForward(fp,m);
    int ch = target[0];
    int i = 0;
    while(ch != '\0'&& i <= max)
    {
        putc(ch,fp);
        i++;
        ch = target[i];
    }
    while(i < max)
    {
        putc(' ',fp);
        i++;
    }
    fclose(fp);
    return OK;
}

SearchStatue IsFileExist(char * FileName)
{
    FILE * fp;
    fp = fopen(FileName,"r");
    if(fp == NULL)
    {
        return No;
    }
    else{
        fclose(fp);
        return Yes;
    }
    
}


Statue FilePointSetEnd(FILE * fp)
{   
    int sta = 0;
    sta = fseek(fp,0L,SEEK_END);
    if(sta == 0)
        return OK;
    else
        return Error;
}

Statue FilePointSetHead(FILE * fp)
{
    int sta = 0;
    sta = fseek(fp,0L,SEEK_SET);
    if(sta == 0)
        return OK;
    else
        return Error;
}

Statue FilePointMoveForward(FILE * fp,long offset)
{
    int sta = 0;
    sta = fseek(fp,offset,SEEK_CUR);
    if(sta == 0)
        return OK;
    else
        return Error;
}

Statue FilePointMoveBackward(FILE * fp,long offset)
{
    int sta = 0;
    offset = -offset;
    sta = fseek(fp,offset,SEEK_CUR);
    if(sta == 0)
        return OK;
    else
        return Error;
}

char * s_gets(char * st,int n)
{
    char * ret;
    int i = 0;

    ret = fgets(st,n,stdin);
    if(ret)
    {
        while(st[i] != '\n' && st[i] != '\0')
            i++;
        if(st[i] == '\n')
        {
            st[i] = '\0';
        }
        else
        {   
           
            while(getchar() != '\n')
                continue;
        }
    }
    return ret;
}

Statue Read_All_Data(char * FileName,char * target)
{
    if(IsFileExist(FileName) == No)
    {
        printf("This File is not exist!!");
        return Error;
    }
    FILE * fp = fopen(FileName,"r");
    int l = 0;
    int i ;
    for(i = 0 ; i < READ_MAX-1 && l != EOF ; i++)
    {   
        l = getc(fp);
        target[i] = l;
    }
    target[i] = '\0';
    fclose(fp);
    return OK;
    
}

Statue Read_All_Data_version2(char * FileName,char * target,int m,int max)
{
    if(IsFileExist(FileName) == No)
    {
        printf("This File is not exist!!");
        return Error;
    }
    FILE * fp = fopen(FileName,"r");
    FilePointMoveForward(fp,m);
    int l = getc(fp);
    int i ;
    for(i = 0 ; i < max && l != EOF && l != ' '; i++)
    {   
        target[i] = l;
        l = getc(fp);
    }
    target[i] = '\0';
    fclose(fp);
    return OK;
}

Statue Delete_AendLetter(char * name,int n) //ɾ�������ļ�����ĸ
{
    int ch1;int ch2;
    FILE * fp,* fp2,* fp1;
    if(IsFileExist(name) == No)
    {
        printf("This file is not exist!\n");
        return Error;
    }
    fp = fopen(name,"r+");
    fp1 = fopen(name,"r+");
    if(fp == NULL || fp1 == NULL)
      {printf("open error!\n");
       return Error;}  
    FilePointMoveForward(fp,n);
    ch1 = getc(fp);
    ch2 = getc(fp1);
    fp2 = fopen("System_temp.txt","w+");
    if(ch1 == EOF)
        return Error;
    while(ch1 != EOF)
    {
        putc(ch2,fp2);
        ch1 = getc(fp);
        ch2 = getc(fp1);
    }
    FilePointSetHead(fp2);
    fclose(fp);fclose(fp1);
    fp = fopen(name,"w+");
    ch1 = getc(fp2);
   // printf("%c",ch1);
    while(ch1 != EOF)
    {
        putc(ch1,fp);
        ch1 = getc(fp2);
    }
    fclose(fp);
    fclose(fp2);
    return OK;

}
//system function
Statue User_register(void)
{   
    char usename[ACCOUNT_MAX] = {0};
    char password[ACCOUNT_MAX] = {0};
    User * temp = (User *)(malloc(sizeof(User)));   //�˴���δ�ͷţ������ģ�������
    printf("You are register now,please enter your account,length:1 ~ 20!\n");
    s_gets(usename,20); 
    printf("please enter your password,length:1 ~ 20!\n");
    s_gets(password,20); 
    Account_Init(temp,usename,password);
    if(Register_process(usename,password) == Error)
    {
        return Error;
    }
    free(temp);//
    return OK;
}

Statue Register_process(char usename[],char password[]) //�����ע�����
{
    if(IsFileExist(usename) == Yes)
        {
            printf("This account has been created !!\n");
            return Error;
        }
    
   Create_A_File_version1(usename);
   
   Write_A_File_version3(usename,usename,20);
 
   Write_A_File_version3(usename,password,20);
 
   Write_A_File_version3(usename,"User_priorty",20);
  
   Write_A_File_version3(usename,"0",20);
   
   //Write_A_File_version1(usename,"#");
  // Write_A_File_version2(SYS_ACCOUNT," ",1,Backward);
   Delete_AendLetter(SYS_ACCOUNT,1);
   Write_A_File_version3(SYS_ACCOUNT,usename,20);
   Write_A_File_version1(SYS_ACCOUNT,"#"); 
   return OK;
}

Statue Account_Init(User * temp,char name[ACCOUNT_MAX],char password[ACCOUNT_MAX]) //�����û�ʱ���˻���ʼ��
{
    strcpy(temp -> account,name);
    strcpy(temp -> password,password);
    temp -> priorty = User_priorty;
    temp -> money = 0;
}

Statue User_login(User * cur)
{   
    char usename[ACCOUNT_MAX] = {0};
    char password[ACCOUNT_MAX] = {0};
    Login_Statue loginstatue;
    printf("You are lording now ,please enter your Account:\n");
    s_gets(usename,20);
    printf("please enter your password:\n");
    s_gets(password,20);
    loginstatue = Account_Login(usename,password);
    if(loginstatue == Successful)
    {
        Read_User_Information(usename,cur);
        return OK;
    }
    else
        return Error;
    
}

Login_Statue Account_Login(char usename[],char password[])
{
    if(IsFileExist(usename) == No)  
        {
            printf("This Account is not exist!\n");
            return Fail;
        }
    char true_password[20] = {0};
    Read_All_Data_version2(usename,true_password,20,20);
    if(strcmp(password,true_password) == 0)
        {
            printf("load successful!\n");
            return Successful;
        }
    else
        {
            printf("password error!\n");
            return Fail;
        }
    
    
}

Statue Read_User_Information(char * usename,User * cur)
{   
    char priorty[ACCOUNT_MAX] = {0};
    char money[ACCOUNT_MAX] = {0};
    Read_All_Data_version2(usename,cur -> account,0,20);
    Read_All_Data_version2(usename,cur -> password,20,20);
    Read_All_Data_version2(usename,priorty,40,20);
    Read_All_Data_version2(usename,money,60,20);
    if(strcmp(priorty,"User_priorty") == 0)
    {
        cur -> priorty = User_priorty;
    }
    else
    {
        cur -> priorty = System_priorty;
    }
    cur -> money = (long)(atoi(money));
    return OK;
}

Statue System_ShowInformation(User * name)
{
    if(name == NULL)
        {
            printf("Showing Error!\n");
            return Error;
        }
    else
        {
            printf("Account:%s \nPassword:%s\nMoney:%d\nPriorty:(1 = system,0 = user) %d\n",name ->account,name ->password,name ->money,name ->priorty);
        }
    return OK;
}

Statue System_ShowAllUser(void)
{
    if(IsFileExist(SYS_ACCOUNT) == No)
    {
        printf("System file is lost!!!\n");
        return  Error;
    }
    printf("Hear are all the Users:\n");
    Show_A_File_version1(SYS_ACCOUNT);
    printf("\n");
    return OK;
}

Statue System_ShowAllDetail(void)
{
    char usename[ACCOUNT_MAX] = {0};
    User * temp = (User *)(malloc(sizeof(User)));
    Read_All_Data_version2(SYS_ACCOUNT,usename,0,20);
    int i = 1;
    while(usename[0] != '#')
    {   
        Read_User_Information(usename,temp);
        System_ShowInformation(temp);
        printf("*******************\n");
        Read_All_Data_version2(SYS_ACCOUNT,usename,(i*20),20);
        i++;
    }
    free(temp);
    return OK;
}


void System_Menu(void)  //δ���,ϵͳ�˵�
{   //while(1);
    system("cls");
    printf("****************************************************\n");
    printf("********Welcome ! Please Enter you Choice!**********\n");
    printf("********    1.register for your account         ****\n");
    printf("********        2.login  your account         ******\n");
    printf("********        3.Enter Manager Menu         *******\n");
    printf("****************************************************\n");
    int select;
    select = getch();
    
    switch(select)
    {
        case '1' :User_register();
                  break;
        case '2' :if(User_login(&System) == OK)
                    UserLoginMenu();
                  else
                  { printf("Load fail!!Please try again!\n");
                    getch();
                  }
                    
                  break;
        case '3' : ManagerMenu();
                  break;
        default : printf("This select is not exist !!,Please enter again!\n");
                  getch();
                  return;
    }
    return;
}

void UserLoginMenu(void) //�û��˵�
{  
    int select;
    while(1)
   {system("cls");
    printf("********************************************************************\n");
    printf("*****Welcome     %-20s! Please Enter you Choice!*****\n",System.account);
    printf("****    1.Show your account's Information       ********************\n");
    printf("*****        2.login out your account         **********************\n");
    printf("********************************************************************\n");
    
        
        select = getch();
        switch(select)
        {
            case '1': if(System_ShowInformation(&System) == OK)
                        printf("Showing Successfully!\n");
                      else
                        printf("Something Wrong!\n");
                      getch();
                      break;  
            case '2': return ;
            default : return ;
        }
    }   
    return ;

}


void ManagerMenu(void) // ����Ա�˵�
{   int select;
while(1)
   {system("cls");
    printf("****************************************************\n");
    printf("*Welcome to Manager Menu ! Please Enter you Choice!*\n");
    printf("*******         1.Change one's Money         *******\n");
    printf("***         2.Show all User's information        ***\n");
    printf("******      3.Change one's Authority           *****\n");
    printf("4.Rangge and show User's Information(Based on Money)\n");
    printf("****************************************************\n");

    
        
    select = getch();
    switch(select)
        {
            case '1': if(System_ChangeMoney() == OK)
                        printf("Change Successfully!\n");
                      else
                        printf("Change Can't Finish!\n");
                      getch();
                      break;  
            case '2': if(System_ShowAllDetail() == OK)
                        printf("Everything is ok!\n");
                      else
                        printf("Something Error!\n");
                      getch();
                      break;
            case '3': System_ChangeAuthority();
                      getch();
                      break;
            case '4':   System_RerangeProcess();
                       break; 
            default:  return ;
        }
    }
    return ;
}


Statue System_ChangeMoney_process(char * usename,int number)
{
    if(IsFileExist(usename) == No)
        {
            printf("Can't Find this User!\n");
            return Error;
        }
    Read_User_Information(usename,&System);
    System.money = number;
    char target[ACCOUNT_MAX] = {0};
    sprintf(target,"%d",number);
    Write_A_File_version4(usename,target,60,20);
    return OK;
}

Statue System_ChangeMoney(void)
{
    char usename[ACCOUNT_MAX] = {0};
    int money = 0;
    printf("Please enter your target AccountName:\n");
    s_gets(usename,20);
    printf("Please Enter your target number:\n");
    scanf("%d",&money);
    getchar();
    if(System_ChangeMoney_process(usename,money) == Error)
        {
            return Error;
        }
    else
        return OK;
}

List * List_init(char * filename) //��ͷ�ڵ��
{
   
    char usename[MAX] = {0};
    List * ret = (List *)(malloc(sizeof(List)));
    List * temp2 = ret;
    List * retu = ret;
    User * usetemp = NULL;
    ret ->cur = NULL;
    ret ->next = NULL;
    Read_All_Data_version2(filename,usename,0,20);
    int i = 1;
    while(usename[0] != '#')
    {   
       
        usetemp = (User *)(malloc(sizeof(User)));
        temp2 = (List *)(malloc(sizeof(List)));
        Read_User_Information(usename,usetemp);
        temp2 -> cur = usetemp;
        temp2 -> next = NULL;
        ret -> next = temp2;
        ret = ret ->next;
        Read_All_Data_version2(SYS_ACCOUNT,usename,(i*20),20);
        i++;
    }
    return retu;
    
}

Statue ShowListData(List * test)
{   
    if(test == NULL )
        {   printf("That is not a avaliable List!\n");
            return Error;}
    test = test -> next;
    printf("%-20s%-20s%-20s\n","Username","Money","Priorty");
    while(test != NULL )
    {   
        
        printf("%-20s",test -> cur-> account);
        printf("%-20d",test ->cur ->money);
        printf("%-20d\n",test->cur->priorty);
        test = test ->next;
    }
    return OK;
}

List * List_sort(List * exam)
{
   return mergesort(exam,NULL);

}


List * merge(List * head1,List * head2)
{
    List * newhead = (List *)(malloc(sizeof(List)));
    List * ret = newhead;
    newhead -> cur = NULL;
    newhead -> next = NULL;
    
    if(head1 == NULL || head2 == NULL)
        {
            printf("That is not a avaliable List!\n");
            return NULL;
        }
    head1 = head1 -> next;
    head2 = head2 -> next;
    while(head1 != NULL && head2 != NULL)
    {
        if(head1 -> cur -> money > head2 -> cur ->money)
        {
            newhead -> next = head1;
            head1 = head1 -> next;
        }
        else
        {
            newhead -> next = head2;
            head2 = head2 -> next;
        }
        newhead = newhead->next;
    }
    while(head1 != NULL)
    {
        newhead -> next = head1;
        head1 = head1 ->next;
        newhead = newhead -> next;
    }
    while(head2 != NULL)
    {
        newhead -> next = head2;
        head2 = head2 ->next;
        newhead = newhead -> next;
    }
    
    return ret;

}

List * mergesort(List * head,List * end)
{   
    List * touhead = head;
    if(head == NULL)
        return NULL;
    head = head -> next;
    if(head == NULL)
        return touhead;
    
    if(head -> next == end)
    {
        head -> next = NULL;
        return touhead;
    }
    List * fast = head -> next;
    List * slow = head -> next;
    List slowhead ;
    while(fast != end && fast -> next != end)
    {
        fast = fast -> next -> next;
        slow = slow -> next;
        
    }
    slowhead.cur = NULL;
    slowhead.next = slow;
    return merge(mergesort(touhead,slow),mergesort(&slowhead,end));
}

List * reverse(List * head)
{
    if(head == NULL )
    {
        printf("That is not a avaliable!\n");
        return NULL;
    }
    List * node ;
    List * newhead = NULL;
    List * ret = (List *)(malloc(sizeof(List)));
    ret -> cur = NULL;
    head = head -> next;
    while(head != NULL )
    {
        node = head;
        head = head -> next;
        node -> next = newhead;
        newhead = node;
    }
    ret -> next = newhead;
    free(head);
    return ret;


}


Statue System_RerangeProcess(void)
{   
   int select; 
   List * test = List_init(SYS_ACCOUNT);
   test = List_sort(test);
   int flag = 0;
   while(1)
   {
       system("cls");
       printf("*****************************************\n");
       printf("******What range do you want ?***********\n");
       printf("press 1 for rise and press 2 for decrease\n");
       printf("*****************************************\n");
       select = getch();
       switch(select)
       {
           case '1':if(flag == 0)
                    {test = reverse(test);
                     flag = 1;} 
                    ShowListData(test);
                    getch();
                    break;
           case '2':if(flag == 1)
                    {
                    test = reverse(test);
                    flag = 0;
                    }
                    ShowListData(test);
                    getch();
                    break;
            default : return OK;

       }
   }
   return OK;
}

Statue System_ChangeAuthority(void)
{
    int select;
    char usename[ACCOUNT_MAX] = {0};
    
    system("cls");
    printf("please enter User's Account:\n");
    s_gets(usename,20);
    printf("What Authority you want give ? 0 for User and 1 for System:\n");
    select = getch();
    if(System_ChangeAuthority_process(usename,select) == Error)
    {
        
        return Error;
    }
    else
    {
        
        return OK;
    }

}

Statue System_ChangeAuthority_process(char * usename,int n)
{
    if(IsFileExist(usename) == No)
        {
            printf("Can't Find this User!\n");
            printf("User's Authority hasn't been changed!\n");
            return Error;
        }
    if(n == 1)
      Write_A_File_version4(usename,"User_priorty",40,20);
    else
      Write_A_File_version4(usename,"System_priorty",40,20);
    printf("User's Authority has been changed!\n");
    return OK;
}