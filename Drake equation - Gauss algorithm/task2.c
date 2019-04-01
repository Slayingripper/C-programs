#include <stdio.h>
#include "get_integer.h"


int i=0, d=0, day=0, ordinal_dayz=0, month=0, year=0, leap=0, fdayear=0,wknumber=0, daynum=0, max=0, dd=0, weekt=0, weeksinY=0,twitchy=0;
void printer()
{
if (twitchy==0)
    printf("%d-W%.2d-%.d\n", year, wknumber, daynum);
else if (twitchy==1)
    printf("%d-W%.2d-%.d\n", ++year, wknumber, daynum);
else if (twitchy==2)
    printf("%d-W%.2d-%.d\n", year-1, wknumber, daynum);
}    
void input()    //used to get input from user
{
        day=get_integer();
        month=get_integer();
        year=get_integer();
        return;
}

void leaptest()  //used to test for leapyear 
{
    if (year%4==0)
        if (year%100==0)
            if (year%400==0)
                leap=1;
            else
                leap=0;
        else
            leap=1;
    else
        leap=0;
    return;
}

int supervalue(int a) //used to calulate week number 
{
int twitchy,h=0;
for(twitchy=0;twitchy<=a;twitchy++){
     h=twitchy;

}
return h;
}
void ordinal() //calculate_ordinal_day
{
    if (month==1)
        {
        ordinal_dayz = day;
        return;
        }
    if (month==2)
        {
        ordinal_dayz = day + 31;
        return;
        }

    ordinal_dayz=max+day;

    if (leap==1)
    ordinal_dayz=ordinal_dayz+60;
    else
    ordinal_dayz = ordinal_dayz + 59;
    return;
}

void fdayearcalc() //calculate the first day of the year
    {
        fdayear=((1+(5*((year-1)%4))+(4*((year-1)%100))+(6*((year-1)%400)))%7);
        return;
    }

int pcalc(int y) //taken from sudo code
    {
        int p=0;
        p = ((y + (y/4) - (y/100) + (y/400)) % 7);
        return p;
    }

int weeksinyear(int y) //calculate the weeks in year
    {
        int py=0, pym=0;
        py=pcalc(y);
        pym=pcalc(y-1);
        if ((py==4)||(pym==3))
            weeksinY=53;
        else
            weeksinY=52;
        return weeksinY;
    }

void numberofdays() //calculates the number of days
    {
        daynum=((ordinal_dayz-1)%7)+fdayear+1;
            if (daynum>7)
                daynum=daynum-7;
        daynum--;
        if (daynum==0)
            {
            daynum=7;
            wknumber--;
            }
        return ;
    }

void weeknumber() //taken from sudo code calculates the number of weeks 
    {
        weekt=((ordinal_dayz-daynum+10)/7);
        wknumber=supervalue(weekt);
        if (wknumber==0){
            wknumber = weeksinyear(year-1);
            twitchy=2;
            }
        if (wknumber>weeksinyear(year))
            if (daynum<4){
                wknumber=1;
                twitchy=1;
                }
        return;
    }


int main (int argc, char *argv[])
{

    input();    
    dd=(int)((30.6*month)-91.4);   //calculating ordinal day here seems to work better 
    max=supervalue(dd);
    leaptest();
    ordinal();
    fdayearcalc();
    numberofdays();
    weeknumber();


    printf("%d-%.2d-%.2d\n", year,month,day);
    printf("%d-%.3d\n", year, ordinal_dayz);
    printer();
    

    return 0;
}
