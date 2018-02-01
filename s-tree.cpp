/*////////////////////////////////////////////////////////////////////////////////
						   线段树
///////////////////////////////////////////////////////////////////////////////*/

/*//////////////////////
1. 点修改:
两个操作:
update(x, v): a[x] = v
query(l, r): 计算 min{a[i]}等值
//////////////////////*/

int n;
int a[maxn];
int minv[4 * maxn], maxv[4 * maxn], sumv[4 * maxn];
int ql, qr, x, v;		// [ql, qr]为查询区间, v为更新值, a[x] = v

// o表示节点的编号
// 建树
void build(int o, int L, int R) {
	if(L == R) {
		minv[o] = maxv[o] = sumv[o] = a[L];
		return;
	}

	int M = L + (R - L) / 2;
	build(2 * o, L, M);
	build(2 * o + 1, M + 1, R);
	minv[o] = min(minv[2 * o], minv[2 * o + 1]);
	maxv[o] = max(maxv[2 * o], maxv[2 * o + 1]);
	sumv[o] = sumv[2 * o] + sumv[2 * o + 1];
}

// 更新
// a[x] = v
void update(int o, int L, int R) {
	if(L == R) {
		minv[o] = maxv[o] = sumv[o] = v;
		return;
	}

	int M = L + (R - L) / 2;
	if(x <= M)
		update(2 * o, L, M);
	else
		update(2 * o + 1, M + 1, R);
	minv[o] = min(minv[2 * o], minv[2 * o + 1]);
	maxv[o] = max(maxv[2 * o], maxv[2 * o + 1]);
	sumv[o] = sumv[2 * o] + sumv[2 * o + 1];
}

// 询问
// 以最小值为例
int query(int o, int L, int R) {
	if(ql <= L && R <= qr)
		return minv[o];
	int M = L + (R - L) / 2, ans = Inf;
	if(ql <= M)
		ans = min(ans, query(2 * o, L, M) );
	if(qr > M)
		ans = min(ans, query(2 * o + 1, M + 1, R) );
	return ans;
}



/*/////////////////////////////////////////////////////////////////
2. 区间修改1
两个操作:
update(L, R, v): a[L] + v, a[L+1] + v, ... , a[R] + v
query(l, r): 计算 min{a[i]}等值
/////////////////////////////////////////////////////////////////*/

int n, q;
int a[maxn];
int sumv[4 * maxn], minv[4 * maxn], maxv[4 * maxn], addv[4 * maxn];
int ql, qr, v;		// v为加的值

// 更新, 若修改的区间包含该节点, 则累加addv值, 否则继续修改他的左右节点
void update(int o, int L, int R) {
	if(ql <= L && R <= qr) {		// 当修改区间包含该节点,则在累加数组上加上v
		addv[o] += v;
	}
	else {
		int M = L + (R - L) / 2;
		if(ql <= M)
			update(2 * o, L, M);
		if(qr > M)
			update(2 * o + 1, M + 1, R);
	}

	// 递归更新之后维护sumv, minv, maxv
	sumv[o] = minv[o] = maxv[o] = 0;
	if(L < R) {		// 排除叶子节点
		sumv[o] = sumv[2 * o] + sumv[2 * o + 1];
		minv[o] = min(minv[2 * o], minv[2 * o + 1]);
		maxv[o] = max(maxv[2 * o], maxv[2 * o + 1]);
	}
	// 除了考虑左右子节点的值,还要加上本节点的累加值
	sumv[o] += addv[o] * (R - L + 1);
	minv[o] += addv[o];
	maxv[o] += addv[o];
}

// 查询
// 由于若修改的区间包含该节点, 则累加addv值, 否则继续修改他的左右节点
// 当前节点的addv值及和,最值等仅仅是当前节点自身的,换句话说,addv的累加
// 仅仅发生在修改区间包含该节点,若某个修改只是涉及当前节点的一部分元素而不是全部,
// 就不会累加addv, 而且不会向下继续传递, 所以计算当前节点时必须加上祖先节点的累加
int Sum, Min, Max;
void query(int o, int L, int R, int add) {		// add为祖先节点的add之和
	if(ql <= L && R <= qr) {
		Sum += sumv[o] + add * (R - L + 1);
		Min = min(Min, minv[o] + add);
		Max = max(Max, maxv[o] + add);
	}
	else {
		int M = L + (R - L) / 2;
		if(ql <= M)
			query(2 * o, L, M, add + addv[o]);
		if(qr > M)
			query(2 * o + 1, M + 1, R, add + addv[o]);
	}
}
// 验证正确
int main()
{
	while(cin >> n >> q) {
		memset(addv, 0, sizeof(addv));
		memset(sumv, 0, sizeof(sumv));
		memset(minv, 0, sizeof(minv));
		memset(maxv, 0, sizeof(maxv));
		for(int i = 1; i <= n; i++) {
			cin >> a[i];
			ql = qr = i;
			v = a[i];
			update(1, 1, n);
		}

		while(q--) {
			char op;
			cin >> op;
			if(op == 'a') {
				cin >> ql >> qr >> v;
				update(1, 1, n);
			}
			else {
				Sum = Max = 0;
				Min = Inf;
				cin >> ql >> qr;
				query(1, 1, n, 0);
				cout << Sum << " " << Min << " " << Max << endl;
			}

		}
	}
	return 0;
}


/*///////////////////////////////////////////////////////////////////////////////
3. 区间修改2
两个操作:
update(L, R, v): a[L] = a[L+1] = ... = a[R] = v
query(l, r): 计算 min{a[i]}等值
set 与 add修改不一样的是前者与操作的先后顺序有关
///////////////////////////////////////////////////////////////////////////////*/
int n, q;
int a[maxn];
int sumv[4 * maxn], minv[4 * maxn], maxv[4 * maxn], setv[4 * maxn];
int ql, qr, v;		// v为加的值

// 维护区间信息
void maintain(int o, int L, int R) {
	sumv[o] = minv[o] = maxv[o] = 0;
	if(setv[o] >= 0) {
		sumv[o] = setv[o] * (R - L + 1);
		minv[o] = maxv[o] = setv[o];
		return;
	}
	if(R > L) {		// 排除叶子节点
		sumv[o] = sumv[2 * o] + sumv[2 * o + 1];
		minv[o] = min(minv[2 * o], minv[2 * o + 1]);
		maxv[o] = max(maxv[2 * o], maxv[2 * o + 1]);
	}
}

// 更新
void update(int o, int L, int R) {
	int lc = 2 * o, rc = 2 * o + 1;
	if(ql <= L && R <= qr)		// 新的set操作区间覆盖当前节点
		setv[o] = v;
	else {
		if(setv[o] >= 0) {	// 当前节点有标记向下传递(每个节点初始为-1,set值为非负数)
			setv[lc] = setv[rc] = setv[o];	// 若新的set操作区间没有覆盖当前节点,
			setv[o] = -1;		// 就将之前的set值向左右子节点传递,当前节点清除标记
		}
		int M = L + (R - L) / 2;
		if(ql <= M)
			update(lc, L, M);
		else
			maintain(lc, L, M);
		if(qr > M)
			update(rc, M + 1, R);
		else
			maintain(rc, M + 1, R);
	}
	maintain(o, L, R);
}

// 查询
int Sum, Min, Max;
void query(int o, int L, int R) {
	if(setv[o] >= 0) {		// 一旦碰到set操作就停止,避免set存在祖先和后代关系
		Sum += setv[o] * (min(R, qr) - max(L, ql) + 1);
		Min = min(Min, setv[o]);
		Max = max(Max, setv[o]);
	}
	else if(ql <= L && R <= qr) {
		Sum += sumv[o];
		Min = min(Min, minv[o]);
		Max = max(Max, maxv[o]);
	}
	else {
		int M = L + (R - L) / 2;
		if(ql <= M)
			query(2 * o, L, M);
		if(qr > M)
			query(2 * o + 1, M + 1, R);
	}
}

// 验证正确
int main()
{
	while(~scanf("%d%d", &n, &q)) {
		fill(setv + 1, setv + 4 * maxn + 1, -1);
		memset(sumv, 0, sizeof(sumv));
		memset(minv, 0, sizeof(minv));
		memset(maxv, 0, sizeof(maxv));
		for(int i = 1; i <= n; i++) {
			scanf("%d", &a[i]);
			ql = qr = i;
			v = a[i];
			update(1, 1, n);
		}

		while(q--) {
			char op;
			scanf("\n%c", &op);
			if(op == 'C') {
				scanf("%d%d%d", &ql, &qr, &v);
				update(1, 1, n);
			}
			else {
				Sum = 0, Min = Inf, Max = 0;
				scanf("%d%d", &ql, &qr);
				query(1, 1, n);
				printf("%d %d %d\n", Sum, Min, Max);
			}
		}
	}
	return 0;
}
