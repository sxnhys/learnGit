/*
RMQ（区间最值）
令d[i][j]为从i开始，长度为2^j的一段元素中的最小值，
则d[i][j] = min(d[i][j-1], d[i+2^(j-1)][j-1])
*/

void init(int a[], int n)
{
	for(int i = 1; i <= n; i++)
		dp[i][0] = a[i];
	for(int j = 1; (1 << j) <= n; j++)
		for(int i = 1; i + (1 << j) - 1 <= n; i++)
			dp[i][j] = min(dp[i][j-1], dp[i + (1 << (j-1))][j-1]);
}

int RMQ(int L, int R) {
	int k = 0;
	if(L > R)
		return 0;
	while((1 << (k+1)) <= R - L + 1) // 找到满足 2^k <= R - L + 1的最大整数k
		k++;
	return min(dp[L][k], dp[R - (1 << k) + 1][k]);
}
