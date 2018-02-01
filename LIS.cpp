/*
LIS（最长上升子序列）
*/

// 最长不下降子序列
int n;
int a[maxn], dp[maxn];		//a[]为原始数据
int len = 1;
for(int i = 1; i <= n; i++) {
	int j;
	for(j = 1; j < len; j++)	//判断是否将a[i]加入LIS中
		if(dp[j] >= a[i])
			break;
	if(j == len)			//a[i]加入LIS,len+1
		len++;
	dp[j] = a[i];			//无论a[i]是否加入LIS，dp[j]总是存储当前a[i],若a[i]加入LIS记录用以判断是否要后继更新，否则记录用以更新或者是否是新的LIS
}
cout << len - 1 << endl;

// 最长不下降子序列，二分查找
int binary_search(int b[], int goal, int len)
{
	int left = 0, right = len, mid;
	while(right != left) {
		mid = (right + left) / 2;
		if(goal == b[mid])
			return mid;
		else if(goal < b[mid])
			right = mid;
		else
			left = mid + 1;
	}	
	return left;
}

int main()
{
	while(cin >> n) {
		for(int i = 1; i <= n; i++)
			cin >> a[i];
		int len = 1;
		dp[0] = -1;
		for(int i = 1; i <= n; i++) {
			dp[len] = 1000000;
			int j = binary_search(dp, a[i], len);
			if(j == len)
				len++;
			dp[j] = a[i];
		}
		cout << n - len + 1 << endl;
	}
	return 0;
}


// 最长上升子序列，二分查找
int binary_search(int b[], int goal, int len)
{
	int left = 0, right = len, mid;
	while(right != left) {
		mid = (right + left) / 2;
		if(goal < b[mid])
			right = mid;
		else
			left = mid + 1;
	}	
	return left;
}

int main()
{
	while(cin >> n) {
		for(int i = 1; i <= n; i++)
			cin >> a[i];
		int len = 1;
		dp[0] = -1;
		for(int i = 1; i <= n; i++) {
			dp[len] = 1000000;
			int j = binary_search(dp, a[i], len);
			if(j == len)
				len++;
			dp[j] = a[i];
		}
		cout << n - len + 1 << endl;
	}
	return 0;
}
