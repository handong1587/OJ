//case: 30/100

#include <stdio.h>
#include <algorithm>

using namespace std;

const int MAX_N = 2005;
const int MAX_M = 505;
const int MAX_M2 = 505*4;
int t,T,N,M,M2;
int** crap;
char **hex_crap;
char **vis;
const int HASH_LEN = 16384;
int myhash[HASH_LEN];
int num[8];
int hashed_num[8];

const int MAX_CRAP_NUM = 10000;
int crap_num;
int merged_crap_num;
struct point
{
  int rt_x;
  int rt_y;
  int lb_x;
  int lb_y;
};

point crap_pos[MAX_CRAP_NUM];
point crap_pos_2[MAX_CRAP_NUM];
point merged_crap_pos[MAX_CRAP_NUM];

int code[10][7]={{0,0,0,1,1,0,1},
                {0,0,1,1,0,0,1},
                {0,0,1,0,0,1,1},
                {0,1,1,1,1,0,1},
                {0,1,0,0,0,1,1},
                {0,1,1,0,0,0,1},
                {0,1,0,1,1,1,1},
                {0,1,1,1,0,1,1},
                {0,1,1,0,1,1,1},
                {0,0,0,1,0,1,1}};

int hex_2_bin[16][4] = {{0,0,0,0},
                        {0,0,0,1},
                        {0,0,1,0},
                        {0,0,1,1},
                        {0,1,0,0},
                        {0,1,0,1},
                        {0,1,1,0},
                        {0,1,1,1},
                        {1,0,0,0},
                        {1,0,0,1},
                        {1,0,1,0},
                        {1,0,1,1},
                        {1,1,0,0},
                        {1,1,0,1},
                        {1,1,1,0},
                        {1,1,1,1},
                        };

bool cmp_rty(point a, point b)
{
  return a.rt_y < b.rt_y;
}


bool cmp_lby(point a, point b)
{
  return a.lb_y < b.lb_y;
}

bool cmp_lbx(point a, point b)
{
  return a.lb_x > b.lb_x;
}

void __swap__(point &p1,point &p2)
{
	point tmp;
	tmp.lb_x = p1.lb_x;
	tmp.lb_y = p1.lb_y;
	tmp.rt_x = p1.rt_x;
	tmp.rt_y = p1.rt_y;

	p1.lb_x = p2.lb_x;
	p1.lb_y = p2.lb_y;
	p1.rt_x = p2.rt_x;
	p1.rt_y = p2.rt_y;

	p2.lb_x = tmp.lb_x;
	p2.lb_y = tmp.lb_y;
	p2.rt_x = tmp.rt_x;
	p2.rt_y = tmp.rt_y;
}
void ksort(int l, int h, point *a,bool (*cmp)(point p1,point p2)){
	if (h < l + 2)
		return;
	int e = h, p = l;
	while (l < h) {
// 		while (++l < e && a[l] <= a[p]);
// 		while (--h > p && a[h] >= a[p]);
		while (++l < e && cmp(a[p],a[l]));
		while (--h > p && cmp(a[h],a[p]));
		if (l < h)
			__swap__(a[l], a[h]);
	}
	__swap__(a[h], a[p]);
	ksort(p, h, a,cmp);
	ksort(l, e, a,cmp);
}

void assign_val(point p1, point p2)
{
	p1.lb_x = p2.lb_x;
	p1.lb_y = p2.lb_y;
	p1.rt_x = p2.rt_x;
	p1.rt_y = p2.rt_y;
}

void MergeSort(point *p_crap, int l, int r, bool(*cmp)(point p1, point p2)){
	int mid, i, j, tmp;
	if (r > l + 1){
		mid = (l + r) / 2;
		MergeSort(p_crap,l, mid,cmp);
		MergeSort(p_crap,mid, r,cmp);
		tmp = l;
		for (i = l, j = mid; i < mid && j < r;){
// 			if (a[i] > a[j]){
// 				c[tmp++] = a[j++];
// 				cnt += mid - i; // 
// 			}
// 			else
// 				c[tmp++] = a[i++];
			if (cmp(p_crap[i],p_crap[j])){
				assign_val(crap_pos_2[tmp++], p_crap[j++]);
			}
			else
				assign_val(crap_pos_2[tmp++], p_crap[i++]);
		}
		if (j < r) 
			for (; j < r; ++j)
				//c[tmp++] = a[j];
				assign_val(crap_pos_2[tmp++], p_crap[j]);
		else 
			for (; i < mid; ++i)
				//c[tmp++] = a[i];
				assign_val(crap_pos_2[tmp++], p_crap[i]);
		for (i = l; i < r; ++i)
			//a[i] = c[i];
			assign_val(p_crap[i], crap_pos_2[i]);
	}
}

void __sort__(point *p_start, point *p_end, bool(*cmp)(point p1, point p2))
{
	int l = 0;
	int h = p_end - p_start;
	//ksort(l, h, p_start, cmp);
	MergeSort(p_start, l, h, cmp);
}

void write_bin_crap(char c, int *bin_crap)
{
  int idx;
  if(c>='0'&&c<='9'){
    idx=c-'0';
  }
  else if(c>='A'&&c<='F') {
    idx=c-'A'+10;
  }
  for(int i=0;i<4;i++) {
    bin_crap[i]=hex_2_bin[idx][i];
  }
}

int decode(int* exp)
{
  int c=0;
  int s=0x40;
  for(int i=0;i<7;i++){
    c |= (exp[i]==1) ? s : 0;
    s >>= 1;
  }
  //printf("decode: %d\n",c);
  return c;
}

void init()
{
  crap=new int*[MAX_N];
  hex_crap=new char*[MAX_N];
  vis=new char*[MAX_N];
  for(int i=0;i<MAX_N;i++){
    crap[i]=new int[MAX_M2];
    hex_crap[i]=new char[MAX_M];
    vis[i]=new char[MAX_M2];
  }
  for(int i=0;i<HASH_LEN;i++){
    myhash[i]=-1;
  }
  for(int i=0;i<10;i++){
    int res=decode(code[i]);
    myhash[res]=i;
  }
}

void freemem()
{
  for(int i=0;i<MAX_N;i++){
    delete []crap[i];
    delete []hex_crap[i];
    delete []vis[i];
  }
  delete []crap;
  delete []hex_crap;
  delete []vis;
}

void init_2()
{
	crap_num = merged_crap_num = 0;
	for(int i=0;i<MAX_N;i++){
		for (int j = 0; j < MAX_M; j++){
			crap[i][j] = 0;
			vis[i][j] = 0;
		}
	}
	//memset(crap,0,sizeof(crap));
	//memset(num,0,sizeof(int)*8);
	for(int i=0; i<8; i++){
		num[i] = 0;
		hashed_num[i] = 0;
	}
}
void test_plot()
{
  printf("N = %d,M = %d\n",N,M);
  for(int i=0;i<N;i++){
    for(int j=0;j<M*4;j++){
      printf("%d",crap[i][j]);
      if(j==M*4-1)
        printf("\n");
    }
  }
}

void test_plot_hex(int lbx,int lby,int rtx,int rty)
{
	printf("N = %d,M = %d\n", N, M);
	for (int i = rty; i < lby; i++){
		for (int j = lbx; j <= rtx; j++){
			printf("%c", hex_crap[i][j]);
			if (j == rtx)
				printf("\n");
		}
	}
}
// multi-crap
// thicker-crap
// dfs find all possible blocks, then merge

void mark_vis(int rt_x, int rt_y,int lb_x, int lb_y)
{
  for(int i=rt_y; i<lb_y; i++){
    for(int j=lb_x; j<=rt_x; j++){
      vis[i][j]=1;
    }
  }
}

int locate_crap()
{
	crap_num = 0;
	for (int i = 0; i < N; i++){
		for (int j = M2 - 1; j >= 0; j--){
			if (vis[i][j] == 1)
				continue;
			if (crap[i][j] == 1){
				int rt_x = j, rt_y = i;
				int lb_x = rt_x, lb_y = rt_y;
				for (int k = rt_x - 1; k >= 0; k--){
					if (crap[rt_y][k] == 0 || vis[rt_y][k] == 1)
						break;
					lb_x = k;
				}
				for (int k = rt_y + 1; k < N; k++){
					if (crap[k][rt_x] == 0 || vis[k][rt_x] == 1)
						break;
					lb_y = k;
				}
				if (lb_y - rt_y >= 5 && lb_y - rt_y <= 100){
					mark_vis(rt_x, rt_y, lb_x, lb_y);

					crap_pos[crap_num].rt_x = rt_x;
					crap_pos[crap_num].rt_y = rt_y;
					crap_pos[crap_num].lb_x = lb_x;
					crap_pos[crap_num].lb_y = lb_y;
					crap_num++;
				}
			}
		}
	}
	return crap_num;
}

void merge_crap()
{
	if (crap_num == 0)
	{
		return;
	}

// 	sort(crap_pos, crap_pos + crap_num, cmp_lbx);
// 	sort(crap_pos, crap_pos + crap_num, cmp_lby);
// 	sort(crap_pos, crap_pos + crap_num, cmp_rty);

	__sort__(crap_pos, crap_pos + crap_num, cmp_lbx);
	__sort__(crap_pos, crap_pos + crap_num, cmp_lby);
	__sort__(crap_pos, crap_pos + crap_num, cmp_rty);  

	merged_crap_num=0;
	merged_crap_pos[merged_crap_num].rt_x = crap_pos[0].rt_x;
	merged_crap_pos[merged_crap_num].rt_y = crap_pos[0].rt_y;
	merged_crap_pos[merged_crap_num].lb_x = crap_pos[0].lb_x;
	merged_crap_pos[merged_crap_num].lb_y = crap_pos[0].lb_y;
	merged_crap_num++;
	for (int i = 1; i <crap_num;i++)
	{
		if (crap_pos[i].rt_y==merged_crap_pos[merged_crap_num-1].rt_y
			&& crap_pos[i].lb_y==merged_crap_pos[merged_crap_num-1].lb_y)
		{
			if (merged_crap_pos[merged_crap_num-1].lb_x-crap_pos[i].rt_x - 1<=15)
			{
				merged_crap_pos[merged_crap_num-1].lb_x = crap_pos[i].lb_x;
			}
			else
			{
				merged_crap_num++;
				merged_crap_pos[merged_crap_num-1].rt_x = crap_pos[i].rt_x;
				merged_crap_pos[merged_crap_num-1].rt_y = crap_pos[i].rt_y;
				merged_crap_pos[merged_crap_num-1].lb_x = crap_pos[i].lb_x;
				merged_crap_pos[merged_crap_num-1].lb_y = crap_pos[i].lb_y;
			}
		}
		else
		{
			merged_crap_num++;
			merged_crap_pos[merged_crap_num-1].rt_x = crap_pos[i].rt_x;
			merged_crap_pos[merged_crap_num-1].rt_y = crap_pos[i].rt_y;
			merged_crap_pos[merged_crap_num-1].lb_x = crap_pos[i].lb_x;
			merged_crap_pos[merged_crap_num-1].lb_y = crap_pos[i].lb_y;
		}
	}

	for (int i = 0; i < merged_crap_num;i++)
	{
		test_plot_hex(merged_crap_pos[i].lb_x/4,
			merged_crap_pos[i].lb_y,
			merged_crap_pos[i].rt_x/4,
			merged_crap_pos[i].rt_y);
		printf("\n");
	}
}

int choose(int w)
{
	if (w < 56)
		return 56;
	else if (w<112)
	{
		return 112;
	}
	else if (w<168)
	{
		return 168;
	}
	else if (w<224)
	{
		return 224;
	}
	return 0;
}

void align_crap()
{
	int possible[4] = { 56, 112, 168, 224 };
	for (int i = 0; i<merged_crap_num; i++) {
		int w = merged_crap_pos[i].rt_x - merged_crap_pos[i].lb_x + 1;
		if (w % 56 != 0)
		{
			if (w>224)
			{
				return;
			}
			int right_w = choose(w);
			int diff = right_w - (w%right_w);
			if (i == 0)
			{
				if (merged_crap_pos[i].lb_x - diff < 0)
				{
					return;
				}
			}
			else
			{
				if (merged_crap_pos[i].lb_x - diff < merged_crap_pos[i - 1].rt_x)
				{
					return;
				}
			}
			merged_crap_pos[i].lb_x -= diff;
		}
	}
}

int verify(int n[8])
{
  int odd,even,verfiy_code;
  odd =myhash[n[0]]+myhash[n[2]]+myhash[n[4]]+myhash[n[6]];
  even=myhash[n[1]]+myhash[n[3]]+myhash[n[5]];
  verfiy_code=myhash[n[7]];
  int sum=odd*3+even+verfiy_code;
  printf("sum=%d\n",sum);
  if(sum%10==0)
    return 1;
  else
    return 0;
}

int solve()
{
  int res=0;
  for(int i=0;i<merged_crap_num;i++) {
    int w=merged_crap_pos[i].rt_x-merged_crap_pos[i].lb_x+1;

    if(w%56==0) {
      int mul=w/56; 
      //printf("mul = %d\n",mul);
      int tmp_crap[56];
      for(int j=merged_crap_pos[i].lb_x, k=0;j<=merged_crap_pos[i].rt_x;j+=mul,k++) {
        tmp_crap[k]=crap[merged_crap_pos[i].rt_y][j];
      }
      int sum=0;
      for(int j=0;j<8;j++) {
        num[j]=decode(tmp_crap+j*7);
        //printf("num[%d] = %d\n",j,num[j]);        
		hashed_num[j] = myhash[num[j]];
		printf("num[%d] = %d, hashed_num[%d] = %d\n", j, num[j],j, hashed_num[j]);
		if (hashed_num[j] < 0)
			return 0;
        sum+=hashed_num[j];
      }
	  if (verify(num) == 0)
	  {
		  return 0;
	  }        

      //printf("sum = %d\n",sum);

      res+=sum;
    }  
  }
  return res;
}

int main()
{
  freopen("crytographic_code.txt","r",stdin);

  init();
  scanf("%d\n",&T);
  for(t=0; t<T; t++) {
    scanf("%d%d\n",&N,&M);
	printf("%d %d\n", N, M);
	M2 = M * 4;
    init_2();

    char c;
    for(int n=0; n<N; n++) {
      for(int m=0; m<M; m++) {
        scanf("%c",&c);
        hex_crap[n][m]=c;
        write_bin_crap(c,crap[n]+m*4);
      }
      scanf("\n");
    }

    locate_crap();
    merge_crap();
    align_crap();
    int res=solve(); 
    //printf("#%d %d\n",t+1,res);
	printf("#%d %d\n\n", t + 1, res);
  }
  freemem();
  
  return 0;
}
