题目链接：https://codeforces.com/contest/2276/problem/D
以下是图片中题面内容的中文翻译：

### D. 穴居人 (D. Caveman)

**每个测试点的时间限制：2秒**
**每个测试点的内存限制：512 MB**

Monocarp 画了一个包含 \(n\) 个顶点和 \(m\) 条边的无向图。他想将每个顶点染成红色或蓝色，使得每个顶点至少有一个颜色相反的邻居。他需要计算符合要求的染色方案数。

Monocarp 是个穴居人：他只认识数字 1、2 和“很多”（任何大于2的数字）。他不知道零，所以如果没有有效的染色方案，他的大脑就会融化。

帮助 Monocarp 用他的语言计算有效的染色方案数。如果在至少一个顶点上颜色不同，则两种染色方案被视为不同。

#### 输入
第一行包含一个整数 \(t\) (\(1 \le t \le 10^4\)) —— 测试用例的数量。

每个测试用例的第一行包含两个整数 \(n\) 和 \(m\) (\(3 \le n \le 3 \cdot 10^5\); \(0 \le m \le \min(\frac{n(n-1)}{2}, 3 \cdot 10^5)\)) —— 顶点和边的数量。

接下来的 \(m\) 行每行包含两个整数 \(u_i\) 和 \(v_i\) (\(1 \le u_i, v_i \le n\)) —— 第 \(i\) 条边连接的两个顶点的编号。图没有自环或重边。

输入的额外限制：
*   所有测试用例中 \(n\) 的总和不超过 \(3 \cdot 10^5\)；所有测试用例中 \(m\) 的总和也不超过 \(3 \cdot 10^5\)。

#### 输出
对于每个测试用例，在单独的一行输出：
*   `1` 或 `2`，如果有效染色方案数分别等于 1 或 2；
*   `Many`，如果有效染色方案数大于 2；
*   `Brain Melt`，如果没有有效的染色方案。

#### 示例
**输入**
```text
4
3 1
1 2
3 2
1 2
1 3
3 3
1 2
2 3
1 3
4 3
1 2
2 3
3 4
```

**输出**
```text
Brain Melt
2
Many
Many
```

---

*(注：题目中要求输出的字符串 `Brain Melt`、`Many` 等应保留英文原样提交给评测系统)*

那下面应该怎么做呢？

**优先考虑判断无解的情况：**

很容易看出：当存在至少一个孤立节点时本题无解，输出BrainMelt。
```cpp
构造：对于每个连通分量，如果它是二分图，直接二分图染色即可。若为非二分图，我们仍可通过奇环染色使其只有一条同色边。
```

同样容易看出如果有一种可能的方案那么我们只需要将全部节点染得颜色全部反转，这样我们就得到了至少两种方案。
```cpp
即：不可能出现输出1的情况，下面我们只需要考虑区分2和Many的方案数
```
至此，算法流程就很清晰了：

1.初始化一个长度n+1的出入度数组deg，初始值为0

2.遍历deg[i]，若deg[i] == 0 → BrainMelt

3.BFS统计图中连通块数量，并判断每张连通图是否为二分图

4.各连通块的方案数相乘，任何≥2个点的连通块至少都有2种合法染色。因此连通块数 ≥ 2 → Many。

5.注意：当连通块个数恰好为1时，还不能一概而论。当且仅当这个联通块为“星形图”时，联通二分图只有两种方案数。

也就是说，有一个顶点的度数为n-1，它链接了其他所有点，而其他点的度数均为一。

AC码：
```cpp
#include <iostream>
#include <vector>
#include <queue>

using namespace std;

void solve()
{
	int n, m;
	cin >> n >> m;
	vector <vector <int>> edge(n + 1);
	vector <int> deg(n + 1);
	for (int i = 0; i < m; i++)
	{
		int u, v;
		cin >> u >> v;
		deg[u]++;
		deg[v]++;
		edge[u].push_back(v);
		edge[v].push_back(u);
	}

	for (int i = 1; i <= n; i++)
	{
		if (deg[i] == 0)
		{
			cout << "Brain Melt" << "\n";
			return;
		}
	}

	vector <int> col(n + 1, -1);
	int com = 0;
	bool b = 1;
	for (int i = 1; i <= n; i++)
	{
		if (col[i] == -1)
		{
			com++;
			queue <int> q;
			q.push(i);
			col[i] = 0;
			while (!q.empty())
			{
				int u = q.front();
				q.pop();
				for (int v : edge[u])
				{
					if (col[v] == -1)
					{
						col[v] = 1 - col[u];
						q.push(v);
					}

					else if(col[v] == col[u])
					{
						b = 0;
					}
				}
			}
		}
	}

	int mx = 0;
	for (int i = 1; i <= n; i++)
	{
		if (deg[i] > mx)
		{
			mx = deg[i];
		}
	}

	if (com == 1 && b && m == n - 1 && mx == n - 1)
	{
		cout << 2 << endl;
		return;
	}
	cout << "Many" << endl;
	return;
}

int main()
{
	int t;
	cin >> t;
	while (t--)
	{
		solve();
	}
	return 0;
}
```
