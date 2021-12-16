#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 10000
typedef struct cost
{
    long All;//全部费用
    long Pre;//预交费用
    long Res;//剩余费用
}Cost;



typedef struct date
{
    int years;
    int months;
    int days;

}Date;



typedef struct time//出住院时间
{
    Date Registration;//挂号时间
    Date in;//住院时间，没住院就显示为0/0/0
    Date out;//出院时间，没出院就全显示为0/0/0
}Time;

typedef union ishospitalization//是否住院
{
    int No;//不住院显示为0
    char Room[10];//住院的病房

}IsHospitalization;

typedef struct hospitalization//住院相关信息
{
   IsHospitalization Stay;
   Time t;


}Hospitalization;

typedef struct relative//亲属信息
{
    char Rname[50];
    char relationship[20];//病人与陪护人关系（parent,child,spouse,other）
    long Rnumber;
}Relative;

typedef struct information
{ char Name[50];//病人姓名
     char Rig[20];//挂号单号
     char Sex;//性别，男M女F
    int Age;//年龄
    long Tel;//电话
    char Sb;//'Y'表示有家属，'N'表示没有家属
    Relative sb;//亲属信息,没有全输入无
    char doctor[50];//主治医师
    char p;//'Y'表示住院‘N’表示不住院
    Hospitalization Hospital;//住院相关信息
    Cost list;//费用相关
}Information;

void SwapInfor (Information *a,Information *b)//交换两个Information类型变量
{
Information temp;
temp = *a;
*a = *b;
*b = temp;

}

void PrintInfor()//按挂号时间顺序5
{
    Information r[100];
    FILE *fp;
fp=fopen("demo.txt","r");
if(fp==NULL)
{
printf("Wrong");
exit(0);
}
int k=0;
for(k=0;feof(fp)==0;k++)
{
fscanf(fp,"%s\t%s\t%c\t%d\t%ld\t%c",r[k].Name,r[k].Rig,&r[k].Sex,&r[k].Age,&r[k].Tel,&r[k].Sb);
if(r[k].Sb=='Y')
{
fscanf(fp,"%s\t%s\t%ld",r[k].sb.Rname,r[k].sb.relationship,&r[k].sb.Rnumber);
}
fscanf(fp,"%d/%d/%d\t%s\t%c",&r[k].Hospital.t.Registration.years,&r[k].Hospital.t.Registration.months,&r[k].Hospital.t.Registration.days,r[k].doctor,&r[k].p);//判断是否住院
if(r[k].p=='N')
{
fscanf(fp,"%d",&r[k].Hospital.Stay.No);
}
if(r[k].p=='Y')
{
fscanf(fp,"%s\t%d/%d/%d\t%d/%d/%d",r[k].Hospital.Stay.Room,&r[k].Hospital.t.in.years,&r[k].Hospital.t.in.months,&r[k].Hospital.t.in.days,&r[k].Hospital.t.out.years,&r[k].Hospital.t.out.months,&r[k].Hospital.t.out.days);//出院时间
}
fscanf(fp,"%ld\t%ld\t%ld",&r[k].list.All,&r[k].list.Pre,&r[k].list.Res);

}
fclose(fp);
k--;
int i,j;
for(i=0;i<k-1;i++)
{
for(j=1;j<k;j++)
{
if(r[j].Hospital.t.Registration.years>r[i].Hospital.t.Registration.years)
{
SwapInfor(&r[i],&r[j]);
}
else if(r[j].Hospital.t.Registration.years==r[i].Hospital.t.Registration.years&&r[j].Hospital.t.Registration.months>r[i].Hospital.t.Registration.months)
{
SwapInfor(&r[i],&r[j]);
}
else if(r[j].Hospital.t.Registration.years==r[i].Hospital.t.Registration.years
&&r[j].Hospital.t.Registration.months==r[i].Hospital.t.Registration.months
&&r[j].Hospital.t.Registration.days>r[i].Hospital.t.Registration.days)
{
SwapInfor(&r[i],&r[j]);
}
}
}
printf("\n");
for(i=0;i<k;i++)//输出病人信息
{

printf("姓名：%s\t挂号单：%s\t性别：%c\t年龄：%d\t电话：%ld\t",r[i].Name,r[i].Rig,r[i].Sex,r[i].Age,r[i].Tel);

printf("\t挂号时间：%d/%d/%d",r[i].Hospital.t.Registration.years,r[i].Hospital.t.Registration.months,r[i].Hospital.t.Registration.days);//挂号时间
printf("\n\n");

}
}

int AddTofile()//1
{
    Information inf;
    int flag3;
    FILE *fp;
        fp=fopen("demo.txt","a");
        if(fp==NULL)
        {
            printf("Failure to open C.txt!\n");
            exit(0);
        }
    while(1)
{

    printf("请输入病人姓名:");
    scanf("%s",inf.Name);
    fflush(stdin);
    printf("请输入挂号单号:");
    scanf("%s",inf.Rig);
    fflush(stdin);
    printf("请输入病人性别:");
    scanf("%c",&inf.Sex);
    fflush(stdin);
    printf("请输入病人年龄:");
    scanf("%d",&inf.Age);
    fflush(stdin);
    printf("请输入病人电话:");
    scanf("%ld",&inf.Tel);
    fflush(stdin);
    printf("是否有陪护人(Y有,N没有):");
    scanf("%c",&inf.Sb);
    if(inf.Sb=='Y')
    {
        fflush(stdin);
        printf("家属姓名:");
        scanf("%s",inf.sb.Rname);
        fflush(stdin);
        printf("关系:");
        scanf("%s",inf.sb.relationship);
        fflush(stdin);
        printf("家属联系方式:");
        scanf("%ld",&inf.sb.Rnumber);
        fflush(stdin);
    }


    printf("请输入挂号时间:");
    scanf("%d/%d/%d",&inf.Hospital.t.Registration.years,&inf.Hospital.t.Registration.months,&inf.Hospital.t.Registration.days);
    fflush(stdin);
    printf("主治医生:");
    scanf("%s",inf.doctor);
    fflush(stdin);

    printf("是否住院(住院Y,不住院N):");
    scanf(" %c",&inf.p);
    if(inf.p=='Y')
    {
        printf("住院病房:");
        scanf("%s",inf.Hospital.Stay.Room);
        fflush(stdin);
        printf("住院时间:");
        scanf("%d/%d/%d",&inf.Hospital.t.in.years,&inf.Hospital.t.in.months,&inf.Hospital.t.in.days);
        fflush(stdin);
        printf("出院时间(未出院0/0/0):");
        scanf("%d/%d/%d",&inf.Hospital.t.out.years,&inf.Hospital.t.out.months,&inf.Hospital.t.out.days);
        fflush(stdin);

    }
    if(inf.p=='N')
    {

        printf("请输入0:\n");
        scanf("%d",&inf.Hospital.Stay.No);
        fflush(stdin);
    }


    printf("费用:\n");
    printf("全部费用:");
    scanf("%ld",&inf.list.All);
    fflush(stdin);
    printf("预交费用:");
    scanf("%ld",&inf.list.Pre);
    fflush(stdin);
    printf("剩余费用:");
    scanf("%ld",&inf.list.Res);
    fflush(stdin);
        fprintf(fp,"%s\t",inf.Name);
       fprintf(fp,"%s\t",inf.Rig);
       fprintf(fp,"%c\t",inf.Sex);
       fprintf(fp,"%d\t",inf.Age);
       fprintf(fp,"%ld\t",inf.Tel);
       fprintf(fp,"%c\t",inf.Sb);//判断是否有家属
       if(inf.Sb=='Y')
       {
       fprintf(fp,"%s\t",inf.sb.Rname);//家属姓名
       fprintf(fp,"%s\t",inf.sb.relationship);//家属关系
       fprintf(fp,"%ld\t",inf.sb.Rnumber);//家属电话
       }
       fprintf(fp,"%d/%d/%d\t",inf.Hospital.t.Registration.years,inf.Hospital.t.Registration.months,inf.Hospital.t.Registration.days);
       fprintf(fp,"%s\t",inf.doctor);
       fprintf(fp,"%c\t",inf.p);
       if(inf.p=='N')
       {
           fprintf(fp,"%d\t",inf.Hospital.Stay.No);
       }
       if(inf.p=='Y')
       {
           fprintf(fp,"%s\t",inf.Hospital.Stay.Room);
         fprintf(fp,"%d/%d/%d\t",inf.Hospital.t.in.years,inf.Hospital.t.in.months,inf.Hospital.t.in.days);
        fprintf(fp,"%d/%d/%d\t",inf.Hospital.t.out.years,inf.Hospital.t.out.months,inf.Hospital.t.out.days);
       }
       fprintf(fp,"%ld\t",inf.list.All);
       fprintf(fp,"%ld\t",inf.list.Pre);
       fprintf(fp,"%ld\n",inf.list.Res);
        printf("是否继续?（1是,2否）:");
        scanf("%d",&flag3);
        fflush(stdin);
        if(flag3==2)
            break;
}
  fclose(fp);
    return 0;

}



int Query()
{
   int Totalpat;
   FILE *fp;
   Information pat[N];
   char E[50];
   fp=fopen("demo.txt","r");
   if(fp==NULL)
   {
       printf("Wrong");
       exit(0);
   }
   int i,j,e=1,m=1;
  for(i=0;feof(fp)==0;i++)
   {
      fscanf(fp,"%s\t%s\t%c\t%d\t%ld\t%c",pat[i].Name,pat[i].Rig,&pat[i].Sex,&pat[i].Age,&pat[i].Tel,&pat[i].Sb);
       if(pat[i].Sb=='Y')
       {
       fscanf(fp,"%s\t%s\t%ld",pat[i].sb.Rname,pat[i].sb.relationship,&pat[i].sb.Rnumber);
       }
       fscanf(fp,"%d/%d/%d\t%s\t%c",&pat[i].Hospital.t.Registration.years,&pat[i].Hospital.t.Registration.months,&pat[i].Hospital.t.Registration.days,pat[i].doctor,&pat[i].p);//判断是否住院
       if(pat[i].p=='N')
       {
           fscanf(fp,"%d",&pat[i].Hospital.Stay.No);
       }
       if(pat[i].p=='Y')
       {
           fscanf(fp,"%s\t%d/%d/%d\t%d/%d/%d",pat[i].Hospital.Stay.Room,&pat[i].Hospital.t.in.years,&pat[i].Hospital.t.in.months,&pat[i].Hospital.t.in.days,&pat[i].Hospital.t.out.years,&pat[i].Hospital.t.out.months,&pat[i].Hospital.t.out.days);//出院时间
       }
       fscanf(fp,"%ld\t%ld\t%ld",&pat[i].list.All,&pat[i].list.Pre,&pat[i].list.Res);

   }
   fclose(fp);
   Totalpat=i-1;
   fflush(stdin);

   do
   {
       printf("\n请输入病人挂号单：");
     scanf("%s",E);
    for(j=0;j<Totalpat;j++)
   {
       if(!strcmp(E,pat[j].Rig))
       {
           printf("姓名：%s\t",pat[j].Name);//姓名
       printf("挂号单：%s\t",pat[j].Rig);//挂号单
       printf("性别：%c\t",pat[j].Sex);//性别
       printf("年龄：%d\t",pat[j].Age);//年龄
       printf("电话：%ld\t",pat[j].Tel);//电话
       printf("是否有家属：%c\t",pat[j].Sb);//判断是否有家属
       if(pat[j].Sb=='Y')
       {
       printf("家属姓名：%s\t",pat[j].sb.Rname);//家属姓名
       printf("关系：%s\t",pat[j].sb.relationship);//家属关系
       printf("电话：%11ld\t",pat[j].sb.Rnumber);//家属电话
       }
       printf("\n");
       printf("挂号时间：%d/%d/%d\t",pat[j].Hospital.t.Registration.years,pat[j].Hospital.t.Registration.months,pat[j].Hospital.t.Registration.days);//挂号时间
       printf("主治医生：%s\t",pat[j].doctor);//主治医师
       printf("是否住院：%c\t",pat[j].p);//判断是否住院
       if(pat[j].p=='N')
       {
           printf("NO:%d\t",pat[j].Hospital.Stay.No);//不是为0
       }
       if(pat[j].p=='Y')
       {
           printf("病房号：%s\t",pat[j].Hospital.Stay.Room);//病房号
           printf("住院时间：%d/%d/%d\t",pat[j].Hospital.t.in.years,pat[j].Hospital.t.in.months,pat[j].Hospital.t.in.days);//住院时间
           printf("出院时间：%d/%d/%d\t",pat[j].Hospital.t.out.years,pat[j].Hospital.t.out.months,pat[j].Hospital.t.out.days);//出院时间
       }
       printf("全部费用：%ld\t",pat[j].list.All);//全部费用
       printf("预交费用：%ld\t",pat[j].list.Pre);//预交费用
       printf("剩余费用：%ld\n\n",pat[j].list.Res);//剩余费用
       e=0;
       }
   }
      if(e)
       {
           fflush(stdin);
           printf("病人不存在！\n");
           }



   fflush(stdin);
   printf("是否继续查找？\n");
   printf("1.YES\t\t\t2.NO\n");
   printf("请选择序号：");
   scanf("%d",&m);
    fflush(stdin);

        if(m==2)
        {
            break;
        }

   }while(m);
   return 0;
}



int user2()//医生输入密码
{
    int k=1;
    FILE *fp;
    int i,j;
    char ch[30], str[1000][50];
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
        fflush(stdin);
        printf("密码：");
        scanf("%s",ch);
    for(j=0;j<i-1;j++)
    {
        if(strcmp(ch,str[j])==0)
        {

           k=2;
        }
    }
    if(k==2)
    {
        break;
    }
    if(k==1)
    {
            printf("密码错误！\n");
            cases--;
            printf("你还有%d次输入机会\n",cases);
        }
    }
    fclose(fp);
    if(!cases)
 {
     exit (0);
 }
   return 1;
}


void Entry()
{

     int i,j,permission=1;
    printf("\n-------欢迎来到病人信息管理系统-------\n");
    printf("请输入账号与密码\n");

        FILE *fp;
    char ch[30], str[1000][50];
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
        fflush(stdin);
        printf("用户：");
        scanf("%s",ch);
    for(j=0;j<i-1;j++)
    {
        if(strcmp(ch,str[j])==0)
        {
            permission=user2();
            permission=2;
        }
    }
    if(permission==2)
    {
        break;
    }
    if(permission==1)
    {
            printf("用户错误！\n");
            cases--;
            printf("你还有%d次输入机会\n",cases);
    }
        }
    fclose(fp);
 if(!cases)
 {
     exit (0);
 }

    printf("\n");
    printf("\n");
    printf("\n");
    printf("##欢迎进入病人管理系统##");
    printf("\n");
    printf("\n");
    printf("\n");

}
void Exit()

{


    printf("--------欢迎下次使用--------");
    exit(0);

}

int Modify()//4
{
  fflush(stdin);
    int Totalpat;
   FILE *fp;
   Information pat[N];
   fp=fopen("demo.txt","r");
   if(fp==NULL)
   {
       printf("Wrong");
       exit(0);
   }
   int i=0;
  for(i=0;feof(fp)==0;i++)
   {
      fscanf(fp,"%s\t%s\t%c\t%d\t%ld\t%c",pat[i].Name,pat[i].Rig,&pat[i].Sex,&pat[i].Age,&pat[i].Tel,&pat[i].Sb);
       if(pat[i].Sb=='Y')
       {
       fscanf(fp,"%s\t%s\t%ld",pat[i].sb.Rname,pat[i].sb.relationship,&pat[i].sb.Rnumber);
       }
       fscanf(fp,"%d/%d/%d\t%s\t%c",&pat[i].Hospital.t.Registration.years,&pat[i].Hospital.t.Registration.months,&pat[i].Hospital.t.Registration.days,pat[i].doctor,&pat[i].p);//判断是否住院
       if(pat[i].p=='N')
       {
           fscanf(fp,"%d",&pat[i].Hospital.Stay.No);
       }
       if(pat[i].p=='Y')
       {
           fscanf(fp,"%s\t%d/%d/%d\t%d/%d/%d",pat[i].Hospital.Stay.Room,&pat[i].Hospital.t.in.years,&pat[i].Hospital.t.in.months,&pat[i].Hospital.t.in.days,&pat[i].Hospital.t.out.years,&pat[i].Hospital.t.out.months,&pat[i].Hospital.t.out.days);//出院时间
       }
       fscanf(fp,"%ld\t%ld\t%ld",&pat[i].list.All,&pat[i].list.Pre,&pat[i].list.Res);

   }
   fclose(fp);
   Totalpat=i-1;
   char s[50];
   int j,k,m,flag2;
   do
   {
       m=0;
       printf("你想修改病人（填挂号单）：");
  do
   {
    k=0;
   scanf("%8s",s);
     for(j=0;j<Totalpat;j++)
    {
        if(strcmp(s,pat[j].Rig))
        {
            k++;
        }
    }
    if(k==Totalpat)
    {
        printf("病人不存在！\n");
        fflush(stdin);
        printf("请重新输入：");
    }
    else
    {
        k=0;
    }

   }while(k);


   for(j=0;j<Totalpat;j++)
   {
       if(!strcmp(s,pat[j].Rig))
       {

       printf("请输入新信息：\n");
       printf("\n姓名：");
       scanf("%s",pat[j].Name);
       fflush(stdin);
        printf("\n挂号单：");
       scanf("%s",pat[j].Rig);
       fflush(stdin);
        printf("\n性别：");
       scanf("%c",&pat[j].Sex);
       fflush(stdin);
        printf("\n年龄：");
       scanf("%d",&pat[j].Age);
       fflush(stdin);
        printf("\n电话：");
       scanf("%ld",&pat[j].Tel);
       fflush(stdin);
         printf("\n是否有陪护人？\n");
          printf("\n是输入Y\t\t\t不是输入N\n");
       scanf("%c",&pat[j].Sb);
       fflush(stdin);
       if(pat[j].Sb=='Y')
       {
           printf("\n陪护人姓名：");
       scanf("%s",pat[j].sb.Rname);
       fflush(stdin);
       printf("\n陪护人与病人关系：");
       scanf("%s",pat[j].sb.relationship);
       fflush(stdin);
       printf("\n陪护人电话：");
       scanf("%ld",&pat[j].sb.Rnumber);
       fflush(stdin);
       }
       printf("\n挂号时间(形式为 / / /）：");
       scanf("%d/%d/%d",&pat[j].Hospital.t.Registration.years,&pat[j].Hospital.t.Registration.months,&pat[j].Hospital.t.Registration.days);
       fflush(stdin);
       printf("\n主治医生：");
       scanf("%s",pat[j].doctor);
       fflush(stdin);
       printf("\n是否住院？\n");
       printf("\n是输入Y\t\t\t不是输入N\n");
       scanf("%c",&pat[j].p);
       fflush(stdin);
       if(pat[j].p=='N')
       {
           printf("\n不住院请输入0：");
           scanf("%d",&pat[j].Hospital.Stay.No);
           fflush(stdin);
       }
       if(pat[j].p=='Y')
       {
           printf("\n病房号:");
           scanf("%s",pat[j].Hospital.Stay.Room);
           fflush(stdin);
       printf("\n住院时间：");
       scanf("%d/%d/%d",&pat[j].Hospital.t.in.years,&pat[j].Hospital.t.in.months,&pat[j].Hospital.t.in.days);
       fflush(stdin);
       printf("\n出院时间：");
       scanf("%d/%d/%d",&pat[j].Hospital.t.out.years,&pat[j].Hospital.t.out.months,&pat[j].Hospital.t.out.days);
       fflush(stdin);
       }
       printf("\n总费用：");
       scanf("\n%ld",&pat[j].list.All);
       fflush(stdin);
       printf("\n预交费用：");
       scanf("%ld",&pat[j].list.Pre);
       fflush(stdin);
       printf("\n剩余费用：");
       scanf("%ld",&pat[j].list.Res);
       fflush(stdin);
       break;

       }
   }
    fflush(stdin);
   printf("\n是否继续修改？\n");
   printf("\n1.YES\t\t\t2.NO\n");
    printf("\n请输入序号：");
       scanf("%d",&flag2);
       while(flag2!=1&&flag2!=2)
       {
           printf("\n输入错误！\n");
           printf("\n请重新输入：");
           scanf("%d",&flag2);
       }
       if(flag2==1)
       {
          m=1;
          printf("\n你想修改病人（填挂号单）：");
          fflush(stdin);
          break;
       }
       if(flag2==2)
       {
           m=0;
       }


}while(m);
   fp=fopen("demo.txt","w");
   if(fp==NULL)
   {
       printf("Wrong");
       exit(0);
   }
    for(j=0;j<Totalpat;j++)
  {
       fprintf(fp,"%s\t",pat[j].Name);
       fprintf(fp,"%s\t",pat[j].Rig);
       fprintf(fp,"%c\t",pat[j].Sex);
       fprintf(fp,"%d\t",pat[j].Age);
       fprintf(fp,"%ld\t",pat[j].Tel);
       fprintf(fp,"%c\t",pat[j].Sb);//判断是否有家属
       if(pat[j].Sb=='Y')
       {
       fprintf(fp,"%s\t",pat[j].sb.Rname);//家属姓名
       fprintf(fp,"%s\t",pat[j].sb.relationship);//家属关系
       fprintf(fp,"%ld\t",pat[j].sb.Rnumber);//家属电话
       }
       fprintf(fp,"%d/%d/%d\t",pat[j].Hospital.t.Registration.years,pat[j].Hospital.t.Registration.months,pat[j].Hospital.t.Registration.days);
       fprintf(fp,"%s\t",pat[j].doctor);
       fprintf(fp,"%c\t",pat[j].p);
       if(pat[j].p=='N')
       {
           fprintf(fp,"%d\t",pat[j].Hospital.Stay.No);
       }
       if(pat[j].p=='Y')
       {
           fprintf(fp,"%s\t",pat[j].Hospital.Stay.Room);
         fprintf(fp,"%d/%d/%d\t",pat[j].Hospital.t.in.years,pat[j].Hospital.t.in.months,pat[j].Hospital.t.in.days);
        fprintf(fp,"%d/%d/%d\t",pat[j].Hospital.t.out.years,pat[j].Hospital.t.out.months,pat[j].Hospital.t.out.days);
       }
       fprintf(fp,"%ld\t",pat[j].list.All);
       fprintf(fp,"%ld\t",pat[j].list.Pre);
       fprintf(fp,"%ld\n",pat[j].list.Res);
  }
         fclose(fp);

   return 0;
}


void Printpat()//显示病人信息
{
    Information r[N];
    FILE *fp;
fp=fopen("demo.txt","r");
if(fp==NULL)
{
printf("Wrong");
exit(0);
}
int j,k=0;
for(k=0;feof(fp)==0;k++)
{
fscanf(fp,"%s\t%s\t%c\t%d\t%ld\t%c",r[k].Name,r[k].Rig,&r[k].Sex,&r[k].Age,&r[k].Tel,&r[k].Sb);
if(r[k].Sb=='Y')
{
fscanf(fp,"%s\t%s\t%ld",r[k].sb.Rname,r[k].sb.relationship,&r[k].sb.Rnumber);
}
fscanf(fp,"%d/%d/%d\t%s\t%c",&r[k].Hospital.t.Registration.years,&r[k].Hospital.t.Registration.months,&r[k].Hospital.t.Registration.days,r[k].doctor,&r[k].p);//判断是否住院
if(r[k].p=='N')
{
fscanf(fp,"%d",&r[k].Hospital.Stay.No);
}
if(r[k].p=='Y')
{
fscanf(fp,"%s\t%d/%d/%d\t%d/%d/%d",r[k].Hospital.Stay.Room,&r[k].Hospital.t.in.years,&r[k].Hospital.t.in.months,&r[k].Hospital.t.in.days,&r[k].Hospital.t.out.years,&r[k].Hospital.t.out.months,&r[k].Hospital.t.out.days);//出院时间
}
fscanf(fp,"%ld\t%ld\t%ld",&r[k].list.All,&r[k].list.Pre,&r[k].list.Res);

}
fclose(fp);
k--;

printf("\n");
for(j=0;j<k;j++)
   {
      printf("姓名：%s\t",r[j].Name);//姓名
       printf("挂号单：%s\t",r[j].Rig);//挂号单
       printf("性别：%c\t",r[j].Sex);//性别
       printf("年龄：%d\t",r[j].Age);//年龄
       printf("电话：%ld\t",r[j].Tel);//电话
       printf("是否有家属：%c\t",r[j].Sb);//判断是否有家属
       if(r[j].Sb=='Y')
       {
       printf("家属姓名：%s\t",r[j].sb.Rname);//家属姓名
       printf("关系：%s\t",r[j].sb.relationship);//家属关系
       printf("电话：%11ld\t",r[j].sb.Rnumber);//家属电话
       }
       printf("\n");
       printf("挂号时间：%d/%d/%d\t",r[j].Hospital.t.Registration.years,r[j].Hospital.t.Registration.months,r[j].Hospital.t.Registration.days);//挂号时间
       printf("主治医生：%s\t",r[j].doctor);//主治医师
       printf("是否住院：%c\t",r[j].p);//判断是否住院
       if(r[j].p=='N')
       {
           printf("NO:%d\t",r[j].Hospital.Stay.No);//不是为0
       }
       if(r[j].p=='Y')
       {
           printf("病房号：%s\t",r[j].Hospital.Stay.Room);//病房号
           printf("住院时间：%d/%d/%d\t",r[j].Hospital.t.in.years,r[j].Hospital.t.in.months,r[j].Hospital.t.in.days);//住院时间
           printf("出院时间：%d/%d/%d\t",r[j].Hospital.t.out.years,r[j].Hospital.t.out.months,r[j].Hospital.t.out.days);//出院时间
       }
       printf("全部费用：%ld\t",r[j].list.All);//全部费用
       printf("预交费用：%ld\t",r[j].list.Pre);//预交费用
       printf("剩余费用：%ld\n\n",r[j].list.Res);//剩余费用

   }
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
            case 3:Query();
            m=3;
            break;
            default :printf("输入错误！\n");
        }
    }while(m==3);
    if(m==2)
    {
        Exit();
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
    printf("6.退出用户\n");
    printf("-------------------------------\n");
}

int main()
{
   a: LOGIN();
    int M,T,t=1,m=1;
    do
    {

    SHOWMENU();
    printf("\n请选择菜单：");
    scanf("%d",&M);
    while(M<0||M>6)
    {
        SHOWMENU();
        fflush(stdin);
        printf("\n请重新选择菜单：");
        scanf("%d",&M);

    }
    switch(M)
    {
    case 1: AddTofile();
            break;
    case 2:printf("%d",M);
            break;
    case 3:Printpat();
            break;
    case 4:Modify();
            break;
    case 5:PrintInfor();
            break;
    case 6:goto a;
    }
    fflush(stdin);
    printf("\n是否继续使用？\n");
    t=1;
    printf("\n1.YES\t\t\t2.NO\n");
     printf("\n请输入序号：");
    while(t)
    {
    scanf("%d",&T);
    if(T==2)
    {
        goto a;
    }
    if(T!=2&&T!=1)
    {
        fflush(stdin);
        printf("\n输入错误！\n");
        printf("\n请重新输入序号：");
    }
    if(T==1)
    {
        t=0;
    }
    }
    }while(m);
}
