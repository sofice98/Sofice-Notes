# 数据结构

## 链表

```c++
//顺序存储
char s[maxn];
int next[maxn];
//链式存储
typedef struct Node {
    int value;
    Node *next;
    Node(int v = 0) :value(v), next(nullptr) {}
}Linklist;
//插入
Linklist* head = new Node();
Node* p = head;
int n;
while (scanf("%d", &n) == 1) {
    Node* newnode = new Node(n);
    p->next = newnode;
    p = p->next;
}
```



## 树

```c++
//二叉树
//顺序存储
const int maxd = 20//最大深度
int btree[1<<maxd];//最大节点个数为2^maxd-1,编号为[1,2^maxd-1]
btree[2k];btree[2k+1];//左右子树
//链式存储
typedef struct Node {
    int value;
    Node *parent, *left, *right;
    Node(int v = 0) :value(v), parent(nullptr), left(nullptr), right(nullptr) {}
}BTree;
//有根树
//左孩子右兄弟
typedef struct Node{ 
    int value;
    Node *parent, *left, *right;
    Node(int v = 0) :value(v), parent(nullptr), left(nullptr), right(nullptr) {}
}Tree;
//孩子指针数组
typedef struct node {
    int value;
    vector<node*> children;
};
```



## 图

```c++
//邻接矩阵
//获取uv关系，添加删除边都为o(1)
//稀疏图浪费空间；基本型只能记录uv间一个关系
int graph[maxv][maxv];

//邻接表
//只需o(E)空间
//获取uv关系时非o(1)；难以有效删除边
vector<vector<int>> graph;
vector<int> graph[MAX];
//加权邻接表，first为终点，second为边权值
vector<pair<int, int>> graph[MAX];

//边结点
struct Edge {
    int u, v, w;
    Edge(int u = 0,int v = 0,int w = 0) :
        u(u), v(v), w(w) {}
    bool operator< (const Edge& e) const {
        return w < e.w;
    }
};    
```

**图遍历**

```c++
int G[maxv][maxv];
bool vis[maxv];
int n;
int u, v;
f(i, 1, m) {
    scanf("%d %d", &u, &v);
    G[u][v] = 1; G[v][u] = 1;
}
//bfs
void bfs(int cur) {
    queue<int> q;
    q.push(cur);
    while (!q.empty()) {
        int i = q.front();
        q.pop();
        vis[i] = true;
        for (int j = 0; j < n; j++) {
            if (!vis[j] && G[i][j])    q.push(j);
        }
    }

}
void bfsTraverse() {
    memset(vis, 0, sizeof(vis));
    for (int i = 0; i < n; i++) {
        if (!vis[i])     bfs(i);
    }
}
//dfs
void dfs(int u) {
    vis[u] = true;
    for (int v = 0; v < n; v++) {
        if (!vis[v] && G[u][v])    dfs(v);
    }
}
void dfsTraverse() {
    memset(vis, 0, sizeof(vis));
    for (int i = 0; i < n; i++) {
        if (!vis[i])     dfs(i);
    }
}
```

**使用数组来变换方向**

```c++
const int dx[] = { -1,1,0,0 };  
const int dy[] = { 0,0,-1,1 };
int newx = x + dx[d];
int newy = y + dy[d];
```

**最短路径**

```c++
int n;
vector<pair<int, int>> graph[MAX];//加权邻接表
int dist[MAX];//距离表
bool vis[MAX];//访问表
int f[MAX];//父节点

//迪杰斯特拉算法+优先级队列，Tn=o((V+E)logV)
void Dijkstra(int src) {
    //初始化
    fill(dist, dist + MAX, INF);
    memset(vis, 0, sizeof(vis));
    dist[src] = 0; parent[src] = -1;
    //优先级队列，pair<dist[i],i>，dist小的优先
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push(make_pair(0, src)); 
    while (!pq.empty()) {
        int u = pq.top().second;
        int d = pq.top().first;
        pq.pop();
        if (vis[u]) continue;
        vis[u] = true;
        for (auto& item : graph[u]) {
            int v = item.first;
            int w = item.second;
            if (!vis[v] && dist[v] > d + w) {
                dist[v] = d + w;
                pq.push(make_pair(dist[v], v));
                parent[v] = u;
            }
        }
    }
}
```

**拓扑排序**



**欧拉回路**

除了起点和终点，其他点的度数应为偶数（进出次数相同），并且图连通。度数为奇数的点最多两个并且为起点和终点

```c++
void euler(int u){
    for(int v =0; v < n; v++)
        if(G[u][v] && !vis[u][v]){
            vis[u][v] = vis[v][u] = 1;
            euler(v);
            printf("%d %d\n", u, v);
        }
}
```



## 并查集

一种用互质集合对数据进行分类管理的数据结构

主要包括合并与查找操作

```c++
struct DisjointSet {
    vector<int> rank, p;//高度，父指针
    DisjointSet() {}
    DisjointSet(int size) {
        rank.resize(size, 0);
        p.resize(size, 0);
        for (int i = 0; i < size; i++)     makeSet(i);
    }
    //建立
    void makeSet(int x) {
        p[x] = x;
        rank[x] = 0;
    }
    //合并
    void unite(int x, int y) {
        int xp = findSet(x);
        int yp = findSet(y);
        if (rank[xp] > rank[yp])  p[yp] = xp;
        else {
            p[xp] = yp;
            if (rank[xp] == rank[yp])    rank[yp]++;
        }
    }
    //查找
    int findSet(int x) {
        if (x != p[x]) {
            p[x] = findSet(p[x]);
        }
        return p[x];
    }

    bool same(int x, int y) {
        return findSet(x) == findSet(y);
    }
};
```



## KDTree

用于k维的范围搜索树

```c++
struct Node {//树节点
    int location;
    int p, l, r;
    Node() {}
};
struct Point {//数据点
    int id, x, y;
    Point() {}
    Point(int id, int x, int y) :id(id), x(x), y(y) {}
    bool operator<(const Point& p) const {
        return id < p.id;
    }
    void print() {
        printf("%d\n", id);
    }
};
//建树，Tn=o(nlog^2n)
int makeKDTree(int l, int r, int depth) {
    if (l >= r) return NIL;
    int mid = l + r >> 1;
    int t = np++;
    if (depth % 2 == 0)  sort(P + l, P + r, lessX);
    else    sort(P + l, P + r, lessY);
    T[t].location = mid;
    T[t].l = makeKDTree(l, mid, depth + 1);
    T[t].r = makeKDTree(mid + 1, r, depth + 1);
    return t;
}
//查找，Tn=o(n^(1-1/k)+d)，d为指定范围内点的数量
void find(int v, int sx, int tx, int sy, int ty, int depth, vector<Point>& ans) {
    int x = P[T[v].location].x;
    int y = P[T[v].location].y;

    if (sx <= x && x <= tx && sy <= y && y <= ty)
        ans.push_back(P[T[v].location]);
    if (depth % 2 == 0) {
        if (T[v].l != NIL && sx<=x) 
            find(T[v].l, sx, tx, sy, ty, depth + 1, ans);
        if (T[v].r != NIL && x <= tx)
            find(T[v].r, sx, tx, sy, ty, depth + 1, ans);
    }
    else {
        if (T[v].l != NIL && sy <= y)
            find(T[v].l, sx, tx, sy, ty, depth + 1, ans);
        if (T[v].r != NIL && y <= ty)
            find(T[v].r, sx, tx, sy, ty, depth + 1, ans);
    }
}
```



## 线段树



## 树状数组



## 单调队列

求数组中一段滑动长度内的最大值或最小值，Tn=o(n)

```c++
typedef struct node {        //队列的节点，包含元素在列表中原来的位置和值
    int order;
    int value;
};
deque<node> hq;    //定义节点类型单调队列
vector<int> m;      //用于储存最大值序列

int n, k, t;           //滑动窗口长度为k，t用于暂时储存输入
node tmp;
scanf("%d%d", &n, &k);
for (int i = 0; i < n; i++) {
    scanf("%d", &t);
    while (!hq.empty() && i - hq.front().order >= k) hq.pop_front(); //剔除队头过期元素   
    while (!hq.empty() && hq.back().value <= t) hq.pop_back();     //剔除队尾小于将入列的值，保证队头为最大值
    tmp.value = t;  //节点入列
    tmp.order = i;
    hq.push_back(tmp);
    if (i >= k - 1) //开始输出           
        m.push_back(hq.front().value);
}
//前缀和+单调队列
//求区间长度[s,t]的最大子串和
int a[MAX];//[1...n]
int sum[MAX];//前缀和[1...n]
sum[0] = 0;//考虑从第一个元素开始
for (int i = 1; i <= n; i++)	sum[i] = sum[i - 1] + a[i];
hq.push_back(0);
for (int i = 1; i <= n; i++) {
    while (!hq.empty() && sum[hq.back()] > sum[i]) hq.pop_back();
    hq.push_back(i);
    while (!hq.empty() && t < i - hq.front()) hq.pop_front();
    ans = max(ans, sum[i] - sum[hq.front()]);
}
printf("%d\n", ans);
```





# 搜索

搜索问题中，最重要的思路就是：**缩减搜索空间**

## 双指针

https://leetcode-cn.com/problems/two-sum-ii-input-array-is-sorted/solution/yi-zhang-tu-gao-su-ni-on-de-shuang-zhi-zhen-jie-fa/

## 二分搜索

满足单调，有最大最小值

一般用于求最小化最大值、最大化最小值

```c++
//二分模版
int left = 0;
int right = n;
while (left <= right) {
    int mid = left + right >> 1;
    if (A[mid] == key) return mid;
    else if (key < A[mid]) right = mid - 1;
    else    left = mid + 1;
}
//双分支，解决问题常用，关键在于建模和check()   
int ans;          //记录答案
while (right - left > 1) {//一定要有1，否则跳不出循环
        int mid = left + right >> 1;
        if (check(mid)){  //检查条件，如果成立
            ans = mid;    
            left = mid;
        }
        else   right = mid;        
}
//实数二分
while(right - left > eps)  　{ ... } //给定精度
for(int i = 0; i < 100; i++) { ... }//精度为1/2^100

//三分法求单峰、谷极值 
//实数
while(R-L > eps){  
    double k =(R-L)/3.0;
    double mid1 = L+k, mid2 = R-k;
    if(check(mid1) > check(mid2)) 
        R = mid2;
    else   L = mid1;
}
//整数
while(R - L > 1){  
    int mid1 = left + (right - left)/3;
    int mid2 = right- (right - left)/3;
    if(check(mid1) > check(mid2))
        R = mid2;
    else   L = mid1;
}
```

lower_bound(起始地址，结束地址，要查找的数值) 返回的是数值 **第一个** 出现的位置，大于等于

upper_bound(起始地址，结束地址，要查找的数值) 返回的是数值 **最后一个** 出现的位置，大于

binary_search(起始地址，结束地址，要查找的数值)  返回的是是否存在这么一个数，是一个**bool值**

## 回溯法

递归函数不满足条件时，不再调用，而是返回上一层调用（递归枚举）

当修改全局变量时，在出口处应当改回来

```c++
void dfs(int cur) {
    if (cur == n) {//到达规定最深处
        //输出结果
        printf("%d", res);
        return;
    }
    //不满足则不继续递归，剪枝
    if (flag) {
        res[cur] = i;//赋值
        vis[i] = true;//设置访问标志
        dfs(cur + 1);//递归搜索
        vis[i] = false;//解除访问标志
    }
    
}
```



## 状态空间搜索

找到一个从初始状态到终止状态的路径，等价于隐式图的最短路径查找

```c++
typedef int State[9];           //定义状态类型
const int maxstate = 1000000;	//最大状态数
State st[maxstate], goal;       //状态数组
int dist[maxstate];             //距离数组
int vis[362880], fact[9];       //状态访问数组和阶乘表
int fa[maxstate];               //父节点编号
const int dx[] = { -1,1,0,0 };	//用数组移动
const int dy[] = { 0,0,-1,1 };
int front = 1, rear = 2;		//头尾指针

int bfs() {
    init_lookup_table();//初始化查找表
    while (front < rear) {
        State& s = st[front];//当前状态
        if(memcmp(goal, s, sizeof(s)) == 0)    return front;//找到目标状态
        for (int d = 0; d < 4; d++) {//尝试搜索下一个相邻状态
            if (flag) {//如果合法
                State& t = st[rear];//扩展新节点
                memcpy(&t, &s, sizeof(s));
                dist[rear] = dist[front] + 1;//更新距离值
                if (try_to_insert(rear)) {
                    fa[rear] = front;
                    rear++;
                }
            }
        }
        front++;
    }
    return 0;//失败
}
```

需要输出过程时，要加上父指针和状态数组

> Eight digital

## 迭代加深搜索(IDDFS)

在DFS的搜索里面，可能会面临一个答案的层数很低，但是DFS搜到了另为一个层数很深的分支里面导致时间很慢，但是又卡BFS的空间

设置递归深度上限的回溯法，每轮依次增加最大递归深度，在深度没有明显上限以及宽度太大的时候，可以使用这种方式

+ 要求必须有解
+ 时间复杂度只比BFS稍差一点（虽然搜索k+1层时会重复搜索k层，但是整体而言并不比广搜慢很多）
+ 空间复杂度与深搜相同，却比广搜小很多

```c++
bool dfs(int cur) {
    if (cur == maxd) {
        if (flag) return false;//没找到解
        if (better(cur))   memcpy(ans, v, sizeof(LL) * (d + 1));//当前解更优
        return true;
    }
    bool ok = false;
    for (int i = from;; i++) {//遍历所有后继状态
        if (bb * (maxd + 1 - d) <= i * aa) break;//剪枝
        v[d] = i;//赋值
        if (dfs(cur + 1))  ok = true;
    }
    return ok;
}

for (maxd = 1;; maxd++) {//迭代加深，每一次循环增加递归最大深度
    memset(ans, -1, sizeof(ans));//初始化结果    
    if (dfs(0)) {//如果找到结果
    	ok = 1; break;//退出循环
    }
}
```

**IDA***

当设计出乐观估计函数，预测从当前节点至少还需要扩展几层节点才有可能得到解，则变成了IDA*











# 动态规划

具有最优子结构（全局最优解包含局部最优解），可以用状态转移（状态转移方程）解决的一个方法

直接递归时，效率往往底下，原因是相同的子问题被重复计算了多次

设置dp含义，求dp转移方程，设置剪枝

```c++
//数字三角形
//递推计算法
for (int j = 1; j < n; j++)    dp[n][j] = a[n][j];//计算最后一列
for (int i = n - 1; i >= 1; i--)//从下往上递推
    for (int j = 1; j <= i; j++)
        dp[i][j] = a[i][j] + max(dp[i + 1][j], dp[i + 1][j + 1]);
//记忆化搜索
memset(dp, -1, sizeof(d));//如果为-1则未访问过
int solve(int i, int j) {
    if (dp[i][j] >= 0)  return dp[i][j];//直接取之前计算过的
    return dp[i][j] = a[i][j] + (i == n ? 0 : max(solve(i + 1, j), solve(i + 1, j + 1)));
}
```

**滚动数组**

用到上一行的结果，从后向前滚动；用到本行的结果，从前向后滚动

**经典动态规划问题**

+ 0/1背包

  $dp[i][j]=max(dp[i-1][j],dp[i-1][j-w[i]]+v[i]$

  可以用滚动数组，j需倒序计算，$dp[j] = max(dp[j], dp[j - w[i]] + v[i])$

+ 完全背包

  $dp[i][j]=max(dp[i-1][j],dp[i][j-w[i]]+v[i]$

  可以用滚动数组，j正序计算，$dp[j] = max(dp[j], dp[j - w[i]] + v[i])$

+ 硬币问题 

  $dp[i][j] = min(dp[i - 1][j], dp[i][j - coins[i]] + 1)$

  滚动数组：$dp[j] = min(dp[j], dp[j - coins[i]] + 1)$
  
+ 最长公共子序列

  $dp[i][j] = dp[i - 1][j - 1] + 1，\quad\quad\quad\quad x[i] = y[j]\\dp[i][j] = max(dp[i][j - 1], dp[i - 1][j])，x[i] \not= y[j]$

+ 最长递增子序列

  $dp[i]=max(dp[j])\quad 0<j<i\,,A_j<A_i\quad T(n)=O(n^2)$

  二分：大于L末尾元素添加，否则lower_bound(a[i])=a[i]

+ 编辑距离

  $dp[i][j] = dp[i - 1][j - 1] + 1，\quad\quad\quad\quad\quad\quad\quad\quad\quad\quad\quad\quad s1[i] = s2[j]\\dp[i][j] = min(dp[i][j - 1], dp[i - 1][j], dp[i - 1][j-1])+1，s1[i] \not= s2[j]$
  
+ 斐波那契数列

  可以不使用dp，只用prev2，prev1，cur三个变量



**DAG(Directed acyclic graph)**

许多动态规划问题都可以转化为DAG上的最长路最短路或路径计数问题





# 字符串

子串要连续，子序列不要求连续

**分割字符串**，实现split

```c++
char* p1, * p2 = &s[0]; p2--;
while(1){
    p1 = ++p2;
    for (char* b = p2; *b != ' ' && *b != '\0';b++) p2++;
    string tmp(p1, p2);
}
```



# 数论

## 素数

关于素数，有以下有趣的事实：
   （1）素数的数量有无限多。
   （2）素数的分布。随着*x*x的增大，素数的分布越来越稀疏；第n个素数渐进于logn；随机整数*x*x是素数的概率是1/log *x*x。
   （3）对于任意正整数n，存在至少n个连续的正合数。
   有大量关于素数的猜想，著名的有：
   （1）波特兰猜想。对任意给定的正整数n > 1，存在一个素数p，使得n < p < 2n。已经证明。
   （2）孪生素数猜想。存在无穷多的形如p和p+2的素数对。
   （3）素数等差数列猜想。对任意正整数n >2，有一个由素数组成的长度为n的等差数列。
   （4）哥德巴赫猜想。每个大于2的正偶数可以写成两个素数的和。这是最有名的素数猜想，也是最令人头疼的猜想，已经困扰数学家3世纪。至今为止，最好的结果仍然是陈景润1966年做出的。

+ **费马素性测试**

**费马小定理**：设n是素数，*a*a是正整数且与n互质，那么有$a^{n−1}≡1(mod\,\,n)$

为了测试n是否为素数，在1~n之间任选一个随机的基值*a*a，注意*a*a并不需要与n互质：
  （1）如果$a^{n−1}≡1(mod\,\,n)$不成立，那么n肯定不是素数。这实际上是费马小定理的逆否命题。
  （2）如果$a^{n−1}≡1(mod\,\,n)$成立，那么n很大概率是素数，尝试的a越多，n是素数的概率越大。称n是一个基于a的**伪素数**。

可惜的是，从（2）可以看出费马素性测试并不是完全正确的。对某个a值，总有一些合数被误判而通过了测试；不同的*a*a值，被误判的合数不太一样。特别地，有一些合数，不管选什么a值，都能通过测试。这种数叫做**Carmichael数**，前三个数是561、1105、1729。不过，Carmichael数很少，前1亿个正整数中只有255个。而且当n趋向无穷时，Carmichael数的分布极为稀疏，费马素性测试几乎不会出错，所以它是一种相当好的方法。

+ **Miller-Rabin素性测试**

  用费马测试排除掉非Carmichael数，而大部分Carmichael数用下面介绍的推论排除

  如果p是一个奇素数，且e≥1，则方程$x^2≡1(mod\,\,p^e)$，仅有两个解：x = 1和x = -1。

  令 $n−1=2^tu$，其中u是奇数，t是正整数，即n-1的二进制表示，是奇数u的二进制表示，后面加t个零。先算出$a^u\,mod\,\,n$，然后对结果连续平方t次取模。

  设有s个a，共做s次测试，出错的概率是$2^{-s}$。当s = 50时，出错概率已经小到可以忽略不计了。

```c++
//小素数判定
bool isPrime(int x) {
    if (x < 2) return false;
    else if (x == 2) return true;
    if (x & 1 == 0) return false;
    for (int i = 3; i * i <= x; i += 2) 
        if (x % i == 0) return false;
    return true;
}
//大素数判定
bool witness(uLL a, uLL n){       // Miller-Rabin素性测试。返回true表示n是合数
        uLL u = n-1; 
        int t = 0;              // n-1的二进制，是奇数u的二进制，后面加t个零
        while(u & 1 == 0) u = u >> 1, t++;    // 整数n-1末尾有几个0，就是t
        uLL x1, x2;
        x1 = fast_pow(a,u,n);            // 先计算  a^u mod n
        
        for(int i = 1; i <= t; i++) {        // 做t次平方取模
            x2 = fast_pow(x1,2,n);       // x1^2 mod n
            if(x2 == 1 && x1 != 1 && x1 != n-1) return true;  //用推论判断
            x1 = x2;
        }
        if(x1 != 1) return true;         //最后用费马测试判断是否为合数
        return false;
}

bool MillerRabin(uLL n,int s){            //对n做s次测试
    if(n < 2)  return 0;  
    if(n == 2) return 1;                   
    if(n & 1 == 0 ) return 0;            

	for(int i = 0;i < s && i < n;i++){   //做s次测试
		uLL a = rand() % (n - 1) + 1;     
 		if(witness(a,n))  return false;      //n是合数，返回0           	              
	}
 	return true;                            //n是素数，返回1
}
//素数筛
int prime[MAX];//第i个素数
bool is_prime[MAX + 1];//第i个是否为素数
int sieve(int n) {
    int p = 0;
    for (int i = 0; i <= n; i++) is_prime[i] = true;
    is_prime[0] = is_prime[1] = false;
    for (int i = 2; i <= n; i++) {
        if (is_prime[i]) {
            prime[i] = i;
            for (int j = 2 * i; j <= n; j += i) is_prime[i] = false;
        }
    }
    return p;
}
```



## 因数

**贝祖定理**：如果a、b是整数，那么一定存在整数x、y使得ax+by=gcd(a,b)

如果ax+by=1有解，那么gcd(a,b)=1

（1）gcd(a,b) = gcd(a, ka+b)
（2）gcd(ka, kb) = k·gcd(a, b)
（3）定义多个整数的最大公约数：gcd(a, b, c) = gcd(gcd(a, b), c)
（4）若gcd(a, b) = d，则gcd(a/d, b/d) = 1，即a/d与b/d互素。
（5）**二元线性丢番图方程**ax+by=c有解的充分必要条件是d=gcd(a,b)能整除c，通解为：x=x0+(b/d)n，y=y0−(a/d)n

```c++
//辗转相除法，递归开销大，要求a>=b
int gcd(LL a, LL b) {
    return a % b == 0 ? b : gcd(b, a % b);
}
//扩展欧里几德，求解二元线性丢番图方程
ll extgcd(ll a, ll b, ll& x, ll& y) {
    ll d = 1;
    if (b != 0) {
        d = extgcd(b, a % b, y, x);
        y -= (a / b) * x;
    }
    else {
        x = 1; y = 0;
    }
    return d;
}
//最小公倍数
int lcm(int a, int b){ 
	return a / gcd(a, b) * b;
}

//更相减损法
int qGCD(int a, int b)
{
	if(a == 0) return b;
	if(b == 0) return a;
	if(!(a & 1) && !(b & 1)) // a % 2 == 0 && b % 2 == 0;
		return qGCD(a >> 1, b >> 1) << 1;
	else if(!(b & 1))
		return qGCD(a, b >> 1);
	else if(!(a & 1))
		return qGCD(a >> 1, b);
	else
		return qGCD(abs(a - b), min(a, b));
}
```

## 质因数分解

```c++
int p[20];  //p[]记录因子，p[1]是最小因子。一个int数的质因子最多有10几个
int c[40];  //c[i]记录第i个因子的个数。一个因子的个数最多有30几个
//试除法
void factorization(int n){
    int m = 0;
    for(int i = 2; i*i <= n; i++)
        if(n%i == 0){
           p[++m] = i, c[m] = 0;
           while(n%i == 0)            //把n中重复的因子去掉
              n/=i, c[m]++;    
        }
    if(n>1)                           //没有被除尽，是素数
       p[++m] = n, c[m] = 1;  
}

```

## 同余

**一元线性同余方程**

设x是未知数，给定a、b、m，求整数x，满足ax≡b(mod m)，等同于求解二元线性丢番图方程

有解的充分必要条件是d=gcd(a,m)能整除b

**逆**

给定整数a，且满足gcd(a,m)=1，称 ax≡1(mod m)的一个解为a模m的逆。记为$a^{−1}$

```c++
//求逆
//扩展欧几里得
ll mod_inverse(ll a, ll m){    
	ll x,y;
    if(extgcd(a,m,x,y))
    	return  (x % m + m) % m;                          //保证返回最小正整数
    else return -1;
}
//费马小定理
ll mod_inverse(ll a,ll mod){
   return fast_pow(a,mod - 2,mod);           
}
```





## 快速幂

```c++
//o(logn)，以x为底，n为指数，对mod取模的幂
ll fast_pow(ll x, ll n, ll mod) {
    ll res = 1;
    while (n > 0) {
        if (n & 1) res = res * x % mod;
        x = x * x % mod;
        n >>= 1;
    }
    return res;
}
```



# 编码

## 全排列映射到整数

```c++
int vis[362880], fact[9];       //状态访问数组和阶乘表
void init_lookup_table() {
    fact[0] = 1;
    for (int i = 1; i < 9; i++)    fact[i] = fact[i - 1] * i;
}

int try_to_insert(int s) {
    int code = 0;//把st[s]映射到整数code
    for (int i = 0; i < 9; i++) {
        int cnt = 0;
        for (int j = i + 1; j < 9; j++)  if (st[s][j] < st[s][i])   cnt++;
        code += fact[8 - i] * cnt;
    }
    if (vis[code])   return 0;
    return vis[code] = 1;
}
```

## 子集生成

二进制法：一位表示一个元素是否在集合中

```c++
void print_subset(int n, int s) {//打印整数s表示的子集
    for (int i = 0; i < n; i++)
        if (s & (1 << i)) printf("%d ", i);
    printf("\n");
}
void generate_subset(int n) {
    //枚举整数
    for (int i = 1; i < (1 << n); i++) {
        print_subset(n, i);
    }
}
```



## 位图

可用一个n位长的bool串表示一个所有元素都小于n的简单非负整数集合

从而方便排序等操作

```c++
//使用为逻辑运算来实现位向量
#define BITSPERWORD 32//一个int元素代表32位
#define  SHIFT 5//计算商
#define MASK 0x1F//计算余数
#define N 10000000//位数不超过10000000
int a[1 + N/BITSPERWORD];//计算需要多少个int
void set(int i){
	a[i>>SHIFT] |= (1<<(i & MASK));
}
void clr(int i){
	a[i>>SHIFT] &= ~(1<<(i & MASK));
}
int test(int i){
	return a[i>>SHIFT] & (1<<(i & MASK));
}
```







# 排序

常见排序算法：

| 排序算法          | 最好T(n) | 平均T(n) | 最坏T(n) | S(n) | 稳定性 | 每趟全局有序 | 链表         |
| ----------------- | -------- | -------- | -------- | ---- | ------ | ------------ | ------------ |
| 直接插入/折半插入 | n        | n2       | n2       | 1    | 1      | 0            | 单/0         |
| 希尔排序          | n        | n1.25    | n1.5     | 1    | 0      | 0            | 0            |
| 冒泡排序          | n        | n2       | n2       | 1    | 1      | 1            | 顺链表顺序冒 |
| 快速排序          | nlogn    | nlogn    | n2       | logn | 0      | 1            | 单           |
| 简单选择排序      | n2       | n2       | n2       | 1    | 0      | 1            | 单           |
| 堆排序            | nlogn    | nlogn    | nlogn    | 1    | 0      | 1            | 树链         |
| 归并排序          | nlogn    | nlogn    | nlogn    | n    | 1      | 0            | 0            |
| 基数排序          | d(n+r)   | d(n+r)   | d(n+r)   | r    | 1      | 0            | 单           |
| 计数排序          | n+k      | n+k      | n+k      | k    | 1      | 1            | 单           |

## Kth Element   问题







# STL

## c++

**vector动态数组**：insert(p,x)，erase(p)都为o(n)

**stack栈**：所有操作o(1)

**queue队列**：所有操作o(1)

**list双向链表**：可以在front处操作，insert(p,x)，erase(p)都为o(1)

**set集合**：insert(key)，erase(key)，find(key)都为o(logn)

**map字典**：insert( (key，val) )，erase(key)，find(key)都为o(logn)

**priority_queue优先级队列**：默认大根堆

```c++
//降序队列，大顶堆，大的优先
priority_queue <int,vector<int>,less<int> >q;
//升序队列，小顶堆，小的优先，或者默认的乘-1
priority_queue <int,vector<int>,greater<int> > q;
//自定义排序，重载仿函数
struct cmp{
    bool operator()(const pair<int, int> &a, const pair<int, int> &b){
            return a.first + a.second < b.first + b.second;//返回true时，说明a的优先级低于b
    }
};
priority_queue<pair<int, int>, vector<pair<int, int>>, cmp> pq;
//自定义node，重载操作符
struct node{
      int x, y;
      node(int x, int y):x(x),y(y){}
      bool operator< (const node &b) const {
           if(x == b.x)  return y >= b.y;
           else return x > b.x;
      }
};
priority_queue<node> pq;
```

## java





# 小技巧

+ 常用变量

  ```c++
  #include<bits/stdc++.h>
  using namespace std;
  typedef long long ll;
  typedef unsigned long long ull;
  constexpr int MOD = 1e9 + 7;
  constexpr int INF = 0x7fffffff;
  constexpr int MAX = 10000;
  constexpr double eps = 1e-7;
  #define f(i, a, b) for(int i = a;i <= b;i++)
  #define equals(a, b) ( fabs( (a) - (b) ) < eps )
  ```

+ 编码解码映射哈希可提高速度

+ 提前求出素数表，阶乘表或多个test公共变量，可加快速度

+ ```c++
  while (scanf("%d", &n) == 1 && n != 0)//n=0结束
  while (scanf("%d", &n) != EOF)//到文档末尾结束
  ```

+  ```c++
  //重定向文件IO
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);
  //不使用重定向的文件IO
  FILE* fin, * fout;
  fin = fopen("data.in", "rb");//标准fin=stdin,fout=stdout
  fout = fopen("data.out", "wb");
  fscanf(fin, "%d", &x);
  fprintf(fout, "%d", x);
  ```
  
+ 枚举排列：

  ```c++
  void print_permutation(序列A，集合S){
      if(S空) 输出序列A
    else 按照顺序考虑S的每个元素v{
          print_permutation(在A末尾添加v，S-{v})
      }       
  }
  ```
  
  或使用next_permutation函数
  
+ 生成一个大随机数
  ```c++
  unsigned long ulrand(){          
      return (
        (((unsigned long)rand()<<24)& 0xFF000000ul)
       |(((unsigned long)rand()<<12)& 0x00FFF000ul)
       |(((unsigned long)rand())    & 0x00000FFFul));
  }
  ```
  
+ 快速读
  
  ```c++
  iostream::sync_with_stdio(false);
  inline int read() {
        int ret = 0, op = 1;
        char c = getchar();
        while (!isdigit(c)) {
            if (c == '-') op = -1; 
            c = getchar();
        }
        while (isdigit(c)) {
            ret = (ret << 3) + (ret << 1) + c - '0';
            c = getchar();
	      }
	      return ret * op;
	  }
	```

- 计算平方时直接用乘法，比sqrt快



# 注意事项

+ 对每个int变量关注其值是否会超过int范围，改为long或long long
+ 赋值时记得类型转换
+ 一定要加上对特殊情况的判别，不但会提高正确率，还能减少Runtime（如开头加上对空参数的判别输出）
+ 大数组申请为全局变量
+ 即使是暴力枚举，也是要认真分析问题的，以减少枚举量
+ 最后答案要求取模时，前面每一步+-*之后都要取模再保存



















