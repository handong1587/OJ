#include <stdio.h>
#include <string.h>

#define _max_(a,b) ((a)>(b)?(a):(b))
#define MAXN 10005

char a[MAXN];
char b[MAXN];
int buf_a[MAXN],buf_b[MAXN], buf_c[MAXN];
int la,lb,max_l,buf_l;
int isNega,isNegb,isNegc;
int carry[MAXN];

void preprocess()
{
    la = strlen(a);
    lb = strlen(b);
    isNega = a[0] == '-' ? 1 : 0;
    isNegb = b[0] == '-' ? 1 : 0;
    la -= isNega;
    lb -= isNegb;
    max_l = _max_(la, lb);
    buf_l = max_l + 1;

    memset(buf_a, 0, sizeof(buf_a));
    memset(buf_b, 0, sizeof(buf_b));

    for(int i=0; i<la; i++){
        buf_a[buf_l - la + i] = a[i+isNega] - '0';
    }
    buf_a[buf_l] = '\0';

    for(int i=0; i<lb; i++){
        buf_b[buf_l - lb + i] = b[i+isNegb] - '0';
    }
    buf_b[buf_l] = '\0';
}

void solve()
{
    memset(carry, 0, sizeof(carry));
    memset(buf_c, 0, sizeof(buf_c));
    buf_c[0] = 0;
    // a > 0, b > 0:
    // c = a + b + carry
    // a < 0, b < 0:
    // c = -(|a| + |b| + carry)
    if((isNega == 0 && isNegb == 0) ||
        (isNega == 1 && isNegb == 1)){
        for (int i = buf_l - 1; i >= 0; i--){
            buf_c[i] = (buf_a[i] + buf_b[i] + carry[i]) % 10;
            if (i > 0){
                carry[i - 1] = (buf_a[i] + buf_b[i] + carry[i]) / 10;
            }
        }
        isNegc = (isNega == 0 && isNegb == 0) ? 0 : 1;
    }

    // a > 0, b < 0:
    if ((isNega == 0 && isNegb == 1) ||
        (isNega == 1 && isNegb == 0)){
        int *large_n = buf_a;
        int *small_n = buf_b;
        if (la > lb){
            large_n = buf_a;
            small_n = buf_b;
            isNegc = (isNega == 0) ? 0 : 1;
        }
        else if (lb > la) {
            large_n = buf_b;
            small_n = buf_a;
            isNegc = (isNegb == 0) ? 0 : 1;
        }
        else{
            int i = 1;
            for (; i < buf_l; i++){
                if (buf_a[i]>buf_b[i]){
                    large_n = buf_a;
                    small_n = buf_b;
                    isNegc = (isNega == 0) ? 0 : 1;
                    break;
                }
                else if (buf_b[i] > buf_a[i]){
                    large_n = buf_b;
                    small_n = buf_a;
                    isNegc = (isNegb == 0) ? 0 : 1;
                    break;
                }
            }
            if (i == buf_l){
                // simply print 0
                return;
            }
        }
        for (int i = buf_l - 1; i >= 0; i--){
            buf_c[i] = ((large_n[i] + 10) - small_n[i] + carry[i]) % 10;
            if (i > 0){
                carry[i - 1] = (large_n[i] - small_n[i] + carry[i] < 0) ? -1 : 0;
            }
        }
    }
}

void print()
{
    if (isNegc == 1){
        printf("-");
    }
    bool isPrefixZero = buf_c[0] == 0 ? true : false;
    for(int i=0; i<buf_l; i++){
        if(isPrefixZero && buf_c[i] == 0){
            if (i == buf_l - 1){
                printf("0\n");
            }
            continue;
        }
        isPrefixZero = false;
        printf("%d%s", buf_c[i], i==buf_l-1? "\n":"");
    }
}

int main()
{
    freopen("1005_big_number_addition.txt","r",stdin);
    scanf("%s",a);
    scanf("%s",b);

    preprocess();
    solve();
    print();

    return 0;
}
