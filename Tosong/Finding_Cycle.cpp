#include <stdio.h>

// doesn't verify correctness

#define MAX_N 105
int M, N;
int T;

bool marked[MAX_N];
bool onStack[MAX_N];
int edgeTo[MAX_N];
bool hasCycle;
int cycle[MAX_N];
int cycleLen;

int adj[MAX_N][MAX_N];
int adjlen[MAX_N];

// sort
void _swap_(int& a, int& b)
{
    int t = a;
    a = b;
    b = t;
}

void ksort(int l, int h, int a[]){
    if (h < l + 2)
        return;
    int e = h, p = l;
    while (l < h) {
        while (++l < e && a[l] <= a[p]);
        while (--h > p && a[h] >= a[p]);
        if (l < h)
            _swap_(a[l], a[h]);
    }
    _swap_(a[h], a[p]);
    ksort(p, h, a);
    ksort(l, e, a);
}
// end of sort

void init()
{
    for (int i = 0; i < MAX_N; i++){
        adjlen[i] = 0;
        for (int j = 0; j < MAX_N; j++){
            adj[i][j] = 0;
        }

        marked[i] = false;
        onStack[i] = false;
    }
    hasCycle = false;
    cycleLen = 0;
}

void dfs(int v)
{
    onStack[v] = true;
    marked[v] = true;
    for (int i = 0; i < adjlen[v]; i++){
        if(cycleLen > 0){
            return;
        }

        int w = adj[v][i];
        if (!marked[w]){
            edgeTo[w] = v;
            dfs(w);
        }
        else if (onStack[w]){
            for(int x=v; x!=w; x=edgeTo[x]){
                cycle[cycleLen++] = x;
            }
            cycle[cycleLen++] = w;
            //cycle[cycleLen++] = v;
        }
    }
    onStack[v] = false;
}

void solve()
{
    for (int v = 1; v <= N; v++){
        if (!marked[v]){
            dfs(v);
        }
    }
}

int main()
{
    freopen("Finding_Cycle.txt", "r", stdin);
    //freopen("Finding_Cycle_case2.txt", "r", stdin);

    scanf("%d",&T);
    for (int t = 1; t <= T;t++){
        init();

        scanf("%d %d", &N, &M);
        for (int i = 0; i < M;i++){
            int v1, v2;
            scanf("%d %d", &v1, &v2);
            adj[v1][adjlen[v1]++] = v2;
        }

        solve();
        ksort(0, cycleLen, cycle);

        if (cycleLen == 0){
            printf("#%d 0\n", t);
        }
        else{
            printf("#%d ", t);
            for (int i = 0; i < cycleLen; i++){
                printf("%d%s", cycle[i], i == cycleLen - 1 ? "\n" : " ");
            }
        }
    }

    return 0;
}
