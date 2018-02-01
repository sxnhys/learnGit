/*////////////////////////////////////////////////////////////////
树状数组（二叉索引树）
n个元素数组 a[1], a[2], ..., a[n]
Add(x, d): 使 a[x] + d
Query(L, R): 计算 a[L] + a[L+1] + ... + a[R]

定义lowbit(x): x的二进制表达式中最右边的1所对应的值，即 x & (-x) 的结果
结点i若是左子节点，则其父节点为i + lowbit(i)，若是右子节点，则其父节点为
i - lowbit(i)

定义辅助数组C[i] = a[i-lowbit(i)+1] + ... + a[i]
*/////////////////////////////////////////////////////////////////

int C[maxn], n;

int lowbit(int x) {
	return x & (-x);
}

// 前缀和
int sum(int x) {
	int ans = 0;
	while(x > 0) {
		ans += C[x];
		x -= lowbit(x);
	}
	return ans;
}

// 更新 a[x] + d
void update(int x, int d) {
	while(x <= n) {
		C[x] += d;
		x += lowbit(x);
	}
}
