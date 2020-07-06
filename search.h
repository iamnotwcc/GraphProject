#ifndef _SEARCH_H_
#define _SEARCH_H_

#define INF 32767
#define N	30000000 
#define inf  0x3f3f3f3f

typedef struct ANode {
	int adjvex;				//点的编号
	struct ANode *nextarc;	//指向下一个的指针 
	int weight;				//该边的权值
//	int cost;				//顶点到此点的花费 
} ArcNode;					//边结点 

typedef struct Vnode {
	ArcNode *firstarc;		//指向第一个边结点 
} VNode;					//头结点 

typedef struct {
	VNode adjlist[500000];	//邻接表的头结点数组 
	int n;					//图的顶点数 
} AdjGraph;

int flag[500000] = {0};
//int dist[500000] = {0};		//dist用来存其余点到v的距离
//int path[500000];			//path用来存储点之间的关系，及路径
AdjGraph G;
int m, n; //m是边的数量,n是点的数量 
//下面是和邻接表有关的定义
int h[N], w[N], e[N], ne[N], idx;
//下面和dfs有关的函数以及定义
int stdfs[N] ;  //st[i]=true 意思是编号为i的点走过了
int p = 0;        //记录step数组的长度 
int step[10001];//记录经过的点 
int has = 0;
//下面是bfs要用的
int st[N];
int dist[N];
int path[N] ;

int stack[N];
int sp = 0;

int hh = 0 , tt = 0, q[N];

void CreateAdj(char name[]);	//建立邻接表
void Dijkstra(int v);
void shortestPath(int u, int v, char algorithm[], char name[]);
int int_to_string(char *s, int n);
int strcmp1(char *a);

void add(int a, int b, int c);
void dfs(int u,int des);
void push(int u);
int top();
void pop();
void print(int s, int n);
void init_();
void bfs(int u, int des);
#endif
