/*Xenny, the traveller, was in AlgoLand for vacation. He wanted to travel from city U to city V. Being quite an explorer, he wanted to travel exactly once by roadways as well as by railways.
Xenny should start from city U and go to some city Z by roadways only. He can traverse one or more than one edges between U and Z by road. From city Z, he must go to city V by railways only. He can use railways one or more than one times between city Z and city V.
Or, he can also go from city U to city Z by railways only and then from city Z to city V by roadways only.
The distance of all cities was known to him, since he had a map that showed not only the paths connecting all cities with roadways, but it also showed all paths connecting all cities with railways.
Since Xenny is now old and slow at calculation, help him find the minimum total distance he must travel, so that he goes from city U to city V, and travels by both - roadways as well as railways, exactly once.

Input
First line contains a single integer N - the number of cities in AlgoLand.
N lines follow, each containing N space-separated natural numbers.
These N lines represent the roadways distance-matrix of size N x N. Aij represents the length of the road from city i to city j.
N more lines follow, each containing N space-separated natural numbers.
These N lines represent the railways distance-matrix of size N x N. Bij represents the length of the railway from city i to city j.
The last line contains 2 space-separated integers - U and V - the starting and ending points respectively.

Output
Print a single natural number - the minimum distance Xenny must travel to satisfy the above-mentioned criteria.

Constraints
3 ≤ N ≤ 1250
0 ≤ Aij, Bij ≤ 100
1 ≤ U, V ≤ N
U ≠ V

Sample Input(Plaintext Link)
 3
0 1 2
3 0 4
5 6 0
0 6 5
1 0 4
3 2 0
1 2
Sample Output(Plaintext Link)
 4
Explanation
Xenny can go from 1 to 3 by roadway, and 3 to 2 by railway.
Distance between 1 and 3 by roadway = 2
Distance between 3 and 2 by railway = 2
Total distance travelled = 4 */
#include <vector>
#include <map>
#include <set>
#include <algorithm>
#include <functional>
#include <utility>
#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <cstring>
#define endl "\n"
#define pb push_back
#define sz() size()
#define all(a) a.begin(),a.end()
#define mp make_pair
#define ff first
#define ss second
#define mod 1000000007
#define d(x) printf(#x" = %d",x)
#define pl puts("")
#define ps pc(' ')
#define gc getchar_unlocked
#define pc putchar_unlocked
#define bitcount __builtin_popcount
#define gcd __gcd
#define SZ 1250
#define INF 1250000
using namespace std;
typedef long long ll;
typedef vector <int> vi;
typedef pair<int,int> pii;
#ifdef _WIN32
int getchar_unlocked() { return getchar(); }
int putchar_unlocked(char c) { return putchar(c); }
#endif
template <typename T>void sc(T &n){register int f=1;n=0;char c=gc();while(c!='-'&&c<'0')c=gc();if(c=='-')f=-1,c=gc();while(c>='0'&&c<='9')n=(n<<3)+(n<<1)+c-'0',c=gc();n=n*f;}
template <typename T>void pr(T &a){char s[30];if(a<0){pc('-');a*=-1;}int i=0;do{s[i++]=a%10+'0';a/=10;}while(a);i--;while(i>=0)pc(s[i--]);}
template <typename T>T sub(T x,T y){if(x<y)return y-x;return x-y;}
int n;
bool sptset[SZ];
int road[SZ][SZ];
int rail[SZ][SZ];
int droad[SZ];
int drail[SZ];
int transroad[SZ][SZ];
int transrail[SZ][SZ];
int mindist(int *dist)
{
    int i,min=INF,pos;
    for(i=0;i<n;i++)
        if(dist[i]<=min && !sptset[i])
            min=dist[i],pos=i;
    return pos;
}
void dijkstra(int *dist,int src,int adj[][SZ])
{
	int i,j;
	memset(sptset,0,sizeof(sptset));
	for(i=0;i<n;i++)dist[i]=INF;
	dist[src]=0;

    for(i=1;i<n;i++)//shortest path tree contains n-1 edges only
    {
        int x=mindist(dist);
        sptset[x]=1;
        for(j=0;j<n;j++)
        {
            if(!sptset[j] && (dist[x]+adj[x][j])<dist[j])
                dist[j]=dist[x]+adj[x][j];
        }
    }
}
int main()
{
	sc(n);
	int i,j,k;

	for(i=0;i<n;i++)for(j=0;j<n;j++)sc(road[i][j]);
	for(i=0;i<n;i++)for(j=0;j<n;j++)sc(rail[i][j]);
	for(i=0;i<n;i++)
		for(j=0;j<n;j++)
		{	transroad[i][j]=road[j][i];
			transrail[i][j]=rail[j][i];
		}
	int st,end;
	sc(st); sc(end);
	st--;
	end--;
	dijkstra(droad,st,road);//start from road
	dijkstra(drail,end,transrail);//then rail
	int ans=INF;
	for(i=0;i<n;i++)
	{
		if(i==st || i==end)continue;
		if(droad[i]+drail[i]<ans)
			ans=droad[i]+drail[i];
	}
	dijkstra(drail,st,rail);
	dijkstra(droad,end,transroad);
	for(i=0;i<n;i++)
	{
		if(i==st || i==end)continue;
		if(droad[i]+drail[i]<ans)
			ans=droad[i]+drail[i];
	}
	pr(ans);
	return 0;
}
