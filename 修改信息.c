#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 100000
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
{
    char Name[50];//病人姓名
     char Rig[20];//挂号单号
     char Sex;//性别，男M女F
    int Age;//年龄
    long Tel;//电话
    Relative sb;//亲属信息
    char doctor[50];//主治医师
    char p;//'Y'表示住院‘N’表示不住院
    Hospitalization Hospital;//住院相关信息
    Cost list;//费用相关
}Information;


int main()
{
   FILE *fp;
   Information pat[N];
   int Totalpat;
   fp=fopen("demo.txt","r");
   if(fp==NULL)
   {
       printf("Wrong");
       exit(0);
   }
   int i,j;
   for(i=0;feof(fp)==0;i++)
   {
       fscanf(fp,"%8s",pat[i].Name);
       fscanf(fp,"%8s",pat[i].Rig);
       fscanf(fp,"%c",&pat[i].Sex);
       fscanf(fp,"%d",&pat[i].Age);
       fscanf(fp,"%11ld",&pat[i].Tel);
       fscanf(fp,"%8s",pat[i].sb.Rname);
       fscanf(fp,"%8s",pat[i].sb.relationship);
       fscanf(fp,"%11ld",&pat[i].sb.Rnumber);
       fscanf(fp,"%8s",pat[i].doctor);
       fscanf(fp,"%c",&pat[i].p);
       if(pat[i].p=='N')
       {
           fscanf(fp,"%d",&pat[i].Hospital.Stay.No);
       }
       if(pat[i].p=='Y')
       {
           fscanf(fp,"%s",pat[i].Hospital.Stay.Room);
       }
       fscanf(fp,"%d/%d/%d",&pat[i].Hospital.t.Registration.years,&pat[i].Hospital.t.Registration.months,&pat[i].Hospital.t.Registration.days);
       fscanf(fp,"%d/%d/%d",&pat[i].Hospital.t.in.years,&pat[i].Hospital.t.in.months,&pat[i].Hospital.t.in.days);
       fscanf(fp,"%d/%d/%d",&pat[i].Hospital.t.out.years,&pat[i].Hospital.t.out.months,&pat[i].Hospital.t.out.days);
       fscanf(fp,"%ld",&pat[i].list.All);
       fscanf(fp,"%ld",&pat[i].list.Pre);
       fscanf(fp,"%ld",&pat[i].list.Res);

   }
   Totalpat=i;
   fclose(fp);




   fp=fopen("demo.txt","w");
   if(fp==NULL)
   {
       printf("Wrong");
       exit(0);
   }
   char s[50];
   int k=0;


   printf("你想修改病人（填挂号单）：");
   do
   {

   scanf("%8s",s);
     for(j=0;j<i;j++)
    {
        if(strcmp(s,pat[j].Rig))
        {
            k++;
        }
    }
    if(k==Totalpat)
    {
        printf("病人不存在！\n");
        printf("请重新输入：");
    }
    else
    {
        k=0;
    }
   }while(k);


   for(j=0;j<i;j++)
   {
       if(!strcmp(s,pat[j].Rig))
       {

       printf("请输入新信息：\n");
       fscanf(fp,"%8s",pat[j].Name);
       fscanf(fp,"%8s",pat[j].Rig);
       fscanf(fp,"%c",&pat[j].Sex);
       fscanf(fp,"%d",&pat[j].Age);
       fscanf(fp,"%11ld",&pat[j].Tel);
       fscanf(fp,"%8s",pat[j].sb.Rname);
       fscanf(fp,"%8s",pat[j].sb.relationship);
       fscanf(fp,"%11ld",&pat[j].sb.Rnumber);
       fscanf(fp,"%8s",pat[j].doctor);
       fscanf(fp,"%c",&pat[j].p);
       if(pat[j].p=='N')
       {
           fscanf(fp,"%d",&pat[j].Hospital.Stay.No);
       }
       if(pat[j].p=='Y')
       {
           fscanf(fp,"%s",pat[j].Hospital.Stay.Room);
       }
       fscanf(fp,"%d/%d/%d",&pat[j].Hospital.t.Registration.years,&pat[j].Hospital.t.Registration.months,&pat[j].Hospital.t.Registration.days);
       fscanf(fp,"%d/%d/%d",&pat[j].Hospital.t.in.years,&pat[j].Hospital.t.in.months,&pat[j].Hospital.t.in.days);
       fscanf(fp,"%d/%d/%d",&pat[j].Hospital.t.out.years,&pat[j].Hospital.t.out.months,&pat[j].Hospital.t.out.days);
       fscanf(fp,"%ld",&pat[j].list.All);
       fscanf(fp,"%ld",&pat[j].list.Pre);
       fscanf(fp,"%ld",&pat[j].list.Res);

       }
   }



  for(j=0;j<i;j++)
  {
       fprintf(fp,"%8s\t",pat[j].Name);
       fprintf(fp,"%8s\t",pat[j].Rig);
       fprintf(fp,"%c\t",pat[j].Sex);
       fprintf(fp,"%d\t",pat[j].Age);
       fprintf(fp,"%11ld\t",pat[j].Tel);
       fprintf(fp,"%8s\t",pat[j].sb.Rname);
       fprintf(fp,"%8s\t",pat[j].sb.relationship);
       fprintf(fp,"%11ld\t",pat[j].sb.Rnumber);
       fprintf(fp,"%8s\t",pat[j].doctor);
       fprintf(fp,"%c\t",pat[j].p);
       if(pat[j].p=='N')
       {
           fprintf(fp,"%d\t",pat[j].Hospital.Stay.No);
       }
       if(pat[j].p=='Y')
       {
           fprintf(fp,"%s\t",pat[j].Hospital.Stay.Room);
       }
       fprintf(fp,"%d/%d/%d\t",pat[j].Hospital.t.Registration.years,pat[j].Hospital.t.Registration.months,pat[j].Hospital.t.Registration.days);
       fprintf(fp,"%d/%d/%d\t",pat[j].Hospital.t.in.years,pat[j].Hospital.t.in.months,pat[j].Hospital.t.in.days);
       fprintf(fp,"%d/%d/%d\t",pat[j].Hospital.t.out.years,pat[j].Hospital.t.out.months,pat[j].Hospital.t.out.days);
       fprintf(fp,"%ld\t",pat[j].list.All);
       fprintf(fp,"%ld\t",pat[j].list.Pre);
       fprintf(fp,"%ld\t",pat[j].list.Res);
  }
  fclose(fp);

   return 0;
}
