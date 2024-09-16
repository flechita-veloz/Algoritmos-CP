#include <bits/stdc++.h>
using namespace std;

int N, Q, T = 1;
int depth[200005];
int up[200005][20];
vector<int> adj[200005];

void dfs(int v) {
	for(int i = 1; i < 20; i++)
		{ up[v][i] = up[up[v][i - 1]][i - 1]; }

	for (int x : adj[v]) {
		if (x != up[v][0]) {
			depth[x] = depth[up[x][0] = v] + 1;
			dfs(x);
		}
	}
}

int jump(int x, int d) {
	for(int i = 0; i < 20; i++) {
		if ((d >> i) & 1) x = up[x][i];
	}
	return x;
}

int LCA(int a, int b) {
	if (depth[a] < depth[b]) swap(a, b);

	a = jump(a, depth[a] - depth[b]);
	if (a == b) return a;

	for(int i = 19; i >= 0; i--) {
		int aT = up[a][i], bT = up[b][i];
		if (aT != bT) a = aT, b = bT;
	}

	return up[a][0];
}

int main() {
	cin >> N >> Q;
	for(int i = 0; i < N - 1; i++) {
		int b;
		cin >> b;
		--b;
		adj[b].push_back(i + 1); 
	}

	up[0][0] = 0, depth[0] = 0;
	dfs(0);

	while(Q--){
		int a, b;
		cin >> a >> b;
		--a;
		--b;
		cout << LCA(a, b) + 1 << endl;
	}
    return 0;
}