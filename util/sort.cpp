#include <stdio.h>

// quick sort
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
    return 0;
}
