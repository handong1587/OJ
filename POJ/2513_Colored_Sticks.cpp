#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// trie + union-set -> Euler circuit

char s1[15],s2[15];
int id1,id2;
int degree[500005];
int parent[500005]; // union-set
int cnt=1;          // to number words
int self;           // number of vertices which root is itself
int oddnum;         // number of vertices with odd digree

struct TRIE
{
    bool isword;
    int id;
    TRIE *next[27];
    TRIE()
    {
        isword=0;
        for(int i=0;i<=27;i++)
            next[i]=NULL;
    }
}root;

int hash(char *s)
{
    int len=strlen(s);
    TRIE *p=&root;
    for(int i=0;i<len;i++)
    {
        int id=s[i]-'a';
        if(!p->next[id])
            p->next[id]=new TRIE;
        p=p->next[id];
    }
    if(p->isword)
        return p->id;
    else
    {
        p->isword=1;
        p->id=cnt++;
    }
    return p->id;
}

void init()
{
    for(int i=1;i<=500005;i++)
        parent[i]=i;
}

int find(int x)
{
    return parent[x]==x?x:find(parent[x]);
}

void unite(int x,int y)
{
    x=find(x);
    y=find(y);
    if(x==y)
        return;
    parent[x]=y;
}

int main()
{
    freopen("2513_Colored Sticks.txt","r",stdin);
    memset(degree,0,sizeof(degree));
    init();
    while (scanf("%s %s",s1,s2)!=EOF)
    {
        id1=hash(s1);
        id2=hash(s2);
        degree[id1]++;
        degree[id2]++;
        unite(id1,id2);
    }
    self=oddnum=0;
    for (int i=1;i<cnt;i++)
    {
        if (degree[i]%2==1)
        {
            oddnum++;
        }
        if (find(i)==i)
        {
            self++;
        }
        if (oddnum>2||self>1)
        {
            printf("Impossible\n");
            return 0;
        }
    }
    if (oddnum==0||oddnum==2)
    {
        printf("Possible\n");
    }
    else
    {
        printf("Impossible\n");
    }
    return 0;
}
