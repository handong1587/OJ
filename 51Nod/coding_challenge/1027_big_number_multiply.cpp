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
{}

int main()
{
    freopen("1027_big_number_multiply.txt", "r", stdin);
    scanf("%s",a);
    scanf("%s",b);
    return 0;
}
