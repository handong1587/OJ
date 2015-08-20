#include <stdio.h>
#include <queue>
#include <vector>

using namespace std;

int N;
int L[50005];
std::priority_queue<int, vector<int>, greater<int> > q;

int main()
{
    freopen("19_huffman.txt","r",stdin);
    scanf("%d",&N);
    for(int i=0;i<N;i++){
        scanf("%d",&L[i]);
        q.push(L[i]);
    }
    int res=0;
    while(q.size() >= 2){
        int v1 = q.top();
        q.pop();
        int v2 = q.top();
        q.pop();
        int v = v1 + v2;
        q.push(v);

        res += v;
    }
    printf("%d\n",res);
    return 0;
}
