#include <stdio.h>
#include <algorithm>

using namespace std;

int N,M;
int w[10005];

bool cmp(int a,int b)
{
    return a<b;
}

int main()
{
    freopen("22_canoe_problem.txt","r",stdin);
    scanf("%d %d",&N,&M);
    for(int i=0;i<N;i++){
        scanf("%d",&w[i]);
    }
    sort(w,w+N,cmp);
    int w_s = 0; // small weight
    int w_l = N-1; //large weight
    int nc = 0; //number of canoe
    while(w_s <= w_l) {
        if(w_s == w_l){
            nc++;
            break;
        }
        if (w[w_l] + w[w_s] <= M){
             w_s++;
             w_l--;
        } else {
            w_l--;
        }
        nc++;
    }
    printf("%d\n",nc);
    return 0;
}
