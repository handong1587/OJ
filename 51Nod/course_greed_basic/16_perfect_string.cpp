#include <stdio.h>
#include <string.h>

char s[10005];
int a[26];
int res;

void _swap_(int& a, int& b)
{
    int t = a;
    a = b;
    b = t;
}

void ksort(int l, int h, int a[])
{
    if(h < l + 2)
        return;
    int e = h, p = l;
    while(l < h) {
        while(++l < e && a[l] <= a[p]);
        while(--h > p && a[h] >= a[p]);
        if(l < h)
            _swap_(a[l], a[h]);
    }
    _swap_(a[h], a[p]);
    ksort(p, h, a);
    ksort(l, e, a);
}

int main()
{
    freopen("16_perfect_string.txt","r",stdin);
    scanf("%s",s);
    int l=strlen(s);
    for(int i=0;i<l;i++){
        int c;
        if(s[i]>='a' && s[i]<='z'){
            c=s[i]-'a';
        }
        else if(s[i]>='A' && s[i]<='Z'){
            c=s[i]-'A';
        }
        a[c]++;
    }
    ksort(0, 26, a);
    for(int p=0;p<26;p++){
         res += a[p] * (p+1);
    }
    printf("%d\n",res);
    return 0;
}
