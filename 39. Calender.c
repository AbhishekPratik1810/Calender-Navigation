#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<conio.h>

void input(int* m, int* y)
{
    printf("    Sample Input: 2,2018 (implying February,2018)\n\n");

    do{
    printf("Enter Month,Year: ");
    scanf("%d,%d",m,y);

    if(!(*m>=1 && *m<=12))
        printf("WRONG INPUT. Enter Month Between 1-12\n\n");

    }while (!(*m>=1 && *m<=12));
}

int last2dig(int y)
{
    int num,arr[2];

    for(int i=0;i<=1;i++)
    {
        arr[i]=y%10;
        y/=10;
    }

    num = (arr[1]*10) + arr[0];

    return num;
}

int centurycode(int y)
{
    if(y>=2100)
    {
        while (y>=2100)
            y-=400;
    }

    else
    {
        while (y<=1700)
            y+=400;
    }

    if(y>=1700 && y<1800)
        return 4;
    else if(y>=1800 && y<1900)
        return 2;
    else if(y>=1900 && y<2000)
        return 0;
    else
        return 6;
}

int keyvalue(int m)
{
    if (m==1 || m==10)
        return 1;
    else if (m==2 || m==3 || m==11)
        return 4 ;
    else if (m==4 || m==7)
        return 0;
    else if (m==5)
        return 2;
    else if (m==6)
        return 5;
    else if (m==8)
        return 3;
    else
        return 6;
}

int checkleapyear(int y)
{
    if (y%4!=0)
        return 0;
    if (y%100==0)
    {
            if(y%400!=0)
                return 0;
            return 1;
    }
    else
        return 1;
}

int calcn(int l2,int cc,int kv,int ly,int m,int y)
{
    int result,tmp;

    tmp=l2/4;
    tmp+=1;
    tmp+=kv;
    if((m==1 || m==2)&& (ly==1))
        tmp-=1;
    tmp+=cc;
    tmp+=l2;

    result = tmp%7;

    if (1<result && result<=6)
        return result-2;
    else if (result==0)
        return 5;
    else
        return 6;
}

int daysofmonth(int m,int ly)
{
    if (m!=2)
    {
        if (m==1||m==3||m==5||m==7||m==8||m==10||m==12)
            return 31;
        else
            return 30;
    }

    else if (ly==1)
        return 29;

    else
        return 28;
}

void generatecal(int ind, int dom, int cal[][7])
{
    int j=ind,sum=1,flag =0;
    for(int i=0;i<6;i++)
    {
        for(;j<7;j++)
        {
            cal[i][j]=sum;
            sum++;

            if (sum>dom)
            {
                flag=1;
                break;
            }
        }
        if (flag==1)
            break;

        j=0;
    }
}

void wordmonth(int m, char s[10])
{
    char* p[12] = {"January","February","March","April","May","June","July","August","September","October","November","December"};
    strcpy(s,p[m-1]);
}

void printcal(int cal[][7],char s[10], int y)
{
    printf("\n\n\t\t\t\t\t\t    %s %d\n\n",s,y);
    printf("\t\t\t\t\tMon  Tue  Wed  Thu  Fri  Sat  Sun\n");
    for(int i=0;i<6;i++)
    {
        printf("\t\t\t\t\t");
        for(int j=0;j<7;j++)
        {
            if(cal[i][j]==0)
                printf("   ");
            else
                printf(" %d ",cal[i][j]);

            if(cal[i][j]<=9)
                printf("  ");
            else
                printf(" ");
        }
        printf("\n");
    }

    printf("\n\n");

    for(int i=1;i<121;i++)
        printf("*");

    printf("\n");
}

int getkey()
{
    int ch;

    if(ch!=224)
        printf("Upper Key - Next Year Same Month\nLower Key - Prev Year Same Month\nRight Key - Same Year Next Month\n Left Key - Same Year Prev Month\n  Esc Key - Stop\n\nEnter Input: ");

    ch=getch();

    printf("\n");

    if(ch!=224)
        for(int i=1;i<121;i++)
            printf("*");

    if(ch==0)
    {
        ch=getch();
        return ch;
    }
    return ch;
}

void newmy(int k, int* m, int* y)
{
    if(k==72)
        (*y)++ ;
    else if(k==80)
        (*y)--;
    else if(k==77)
    {
        if ((*m)!=12)
            (*m)++;
        else
        {
            (*m)=1;
            (*y)++;
        }
    }
    else if(k==75)
    {
        if((*m)!=1)
            (*m)--;
        else
        {
            (*m)=12;
            (*y)--;
        }
    }
    //->: 77, <- : 75, Esc : 27, Up : 72, Down : 80

}

int main()
{
    int month,year,kv,index,l2,cc,ly,dom,key,count;
    char s[10];

    input(&month,&year);

    do{

    if(key!=224)
    {
        int cal[6][7]={0};
        l2=last2dig(year);
        cc=centurycode(year);
        kv=keyvalue(month);
        ly=checkleapyear(year);

        index = calcn(l2,cc,kv,ly,month,year);

        dom = daysofmonth(month,ly);

        generatecal(index,dom,cal);

        wordmonth(month,s);

        printcal(cal,s,year);
    }
    key=getkey();
    count++;
    newmy(key,&month,&year);

    } while (key!=27);

    system("pause");
    return 0;
}
