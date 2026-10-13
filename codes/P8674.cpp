#include <iostream>
#include <vector>
#include <queue>
using namespace std;
int main()
{
	int n, k;
	cin >> n >> k;
	vector <int> dist(n + 1, -1); //下标为n的节点与最远的点的距离，初始时都赋值-1标记未访问
	queue <int> q;                //BFS队列
	dist[0] = 0;                  
	q.push(0);                    //第一个节点0入列
	int ans = 0;
	while (!q.empty())            //BFS
	{
		int u = q.front();
		q.pop();
		if (dist[u] > ans)        //更新dist数组
			ans = dist[u];
		int v = (u + 1) % n;
		if (dist[v] == -1)        //使用前一个dist数组进行更新
		{
			dist[v] = dist[u] + 1;
			q.push(v);
		}
		v = (u + k) % n;
		if (dist[v] == -1)        //使用一次访问k的方式更新数组
		{
			dist[v] = dist[u] + 1;
			q.push(v);
		}
	}
	cout << ans << "\n";
	return 0;
}
