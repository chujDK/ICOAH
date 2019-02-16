/*
 *powered by cj
 *烷烃的同分异构计数
 *基于动态规划
 *感谢UOJ FlashHu 的高精度重载 性能非常
 *2019/01/12-2019/01/13
 */
#include<cassert>
#include<cctype>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<iostream>
using std::cin;
using std::cout;
using std::endl;
namespace BigNum
{
#define RG register
#define UI unsigned int
#define UL unsigned long long
#define FR(op,re) inline friend re operator op(RG bign a,RG bign b)
#define OP(op,re,tp) inline re operator op(RG tp a)
#define ON(op,re) inline re operator op()
#define EQ(op,tp) OP(op,bign&,tp)
#define clear memset(n,0,SIZE)
#define bitop(op,eq)							\
	FR(op,bign)									\
	{											\
		for(RG UI i=0;i<LEN;++i)				\
			a.n[i]eq b.n[i];					\
		return a;								\
	}											\
	EQ(eq,bign){								\
		for(RG UI i=0;i<LEN;++i)				\
			n[i]eq a.n[i];						\
		return*this;							\
	}
#define logop(op,re) FR(op,bool)				\
	{											\
		for(RG UI i=LEN-1;i;--i)				\
			if(a.n[i]!=b.n[i])return re;		\
		return a.n[0]op b.n[0];					\
	}

	const int LEN=12,SIZE=LEN<<3;//LEN is decided by yourself

	struct bign
	{
		UL n[LEN];

		//initializations
		EQ(=,UL)
		{
			clear;
			n[0]=a;
			return*this;
		}
		EQ(=,const char*)
		{
			clear;
			while(isdigit(*a))
				*this=(*this<<3)+(*this<<1)+(*a++&15);
			return*this;
		}
		template<typename TP>
		inline bign(RG TP a)
		{
			*this=a;
		}
		inline bign()
		{
			clear;
		}

		//bit operations
		ON(~,bign)
		{
			RG bign ret;
			for(RG UI i=0; i<LEN; ++i)
				ret.n[i]=~n[i];
			return ret;
		}
		OP(<<,bign,UI)
		{
			RG bign ret;
			if(a>=SIZE<<3)return ret;
			RG UI i,d=a>>6,l=a&63;
			if(l)
			{
				RG UI r=64-l;
				for(i=LEN-d-1; i; --i)
					ret.n[i+d]=n[i]<<l|n[i-1]>>r;
				ret.n[d]=n[0]<<l;
				return ret;
			}
			for(i=LEN-d-1; ~i; --i)ret.n[i+d]=n[i];
			return ret;
		}
		EQ(<<=,UI)
		{
			if(a>=SIZE<<3)
			{
				clear;
				return*this;
			}
			RG UI i,d=a>>6,l=a&63;
			if(l)
			{
				RG UI r=64-l;
				for(i=LEN-d-1; i; --i)
					n[i+d]=n[i]<<l|n[i-1]>>r;
				n[d]=n[0]<<l;
			}
			else for(i=LEN-d-1; ~i; --i)n[i+d]=n[i];
			for(i=d-1; ~i; --i)n[i]=0;
			return*this;
		}
		OP(>>,bign,UI)
		{
			RG bign ret;
			if(a>=SIZE<<3)return ret;
			RG UI i,d=a>>6,r=a&63;
			if(r)
			{
				RG UI l=64-r;
				for(i=d; i<LEN-1; ++i)
					ret.n[i-d]=n[i]>>r|n[i+1]<<l;
				ret.n[i-d]=n[i]>>r;
				return ret;
			}
			for(i=d; i<LEN; ++i)ret.n[i-d]=n[i];
			return ret;
		}
		EQ(>>=,UI)
		{
			if(a>=SIZE<<3)
			{
				clear;
				return*this;
			}
			RG UI i,d=a>>6,r=a&63;
			if(r)
			{
				RG UI l=64-r;
				for(i=d; i<LEN-1; ++i)
					n[i-d]=n[i]>>r|n[i+1]<<l;
				n[i-d]=n[i]>>r;
			}
			else for(i=d; i<LEN; ++i)n[i-d]=n[i];
			for(i=LEN-d; i<LEN; ++i)n[i]=0;
			return*this;
		}
		bitop(&,&=);
		bitop(^,^=);
		bitop(|,|=);

		//logic operations
		logop(<,a.n[i]<b.n[i]);
		logop(>,a.n[i]>b.n[i]);
		logop(<=,a.n[i]<b.n[i]);
		logop(>=,a.n[i]>b.n[i]);
		logop(==,0);
		logop(!=,1);
		ON(!,bool)
		{
			for(RG UI i=0; i<LEN; ++i)
				if(n[i])return 0;
			return 1;
		}
		FR(&&,bool)
		{
			return !!a&&!!b;
		}
		FR(||,bool)
		{
			return !!a||!!b;
		}

		//arithmetic operation
		ON(++,bign&)
		{
			for(RG UI i=0; !++n[i]&&i<LEN; ++i);
			return*this;
		}
		ON(--,bign&)
		{
			for(RG UI i=0; !n[i]--&&i<LEN; ++i);
			return*this;
		}
		FR(+,bign)
		{
			RG bool car=0;
			for(RG UI i=0; i<LEN; ++i)
			{
				a.n[i]+=b.n[i]+car;
				car=car?a.n[i]<=b.n[i]:a.n[i]<b.n[i];
			}
			return a;
		}
		EQ(+=,bign)
		{
			RG bool car=0;
			for(RG UI i=0; i<LEN; ++i)
			{
				n[i]+=a.n[i]+car;
				car=car?n[i]<=a.n[i]:n[i]<a.n[i];
			}
			return*this;
		}
		FR(-,bign)
		{
			RG bool bor=0;
			RG UL lst;
			for(RG UI i=0; i<LEN; ++i)
			{
				lst=a.n[i];
				a.n[i]-=b.n[i]+bor;
				bor=bor?lst<=a.n[i]:lst<a.n[i];
			}
			return a;
		}
		EQ(-=,bign)
		{
			RG bool bor=0;
			RG UL lst;
			for(RG UI i=0; i<LEN; ++i)
			{
				lst=n[i];
				n[i]-=a.n[i]+bor;
				bor=bor?lst<=n[i]:lst<n[i];
			}
			return*this;
		}
		FR(*,bign)
		{
			RG bign ret;
			RG UI*p=(UI*)&a,*q=(UI*)&b,i,j,k;
			RG UL*r=ret.n,mul;
			for(i=(LEN-1)<<1,k=0; k<i; ++k,r=(UL*)((UI*)r+1))
				for(j=k; ~j; --j)
				{
					mul=(UL)p[j]*q[k-j];
					if((*r+=mul)<mul)++*(r+1);
				}
			for(j=k; ~j; --j)
				*r+=(UL)p[j]*q[k-j];
			for(j=++k; ~j; --j)
				*(UI*)(r+1)+=p[j]*q[k-j];
			return ret;
		}
		EQ(*=,bign)
		{
			RG bign b=*this;
			RG UI*p=(UI*)&a,*q=(UI*)&b,i,j,k;
			RG UL*r=n,mul;
			clear;
			for(i=(LEN-1)<<1,k=0; k<i; ++k,r=(UL*)((UI*)r+1))
				for(j=k; ~j; --j)
				{
					mul=(UL)p[j]*q[k-j];
					if((*r+=mul)<mul)++*(r+1);
				}
			for(j=k; ~j; --j)
				*r+=(UL)p[j]*q[k-j];
			for(j=++k; ~j; --j)
				*(UI*)(r+1)+=p[j]*q[k-j];
			return*this;
		}
		FR(/,bign)
		{
			assert(!!b);
			if(a<b)return 0;
			RG bign cur,ret;
			RG UI i,j,e;
			RG UL t;
			for(i=LEN-1; !a.n[i]; --i);
			for(j=i<<6,t=a.n[i]>>1;
			        t;
			        ++j,t>>=1);
			for(i=LEN-1; !b.n[i]; --i);
			for(e=i<<6,t=b.n[i]>>1;
			        t;
			        ++e,t>>=1);
			for(j-=e; ~j; --j)
				if(a>=(cur=b<<j))
					ret.n[j>>6]|=1ull<<j,a-=cur;
			return ret;
		}
		EQ(/=,bign)
		{
			assert(!!a);
			if(*this<a)
			{
				clear;
				return*this;
			}
			RG bign b=*this,cur;
			RG UI i,j,e;
			RG UL t;
			for(i=LEN-1; !n[i]; --i);
			for(j=i<<6,t=n[i]>>1;
			        t;
			        ++j,t>>=1);
			for(i=LEN-1; !a.n[i]; --i);
			for(e=i<<6,t=a.n[i]>>1;
			        t;
			        ++e,t>>=1);
			clear;
			for(j-=e; ~j; --j)
				if(b>=(cur=a<<j))
					n[j>>6]|=1ull<<j,b-=cur;
			return*this;
		}
		FR(%,bign)
		{
			assert(!!b);
			if(a<b)return a;
			RG bign cur;
			RG UI i,j,e;
			RG UL t;
			for(i=LEN-1; !a.n[i]; --i);
			for(j=i<<6,t=a.n[i]>>1;
			        t;
			        ++j,t>>=1);
			for(i=LEN-1; !b.n[i]; --i);
			for(e=i<<6,t=b.n[i]>>1;
			        t;
			        ++e,t>>=1);
			for(j-=e; ~j; --j)
				if(a>=(cur=b<<j))a-=cur;
			return a;
		}
		EQ(%=,bign)
		{
			assert(!!a);
			if(*this<a)return*this;
			RG bign cur;
			RG UI i,j,e;
			RG UL t;
			for(i=LEN-1; !a.n[i]; --i);
			for(e=i<<6,t=a.n[i]>>1;
			        t;
			        ++e,t>>=1);
			for(i=LEN-1; !n[i]; --i);
			for(j=i<<6,t=n[i]>>1;
			        t;
			        ++j,t>>=1);
			for(j-=e; ~j; --j)
				if(*this>=(cur=a<<j))*this-=cur;
			return*this;
		}
		OP(/,bign,UL)
		{
			assert(a);
			RG char*p=(char*)&a;
			RG UI d;
			for(d=7; !p[d]; --d);
			if(!(d=7-d))return*this/(bign)a;
			RG bign b=*this,ret;
			RG UL*cur;
			RG char*r=(char*)&ret;
			p=(char*)&b;
			for(RG int i=SIZE-8; i>0; i-=d)
				*(UL*)(r+i)|=*(cur=(UL*)(p+i))/a,*cur%=a;
			*(UL*)r|=*(UL*)p/a;
			return ret;
		}
		OP(/=,bign&,UL)
		{
			assert(a);
			RG char*p=(char*)&a;
			RG UI d;
			for(d=7; !p[d]; --d);
			if(!(d=7-d))return*this/=(bign)a;
			RG bign b=*this;
			RG UL*cur;
			RG char*r=(char*)this;
			p=(char*)&b;
			clear;
			for(RG int i=SIZE-8; i>0; i-=d)
				*(UL*)(r+i)|=*(cur=(UL*)(p+i))/a,*cur%=a;
			*(UL*)r|=*(UL*)p/a;
			return *this;
		}
		OP(%,bign,UL)
		{
			assert(a);
			RG char*p=(char*)&a;
			RG UI d;
			for(d=7; !p[d]; --d);
			if(!(d=7-d))return*this%(bign)a;
			RG bign ret=*this;
			p=(char*)&ret;
			for(RG int i=SIZE-8; i>0; i-=d)
				*(UL*)(p+i)%=a;
			*(UL*)p%=a;
			return ret;
		}
		OP(%=,bign&,UL)
		{
			assert(a);
			RG char*p=(char*)&a;
			RG UI d;
			for(d=7; !p[d]; --d);
			if(!(d=7-d))return*this%=(bign)a;
			p=(char*)this;
			for(RG int i=SIZE-8; i>0; i-=d)
				*(UL*)(p+i)%=a;
			*(UL*)p%=a;
			return*this;
		}
		friend inline std::istream&operator>>(RG std::istream&in,RG bign&a)
		{
			RG char s[LEN*20];
			in>>s;
			a=s;
			return in;
		}
		friend inline std::ostream&operator<<(RG std::ostream&ou,RG bign a)
		{
			RG char s[LEN*20],*p=s+LEN*20-1;
			*p='\0';
			RG bign b;
			RG int i,j;
			RG UL*cur;
			RG char*q=(char*)&a,*r=(char*)&b,*t;
			for(i=SIZE-1; !q[i]; --i);
			while(i>7)
			{
				for(j=i-7; j>0; j-=7)
					*(UL*)(r+j)|=*(cur=(UL*)(q+j))/10,*cur%=10;
				*(UL*)r|=*(cur=(UL*)q)/10;
				*--p=*cur%10+'0';
				*cur=0;
				t=q;
				q=r;
				r=t;
				while(!q[i])--i;
			}
			return ou<<*(UL*)q<<p;
		}
	};
}

BigNum::bign f[10001][5];
BigNum::bign ans,sum_of_tree;//sum_of_tree为当前各子树总和
int Num_Of_Carbonium;//碳的数量
const int degree=4;

inline BigNum::bign C(BigNum::bign n,int m)//计算组合数
{
	BigNum::bign ret=n;
	for(int i=m; i>1; i--) ret*=--n;
	for(int i=m; i>1; i--) ret/=i;
	return ret;
}

int main()
{
	f[1][0]=1;
	scanf("%d",&Num_Of_Carbonium);
	for(int size=1; size<(Num_Of_Carbonium+1)>>1; size++)
	{
		int j=0;
		for(sum_of_tree=j; j<degree; j++)
			sum_of_tree+=f[size][j];
		for(int i=Num_Of_Carbonium; i>size; i--)
			for(int j=1; j<=degree; j++)
				for(int k=1; k<=j&&k*size<i; k++)
					f[i][j]+=f[i-k*size][j-k]*C(sum_of_tree+(k-1),k);
	}
	for(int j=0; j<=degree; j++)
		ans+=f[Num_Of_Carbonium][j];
	if(!(Num_Of_Carbonium&1))//双重心的特判
	{
		int j=0;
		for(sum_of_tree=j=0; j<degree; j++)
			sum_of_tree+=f[Num_Of_Carbonium>>1][j];
		ans+=C(++sum_of_tree,2);
	}
	cout<<ans;
}
