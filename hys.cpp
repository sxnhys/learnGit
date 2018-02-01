#include <iostream>
#include <cstring>
using namespace std;

int t;
int n, a[1000010];

int f(int k) {
	if(k == 0)
		return 1;
	return 0;
}

int main()
{
	char s[] = "a\'\029";
	char s1[] = "b\xabHc\077345\\";
	cout << sizeof(s) << endl;
	cout << sizeof(s1) << endl;
	cout << strlen(s) << " " << strlen(s1) << endl;
	cout << s << " " << s1 << endl;

	int a[] = {1, 2, 3, 4, 5}, *p;
	double *q = (double *)a;
	cout << *q << endl;
	q++;
	cout << *q << endl;
	p = (int *)q;
	cout << *p << endl;

	int k = 1;
	cout << ++k + k++ << endl;
	cout << k << endl;
}