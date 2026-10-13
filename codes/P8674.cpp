#include <iostream>
#include <vector>
#include <queue>
using namespace std;
int main()
{
	int n, k;
	cin >> n >> k;
	vector <int> dist(n + 1, -1);
	queue <int> q;
	dist[0] = 0;
	q.push(0);
	int ans = 0;
	while (!q.empty())
	{
		int u = q.front();
		q.pop();
		if (dist[u] > ans)
			ans = dist[u];
		int v = (u + 1) % n;
		if (dist[v] == -1)
		{
			dist[v] = dist[u] + 1;
			q.push(v);
		}
		v = (u + k) % n;
		if (dist[v] == -1)
		{
			dist[v] = dist[u] + 1;
			q.push(v);
		}
	}
	cout << ans << "\n";
	return 0;
}
