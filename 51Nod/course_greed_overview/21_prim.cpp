#include <stdio.h>

#define _min_(a,b) ((a)<(b)?(a):(b))
#define INF 0x3f3f3f3f

int N,M;
int W[1005][1005];
int mincost[1005];
bool used[1005];

void init()
{
    for(int i=0;i<1005;i++){
        for(int j=0;j<1005;j++){
            W[i][j]=INF;
        }
        mincost[i]=INF;
        used[i]=false;
    }
}

long long prim()
{
    long long res=0;
    mincost[1]=0;

    while(true){
         int v=-1;
         for(int u=1;u<=N;u++){
             if(!used[u] && (v==-1 || mincost[u] < mincost[v])){
                 v = u;
             }
         }
         if(v==-1){
              break;
         }
         used[v] = true;
         res += mincost[v];

         for(int u=1;u<=N;u++){
             mincost[u] = _min_(mincost[u], W[v][u]);
         }
    }

    return res;
}

int main()
{
    freopen("21_prim_case4.txt","r",stdin);
    init();
    scanf("%d %d",&N,&M);
    for(int i=0;i<M;i++){
        int s,e,w;
        scanf("%d %d %d",&s,&e,&w);
        W[s][e]=w;
        W[e][s]=w;
    }
    long long res = prim();
    printf("%lld\n",res);
    return 0;
}
