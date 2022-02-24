/**********
*���㼸��ѧ
*Sofice
*2020/8/7
***********/
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
constexpr int MOD = 1e9 + 7;
constexpr int INF = 0x7fffffff;
constexpr int MAX = 10000;
constexpr double eps = 1e-7;
#define f(i, a, b) for(int i = a;i <= b;i++)
#define equals(a, b) ( fabs( (a) - (b) ) < eps )
/*************************����*************************/
//ccw
constexpr const int COUNTER_CLOCKWISE = 1;//��ʱ��
constexpr const int CLOCKWISE = -1;//˳ʱ��
constexpr const int ONLINE_BACK = 2;//������
constexpr const int ONLINE_FRONT = -2;//������
constexpr const int ON_SEGMENT = 0;//�߶���
//contains
constexpr const int IN = 2;//�������
constexpr const int ON = 1;//�������
constexpr const int OUT = 0;//�������
//manhattanIntersection
constexpr const int BOTTOM = 0;
constexpr const int LEFT = 1;
constexpr const int RIGHT = 2;
constexpr const int TOP = 3;
/***********************�ṹ��************************/
//�㣬����
typedef struct Point {
    double x, y;

    Point(double x = 0, double y = 0) :x(x), y(y) {}

    Point operator + (Point p) { return Point(x + p.x, y + p.y); }
    Point operator - (Point p) { return Point(x - p.x, y - p.y); }
    Point operator * (double a) { return Point(a * x, a * y); }
    Point operator / (double a) { return Point(x / a, y / a); }
    //L2����
    double abs() { return sqrt(norm()); }
    double norm() { return x * x + y * y; }

    bool operator < (const Point& p) const {
        return x != p.x ? x < p.x : y < p.y;
    }
    bool operator == (const Point& p) const {
        return fabs(x - p.x) < eps && fabs(y - p.y) < eps;
    }
}Vector;
//�߶Σ�ֱ��
typedef struct Segment {
    Point p1,p2;
}Line;
//�����
typedef vector<Point> Polygon;
/***********************����************************/
//�ڻ�
double dot(Vector a, Vector b) {
    return a.x * b.x + a.y * b.y;
}
//���
double cross(Vector a, Vector b) {
    return a.x * b.y - a.y * b.x;
}
//����
bool isOrthogonal(Vector a, Vector b) {
    return equals(dot(a, b), 0.0);
}
bool isOrthogonal(Point a1, Point a2, Point b1, Point b2) {
    return isOrthogonal(a1 - a2, b1 - b2);
}
bool isOrthogonal(Segment s1, Segment s2) {
    return equals(dot(s1.p2 - s1.p1, s2.p2 - s2.p1), 0.0);
}
//ƽ��
bool isParallel(Vector a, Vector b) {
    return equals(cross(a, b), 0.0);
}
bool isParallel(Point a1, Point a2, Point b1, Point b2) {
    return isParallel(a1 - a2, b1 - b2);
}
bool isParallel(Segment s1, Segment s2) {
    return equals(dot(s1.p2 - s1.p1, s2.p2 - s2.p1), 0.0);
}
//ͶӰ����p���߶�s�ϵ�ͶӰ
Point project(Segment s, Point p) {
    Vector base = s.p2 - s.p1;
    double r = dot(p - s.p1, base) / base.norm();
    return s.p1 + base * r;
}
//ӳ�񣬵�p�����߶�s����ԳƵ�
Point reflect(Segment s, Point p) {
    return p + (project(s, p) - p) * 2.0;
}
//����
double getDistance(Point a, Point b) {
    return (a - b).abs();
}
double getDistanceLP(Line l, Point p) {
    return abs(cross(l.p2 - l.p1, p - l.p1) / (l.p2 - l.p1).abs());
}
double getDistanceSP(Segment s, Point p) {
    if (dot(s.p2 - s.p1, p - s.p1) < 0.0)   return (p - s.p1).abs();
    if (dot(s.p1 - s.p1, p - s.p2) < 0.0)   return (p - s.p2).abs();
    return getDistanceLP(s, p);
}
//��ʱ�뷽�򣬵�p2������p0p1���ĸ�����
int ccw(Point p0, Point p1, Point p2) {
    Vector a = p1 - p0;
    Vector b = p2 - p0;
    if (cross(a, b) > eps) return COUNTER_CLOCKWISE;
    if (cross(a, b) < -eps) return CLOCKWISE;
    if (dot(a, b) < -eps) return ONLINE_BACK;
    if (a.norm() < b.norm()) return ONLINE_FRONT;
    return ON_SEGMENT;
}
//�ཻ���ж��߶�p1p2��p3p4�Ƿ��ཻ
bool intersect(Point p1, Point p2, Point p3, Point p4) {
    return (ccw(p1, p2, p3) * ccw(p1, p2, p4) <= 0 &&
        ccw(p3, p4, p1) * ccw(p3, p4, p2) <= 0);
}
bool intersect(Segment s1, Segment s2) {
    return intersect(s1.p1, s1.p2, s2.p1, s2.p2);
}
//���㣬�߶�s1��s2�Ľ���
Point getCrossPoint(Segment s1, Segment s2) {
    Vector base = s2.p2 - s2.p1;
    double d1 = abs(cross(base, s1.p1 - s2.p1));
    double d2 = abs(cross(base, s1.p2 - s2.p1));
    double t = d1 / (d1 + d2);
    return s1.p1 + (s1.p2 - s1.p1) * t;
}
/***********************����ڰ�************************/
int contains(Polygon g, Point p) {
    int n = g.size();
    bool x = false;
    for (int i = 0; i < n; i++) {
        Vector a = g[i] - p;
        Vector b = g[(i + 1) % n] - p;
        if (abs(cross(a, b)) < eps && dot(a, b) < eps) return ON;
        if (a.y > b.y) swap(a, b);
        if (a.y < eps && eps < b.y && cross(a, b) > eps) x = !x;
    }
    return (x ? 2 : 0);
}
/***********************���͹��************************/
Polygon andrewScan(Polygon s) {
    Polygon u, l;
    if (s.size() < 3) return s;
    sort(s.begin(), s.end());
    //��xֵ��С��2���������u
    u.push_back(s[0]);
    u.push_back(s[1]);
    //��xֵ����2���������l
    l.push_back(s[s.size() - 1]);
    l.push_back(s[s.size() - 2]);

    //ÿһ���ڼ����½��֮ǰ��ĩβ������͹���ĵ�ɾ��
    //����͹���ϲ�
    for (int i = 2; i < s.size(); i++) {
        for (int n = u.size(); n >= 2; n--) {
            int ccwans = ccw(u[n - 2], u[n - 1], s[i]);
            if(ccwans != CLOCKWISE && ccwans != ONLINE_FRONT)
                u.pop_back();
        }
        u.push_back(s[i]);
    }
    //����͹���²�
    for (int i = s.size() - 3; i >= 0; i--) {
        for (int n = l.size(); n >= 2; n--) {
            int ccwans = ccw(l[n - 2], l[n - 1], s[i]);
            if (ccwans != CLOCKWISE && ccwans != ONLINE_FRONT)
                l.pop_back();
        }
        l.push_back(s[i]);
    }

    //��˳ʱ�뷽������͹���ĵ������
    for (int i = 1; i <= l.size() - 2; i++) u.push_back(l[i]);
    return u;
}
/***********************�߶��ཻ���⣺�����ټ���************************/
struct EndPoint {
    Point p;
    int seg, st;//�߶�ID���˵�����
    EndPoint() {}
    EndPoint(Point p, int seg, int st) :p(p), seg(seg), st(st) {}
    bool operator < (const EndPoint& ep) const {
        //��˳���£����ң�������
        if (p.y == ep.p.y) return st < ep.st;
        else return p.y < ep.p.y;
    }
};
EndPoint EP[MAX];
int manhattanIntersection(vector<Segment> s) {
    int n = s.size();
    for (int i = 0, k = 0; i < n; i++) {
        //��֤��С�Ҵ�
        if (s[i].p1.y == s[i].p2.y) {
            if (s[i].p1.x > s[i].p2.x) swap(s[i].p1, s[i].p2);
        }
        else if (s[i].p1.y > s[i].p2.y) swap(s[i].p1, s[i].p2);

        //��ˮƽ�߶�������˵��б�
        if (s[i].p1.y == s[i].p2.y) {
            EP[k++] = EndPoint(s[i].p1, i, LEFT);
            EP[k++] = EndPoint(s[i].p2, i, RIGHT);
        }
        //����ֱ�߶�������˵��б�
        else {
            EP[k++] = EndPoint(s[i].p1, i, BOTTOM);
            EP[k++] = EndPoint(s[i].p2, i, TOP);
        }
    }
    sort(EP, EP + 2 * n);
    set<int>BT;//����������
    BT.insert(INF);
    int cnt = 0;
    for (int i = 0; i < 2 * n; i++) {
        if (EP[i].st == TOP) BT.erase(EP[i].p.x);
        else if (EP[i].st == BOTTOM) BT.insert(EP[i].p.x);
        else if (EP[i].st == LEFT) {
            set<int>::iterator b = BT.lower_bound(s[EP[i].seg].p1.x);//o(logn)
            set<int>::iterator e = BT.upper_bound(s[EP[i].seg].p2.x);//o(logn)
            cnt += distance(b, e);//o(k)
        }
    }
    return cnt;
}

int main() {
    int n;
    scanf("%d", &n);
    Polygon p;
    f(i, 1, n) {
        float x, y;
        scanf("%f %f", &x, &y);
        p.push_back(Point(x,y));
    }
    Polygon ans = andrewScan(p);
    for (auto it : ans) 
        printf("%.2f %.2f\n", it.x, it.y);

    system("pause");
    return 0;
}
