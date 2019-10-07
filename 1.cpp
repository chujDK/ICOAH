#include<cstdio>
#include<queue>
#include<cstring>

struct EDGE
{
	int to,dis,nxt;
}edge[5010],edge_p[5010];

void _add(int from,int to,int dis)
{
	edge[++num_edge].dis=dis;
	edge[num_edge].nxt=head[from];
	edge[num_edge].to=to;
	head[from]=num_edge;
}

int f[1001],head[1001];
int l,p,num_edge,u,v,d;
double left,right,mid,ans;

bool spfa(double )

int main()
{
	scanf("%d%d",&l,&p);
	for(int i=1;i<=l;i++) scanf("%d",&f[i]);
	for(int i=0;i<p;i++) 
	{
		scanf("%d%d%d",&u,&v,&d);
		_add(u,v,d);
	}
	while(right-left>=0.001)
	{
		mid=(right+left)/2.0
		if(spfa(mid)) ans=mid,left=mid+0.001;
		else right=mid-0.001;
	}
}
