#include <stdio.h>
#include <stdlib.h>
typedef struct cost
{
    int All;//全部费用
    int Pre;//预交费用
    int Res;//剩余费用
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
    Date in;//住院时间，没住院就显示为0
    Date out;//出院时间，没出院就全显示为0
}Time;

typedef union ishospitalization//是否住院
{
    int No;//不住院
    char Room[10];//住院的病房

}IsHospitalization;

typedef struct hospitalization//住院相关信息
{
   IsHospitalization Stay；
   Time t;


}Hospitalization;

typedef struct relative//亲属信息
{
    char Rname[50];
    char relationship[20];//病人与陪护人关系（parent,child,spouse,other）
    int Rnumber;
}Relative;

typedef struct information
{
    char Name[10];//病人姓名
     char Rig[20];//挂号单号
    Relative sb;//亲属信息
    char doctor;//主治医师
    char Sex;//性别，男M女F
    int Age;//年龄
    int Tel;//电话
    Hospitalization HOSPTOCAL;//住院相关信息
    Cost list;//费用相关
}Information;
