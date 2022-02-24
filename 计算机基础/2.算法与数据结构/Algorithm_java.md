[维基百科算法与数据结构](https://oi-wiki.org)

ACM模式模板：

```java
import java.io.*;
import java.util.*;
public class Main{
    public static void main(String[] args) throws IOException{
        Scanner in = new Scanner(System.in);
        int q = in.nextInt();
        // BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
        String[] arg = in.nextLine().split(" ");
        int n = Integer.parseInt(arg[0]);
        int m = Integer.parseInt(arg[1]);
        int k = Integer.parseInt(arg[2]);
        int[][] a = new int[n][m];
        for (int i = 0; i < n; i++){
            arg = in.nextLine().split(" ");
            for(int j = 0; j < m; j++){
                a[i][j] = Integer.parseInt(arg[j]);
            }
        }
        fun();
    }

    public static boolean fun(int[][] arr,int target){
        
    }
}
```



# 一、数据结构

## :chains: 链表

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



## :evergreen_tree: 树

```java
//二叉树
//顺序存储
int maxd = 20//最大深度
int[] btree = new int[1<<maxd];//最大节点个数为2^maxd-1,编号为[1,2^maxd-1]
btree[2k];btree[2k+1];//左右子树
//链式存储
public class TreeNode {
    int val;
  	TreeNode left;
  	TreeNode right;
  	TreeNode() {}
  	TreeNode(int val) { this.val = val; }
  	TreeNode(int val, TreeNode left, TreeNode right) {
    		this.val = val;
    		this.left = left;
    		this.right = right;
  	}
}

//有根树
//左孩子右兄弟
class Node {
    int val;
    Node parent, left, right;
    
    public Node() {}
    public Node(int _val) {
        val = _val;parent = null;left = null;right = null;
    }
    public Node(int _val, Node _parent, Node _left, Node _right) {
        val = _val;parent = _parent;left = _left;right = _right;
    }
}
//孩子指针数组
class Node {
    public int val;
    public List<Node> children;

    public Node() {}

    public Node(int _val) {
        val = _val;
    }

    public Node(int _val, List<Node> _children) {
        val = _val;
        children = _children;
    }
};
```

### 遍历

前中后序遍历

前序遍历求深度，后序遍历求高度

```java
// 前序遍历顺序：中-左-右，入栈顺序：中-右-左
public List<Integer> preorderTraversal(TreeNode root) {
    List<Integer> result = new ArrayList<>();
    if (root == null){
        return result;
    }
    Stack<TreeNode> stack = new Stack<>();
    stack.push(root);
    while (!stack.isEmpty()){
        TreeNode node = stack.pop();
        result.add(node.val);
        if (node.right != null){
            stack.push(node.right);
        }
        if (node.left != null){
            stack.push(node.left);
        }
    }
    return result;
}

// 中序遍历顺序: 左-中-右 入栈顺序： 左-右
public List<Integer> inorderTraversal(TreeNode root) {
    List<Integer> result = new ArrayList<>();
    if (root == null){
        return result;
    }
    Stack<TreeNode> stack = new Stack<>();
    TreeNode cur = root;
    while (cur != null || !stack.isEmpty()){
        if (cur != null){
            stack.push(cur);
            cur = cur.left;
        }else{
            cur = stack.pop();
            result.add(cur.val);
            cur = cur.right;
        }
    }
    return result;
}

// 后序遍历顺序 左-右-中 入栈顺序：中-左-右 出栈顺序：中-右-左， 最后翻转结果
public List<Integer> postorderTraversal(TreeNode root) {
    List<Integer> result = new ArrayList<>();
    if (root == null){
        return result;
    }
    Stack<TreeNode> stack = new Stack<>();
    stack.push(root);
    while (!stack.isEmpty()){
        TreeNode node = stack.pop();
        result.add(node.val);
        if (node.left != null){
            stack.push(node.left);
        }
        if (node.right != null){
            stack.push(node.right);
        }
    }
    Collections.reverse(result);
    return result;
}

```

层次遍历

```java
// 队列
public List<List<Integer>> levelOrder(TreeNode root) {
    List<List<Integer>> res = new ArrayList<>();
    if(root == null) return res;
    Queue<TreeNode> q = new LinkedList<>();
    q.offer(root);
    while(!q.isEmpty()){
        List<Integer> tmpList = new ArrayList<Integer>();

        for(int len = q.size();len > 0;len--){
            TreeNode tmpNode = q.poll();
            tmpList.add(tmpNode.val);

            if (tmpNode.left != null) q.offer(tmpNode.left);
            if (tmpNode.right != null) q.offer(tmpNode.right);
        }

        res.add(tmpList);
    }
    return res;
}

// 递归
public List<List<Integer>> levelOrder(TreeNode root) {
    fun(root,0);
    return resList;
}
public void fun(TreeNode node, Integer deep) {
    if (node == null) return;
    deep++;

    if (resList.size() < deep) {
        //当层级增加时，list的Item也增加，利用list的索引值进行层级界定
        List<Integer> item = new ArrayList<Integer>();
        resList.add(item);
    }
    resList.get(deep - 1).add(node.val);

    checkFun01(node.left, deep);
    checkFun01(node.right, deep);
}
```

morris遍历



## :chart_with_upwards_trend: 图

```java
//邻接矩阵
//获取uv关系，添加删除边都为o(1)
//稀疏图浪费空间；基本型只能记录uv间一个关系
int[][] graph;

//邻接表
//只需o(E)空间
//获取uv关系时非o(1)；难以有效删除边
List<List<Integer>> graph;
for(int i = 0; i < numCourses; i++) graph.add(new ArrayList<Integer>());
//加权邻接表，first为终点，second为边权值
List<Integer[]>[] graph;  
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

维护一个集合s，保存入度为0的结点，每次将s中的一个结点n放入结果list中，并删除n的所有边

T(n)=O(E+V)

拓扑排序可以用来判断图中是否有环，还可以用来判断图是否是一条链。

BFS：

```java
List<List<Integer>> G = new ArrayList<>();
int[] indeg;//入度
List<Integer> res;

boolean topsort() {
    Queue<Integer> queue = new LinkedList<Integer>();
    for (int i = 0; i < n; ++i) {
        if (indeg[i] == 0) {
            queue.offer(i);
        }
    }

    int visited = 0;
    while (!queue.isEmpty()) {
        ++visited;
        int u = queue.poll();
        res.add(u);
        for (int v : G[u]) {
            --indeg[v];
            if (indeg[v] == 0) queue.offer(v);
        }
    }

    return visited == n;
}
```

DFS：

```java
List<Integer>[] G;// 邻接表
int[] visit;
List<Integer> res;
boolean valid = true;

void topsort(){
	for (int u = 0; u < n && valid; u++)
        if(visit[u] == 0) dfs(u);
	res.reverse();
}
bool dfs(int u){
    visit[u] = 1;
    for (int v : G[u]){
    	if (visit[v] == 0){
            dfs(v);
            if(!valid) return;
 		}
        else if (visit[v] == 1) {
        	valid = false;
            return;
        }
    }
    visit[u] = 2;
    res.add(u);
}
```





**欧拉回路**

除了起点和终点，其他点的度数应为偶数（进出次数相同），并且图连通。度数为奇数的点最多两个并且为起点和终点

```java
void euler(int u){
    for(int v = 0; v < n; v++)
        if(G[u][v] && !vis[u][v]){
            vis[u][v] = vis[v][u] = 1;
            euler(v);
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





## 树状数组(Binary Indexed Trees)

<img src="http://mdimg.sofice.top/202112111332318.png" alt="image-20210920164835582" style="zoom: 80%;" />

[csdn]:https://blog.csdn.net/bestsort/article/details/80796531?ops_request_misc=%257B%2522request%255Fid%2522%253A%2522163212612816780255263522%2522%252C%2522scm%2522%253A%252220140713.130102334..%2522%257D&request_id=163212612816780255263522&biz_id=0&utm_medium=distribute.pc_search_result.none-task-blog-2~all~top_positive~default-1-80796531.first_rank_v2_pc_rank_v29&utm_term=%E6%A0%91%E7%8A%B6%E6%95%B0%E7%BB%84&spm=1018.2226.3001.4187
[wiki]: https://oi-wiki.org/ds/fenwick/

```java
class BinaryIndexedTree{
    int[] tree;
    int n;
	// 建树
    BinaryIndexedTree(int[] a){
        this.n = a.length;
        this.tree = new int[n+1];
        for(int i = 0;i < a.length;i++){
            tree[i+1] += a[i];
            int father = i+1 + lowBit(i+1);
            if(father <= n) tree[father] += tree[i+1];
        }
    }
    // 将index处值设置成val
    public void update(int index, int val){
        index++;
        int delta = val - (sum(index) - sum(index-1));
        while(index <= n){
            tree[index] += delta;
            index += lowBit(index);
        }
    }
    // 计算[1...index]和
    private int sum(int index){
        int res = 0;
        while(index > 0){
            res += tree[index];
            index -= lowBit(index);
        }
        return res;
    }
    // 计算[l,r]和
    public int sumRange(int l, int r){
        l++;r++;
        return sum(r) - sum(l-1);
    }
	// x的最低位代表的数，
    private int lowBit(int x){
        return x & -x;
    }
}
```





## 线段树



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



## 红黑树

红黑树（Red-Black Tree，R-B Tree）是一种不严格的平衡二叉查找树。

<img src="http://mdimg.sofice.top/202201221234808.png" alt="img" style="zoom:50%;" />

**需要满足以下要求：**

- 每个节点是黑色的或红色的
- 根节点是黑色的
- 每个叶子节点都是黑色的空节点（NIL），也就是说，叶子节点不存储数据（图中将黑色的、空的叶子节点都省略掉了）
- 任何相邻的节点都不能同时为红色，也就是说，红色节点是被黑色节点隔开的
- 每个节点，从该节点到达其可达叶子节点的所有路径，都包含相同数目的黑色节点



**与AVL平衡二叉树的区别：**

- 平衡二叉树通过保持任一节点左、右子树高度差的绝对值不超过1来维持二叉树的平衡；而红黑树是根据查找路径上黑色节点的个数以及红、黑节点之间的联系来维持二叉树的平衡。
- 平衡二叉树在插入或者删除节点时为了保证左右子树的高度差会进行旋转，这一个旋转根据数据的不同旋转的复杂度也会不一样，所以在插入或者删除平衡二叉树的节点时，旋转的次数不可知，这也导致在频繁的插入、修改中造成的效率问题；红黑树在执行插入修改的操作时会发生旋转与变色（红变黑，或者黑变红）以确保没有一条路径会比其它路径长出两倍，**旋转情况少于AVL树**。
- 总体来说，红黑树整体性能略优于AVL树。



**插入操作：**

- 如果插入的节点是根节点，直接变成黑色

- 如果插入节点的父节点是黑色的，那我们什么都不用做，它仍然满足红黑树的定义

- 如果插入节点的父节点是红色的，就破坏了定义，需要转换：

  - 如果关注节点是 a，它的叔叔节点 d 是红色

    将关注节点 a 的父节点 b、叔叔节点 d 的颜色都设置成黑色；将关注节点 a 的祖父节点 c 的颜色设置成红色；关注节点变成 a 的祖父节点 c；跳到情况二或者情况三。

    <img src="http://mdimg.sofice.top/202201221249277.png" alt="img" style="zoom:50%;" />

  - 如果关注节点是 a，它的叔叔节点 d 是黑色，关注节点 a 是其父节点 b 的右子节点

    关注节点变成节点 a 的父节点 b；围绕新的关注节点b 左旋；跳到情况三。

    <img src="http://mdimg.sofice.top/202201221249724.png" alt="img" style="zoom:50%;" />

  - 如果关注节点是 a，它的叔叔节点 d 是黑色，关注节点 a 是其父节点 b 的左子节点

    围绕关注节点 a 的祖父节点 c 右旋；将关注节点 a 的父节点 b、兄弟节点 c 的颜色互换，调整结束。

    <img src="http://mdimg.sofice.top/202201221251866.png" alt="img" style="zoom:50%;" />



**删除操作：**

1. **第一步是针对删除节点初步调整**。初步调整只是保证整棵红黑树在一个节点删除之后，仍然满足最后一条定义的要求，也就是说，每个节点，从该节点到达其可达叶子节点的所有路径，都包含相同数目的黑色节点；
2. **第二步是针对关注节点进行二次调整，让它满足红黑树的第三条定义**，即不存在相邻的两个红色节点。



## B树 & B+树

**B树**

B树是一颗多路平衡查找树。我们描述一颗B树时需要指定它的阶数，阶数表示了一个结点最多有多少个孩子结点，一般用字母m表示阶数。当m取2时，就是我们常见的二叉搜索树。

一颗m阶的B树定义如下：

- 每个结点最多有m-1个关键字。
- 根结点最少可以只有1个关键字。
- 非根结点至少有Math.ceil(m/2)-1个关键字。
- 每个结点中的关键字都按照从小到大的顺序排列，每个关键字的左子树中的所有关键字都小于它，而右子树中的所有关键字都大于它。
- 所有叶子结点都位于同一层，或者说根结点到每个叶子结点的长度都相同。

![在这里插入图片描述](http://mdimg.sofice.top/202202181446382.png)



**B+树**

关键字个数比孩子结点个数小1

- B+树包含2种类型的结点：内部结点（也称索引结点）和叶子结点。根结点本身即可以是内部结点，也可以是叶子结点。根结点的关键字个数最少可以只有1个。
- B+树与B树最大的不同是内部结点不保存数据，只用于索引，所有数据（或者说记录）都保存在叶子结点中。
- m阶B+树表示了内部结点最多有m-1个关键字（或者说内部结点最多有m个子树），阶数m同时限制了叶子结点最多存储m-1个记录。
- 内部结点中的key都按照从小到大的顺序排列，对于内部结点中的一个key，左树中的所有key都小于它，右子树中的key都大于等于它。叶子结点中的记录也按照key的大小排列。
- 每个叶子结点都存有相邻叶子结点的指针，叶子结点本身依关键字的大小自小而大顺序链接。

![在这里插入图片描述](http://mdimg.sofice.top/202202181448226.png)

B树和B+树区别

1. B+**树的层级更少**：B+树的**非叶子**节点不保存关键字记录的指针，只进行数据索引，这样使得B+树每个**非叶子**节点所能保存的关键字大大增加，树的层级更少所以查询数据更快；
2. B+**树查询速度更稳定**：B+所有关键字数据地址都存在**叶子**节点上，所有数据地址必须要到叶子节点才能获取到，所以**每次数据查询的次数都一样**;
3. B+**树天然具备排序功能：**B+树所有的**叶子**节点数据构成了一个有序链表，在查询大小区间的数据时候更方便，数据紧密性很高，缓存的命中率也会比B树高。
4. B+**树全节点遍历更快：**B+树遍历整棵树只需要遍历所有的**叶子**节点即可，，而不需要像B树一样需要对每一层进行遍历，这有利于数据库做全表扫描。

**B树**相对于**B+树**的优点是，如果经常访问的数据离根节点很近，而**B树**的**非叶子**节点本身存有关键字其数据的地址，所以这种数据检索的时候会要比**B+树**快。






# 二、:mag: 搜索

搜索问题中，最重要的思路就是：**缩减搜索空间**

## 双指针

https://leetcode-cn.com/problems/two-sum-ii-input-array-is-sorted/solution/yi-zhang-tu-gao-su-ni-on-de-shuang-zhi-zhen-jie-fa/



## 滑动窗口

```java
/* 滑动窗口算法框架 */
void slidingWindow(string s, string t) {
    unordered_map<char, int> need, window;
    for (char c : t) need[c]++;

    int left = 0, right = 0;
    int valid = 0; 
    while (right < s.size()) {
        // c 是将移入窗口的字符
        char c = s[right];
        // 右移窗口
        right++;
        // 进行窗口内数据的一系列更新
        ...

        /*** debug 输出的位置 ***/
        printf("window: [%d, %d)\n", left, right);
        /********************/

        // 判断左侧窗口是否要收缩
        while (window needs shrink) {
            // d 是将移出窗口的字符
            char d = s[left];
            // 左移窗口
            left++;
            // 进行窗口内数据的一系列更新
            ...
        }
    }
}
```







## :two: 二分搜索

满足单调，有最大最小值

一般用于求最小化最大值、最大化最小值



**基本二分**

如果存在， 返回其索引，否则返回 -1

```java
int binarySearch(int[] nums, int target) { 
    int left = 0;
    int right = nums.length - 1; // 注意 
    while(left <= right) { // 注意 
        int mid = left + (right - left) / 2; 
        if(nums[mid] == target) 
            return mid; 
        else if (nums[mid] < target) 
            left = mid + 1; // 注意 
        else if (nums[mid] > target) 
            right = mid - 1; // 注意 
    }
    return -1; 
}
```

**终止条件要满足搜索区间为空**

- 因为`right = nums.length - 1`，所以每次搜索 [left, right] 两端都闭的区间

- 如果`right = nums.length`，每次搜索的就是 [left, right)，while里为`left < right`

**因为 mid 已经搜索过，应该从搜索区间中去除。**所以 mid 要加1减1



**寻找边界**

```java
// 左侧边界
int left_bound(int[] nums, int target) { 
    int left = 0, right = nums.length - 1; 
    while (left <= right) { 
        int mid = left + (right - left) / 2; 
        if (nums[mid] < target) { 
            left = mid + 1; 
        } else if (nums[mid] > target) { 
            right = mid - 1; 
        } else if (nums[mid] == target) { 
            // 别返回，锁定左侧边界 
            right = mid - 1; // 修改
        } 
    }
    // 最后要检查 left 越界的情况 
    if (left >= nums.length || nums[left] != target) // 修改
        return -1; 
    return left; 
}

// 右侧边界
int right_bound(int[] nums, int target) { 
    int left = 0, right = nums.length - 1; 
    while (left <= right) { 
        int mid = left + (right - left) / 2; 
        if (nums[mid] < target) { 
            left = mid + 1; 
        } else if (nums[mid] > target) { 
            right = mid - 1; 
        } else if (nums[mid] == target) { 
            // 别返回，锁定右侧边界 
            left = mid + 1; // 修改
        } 
    }
    // 最后要检查 right 越界的情况 
    if (right < 0 || nums[right] != target) // 修改
        return -1; 
    return right; 
}
```

**为什么算法能够找到边界：**`nums[mid] == target`时不返回，缩小边界



## 回溯法(DFS)

递归函数不满足条件时，不再调用，而是返回上一层调用（递归枚举），本质是DFS

修改后要撤销

```java
void backtrack(路径，选择列表) {
    if (满足结束条件 | 到达规定最深处) {
        // 输出结果
        res.add(路径)
        return;
    }
    // 不满足则不继续递归，剪枝
    for (选择 : 选择列表) {
        // 做选择，赋值，设置访问标志
        backtrack(cur + 1);// 递归 搜索
        // 撤销选择，撤销赋值，撤销访问标志
    }
    
}

List<List<String>> res = new ArrayList<>();
LinkedList<String> path = new LinkedList<>();
public List<List<String>> task(String s) {
    if(s.length()==0) return res;
    backtrack(s,0);
    return res;
}
private void backtrack(String s, int begin){
    if(满足结束条件 | 到达规定最深处){
        res.add(new ArrayList<>(path));
        return;
    }
    for(int i=begin;i<s.length();i++){
        if(满足条件 | 剪枝){
            path.add(s.substring(begin,i+1));// 做选择，赋值，设置访问标志
            backtrack(s,i+1);// 递归 搜索
            path.removeLast();// 撤销选择，撤销赋值，撤销访问标志
        }
    }
}
```

`res.add(new ArrayList<>(path)); ` **添加路径一定要new对象**

## BFS

```java
// 计算从起点 start 到终点 target 的最近距离 
int BFS(Node start, Node target) { 
    Queue<Node> q; // 核⼼数据结构 
    Set<Node> visited; // 避免⾛回头路 
    
    q.offer(start); // 将起点加⼊队列 
    visited.add(start); 
    int step = 0; // 记录扩散的步数 
    while (q not empty) { 
        int sz = q.size(); /* 将当前队列中的所有节点向四周扩散 */ 
        for (int i = 0; i < sz; i++) { 
            Node cur = q.poll(); /* 划重点：这⾥判断是否到达终点 */
            if (cur is target) 
                return step; /* 将 cur 的相邻节点加⼊队列 */ 
            for (Node x : cur.adj()) 
                if (x not in visited) { 
                    q.offer(x); 
                    visited.add(x); 
                } 
        }
        /* 划重点：更新步数在这⾥ */ 
        step++; 
    } 
}
```

**双向 BFS 优化**

传统的 BFS 框架就是从起点开始向四周扩散，遇到终点时停⽌；⽽双向 BFS 则是从起点和终点同时开始扩散，当两 边有交集的时候停⽌

不过，双向 BFS 也有局限，因为你必须知道终点在哪⾥

```java
int openLock(String[] deadends, String target) { 
    // ⽤集合不⽤队列，可以快速判断元素是否存在 
    Set<String> q1 = new HashSet<>(); 
    Set<String> q2 = new HashSet<>(); 
    Set<String> visited = new HashSet<>(); 
    
    int step = 0; 
    q1.add(起点); 
    q2.add(终点); 
    while (!q1.isEmpty() && !q2.isEmpty()) { 
        // 哈希集合在遍历的过程中不能修改，⽤ temp 存储扩散结果
        Set<String> temp = new HashSet<>(); 
        /* 将 q1 中的所有节点向周围扩散 */ 
        for (cur : q1) { 
            /* 判断是否到达终点 */ 
            if (q2.contains(cur)) // 两个bfs树有交集
                return step; 
            visited.add(cur); 
            
            /* 将⼀个节点的未遍历相邻节点加⼊集合 */ 
            for (node: cur.adj) { 
                if (!visited.contains(node)) 
                    temp.add(node); 
            } 
        }
        /* 在这⾥增加步数 */
        step++; 
        // temp 相当于 q1 
        // 这⾥交换 q1 q2，下⼀轮 while 就是扩散 q2 
        q1 = q2; 
        q2 = temp; 
    }
    return -1; 
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











# 三、:zap: 动态规划

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

**滚动数组，空间优化**

如果只用到上一行或上一个的历史状态，可以缩小一个维度来存储值。

用到上一行的结果，从后向前滚动；用到本行的结果，从前向后滚动。

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
  
+ 股票问题（LC121,122,123,309,714)

  $dp[i][k][0,1]$是第i天，已经进行了k次交易，手中是否（0,1）握有股票时，能获得的最大利润

  $dp[i][k][0]=max(dp[i-1][k][0],dp[i-1][k][1]+price[i])$

  $dp[i][k][1]=max(dp[i-1][k][1],dp[i-1][k-1][0]-price[i])$

  base case：$dp[-1][k][0] = dp[i][0][0] = 0,\quad dp[-1][k][1] = dp[i][0][1] = -infinity $

  



**DAG(Directed acyclic graph)**

许多动态规划问题都可以转化为DAG上的最长路最短路或路径计数问题



## 数位DP

数位dp是一种计数用的dp。数位的含义：一个数有个位、十位、百位、千位......数的每一位就是数位。

对于「数位 DP」题，都存在「询问 [a,b][a, b][a,b]（aaa 和 bbb 均为正整数，且 a<ba < ba<b）区间内符合条件的数值个数为多少」的一般形式



# 四、字符串

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

## 字典树 (Trie)

https://oi-wiki.org/string/trie/

<img src="http://mdimg.sofice.top/202201201003659.png" alt="image-20220120100325290" style="zoom: 50%;" />

数组实现：

```java
class Trie {
    private Trie[] children; // children[i]!=null 则表示有从此节点到i的路径
    private boolean isEnd;	 // 此节点是否为叶子

    public Trie() {
        children = new Trie[26];
        isEnd = false;
    }

    /** Inserts a word into the trie. */
    public void insert(String word) {
        Trie node = this;
        for (int i = 0; i < word.length(); i++) {
            char ch = word.charAt(i);
            int index = ch - 'a';
            if (node.children[index] == null) {
                node.children[index] = new Trie();
            }
            node = node.children[index];
        }
        node.isEnd = true;
    }

    /** Returns if the word is in the trie. */
    public boolean search(String word) {
        Trie node = searchPrefix(word);
        return node != null && node.isEnd;
    }

    /** Returns if there is any word in the trie that starts with the given prefix. */
    public boolean startsWith(String prefix) {
        return searchPrefix(prefix) != null;
    }
	// 前缀存在，返回前缀的最后一个节点；不存在返回null
    private Trie searchPrefix(String prefix) {
        Trie node = this;
        for (int i = 0; i < prefix.length(); i++) {
            char ch = prefix.charAt(i);
            int index = ch - 'a';
            if (node.children[index] == null) {
                return null;
            }
            node = node.children[index];
        }
        return node;
    }
   
    //软删除
    public boolean delete(String word){
        Trie node = this;
        for(int i=0;i<word.length();i++){
            node = node.children[word.charAt(i)-'a'];
        }
        if(node.isEnd){
            node.isEnd = false;
            return true;
        }
        else return false;
    }
}
```

- 时间复杂度：初始化为 O(1)，其余操作为 O(∣S∣)，其中 ∣S∣是每次插入或查询的字符串的长度。

- 空间复杂度：O(∣T∣⋅Σ)，其中 ∣T∣为所有插入字符串的长度之和，Σ为字符集的大小，本题 Σ=26。



## 霍夫曼树

https://oi-wiki.org/ds/huffman-tree/

用于编码



# 五、数论

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



## 位运算

异或运算有以下三个性质：

- 任何数和 0 做异或运算，结果仍然是原来的数，即 a⊕0=a。
- 任何数和其自身做异或运算，结果是 0，即 a⊕a=0。
- 异或运算满足交换律和结合律，即 a⊕b⊕a = b⊕a⊕a = b⊕(a⊕a) = b⊕0 = b。





# 六、编码

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



## 前缀和

前缀和的最主要目的就是求**子数组的和**的大小



# 七、排序

## 十大经典排序算法

| 排序算法          | 最好T(n) | 平均T(n) | 最坏T(n) | S(n) | 稳定性 | 每趟全局有序 | 排序方式 | 是否适合链表 |
| ----------------- | -------- | -------- | -------- | ---- | ------ | ------------ | -------- | ------------ |
| 直接插入/折半插入 | n        | n2       | n2       | 1    | 1      | 0            | in       | 单/0         |
| 希尔排序          | n        | n1.25    | n1.5     | 1    | 0      | 0            | in       | 0            |
| 冒泡排序          | n        | n2       | n2       | 1    | 1      | 1            | in       | 顺链表顺序冒 |
| 快速排序          | nlogn    | nlogn    | n2       | logn | 0      | 1            | in       | 单           |
| 简单选择排序      | n2       | n2       | n2       | 1    | 0      | 1            | in       | 单           |
| 堆排序            | nlogn    | nlogn    | nlogn    | 1    | 0      | 1            | in       | 树链         |
| 归并排序          | nlogn    | nlogn    | nlogn    | n    | 1      | 0            | out      | 0            |
| 基数排序          | d(n+r)   | d(n+r)   | d(n+r)   | r    | 1      | 0            | out      | 单           |
| 计数排序          | n+k      | n+k      | n+k      | k    | 1      | 1            | out      | 单           |
| 桶排序            | n+k      | n+k      | n2       | n+k  | 1      | 0            | out      |              |

### 插入法

**插入排序 InsertSort**

对于未排序的数据，在已排序序列中从后向前扫描，找到相应位置并插入。

**插入排序在对几乎已经排好序的数据操作时，效率高，即可以达到线性排序的效率；**

![img](http://mdimg.sofice.top/202112202000570.gif)

```java
public class InsertSort {

    public void insertSort(int[] arr) {
        if (arr.length < 2) {
            return;
        }
        
        // 从下标为 1 的元素开始选择合适的位置插入, 依次将代排序列中的元素插入到有序序列中
        for (int i = 1; i < arr.length; i ++) {
            // 记录要进行插入的数据
            int temp = arr[i];
            // 有序序列的最后一个元素下标
            int j = i - 1;
            // 将要插入的元素插入到有序序列中
            while (j >= 0 && temp < arr[j]) {
                // 有序序列中的元素右移 arr[j] -> arr[j+1]
                arr[j + 1] = arr[j]; 
                j --;
            }
            // 插入数据
            if (j + 1 != i) {
                arr[j + 1] = temp;
            }
        }
    }

}
```

**折半插入 BinaryInsertSort**

将插入排序中的搜索部分改为二分法搜索插入位置，但移动仍然需要O(n)时间



**希尔排序 ShellSort**

也称递减增量排序算法，是插入排序的一种更高效的改进版本。但希尔排序是**非稳定**排序算法。

希尔排序是基于插入排序的以下两点性质而提出改进方法的：

- 插入排序在对几乎已经排好序的数据操作时，效率高，即可以达到线性排序的效率；
- 但**插入排序一般来说是低效的，因为插入排序每次只能将数据移动一位**；

希尔排序的基本思想是：先将整个待排序的/记录序列**按照步长分割成为若干子序列分别进行直接插入排序**，待整个序列中的记录"基本有序"时，再对全体记录进行依次直接插入排序（即步长为 1）。

【算法步骤】：

- 选择一个增量（步长）序列 t1，t2，……，tk，其中 ti > tj, tk = 1；（一般都是从数组长度的一半开始，每次减半）
- 按增量序列个数 k，对序列进行 k 趟排序；
- 每趟排序，根据对应的增量 ti，将待排序列分割成若干长度为 m 的子序列，分别对各子表进行直接插入排序。仅增量因子为 1 时，整个序列作为一个表来处理，表长度即为整个序列的长度。

【具体代码】：

```java
public class ShellSort {

    public void shellSort(int[] arr) {
        if (arr.length < 2) {
            return;
        }
        
        // 步长(增量), 每次减半
        for (int step = arr.length / 2; step >= 1; step /= 2) {
            // 从下标为 1 的元素开始选择合适的位置插入, 依次将代排序列中的元素插入到有序序列中
            for (int i = step; i < arr.length; i ++) {
                // 记录要进行插入的数据
                int temp = arr[i];
                // 有序序列的最后一个元素的下标
                int j = i - step;
                // 将要插入的元素插入到有序序列中
                while (j >= 0 && temp < arr[j]) {
                    // 有序序列中的元素右移 arr[j] -> arr[j+step]
                    arr[j + step] = arr[j];
                    j -= step;
                }

                // 插入数据
                if (j + step != i) {
                    arr[j + step] = temp;
                }
            }
        }
    }
}
```

可以发现，希尔排序不过就是在插入排序的代码外围套了一层关于增量的循环，然后把 i 改成了 step 罢了。

### 交换法

**冒泡排序 BubbleSort**

**它重复地走访过要排序的数列，一次比较两个元素，如果他们的顺序错误就把他们交换过来**，直到整个数列已经排序完成。

这个算法的名字由来是因为越小（大）的元素会经由交换慢慢"浮"到数列的顶端。

> 冒泡排序还有一种优化算法，就是立一个 flag，当在一趟序列遍历中元素没有发生交换，则证明该序列已经有序。但这种改进就事件复杂度来说并没有什么太大作用。

![img](http://mdimg.sofice.top/202112202000552.gif)

【算法步骤】：

1. **比较相邻的元素。如果第一个比第二个大，就交换他们两个**。
2. 对每一对相邻元素作同样的工作，从开始第一对到结尾的最后一对。这步做完后，最后的元素会是最大的数。
3. 针对所有的元素重复以上的步骤，除了最后一个。

【具体代码】：

```java
public class BubbleSort {

    public void bubbleSort(int[] arr) {
        if (arr.length < 2) {
            return;
        }
        
        // 外层循环代表循环 (冒泡) 次数
        // 每完成一次冒泡就会有一个最小的数浮到数列顶端
        for (int i = 0; i < arr.length - 1; i++) {
            // 内存循环代表两两比较 (每完成一次冒泡就可以相应的减少一次比较)
            for (int j = 0; j < arr.length - i - 1; j++) {
                if (arr[j] > arr[j + 1]) {
                    swap(arr, j, j + 1);
                }
            }
        }
    }

    private void swap(int[] arr, int i, int j) {
        int temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
    }

}
```



**快速排序 QuickSort**

当数组基本有序时性能最差

【算法步骤】：

1．先从数列中取出一个数作为基准数。

2．分区过程，将比这个数大的数全放到它的右边，小于或等于它的数全放到它的左边。

3．再对左右区间重复第二步，直到各区间只有一个数。  

```java
public void QuickSort(int[] a, int l, int h){
    if(l >= h) return;
    int pivot = partition(a,l,h);
    QuickSort(a, l, pivot-1);
    QuickSort(a, pivot+1, h);
}

private int partition(int[] a, int l, int h) {
    int i = l, j = h + 1;
    while (true) {
        while (a[++i] < a[l] && i < h) ;
        while (a[--j] > a[l] && j > l) ;
        if (i >= j) {
            break;
        }
        swap(a, i, j);
    }
    swap(a, l, j);
    return j;
}

private void swap(int[] a, int i, int j) {
    int t = a[i];
    a[i] = a[j];
    a[j] = t;
}
```

==稳定快排==：partition中，另起数组tmp，遍历第一遍：将小于pivot的按原顺序放在tmp左边；遍历第二遍：将大于pivot的按原顺序放在tmp右边；放入pivot；将tmp更新到a



### 选择法

**简单选择排序 SelectionSort**

无论什么数据进去都是 $O(n^2)$ 的时间复杂度。所以用到它的时候，数据规模越小越好。

【算法步骤】：

- 首先在未排序序列中找到最小（大）元素，存放到排序序列的起始位置。
- 再从剩余未排序元素中继续寻找最小（大）元素，然后放到已排序序列的末尾。
- 重复第二步，直到所有元素均排序完毕。

![img](http://mdimg.sofice.top/202112202000797.gif)

【具体代码】：

以从小到大排序为例：

```java
public class SelectionSort {

    public void selectionSort(int[] arr) {
        if (arr.length < 2) {
            return;
        }
        
        // 一共需要经过 arr.length - 1 轮的比较
        for (int i = 0; i < arr.length - 1; i ++) {
            // 找到待排序列中的最小元素
            int min = i;
            for (int j = i + 1; j < arr.length; j ++) {
                if (arr[j] < arr[min]) {
                    // 记录目前能找到的最小元素的下标
                    min = j;
                }
            }
            // 将未排序序列中的最小元素存放到已排序序列的最后
            if (i != min) {
                swap(arr, i, min);
            }
        }
    }

    private void swap(int[] arr, int i, int j) {
        int temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
    }
}
```



**堆排序 HeapSort**

堆的子结点的键值总是小于（或者大于）它的父节点：

- 大顶堆：每个节点的值都大于或等于其子节点的值，在堆排序算法中用于升序排列；
- 小顶堆：每个节点的值都小于或等于其子节点的值，在堆排序算法中用于降序排列；

堆排序的平均时间复杂度为 Ο(nlogn)。

【算法步骤】：

1. 创建一个堆 H[0……n-1]；
2. 把堆首（最大值）和堆尾互换；
3. 把堆的尺寸缩小 1，并把新的数组顶端数据调整到相应位置；
4. 重复步骤 2，直到堆的尺寸为 1。

【具体代码】：

```java
public class HeapSort {

    // 堆排序
    public static int[] heapSort(int[] arr) {
        int len = arr.length;
        if (len < 2) {
            return;
        }
        
        // 构造大根堆，o(nlogn)
        buildMaxHeap(arr, len);

        // 不断地交换堆顶元素和当前堆中的最后一个元素, 并且不断地调整堆
        // 那么就可以得到一个从尾到头的递减序列, 从正向来看就是一个递增序列，o(nlogn)
        for (int i = len - 1; i > 0; i--) {
            // 交换堆顶元素和当前堆中的最后一个元素
            swap(arr, 0, i);
            // 调整堆
            len--;
            heapify(arr, 0, len);
        }

        return arr;
    }

    // 初始数据构造大根堆 (下沉)，o(nlogn)
    private static void buildMaxHeap(int[] arr, int len) {
        // 从最后一个非叶子结点开始，依次向前
        // 当一个节点比其子节点小，则需要不断地向下进行比较和交换操作
        for (int i = len >> 1; i >= 0; i--) {
            heapify(arr, i, len);
        }
    }

    // 调整堆中以第 i 个节点为 root 的子树，o(logn)
    private static void heapify(int[] arr, int i, int len) {
        // 第 i 个节点的左孩子
        int left = 2 * i + 1;
        // 第 i 个节点的右孩子
        int right = 2 * i + 2;

        // 一个节点如果有两个子节点，应当与两个子节点中最大那个节点进行交换
        int largest = i;
        if (left < len && arr[left] > arr[largest]) {
            largest = left;
        }
        if (right < len && arr[right] > arr[largest]) {
            largest = right;
        }
        if (largest != i) {
            swap(arr, i, largest);
            // 继续调整堆中以 largest 为 root 的子树
            heapify(arr, largest, len);
        }
    }

    private static void swap(int[] arr, int i, int j) {
        int temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
    }

}
```



**归并排序 MergeSort**

归并排序（Merge sort）是建立在归并操作上的一种有效的排序算法。该算法是采用**分治法**（Divide and Conquer）的一个非常典型的应用。

一般我们说的归并排序都是二路归并，即两两归并。

【算法步骤】：

归并排序：

- 将待排数组一分为二
- 递归排序左侧子序列
- 递归排序右侧子序列
- 合并这两个有序子序列

合并两个有序数组：

- 申请一个新的数组空间，用来存放合并后的序列；
- 设置两个指针分别指向两个数组的起始位置
- 比较两个指针所指向的元素，选择相对小的元素放入到合并空间，并移动指针到下一位置；
- 重复步骤 3 直到某一指针达到序列尾；
- 将较长的那个子数组中剩下的所有元素直接复制到合并序列尾。

【具体代码】：

```java
public class MergeSort  {
    
    public static void main(String[] args) {
        int[] arr = new int[] {4, 3, 2, 9, 4, 2, 5, 1};
        int[] res = mergeSort(arr);
        for (int i : res) {
            System.out.println(i);
        }
    }
    
    public static int[] mergeSort(int[] arr) {
        if (arr.length < 2) {
            return arr;
        }
		
        int mid = (int) Math.floor(arr.length >> 1);
        int[] left = Arrays.copyOfRange(arr, 0, mid);
        int[] right = Arrays.copyOfRange(arr, mid, arr.length);
        
        return merge(mergeSort(left), mergeSort(right));
    }

    private static int[] merge(int[] left, int[] right) {
        int[] res = new int[left.length + right.length];
        int index_res = 0;
        int index_left = 0;
        int index_right = 0;

        // 比较两个指针所指向的元素，选择相对小的元素放入到合并空间，并移动指针到下一位置
        while (index_left < left.length && index_right < right.length) {
            if (left[index_left] < right[index_right]) {
                res[index_res ++] = left[index_left];
                index_left ++;
            } else {
                res[index_res ++] = right[index_right];
                index_right ++;
            }
        }

        // 将较长的那个子数组中剩下的所有元素直接复制到 res 序列尾
        while (index_left < left.length) {
            res[index_res ++] = left[index_left ++];
        }

        while (index_right < right.length) {
            res[index_res ++] = right[index_right ++];
        }

        return res;
    }

}
```

### 非比较排序

**基数排序**

依次从低位到高位比较各个数字的数位

![在这里插入图片描述](http://mdimg.sofice.top/202112211637668.png)

==为什么从低位到高位==：高位的权重是高于低位的，如果先排高位，排低位的时候高位就会打乱



**计数排序**

优势在于在对一定范围内的整数排序时，它的复杂度为Ο(n+k)（其中k是整数的范围），快于任何比较排序算法。

【算法步骤】：

1. 构建count数组，大小为`max(arr)`，`count[i]` 为数字 i 出现的次数
2. 顺序更新：`count[i] += count[i-1]`
3. 逆序遍历原数组，获得count值，放在新数组`count[i]`位置，`count[i]--`

**空间浪费问题**：作差

**稳定性问题**：第三步逆序遍历原数组，并且`count[i]--`保证之前的相同数值被排在之前



**桶排序**

桶排序利用了函数的映射关系，**高效与否的关键就在于这个映射函数**。为了使桶排序更加高效，我们需要做到这两点：

1. 在额外空间充足的情况下，尽量增大桶的数量
2. **使用的映射函数能够将输入的 N 个数据均匀的分配到 K 个桶中**

同时，对于桶中元素的排序，选择何种比较排序算法对于性能的影响至关重要。

**什么时候最快**：当输入的数据可以均匀的分配到每一个桶中。

**什么时候最慢**：当输入的数据被分配到了同一个桶中。

【算法步骤】：

基本思想其实就是先划分好几个桶，然后把元素映射到对应的桶中，再在各个桶内进行排序就好了

**示意图**：元素分布在桶中：

![img](http://mdimg.sofice.top/202112202000639.png)

然后，元素在每个桶中排序：

![img](http://mdimg.sofice.top/202112202000663.png)











## Kth Element   问题

先排序，建堆，使用快排的思想

https://leetcode-cn.com/problems/kth-largest-element-in-an-array/



# STL

## java

**vector动态数组**：insert(p,x)，erase(p)都为o(n)

**stack栈**：所有操作o(1)

**queue队列**：所有操作o(1)

**list双向链表**：LinkedList可以add/remove First/Last

**set集合**：insert(key)，erase(key)，find(key)都为o(logn)

**map字典**：insert( (key，val) )，erase(key)，find(key)都为o(logn)





```java
// 转collection为数组：
collection.stream().mapToInt(Integer::intValue).toArray();
// 回收空间，减少内存消耗
static {
    System.runFinalization();
    System.gc();
}
```

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



















