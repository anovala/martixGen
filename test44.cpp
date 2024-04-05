#include <stdio.h>
#include <map>
#include "martixcal.h"

//特别为了n44并且2个零点写的函数
int whatStepn44(int x, int y)
{
    printf("call for x=%d, y=%d\n",x,y);
    if(x <= 1 && y <=1)
        return 0;
    if( (x == 1 && y ==2) || ( x == 2 && y == 1))
        return 1;
    /*else if ((x == 3 && y == 2) || (x == 1 && y == 4))  //特定不能走的点
    {
        return 0;
    }*/
    else
    {
        if(x>= 2 && y>=2)
            return whatStepn44(x-1,y)+whatStepn44(x,y-1);
        else if(x >=2)
            return whatStepn44(x-1,y);
        else 
            return whatStepn44(x,y-1);
    }

}

// 不设置0点，n=3，x=9， n=4,x=20
//要处理数组下表从0，还是从1开始的问题，要取一个标准
int main(void)
{
    int n = 2;
    int arr[n][n];
    int *ptr = &arr[0][0];

    for(int i =0; i<n*n;++i)
        *(ptr+i) = 1;

    //arr[0][3] = 0;

    int step = whatStep(n-1,n-1,true,ptr,n);
    printf("step for %d*%d = %d\n",n,n,step);

    return 0;
}