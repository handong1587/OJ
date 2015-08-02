#include <stdio.h>
#include <algorithm>

using namespace std;

#define _min_(a,b) ((a)<(b)?(a):(b))
#define _max_(a,b) ((a)>(b)?(a):(b))

struct Activity
{
    int s;
    int e;
};

int N;
Activity a1[10005], a2[10005];

bool cmp_s(Activity a1, Activity a2)
{
    return a1.s < a2.s;
}

bool cmp_e(Activity a1, Activity a2)
{
    return a1.e < a2.e;
}

int maxa;

int main()
{
    freopen("21_activity_arrangement_II_case3.txt","r",stdin);
    scanf("%d",&N);
    for(int i=0;i<N;i++){
        int tmps,tmpe;
        scanf("%d %d",&tmps,&tmpe);
        a1[i].s = tmps, a2[i].s = tmps;
        a1[i].e = tmpe, a2[i].e = tmpe;
    }
    sort(a1, a1+N, cmp_s);
    sort(a2, a2+N, cmp_e);

    int cur_s, cur_s_pos, cur_e, cur_e_pos;
    cur_s_pos = cur_e_pos = 0;
    cur_s = a1[cur_s_pos].s;
    cur_e = a2[cur_e_pos].e;

    int num_overlap = 0;
    for(int i=0;;i++){
        if(cur_s_pos < N){
            cur_s = a1[cur_s_pos].s;
        }
        if(cur_e_pos < N){
            cur_e = a2[cur_e_pos].e;
        }

        if(cur_s < cur_e){
            num_overlap++;
            cur_s_pos++;
        } else{
            num_overlap--;
            cur_e_pos++;
        }
        maxa = _max_(maxa,num_overlap);
        if(cur_s_pos >= N){
            break;
        }
    }
    printf("%d\n",maxa);
    return 0;
}
