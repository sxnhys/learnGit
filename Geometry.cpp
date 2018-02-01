/*///////////////////////////////////////////////////////////////////////////////////
							       计算几何
///////////////////////////////////////////////////////////////////////////////////*/

// 点
struct Point {
	double x, y;
	Point (double x = 0, double y = 0) : x(x), y(y) {}
};

// 向量
typedef Point Vector;

Vector operator + (Vector A, Vector B) {
	return Vector(A.x + B.x, A.y + B.y);
}

Vector operator - (Vector A, Vector B) {
	return Vector(A.x - B.x, A.y - B.y);
}

Vector operator * (Vector A, double p) {
	return Vector(A.x * p, A.y * p);
}

Vector operator / (Vector A, double p) {
	return Vector(A.x / p, A.y / p);
}

bool operator < (const Point& a, const Point& b) {
	return a.x < b.x || (a.x == b.x && a.y < b.y);
}

bool cmp(Point a, Point b) {
	return a < b;
}

const double eps = 1e-8;
int dcmp(double x) {	// 三态函数，减少精度问题
	if(fabs(x) < eps)
		return 0;
	return x < 0 ? -1 : 1;
}

bool operator == (const Point& a, const Point& b) {
	return dcmp(a.x - b.x) == 0 && dcmp(a.y - b.y) == 0;
}

// 点积
double Dot(Vector A, Vector B) {
	return A.x * B.x + A.y * B.y;
}

// 两点之间距离的平方
double dis2(Point a, Point b) {
	return Dot(b - a, b - a);
}

// 向量长度
double Len(Vector A) {
	return sqrt(Dot(A, A));
}

// 叉积
// 即两个向量组成的三角形的有向面积的两倍
// Cross(A, B): 顺着A看，若B在左边则叉积大于0，否则小于0
double Cross(Vector A, Vector B) {
	return A.x * B.y - A.y * B.x;
}

// 三角形ABC的面积
double Area2(Point A, Point B, Point C) {
	return fabs(Cross(B - A, C - A)) / 2.0;
}

// 旋转
Vector Rotate(Vector A, double rad) {
	return Vector(A.x * cos(rad) - A.y * sin(rad), 
		A.x * sin(rad) + A.y * cos(rad));
}

// 两向量夹角
double Ang(Vector A, Vector B) {
	return acos(Dot(A, B) / Len(A) / Len(B));
}

// 向量极角
double ANG(Vector A) {
	return atan2(A.y, A.x);
}	

// 单位法向量
Vector Normal(Vector A) {
	double L = Len(A);
	return Vector(-A.y / L, A.x / L);
}

// 两直线交点
Point Gen_Intersection(Point P, Vector v, Point Q, Vector w) {
	Vector u = P - Q;
	double t = Cross(w, u) / Cross(v, w);
	return P + v * t;
}

// 点到直线的距离
double DistanceToLine(Point P, Point A, Point B) {
	Vector v1 = B - A, v2 = P - A;
	return fabs(Cross(v1, v2)) / Len(v1);
}

// 点到线段的距离
double DistanceToSegment(Point P, Point A, Point B) {
	if(A == B)
		return Len(P - A);
	Vector v1 = B - A, v2 = P - A, v3 = P - B;
	if(dcmp(Dot(v1, v2)) < 0)
		return Len(v2);
	else if(dcmp(Dot(v1, v3)) > 0)
		return Len(v3);
	else
		return fabs(Cross(v1, v2)) / Len(v1);
}

// 点在直线上的投影
Point Gen_LineProjection(Point P, Point A, Point B) {
	Vector v = B - A;
	return A + v * (Dot(v, P - A) / Dot(v, v));
}

// 线段相交判定
bool SegmentProperIntersection(Point a1, Point a2, Point b1, Point b2) {
	double c1 = Cross(a2 - a1, b1 - a1);
	double c2 = Cross(a2 - a1, b2 - a1);
	double c3 = Cross(b2 - b1, a1 - b1);
	double c4 = Cross(b2 - b1, a2 - b1);
	return dcmp(c1) * dcmp(c2) < 0 && dcmp(c3) * dcmp(c4) < 0;
}

// 判断点是否在线段上（不包含端点）
bool OnSegment(Point p, Point a1, Point a2) {
	return dcmp(Cross(a1 - p, a2 - p)) == 0 && dcmp(Dot(a1 - p, a2 - p)) < 0;
}

// 多边形有向面积
double PolygonArea(Point *p, int n) {
	double area = 0;
	for(int i = 1; i < n - 1; i++)
		area += Cross(p[i] - p[0], p[i+1] - p[0]);
	return area / 2;
}

// 弧度转角度
double angtran(double rad) {
	if(dcmp(rad - PI) == 0)
		return 0.0;
	if(rad < 0)
		rad += PI;
	return rad / PI * 180.0;
}


///////////////////////////////////////////////////////////////////////
// 圆
struct Circle
{
	Point c;
	double r;
	Circle (Point c, double r) : c(c), r(r) {};
	Point point (double a) {	// a为圆上任意一点的极角
		return Point(c.x + r * cos(a), c.y + r * sin(a));
	}
};

// 直线
struct Line
{
	Point p;
	Vector v;
	Line (Point p, Vector v) : p(p), v(v) {};
	Point point(double t) {
		return p + v * t;
	}
};

// 直线和圆的位置关系
int L_C(Line L, Circle C, vector<Point>& sol)
{
	double t1, t2;
	// 直线和圆方程联立得 (at + b)^2 + (ct + b)^2 = r^2
	double a = L.v.x, b = L.p.x - C.c.x, c = L.v.y, d = L.p.y - C.c.y;
	// 化简为 e*t^2 + f*t + g = 0
	double e = a * a + c * c, f = 2 * a * b + 2 * c * d,
			g = b * b + d * d - C.r * C.r;
	double delt = f * f - 4 * e * g;	// 判别式
	if(dcmp(delt) < 0)		// 相离
		return 0;
	if(dcmp(delt) == 0) {	// 相切
		t1 = t2 = -f / (2 * e);
		sol.push_back(L.point(t1));
		return 1;
	}

	// 相交
	double sqdelt = sqrt(delt);
	t1 = (-f - sqdelt) / (2 * e);
	sol.push_back(L.point(t1));
	t2 = (-f + sqdelt) / (2 * e);
	sol.push_back(L.point(t2));
	return 2;
}

// 两圆的位置关系
int C_C(Circle C1, Circle C2, vector<Point>& sol) {
	double d = Len(C1.c - C2.c);
	if(dcmp(d) == 0) {
		if(dcmp(C1.r - C2.r) == 0)
			return -1;		// 重合
		return 0;		// 不相交，内含（同心圆）
	}
	if(dcmp(C1.r + C2.r - d) < 0)
		return 0;	// 不相交，相离
	if(dcmp(fabs(C1.r - C2.r) - d) > 0)
		return 0;	// 不相交，内含

	// 向量C1C2极角
	double a = ANG(C2.c - C1.c);
	double da = acos((C1.r * C1.r + d * d - C2.r * C2.r) / (2 * C1.r * d));
	Point p1 = C1.point (a - da), p2 = C1.point(a + da);

	sol.push_back(p1);
	if(p1 == p2);
	return 1;	// 相切
	sol.push_back(p2);
	return 2;	// 相交
}

// 过定点做圆的切线
int Gen_Tangents(Point p, Circle C, Vector *v) {
	Vector u = C.c - p;
	double dis = Len(u);
	if(dis < C.r)	// 点在圆内
		return 0;
	else if(dcmp(dis - C.r) == 0) {		// 点在圆上
		v[0] = Rotate(u, PI / 2);
		return 1;
	}
	else {		// 点在圆外
		double ang = asin(C.r / dis);
		v[0] = Rotate(u, -ang);
		v[1] = Rotate(u, ang);
		return 2;
	}
}

// 两圆的公切线
int Gen_Tangents2(Circle A, Circle B, Point *a, Point *b) {
	int cnt = 0;
	if(A.r < B.r) {
		swap(A, B);
		swap(a, b);
	}
	int d2 = Len(B.c - A.c);
	int rd = A.r - B.r;
	int rs = A.r + B.r;
	if(d2 < rd * rd)
		return 0;		// 内含，无公切线

	double base = ANG(B.c - A.c);
	if(d2 == 0 && A.r == B.r)
		return -1;		// 重合，无数条公切线
	if(d2 == rd * rd) {		// 内切，一条公切线
		a[cnt] = A.point(base);
		b[cnt] = B.point(base);
		cnt++;
		return 1;
	}

	// 有外公切线
	double ang = acos((A.r - B.r) / sqrt(d2));
	a[cnt] = A.point(base + ang);
	b[cnt] = B.point(base + ang);
	cnt++;
	a[cnt] = A.point(base - ang);
	b[cnt] = B.point(base - ang);
	cnt++;
	if(d2 == rs * rs) {		// 外切，还有一条内公切线	
		a[cnt] = A.point(base);
		b[cnt] = B.point(base);
		cnt++;
	}
	else if(d2 > rs * rs) {		// 相离，还有两条内公切线
		double ang = acos((A.r + B.r) / sqrt(d2));
		a[cnt] = A.point(base + ang);
		b[cnt] = B.point(base + ang);
		cnt++;
		a[cnt] = A.point(base - ang);
		b[cnt] = B.point(base - ang);
		cnt++;
	}
	return cnt;
}

////////////////////////////////////////////////////////////////////////////////////
// 判断点是否在多边形内部
// 转角法
int isPointInPolygon(Point p, Polygon poly) {
	int wn = 0;
	int n = poly.size();
	for(int i = 0; i < n; i++) {
		if(OnSegment(p, poly[i], poly[(i+1) % n]))	// 在边界上
			return -1;
		int k = dcmp(Cross(poly[(i+1)%n] - poly[i], p - poly[i]));
		int d1 = dcmp(poly[i].y - p.y);
		int d2 = dcmp(poly[(i+1)%n].y - p.y);
		if(k > 0 && d1 <= 0 && d2 > 0)
			wn++;
		if(k < 0 && d2 <= 0 && d1 > 0)
			wn--;
	}
	if(wn != 0)
		return 1;	// 在内部
	return 0;	// 在外部
}

// 凸包
// p[]为输入点，ch[]为凸包点
int ConvexHull(Point *p, int n, Point *ch) {
	sort(p, p + n);
	int m = 0;
	for(int i = 0; i < n; i++) {
		while(m > 1 && Cross(ch[m-1] - ch[m-2], p[i] - ch[m-2]) <= 0)	// 若不能凸包边上有点，则改为<
			m--;														// 精度要求较高时，用dcmp比较
		ch[m++] = p[i];
	}
	int k = m;
	for(int i = n - 2; i >= 0; i--) {
		while(m > k && Cross(ch[m-1] - ch[m-2], p[i] - ch[m-2]) <= 0)
			m--;
		ch[m++] = p[i];
	}
	if(n > 1)
		m--;
	return m;
}

// 旋转卡壳 O(n)
double RoatingCalipers(int m, Point *ch) {	// m为凸包顶点数
	double ans = 0;
	int q = 1;
	for(int i = 0; i < m - 1; i++) {
		while(Cross(ch[i+1] - ch[i], ch[q+1] - ch[i]) > Cross(ch[i+1] - ch[i], ch[q] - ch[i]))
			q = (q + 1) % m;
		double tmp = max(dis2(ch[q], ch[i]), dis2(ch[q], ch[i+1]));
		ans = ans > tmp ? ans : tmp;
	}
	return sqrt(ans);
}

// 半平面交
