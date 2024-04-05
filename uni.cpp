#include "martixcal.h"

int main(void)
{
    int n = 0;
    int step  = 0;
    printf("Input x:\n");
    scanf("%d",&targetStep);

    //确定n的值
    for(int i=2; i<=30;++i)
    {
        mp.clear();
        step = whatStep(i-1,i-1,false,nullptr,i);
        if( step >= targetStep)
        {
            n =  i;
            break;
        }
    }

    if(n == 0)
    {
        printf("x too large，exit\n");
        return -1;
    }

    //分配矩阵内存
    int* narray = (int *)malloc((n*n)*sizeof(int));

    if(genAndTest(narray,n))
    {
        printMartix(narray,n);
        free(narray);
        return 0;
    }

    n++;

    narray = (int *)malloc((n*n)*sizeof(int));

    if(genAndTest(narray,n))
    {
        printMartix(narray,n);
        free(narray);
    }
        
    return 0;
}