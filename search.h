#ifndef _SEARCH_H_
#define _SEARCH_H_

#define INF 32767
#define N	30000000 
#define inf  0x3f3f3f3f

typedef struct ANode {
	int adjvex;				//��ı��
	struct ANode *nextarc;	//ָ����һ����ָ�� 
	int weight;				//�ñߵ�Ȩֵ
//	int cost;				//���㵽�˵�Ļ��� 
} ArcNode;					//�߽�� 

typedef struct Vnode {
	ArcNode *firstarc;		//ָ���һ���߽�� 
} VNode;					//ͷ��� 

typedef struct {
	VNode adjlist[500000];	//�ڽӱ��ͷ������� 
	int n;					//ͼ�Ķ����� 
} AdjGraph;

int flag[500000] = {0};
//int dist[500000] = {0};		//dist����������㵽v�ľ���
//int path[500000];			//path�����洢��֮��Ĺ�ϵ����·��
AdjGraph G;
int m, n; //m�Ǳߵ�����,n�ǵ������ 
//�����Ǻ��ڽӱ��йصĶ���
int h[N], w[N], e[N], ne[N], idx;
//�����dfs�йصĺ����Լ�����
int stdfs[N] ;  //st[i]=true ��˼�Ǳ��Ϊi�ĵ��߹���
int p = 0;        //��¼step����ĳ��� 
int step[10001];//��¼�����ĵ� 
int has = 0;
//������bfsҪ�õ�
int st[N];
int dist[N];
int path[N] ;

int stack[N];
int sp = 0;

int hh = 0 , tt = 0, q[N];

void CreateAdj(char name[]);	//�����ڽӱ�
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
