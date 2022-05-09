#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

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

//This is my FileIO function
Statue Show_A_File_version1(char * FileName);//显示一个文本文件的所有内容
Statue Create_A_File_version1(char * FileName);//创建一个文本文件，需要带后缀
SearchStatue IsFileExist(char * FileName);//查找一个文件是否存在
Statue Write_A_File_version1(char * FileName,char * target);//在末尾写内容
Statue FilePointSetEnd(FILE * fp);//将当前文件指针位置设置在末尾
Statue FilePointSetHead(FILE * fp);//将当前文件指针位置设置在开头
Statue FilePointMoveForward(FILE * fp,long offset);//当前文件指针往后移
Statue FilePointMoveBackward(FILE * fp,long offset);//当前文件指针往前移
Statue Write_A_File_version2(char * FileName,char * target,int offset,Movetype flag);//在距开头offset处写文件或尾部写文件

//This is my IO function
char * s_gets(char * st,int n);

int main(void)
{   
    char file[MAX] = {0};
    char target[MAX] = {0};
    s_gets(file,MAX);
    s_gets(target,MAX);
    Write_A_File_version2(file,target,5L,Backward);
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
Statue Write_A_File_version1(char * FileName,char * target)//在末尾写内容
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

Statue Write_A_File_version2(char * FileName,char * target,int offset,Movetype flag)//在距开头offset处写文件或距结尾offset..
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

