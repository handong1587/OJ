#include <stdio.h>
#include <algorithm>

using namespace std;

#define _min_(a,b) ((a)<(b)?(a):(b))

struct Activity
{
    int s;
    int e;
};

int N;
Activity a[10005];
int res;
int laste;

bool cmp(Activity a1, Activity a2)
{
    return a1.e < a2.e;
}

int main()
{
    freopen("14_activity_arrangement_case1.txt","r",stdin);
    scanf("%d",&N);
    laste=0x7fffffff;
    for(int i=0;i<N;i++){
        scanf("%d %d",&a[i].s,&a[i].e);
        laste=_min_(laste,a[i].s);
    }
    sort(a,a+N,cmp);
    res = 0;
    laste--;
    for(int i=0;i<N;i++){
        if(a[i].s >= laste){
            res++;
            laste = a[i].e;
        }
    }
    printf("%d\n",res);
    return 0;
}
