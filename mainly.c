#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int user2()//医生输入密码
{
    int k=0;
    FILE *fp;
    int i,j;
    char ch[30], str[10][50];
    if((fp=fopen("user2.txt","r"))==NULL)
    {
        printf("Failure to open user.txt!\n");
        exit(0);
    }
    for(i=0;feof(fp)==0;i++)
    {
        fgets(str[i],15,fp);
     for(j=0;str[i][j]!='\0';j++)
        {
            if(str[i][j]=='\n')
            {
                str[i][j]='\0';
            continue;
            }
        }
    }
    int cases=3;
    while(cases)
    {
        printf("密码：");
        scanf("%s",ch);
    for(j=0;j<i-1;j++)
    {
        if(strcmp(ch,str[j])==0)
        {
           k=1;
           break;
        }
    }
    if(k==1)
    {
        break;
    }

            printf("用户错误！\n");
            cases--;
            printf("你还有%d次输入机会\n",cases);
        }
    fclose(fp);
   return 1;
}


void Entry()
{

     int i,j,permission;
    printf("\n-------欢迎来到病人信息管理系统-------\n");
    printf("请输入账号与密码\n");

        FILE *fp;
    char ch[30], str[10][50];
    if((fp=fopen("user.txt","r"))==NULL)
    {
        printf("Failure to open user.txt!\n");
        exit(0);
    }
    for(i=0;feof(fp)==0;i++)
    {
        fgets(str[i],15,fp);
     for(j=0;str[i][j]!='\0';j++)
        {
            if(str[i][j]=='\n')
            {
                str[i][j]='\0';
            continue;
            }
        }
    }
    int cases=3;
    while(cases)
    {
        printf("用户：");
        scanf("%s",ch);
    for(j=0;j<i-1;j++)
    {
        if(strcmp(ch,str[j])==0)
        {
            permission=user2();
            break;
        }
    }
    if(permission==1)
    {
        break;
    }

            printf("用户错误！\n");
            cases--;
            printf("你还有%d次输入机会\n",cases);
        }
    fclose(fp);


    printf("\n");
    printf("\n");
    printf("\n");
    printf("欢迎进入病人管理系统");
    printf("\n");
    printf("\n");
    printf("\n");

}
void Exit()

{


    printf("--------欢迎下次使用--------");

}









void LOGIN()
{
    int n,m=0;
    do
    {

        printf("\n******病人信息管理系统******        \n");
        printf("1.用户登录\n");
        printf("2.退出系统\n");
        printf("3.信息查询\n");
        printf("请选择：");
        scanf("%d",&n);
        switch(n)
        {
            case 1:Entry();
            m=1;
            break;
            case 2:Exit();
            m=2;
            case 3:
            break;
            default :printf("输入错误！\n");
        }
    }while(m==0);
    if(m==2)
    {
        exit (0);
    }
}


void SHOWMENU()
{

    printf("-----病人信息管理系统-----\n");
    printf("1.新增病人信息\n");
    printf("2.删除病人信息\n");
    printf("3.显示病人信息\n");
    printf("4.修改病人信息\n");
    printf("5.显示挂号时间\n");
    printf("6.退出系统\n");
    printf("-------------------------------\n");
}

int main()
{
    LOGIN();
    int M;
    SHOWMENU();
    printf("请选择菜单：");
    scanf("%d",&M);
    while(M<0||M>6)
    {
        SHOWMENU();
        printf("请重新选择菜单：");
        fflush(stdin);
        scanf("%d",&M);


    switch(M)
    {
    case 1:printf("%d",M);
            break;
    case 2:printf("%d",M);
            break;
    case 3:printf("%d",M);
            break;
    case 4:printf("%d",M);
            break;
    case 5:printf("%d",M);
            break;
    case 6:printf("欢迎下次使用！");
            exit (0);
    }
    }

}
