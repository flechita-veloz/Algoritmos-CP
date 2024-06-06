#include<bits/stdc++.h>
using namespace std;
int n;
const int mxn = 2e5 + 5, l = 18; // 18 is calculated by log2(N)
int up[l][mxn];

void build(){
    for(int i = 1; i < l; i++)
	for(int j = 1; j <= n; j++)
	up[i][j] = up[i - 1][up[i - 1][j]];
}
int jmp(int x, int d) {
	for(int i = 0; i < l; i++) if ((d >> i) & 1) x = up[i][x];
	return x ? :-1;  // modfication to return -1 if not found
}

int main() {
    int q;
	cin >> n >> q;
	for(int i = 2; i <= n; i++){
		int a;
		cin >> a;
		up[0][i] = a;
	}
    build();
	while(q--){
		int a, b;
		cin >> a >> b;
		cout << jmp(a, b) << endl;
	}
}