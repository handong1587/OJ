#include <stdio.h>

int T,M1,M2,A1[505],A2[505];
int L,S[505];

int main()
{
  freopen("zoj2432_Greatest_Common_Increasing_Subsequence.txt","r",stdin);

  scanf("%d\n",&T);
  for(int t=1;t<=T;t++){
    scanf("%d",&M1);
    for(int i=0;i<M1;i++){      
      scanf("%d",&A1[i]);
    }
    scanf("%d",&M2);
    for(int i=0;i<M2;i++){      
      scanf("%d",&A2[i]);
    }

    printf("%d\n",L);
    for(int i=0;i<L;i++){
      printf("%d%s",S[i],i==L-1?"\n":" ");
    }
  }

  return 0;
}
