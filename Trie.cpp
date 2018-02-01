/*
Trie(前缀树，字典树)
*/

struct Trie {
	// ch[i][j]表示结点i的编号为j的子节点是否存在，maxn1为最大结点总数，
	// maxn2为每个结点可能字符的总数，例如26
	int ch[maxn1][maxn2];
	int val[maxn1];		// val[i]表示结点i所记录的信息
	int sum;			// sum记录结点总数
	Trie () {
		sum = 1;		// 初始时只有一个根节点
		memset(ch[0], 0, sizeof(ch[0]));
	}

	int id(char c) {		// 定义字符c的编号
		return c - 'a';
	}

	// 插入字符串s，附加信息v，只有单词结点(最后一个字母)才存储信息，其余赋值为0
	void insert(char *s, int v) {
		int u  = 0, len = strlen(s);
		for(int i = 0; i < len; i++) {
			int c = id(s[i]);
			if(!ch[u][c]) {			// 结点不存在
				memset(ch[sum], 0, sizeof(ch[sum]));
				val[sum] = 0;
				ch[u][c] = sum++;		// 新建节点
			}
			u = ch[u][c];
		}
		val[u] = v;		// 单词最后一个字母记录信息
	}

	// 查询单词s所记录的信息，即该单词最后一个字母的附加信息，若该单词不存在，返回-1
	int query(char *s) {
		int u = 0, len = strlen(s);
		for(int i = 0; i < len; i++) {
			int c = id(s[i]);
			if(!ch[u][c])
				return -1;
			u = ch[u][c];
		}
		return val[u];
	}
};
