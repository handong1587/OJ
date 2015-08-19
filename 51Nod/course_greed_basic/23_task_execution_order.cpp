#include <stdio.h>
#include <algorithm>

using namespace std;

#define _abs_(a) ((a)<0?-(a):(a))
#define _max_(a,b) ((a)>(b)?(a):(b))

int N;
struct Task
{
    int r;
    int o;
    int b;
};
Task t[100005];

bool cmp(Task t1, Task t2)
{
    if(t1.b == t2.b){
        return t1.r > t2.r;
    }
    return t1.b > t2.b;
}

int main()
{
    //freopen("23_task_execution_order.txt","r",stdin);
    freopen("23_task_execution_order_case4.txt","r",stdin);
    scanf("%d",&N);
    for(int i=0; i < N; i++){
        scanf("%d %d",&t[i].r,&t[i].o);
        t[i].b = t[i].r - t[i].o;
    }
    sort(t, t+N, cmp);
    int execMem = 0;
    int lastMem = 0;
    for (int i = 0; i < N; ++i) {
         execMem = std::max(lastMem+t[i].r, execMem);
         lastMem += t[i].o;
    }
    printf("%d\n", execMem);
    return 0;
}
