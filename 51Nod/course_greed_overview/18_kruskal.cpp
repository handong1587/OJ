#include <stdio.h>
#include <algorithm>

using namespace std;

#define _min_(a,b) ((a)<(b)?(a):(b))
#define INF 0x3f3f3f3f
#define MAX_N 1005
#define MAX_E 50005

struct edge
{
    int u;
    int v;
    int cost;
};

edge es[MAX_E];

int N,M;
int W[MAX_N][MAX_N];
int mincost[MAX_N];
bool used[MAX_N];

bool cmp(edge e1, edge e2)
{
    return e1.cost < e2.cost;
}

// union-find set
int par[MAX_N];
int rank[MAX_N];
void init_inion_find(int n)
{
    for(int i=0;i<n;i++){
        par[i]=i;
        rank[i]=0;
    }
}
int find(int x)
{
    if(par[x]==x){
        return x;
    }else{
        return par[x]=find(par[x]);
    }
}
void unite(int x,int y)
{
     x=find(x);
     y=find(y);
     if(x==y){
         return;
     }
     if(rank[x]<rank[y]){
         par[x]=y;
     }else{
          par[y]=x;
          if(rank[x]==rank[y]){
              rank[x]++;
          }
     }
}
bool same(int x, int y)
{
     return find(x)==find(y);
}
// end of union-find set

void init()
{
    for(int i=0;i<MAX_N;i++){
        for(int j=0;j<MAX_N;j++){
            W[i][j]=INF;
        }
        mincost[i]=INF;
        used[i]=false;
    }
}

long long kruskal()
{
    long long res=0;
    for(int i=0;i<M;i++){
        edge e=es[i];
        if(!same(e.u, e.v)){
            unite(e.u, e.v);
            res += e.cost;
        }
    }
    return res;
}

int main()
{
    freopen("18_kruskal.txt","r",stdin);
    init();
    scanf("%d %d",&N,&M);
    for(int i=0;i<M;i++){
        int u,v,cost;
        scanf("%d %d %d",&u,&v,&cost);
        es[i].u = u-1;
        es[i].v = v-1;
        es[i].cost = cost;
    }
    sort(es,es+M,cmp);

    init_inion_find(N);

    long long res = kruskal();
    printf("%lld\n",res);
    return 0;
}
