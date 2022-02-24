/*******
*八数码问题
*2020/7/1
*Sofice
********/
#include<unordered_set>
#include<cstring>
#include<windows.h>

using namespace std;

typedef int State[9];           //定义状态类型
const int maxstate = 1000000;
State st[maxstate], goal;       //状态数组
int dist[maxstate];             //距离数组
int vis[362880], fact[9];       //状态访问数组和阶乘表
int fa[maxstate];               //父节点编号
const int dx[] = { -1,1,0,0 };  //用数组移动
const int dy[] = { 0,0,-1,1 };
int front = 1, rear = 2;        //头尾指针

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

int bfs() {//bfs+队列
    init_lookup_table();//初始化查找表
    while (front < rear) {
        State& s = st[front];
        if(memcmp(goal, s, sizeof(s)) == 0)    return front;//找到目标状态
        int z;
        for (z = 0; z < 9; z++)    if (!s[z])   break;//找0的位置
        int x = z / 3, y = z % 3;//获取行列编号0-2
        for (int d = 0; d < 4; d++) {
            //尝试上下左右移动
            int newx = x + dx[d];
            int newy = y + dy[d];
            int newz = newx * 3 + newy;
            if (newx >= 0 && newx < 3 && newy >= 0 && newy < 3) {//如果移动合法
                State& t = st[rear];
                memcpy(&t, &s, sizeof(s));//扩展新节点
                t[newz] = s[z];
                t[z] = s[newz];
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

void print(int index) {
    for (int i = 0; i < 9; i++) {
        if(st[index][i] == 0)   printf("# ");
        else    printf("%d ", st[index][i]);
        if(i%3 == 2)    printf("\n");
    }
    printf("\n");
    return;
}

void visualize(int index) {
    if (index == 0) {
        print(index);
        return;
    }
    visualize(fa[index]);
    print(index);
}

int main() {
    for (int i = 0; i < 9; i++)    scanf("%d", &st[1][i]);//起始状态(2 6 4 1 3 7 0 5 8)
    for (int i = 0; i < 9; i++)    scanf("%d", &goal[i]);//终止状态(8 1 5 7 3 6 4 0 2)
    int ans = bfs();
    //可视化移动过程
    if (ans > 0) {
        visualize(front);
        printf("steps:%d\n", dist[ans]);
    }    
    else printf("cannot deal\n");

    system("pause");
    return 0;
}