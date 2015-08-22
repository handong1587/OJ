#include <iostream>
#include <stdio.h>
#include <string.h>

using namespace std;

// copy from internet

#define MAX_N 400000

struct QueStruct
{
    char op;
    int num, id, pre;
};
QueStruct que[MAX_N];
int head, tail;
int fac[9] = { 1, 1, 2, 6, 24, 120, 720, 5040, 40320 };
int Pow[9] = { 100000000, 10000000, 1000000, 100000, 10000, 1000, 100, 10, 1 };
int vis[MAX_N];

int p_hash(int num) //calculate inverse number of each permutation using Cantor expansion
{
    int i, j, n[10];
    for (i = 0; i < 9; i++)
    {
        n[i] = num % 10;
        num /= 10;
    }
    int key = 0;
    for (i = 0; i < 9; i++)
    {
        int cnt = 0;
        for (j = 0; j < i; j++)
        {
            if (n[i] > n[j])
                cnt++;
        }
        key += cnt * fac[i];
    }
    return key;
}

void exchange(int num, int a, int b, char op)  // exchange ath number and bth number
{
    int n1, n2;
    n1 = num / Pow[a] % 10;
    n2 = num / Pow[b] % 10;
    num = num - (n1 - n2)*Pow[a] + (n1 - n2)*Pow[b];
    int key = p_hash(num);
    if (!vis[key])
    {
        vis[key] = 1;
        que[tail].op = op;
        que[tail].num = num;
        que[tail].pre = head;
        que[tail++].id = b;
    }
}

void output(int k)
{
    if (que[k].op != 0)
    {
        output(que[k].pre);
        cout << que[k].op;
    }
}

int main()
{
    int i, num, id, t;
    char c;
    freopen("1077_Eight.txt", "r", stdin);
    for (num = i = 0; i < 9; i++)
    {
        cin >> c;
        if (c == 'x')
        {
            t = 9;
            id = i;
        }
        else
        {
            t = c - '0';
        }
        num = 10 * num + t;
    }
    memset(vis, 0, sizeof(vis)); //
    vis[p_hash(num)] = 1; //

    bool flag = false;
    head = 0, tail = 1;
    que[0].id = id;
    que[0].num = num;
    while (tail > head && !flag)
    {
        int cnt = tail - head;
        while (cnt--)
        {
            num = que[head].num;
            if (num == 123456789)
            {
                flag = true;
                break;
            }
            id = que[head].id;
            if (id % 3 != 2)
                exchange(num, id, id + 1, 'r');
            if (id % 3 != 0)
                exchange(num, id, id - 1, 'l');
            if (id > 2)
                exchange(num, id, id - 3, 'u');
            if (id < 6)
                exchange(num, id, id + 3, 'd');
            head++;
        }
    }
    if (flag)
        output(head);
    else
        cout << "unsolvable";
    cout << endl;
    return 0;
}
