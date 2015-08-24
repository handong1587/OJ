#include <stdio.h>
#include <string.h>
#include <algorithm>

using namespace std;

#define MAX_N 10
char s[MAX_N];

int n, m;        // n numbers, m are different from each other
int v[MAX_N];
int rcd[MAX_N];  // record the number in each location
int used[MAX_N]; // record how many time m numbers can be used
int num[MAX_N];  // save m numbers which are different from each other

// full permutation: n! permutations, include duplications.
void init_full_permutation()
{
    for (int i=0; i<n; i++)
        num[i] = v[i];
    for (int i=0; i<n; i++)
        used[i] = 0;
}
void full_permutation(int l)
{
    if (l == n){
        for (int i=0; i<n; i++){
            printf("%d", rcd[i]);
            //if (i < n-1)
            //    printf(" ");
        }
        printf("\n"); return ;
    }
    for (int i=0; i<n; i++){
        if (!used[i]){
            used[i] = 1;
            rcd[l] = num[i];
            full_permutation(l+1);
            used[i] = 0;
        }
    }
}
// end of full permutation

// unrepeat permutation
bool cmp(int v1, int v2)
{
     return v1 < v2;
}
void init_unrepeat_permutation()
{
    for(int i=0; i<n; i++){
        int val = v[i];
        int j = 0;
        for(; j<m; j++){
            if(num[j] == val){
                used[j]++;
                break;
            }
        }
        if(j == m){
             num[m] = val;
             used[m++] = 1;
        }
    }
}
void unrepeat_permutation(int l)
{
    int i;
    if (l == n){                // finished operating n numbers, print
        for (i=0; i<n; i++){
            printf("%d", rcd[i]);
            //if (i < n-1)
            //    printf(" ");
        }
        printf("\n");
        return ;
    }
    for (i=0; i<m; i++){        // enumerate m different numbers
        if (used[i] > 0){       // if num[i] can be used, decrease used[i]
            used[i]--;
            rcd[l] = num[i];    // put this number on location l
            unrepeat_permutation(l+1); // put next location
            used[i]++;          // restore
        }
    }
}
// end of unrepeat permutation

int main()
{
    freopen("1384_full_permutation.txt", "r", stdin);
    scanf("%s",s);
    n = strlen(s);
    m = 0;

    for(int i=0; i<n; i++){
        v[i] = (int)(s[i] - '0');
    }
    sort(v, v+n, cmp);

    // full permutation
    //init_full_permutation();
    //full_permutation(0);
    // unrepeat permutation
    init_unrepeat_permutation();
    unrepeat_permutation(0);

    return 0;
}
