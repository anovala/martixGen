#include <stdio.h>
#include <map>
#include <mem.h>
#include <time.h>
#include <stdlib.h>
#include <unordered_set>


typedef struct 
{
    int x;
    int y;

    /*
    bool operator<(const Point& p2)const
    {
        if(x < p2.x)
            return true;
        else if(x == p2.x)
            return (y < p2.y);
        else 
            return false;
    }
    */

}Point;


bool operator<(const Point& p1, const Point& p2) {
    if (p1.x < p2.x)
        return true;
    else if (p1.x == p2.x)
        return p1.y < p2.y;
    else
        return false;
}

std::map<Point,int> mp; //保存点以及步数
int targetStep = 0;
std::unordered_set<int> zeroIndices;

void printMartix(int *ptr, int n);
bool cantWalk(int *ptr, int n , int x, int y);


// bool 判断矩阵是否插入了0 ,如果插入了0，需要额外判断
// x和y 从0开始 
// n 表示n * n 矩阵
int whatStep(int x, int y , bool b,int *ptr,int n)
{
    //printf("call for x=%d, y=%d\n",x,y);

    Point p;
    p.x = x;
    p.y = y;
    int step = 0;

    //先从map里查，查不到再算
    auto it = mp.find(p);
    if(it != mp.end())
        return it->second;

    if(x <= 0 && y <=0)
        return 0;
    if( (x == 0 && y ==1) || ( x == 1 && y == 0))
        return 1;
    else if (b && cantWalk(ptr,n,x,y))  //特定不能走的点
    {
        printf("x = %d, y = %d, can not walk\n",x,y);
        return 0;
    }
    else
    {
        //计算出值就存map，减少计算次数
        if(x>= 1 && y>=1)
        {
            step = whatStep(x-1,y,b,ptr,n)+whatStep(x,y-1,b,ptr,n);
            mp.insert(std::make_pair(p,step));
            return step;
        }
        else if(x >=1)
        {
            step = whatStep(x-1,y,b,ptr,n);
            mp.insert(std::make_pair(p,step));
            return step;
        }
        else {
            step = whatStep(x,y-1,b,ptr,n);
            mp.insert(std::make_pair(p,step));
            return step;
        }
    }

}
//为一个n*n的矩阵添加随机位置的0
int genMatrix(int *ptr, int n)
{
    mp.clear();
    static int counter = 0;

    while(1)
    {
        srand((unsigned)time(NULL)+(++counter));
        int x = rand()%n;
        int y = rand()%n;

        if(x == 0 && y == 0)
            continue;

        int index = n*x+y;

        if(zeroIndices.find(index) == zeroIndices.end())
        {
            *(ptr + index) = 0;
            zeroIndices.insert(index);
            break;
        }

    /*if(counter > 900 )
    {
        printf("error\n");
        exit(-1);
    }*/

    } 

    return 1;
}
//矩阵初始化为1,清空全局变量
int resetMartix(int *ptr, int n)
{
    zeroIndices.clear();
    mp.clear();

    for(int i = 0; i<n*n;++i)
    {
        *(ptr+i) = 1;
    }

    return 1;
}

//判断点x,y是否能走
bool cantWalk(int *ptr, int n , int x, int y)
{
    if( (x > (n-1)) || (y >(n-1)))
        return false;    
    else {
        //return zeroIndices.find((n-1)*y) == zeroIndices.end();
        return (*(ptr+((n)*x+y)) == 0);
    }
}

//生成和测试，直到矩阵符合要求
bool genAndTest(int *ptr, int n)
{
    int time = 0;
    int step = 0;

    resetMartix(ptr,n);

    while(1){
        ++time;
        if(time > n*n*10) //求解多少次，自己改
        {
            printf("try more than %d times , exit!\n",n*n*10);
            return false;
        }    
        
        step = whatStep(n-1,n-1,true,ptr,n);

        printf("try %d time:\n",time);
        printf("step = %d\n",step);
        printMartix(ptr,n);

        if(step == targetStep)
        {
            printf("figure out, try %d times\n",time);
            return true;
        }
        else if(step < targetStep) 
            resetMartix(ptr,n); //0插入太多，重新来一次
        else
        {
            genMatrix(ptr,n);  //继续插入0
            continue;
        }
    }

}

void printMartix(int *ptr, int n)
{
    printf("%d\n",n);

    for(int i = 0;i<(n*n);i++)
    {
        printf("%d ",*(ptr+i));
        //打印n个换行
        if(((i+1)%n) == 0)
            printf("\n");
    }
}