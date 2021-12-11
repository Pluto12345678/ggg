#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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

int main()
{

    int Totalpat;
   FILE *fp;
   Information pat[100];
   fp=fopen("demo.txt","r");
   if(fp==NULL)
   {
       printf("Wrong");
       exit(0);
   }
   int i=0;
  for(i=0;feof(fp)==0;i++)
   {
      fscanf(fp,"%10s\t%s\t%c\t%d\t%ld\t%c",pat[i].Name,pat[i].Rig,&pat[i].Sex,&pat[i].Age,&pat[i].Tel,&pat[i].Sb);
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
   printf("%d",i);
   Totalpat=i-1;
   int j;
   for(j=0;j<Totalpat;j++)
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

   }
   char s[50];
   int k,m,flag1,flag2;
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
       printf("姓名：");
       scanf("%8s",pat[j].Name);
       fflush(stdin);
        printf("挂号单：");
       scanf("%8s",pat[j].Rig);
       fflush(stdin);
        printf("性别：");
       scanf("%c",&pat[j].Sex);
       fflush(stdin);
        printf("年龄：");
       scanf("%d",&pat[j].Age);
       fflush(stdin);
        printf("电话：");
       scanf("%11ld",&pat[j].Tel);
       fflush(stdin);
         printf("是否有陪护人？");
          printf("1.YES\t\t2.NO\n");
       printf("请输入序号：");
       scanf("%d",&flag1);
       fflush(stdin);
       if(flag1==1)
       {
           printf("陪护人姓名：");
       scanf("%8s",pat[j].sb.Rname);
       fflush(stdin);
       printf("陪护人与病人关系：");
       scanf("%8s",pat[j].sb.relationship);
       fflush(stdin);
       printf("陪护人电话：");
       scanf("%11ld",&pat[j].sb.Rnumber);
       fflush(stdin);
       }
       printf("挂号时间(形式为 / / /）：");
       scanf("%d/%d/%d",&pat[j].Hospital.t.Registration.years,&pat[j].Hospital.t.Registration.months,&pat[j].Hospital.t.Registration.days);
       fflush(stdin);
       printf("主治医生：");
       scanf("%8s",pat[j].doctor);
       fflush(stdin);
       printf("是否住院？");
       printf("是输入Y   不是输入N\n");
       scanf("%c",&pat[j].p);
       fflush(stdin);
       if(pat[j].p=='N')
       {
           printf("请输入0：");
           scanf("%d",&pat[j].Hospital.Stay.No);
           fflush(stdin);
       }
       if(pat[j].p=='Y')
       {
           printf("病房号:");
           scanf("%s",pat[j].Hospital.Stay.Room);
           fflush(stdin);
       printf("住院时间：");
       scanf("%d/%d/%d",&pat[j].Hospital.t.in.years,&pat[j].Hospital.t.in.months,&pat[j].Hospital.t.in.days);
       fflush(stdin);
       printf("出院时间：");
       scanf("%d/%d/%d",&pat[j].Hospital.t.out.years,&pat[j].Hospital.t.out.months,&pat[j].Hospital.t.out.days);
       fflush(stdin);
       }
       printf("总费用：");
       scanf("%ld",&pat[j].list.All);
       fflush(stdin);
       printf("预交费用：");
       scanf("%ld",&pat[j].list.Pre);
       fflush(stdin);
       printf("剩余费用：");
       scanf("%ld",&pat[j].list.Res);
       fflush(stdin);
       break;

       }
   }
    fflush(stdin);
   printf("是否继续修改？");
   printf("1.YES\t\t2.NO");
    printf("请输入序号：");
       scanf("%d",&flag2);
       while(flag2!=1&&flag2!=2)
       {
           printf("输入错误！");
           printf("请重新输入：");
           scanf("%d",&flag2);
       }
       if(flag2==1)
       {
          m=1;
          printf("你想修改病人（填挂号单）：");
          fflush(stdin);
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


