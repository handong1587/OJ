#include <stdio.h>
#include <string.h>

#define MAXL 1005
char a[MAXL];
char b[MAXL];
int buf_a[MAXL];
int buf_b[MAXL];
int la,lb;
int carry[MAXL * 2];
int buf_c[MAXL * 2];

void init()
{
    la = strlen(a);
    lb = strlen(b);
    for(int i=MAXL-la, j=0; i<=MAXL-1; i++, j++){
        buf_a[i] = a[j] - '0';
    }
    for(int i=MAXL-lb, j=0; i<=MAXL-1; i++, j++){
        buf_b[i] = b[j] - '0';
    }
}

void solve()
{
    for(int i=MAXL-1, m=0; i>=MAXL-la; i--, m++){
        memset(carry, 0, sizeof(carry));
        for(int j=MAXL-1, k=MAXL*2-1, n=0; j>=0; j--, n++, k--){
            int v_buf, v_carry;
            v_buf = (buf_c[k-m] + buf_a[i] * buf_b[j] + carry[k-m]) % 10;
            v_carry = (buf_c[k-m] + buf_a[i] * buf_b[j] + carry[k-m]) / 10;
            buf_c[k - m] = v_buf;
            carry[k - m - 1] = v_carry;
        }
    }
}

void print()
{
    bool isPrefixZero = true;
    for(int i=0; i<MAXL * 2; i++){
        if(isPrefixZero && buf_c[i]==0){
            if (i == MAXL* 2 - 1){
                printf("0\n");
            }
            continue;
        }
        isPrefixZero = false;
        printf("%d%s", buf_c[i], i==MAXL*2-1?"\n":"");
    }
}

int main()
{
    freopen("1027_big_number_multiply.txt", "r", stdin);
    scanf("%s",a);
    scanf("%s",b);

    init();
    solve();
    print();

    return 0;
}
