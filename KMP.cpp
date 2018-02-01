/*//////////////////////////////////////////////////////////////////////////////
KMP   Knuth-Morris-Pratt 字符串查找算法
1、求next数组	
代表当前字符之前的字符串中，有多大长度的相同前缀后缀
寻找前缀后缀最长公共元素长度，然后减1
next[j] = k意味着p[j]之前的模式串子串中，有长度为k的相同前缀和后缀；
现已知next[j]，递推求next[j+1]:
	若p[k] == p[j]，则next[j+1] = next[j] + 1 = k + 1
	若p[k] != p[j]，则比较p[next[k]]和p[j]，其中k = next[j]，
					重复此过程直到匹配相等

2、文本串和模式串匹配
如果j = -1，或者当前字符匹配成功（即S[i] == P[j]），都令i++，j++，继续匹配下一个字符；
如果j != -1，且当前字符匹配失败（即S[i] != P[j]），则令 i 不变，j = next[j]。
			此举意味着失配时，模式串P相对于文本串S向右移动了j - next [j] 位。 
*///////////////////////////////////////////////////////////////////////////////


// 求next[]数组（编译器会报错，next有歧义，Next[]即可）
void gen_next(char *p, int next[]) {
	int plen = strlen(p), k = -1, j = 0;
	next[0] = -1;
	while(j < plen - 1) {
		if(k == -1 || p[j] == p[k])		// 刚开始匹配或者当前匹配成功
			next[++j] = ++k;
		else
			k = next[k];
	}
}

// next[]数组求法优化
// 当p[j] != s[i] 时，下次匹配必然是p[next[j]] 跟s[i]匹配，
// 如果p[j] = p[next[j]]，必然导致后一步匹配失败，
// 所以不能允许p[j] = p[next[j]]。 此时的next[]的含义并没有之前那么直接
void gen_next(char *p, int next[]) {
	int plen = strlen(p), k = -1, j = 0;
	next[0] = -1;
	while(j < plen - 1) {
		if(k == -1 || p[j] == p[k]) {
			j++, k++;
			if(p[j] != p[k])
				next[j] = k;
			else		// p[j] == p[k] 时，next[j] = k在最终匹配时必然失败
				next[j] = next[k];
		}
		else
			k = next[k];
	}
}

// 文本串和模式串匹配
int KMP(char *s, char *p) {
	int slen = strlen(s), plen = strlen(p);
	int i = 0, j = 0;
	while(i < slen && j < plen) {
		if(j == -1 || s[i] == p[j])		// 刚开始匹配或者当前字符匹配成功
			i++, j++;
		else
			j = next[j];
	}
	if(j == plen)
		return i - j;
	return -1;
}
