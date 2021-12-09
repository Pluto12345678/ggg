#include <stdio.h>

struct TIME
{
    int hours,minutes,seconds;
};

void differenceBetweenTimePeriod(struct TIME t1, struct TIME t2, struct TIME *diff);


int main()
{
    struct TIME startTime,stopTime,diff;
     //输入开始时间:
    //输入小时、分钟、秒
    scanf("%d %d %d", &startTime.hours, &startTime.minutes, &startTime.seconds);

    //输入停止时间:
    //输入小时、分钟、秒
    scanf("%d %d %d", &stopTime.hours, &stopTime.minutes, &stopTime.seconds);

    // 计算差值
    differenceBetweenTimePeriod(startTime, stopTime, &diff);


    printf("= %d:%d:%d\n", diff.hours, diff.minutes, diff.seconds);

    return 0;
}

void differenceBetweenTimePeriod(struct TIME start, struct TIME stop, struct TIME *diff)
{
    struct TIME temp={0,0,0};;
    if(start.hours>stop.hours||(start.hours==stop.hours&&stop.minutes<start.minutes)||(start.hours==stop.hours&&stop.minutes==start.minutes&&stop.seconds<start.seconds))
    {
        temp=start;
        start=stop;
        stop=temp;

    }
    diff->hours=stop.hours-start.hours;
    diff->minutes=stop.minutes-start.minutes;
    if(diff->minutes<0)
    {
        diff->hours--;
        diff->minutes+=60;
    }

    diff->seconds=stop.seconds-start.seconds;
    if(diff->seconds<0)
    {
        if(diff->minutes>0)
        {
            diff->minutes--;
            diff->seconds+=60;
        }

        if(diff->minutes==0)
        {
            diff->hours--;
            diff->minutes=59;
            diff->seconds+=60;
        }

    }


}


