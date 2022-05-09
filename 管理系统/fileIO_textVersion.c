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
Statue Show_A_File_version1(char * FileName);//��ʾһ���ı��ļ�����������
Statue Create_A_File_version1(char * FileName);//����һ���ı��ļ�����Ҫ����׺
SearchStatue IsFileExist(char * FileName);//����һ���ļ��Ƿ����
Statue Write_A_File_version1(char * FileName,char * target);//��ĩβд����
Statue FilePointSetEnd(FILE * fp);//����ǰ�ļ�ָ��λ��������ĩβ
Statue FilePointSetHead(FILE * fp);//����ǰ�ļ�ָ��λ�������ڿ�ͷ
Statue FilePointMoveForward(FILE * fp,long offset);//��ǰ�ļ�ָ��������
Statue FilePointMoveBackward(FILE * fp,long offset);//��ǰ�ļ�ָ����ǰ��
Statue Write_A_File_version2(char * FileName,char * target,int offset,Movetype flag);//�ھ࿪ͷoffset��д�ļ���β��д�ļ�

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

