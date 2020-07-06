#include <stdio.h>
#include <stdlib.h>
//#include "search.h"
//#include "stats.h"
//#include "search.c"
//#include "stats.c"
//**********************************************************************************
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

//*********************
int flag_vertices[500000] = {0};				//��ı�� 
int flag_vertices_import[500000] = {0};			//������Ӹ��� 
int num_vertices = 0;
int num_edges = 0;
int max_vertices_import = 0;

int numberOfEdges(char name[]);
int numberOfVertices(char name[]);
float freemanNetworkCentrality(char name[]);
//*****************
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

int scmp(char *s1, char *s2);
void draw();
int str_to_int(char *s);

int numberOfEdges(char name[])
{
	FILE *fp = fopen(name, "r");
	if (fp == NULL) {
		printf("Failed to open teh file\n");
	}
	int m, n, weight;				//���������Ȩ�� 
	while (fscanf(fp, "%d %d %d", &m, &n, &weight) != EOF) {
		num_edges++;
	}
	fclose(fp);
	return num_edges;
}

int numberOfVertices(char name[])
{
	FILE *fp = fopen(name, "r");
	if (fp == NULL) {
		printf("Failed to open the file\n");
	}
	int m, n, weight;
	while (fscanf(fp, "%d %d %d", &m, &n, &weight) != EOF) {
		if (flag_vertices[m] == 0) {
			flag_vertices[m] = 1;
			num_vertices++;
		}
		if (flag_vertices[n] == 0) {
			flag_vertices[n] = 1;
			num_vertices++;
		}
	}
	fclose(fp);
	return num_vertices;
}

float freemanNetworkCentrality(char name[])
{
	int s = 0;
	if (num_vertices == 0) {
		s = numberOfVertices(name);
	} else {
		s = num_vertices;
	}
	int m, n, weight;				//���������Ȩ�� 
	FILE *fp = fopen(name, "r");
	if (fp == NULL) {
		printf("Failed to open teh file\n");
	}
	while (fscanf(fp, "%d %d %d", &m, &n, &weight) != EOF) {
		flag_vertices_import[m]++;
		flag_vertices_import[n]++;
		if (flag_vertices_import[m] > max_vertices_import) {
			max_vertices_import = flag_vertices_import[m];
		}
		if (flag_vertices_import[n] > max_vertices_import) {
			max_vertices_import = flag_vertices_import[n];
		}
	}
	int sum = 0;
	int i;
	for (i = 0; i < 500000; i++) {
		if (flag_vertices[i] == 1) {
			sum += max_vertices_import - flag_vertices_import[i];
		}
	}
	return ((float)sum / (s - 1) / (s - 2));
}

void add(int a, int b, int c)
{
    e[idx] = b;
	w[idx] = c;
	ne[idx] = h[a];
	h[a] = idx++;
}
  
void dfs(int u,int des)
{	
	if(has) return ;
	
    stdfs[u] = 1;
    step[p++] = u;
    
    if(u == des) {	 
    	has = 1;
 
        printf("%d", step[0]);
        int i;
        for(i = 1; i < p - 1; i++) {
        	printf("->%d", step[i]);
		}
    	printf("->%d\n", des); 
	}
	
	int i;
    for(i = h[u]; i != -1; i = ne[i]) {
		int j = e[i];
		
		if(stdfs[j] == 1) continue;
		
		stdfs[j] = 1;
		dfs(j, des); 
		stdfs[j] = 0; 
    }
    
    step[--p] = 0;
}

void push(int u)
{
	stack[sp++] = u;
}

int top()
{
	return stack[sp-1];
}

void pop()
{
	sp--;
}

void print(int s, int n)
{
    int p = n;
    while(path[p] != -1) {
        push(p);
        p = path[p];
	}
    push(p);
    if(sp != 1) 
    printf("%d", top());
    pop(); 
    while(sp != 0) {       	
        printf("->%d", top());
		pop();
    }
}
 
void init_()
{
	int i;
	for(i = 0; i < N; i++)
		dist[i] = inf;
		
	for(i = 0; i < N; i++)
		path[i] = -1;
}

void bfs(int u, int des)
{ 
    init_();

    q[0] = u;
    dist[u] = 0;
    st[u] = 1;
    
    while(hh <= tt)
    {    
        int p = q[hh++];
        st[p] = 0;
        
        int i;
        for(i = h[p]; i != -1; i = ne[i])
        {
            int j = e[i];
            
            if(dist[j] > dist[p] + w[i])
            {              	
                dist[j] = dist[p] + w[i];
                path[j] = p;
            
                if(!st[j])
                {
                    q[++tt] = j;
                    st[j] = 1;
                }
            }
        }
    }
    
	print(u, des);

}

int int_to_string(char *s, int n)
{
	int temp[10];
	int count = 0;
	if (n == 0) {
		temp[0] = 0;
		count++;
	} else {
		while (n > 0) {
			temp[count] = n % 10;
			n /= 10;
			count++;
		}
	}
	int result = count;
	int i;
	for (i = 0; count > 0; i++) {
		s[i] = (char)(temp[count - 1] + '0');
		count--;
	}
	return result;
}

void CreateAdj(char name[])		//�����ڽӱ� 
{
	FILE *fp = fopen(name, "r");
	AdjGraph G;
	if (fp == NULL) {
		printf("Failed to open teh file\n");
	}
	int i;
	for (i = 0; i < 500000; i++) {
		G.adjlist[i].firstarc = NULL;
	}
	int num = 0;
	int m, n, weight;
	while (fscanf(fp, "%d %d %d", &m, &n, &weight) != EOF) {
		ArcNode *p = (ArcNode *)malloc(sizeof(ArcNode));
		p->adjvex = n;
		p->weight = weight;
		p->nextarc = G.adjlist[m].firstarc;
		G.adjlist[m].firstarc = p;
		if (flag[m] == 0) {				//�������������� 
			flag[m] = 1;
			num++;
		}
		if (flag[n] == 0) {
			flag[n] = 1;
			num++;
		}
	}
	G.n = num;
	fclose(fp);
}

void Dijkstra(int v)
{
	int S[500000] = {0};				//S������¼���Ƿ��ҹ��ļ�¼
	int MINdis, i, j, u;
	for (i = 0; i < 500000; i++) {
		if (flag[i] == 1) {
			path[i] = -1;
			dist[i] = INF;
		}
	}
	ArcNode *p = G.adjlist[v].firstarc;	//����ָ��v�ڽӱ�ĵ�һ����� 
	while (p != NULL) {
		dist[p->adjvex] = p->weight;				//��Ϊ����·��������ֱ���޸�dist��ֵ 
		path[p->adjvex] = v;
		p = p->nextarc;
	}
	S[v] = 1;										//�޸ĵĽ��v�ļ�¼ 
	path[v] = -1;
	for (i = 0; i < G.n - 1; i++) {
		MINdis = INF;
		int count = 0;
		for (j = 0; count != G.n; j++) {			//���ȶ����Ż�����С·�� 
			if (flag[j] == 1) {
				if (S[j] == 0 && dist[j] < MINdis) {
					u = j;
					MINdis = dist[j];
				}
				count++;
			}
		}
		S[u] = 1;
		p = G.adjlist[u].firstarc;		//ָ��õ��ڽӱ�ĵ�һ����� 
		while (p != NULL) {
			if (S[p->adjvex] == 0) {
				if (dist[u] + p->weight < dist[p->adjvex]) {	//�Ƚϵ�ľ��벢�����޸� 
					dist[p->adjvex] = dist[u] + p->weight;
					path[p->adjvex] = u;
				}
			}
			p = p->nextarc;
		}
	}
}
int strcmp1(char *a)
{
	if (a[0] == 'D' && a[1] == 'i') {
		return 0;
	} else if (a[0] == 'D' && a[1] == 'F') {
		return 1;
	} else {
		return 2;
	}
}
void shortestPath(int u, int v, char algorithm[], char name[])
{
	CreateAdj(name);
	int al = strcmp1(algorithm);
	if (al == 0) {
		Dijkstra(u);
		int temp[5000];
		int count = 0;
		temp[0] = v;
		count++;
		int i;
		for (i = v; path[i] != -1; ) {
			temp[count] = path[i];
			count++;
			i = path[i];
		}
		count--;
		static char result[10000];
		int j = 0;
		for (i = count; i > 0; i--) {
			j += int_to_string(result + j, temp[i]);
			result[j] = ' ';
			j++;
			result[j] = '-';
			j++;
			result[j] = '>';
			j++;
			result[j] = ' ';
			j++;
		}
		j += int_to_string(result + j, temp[0]);
		result[j] = '\0';
		printf("%s", result);
//		return result;
	} else if (al == 1) {
	    int i;
		for(i = 0; i < N; i++) h[i] = -1;
	    FILE *fp = fopen(name, "r");
	    
	    if (fp == NULL) {
	    	printf("Failed to open teh file\n");
	    }

	    int m, n, weight;
    	while (fscanf(fp, "%d %d %d", &m, &n, &weight) != EOF) { 
		    add(m, n, weight);
	    }
	    fclose(fp);

        dfs(u, v);
	} else {
		int i;
	    for(i = 0; i < N; i++) h[i] = -1;
	    FILE *fp = fopen(name, "r");
	    
	    if (fp == NULL) {
	    	printf("Failed to open teh file\n");
	    }

	    int m, n, weight;
    	while (fscanf(fp, "%d %d %d", &m, &n, &weight) != EOF) { 
		    add(m, n, weight);
	    }
	    fclose(fp);
 
        bfs(u, v);	
	}
}
//*********************************************************************************************************
int scmp(char *s1, char *s2)
{
	int i = 0;
	while (s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0') {
		i++;
	}
	if (i > 0 && s1[i] == '\0' && s2[i] == '\0') {
		return 0;
	}
	return 1;
}
void draw()
{
	printf("                  	           |----|\n");
    printf("                                   |----|\n");
    printf("	                           |----|\n");
	printf("	                           |----|\n");
	printf("                +------------------------------------------+\n");
    printf("        	|                                          |\n");
    printf("	        |    +                                 +   |\n");
    printf("	        |    |                                 |   |\n");
    printf("   		|    +------->                <--------+   |\n");
    printf("	        |                                          |\n");
	printf("    +-----------+                                          +--------------+\n");
	printf("    |           |                                          |              |\n");
	printf("    |           |                                          |              |\n");
	printf("    |           |             +--------------+             |              |\n");
	printf("    v           |                                          |              v\n");
    printf("	        |                                          |\n");
    printf("       	        +------------+---------------+-------------+\n");
    printf("        	             |               |\n");
    printf("            	             |               |\n");
    printf("                	     |               |\n");
    printf("                       	     |               |\n");
    printf("                      	     |               |\n");
    printf("                    	     |               |\n");
    printf("                    	     |               |\n");
    printf("        	 <-----------+               +---------------->\n");
}
int str_to_int(char *s)
{
	int temp[10];
	int i = 0;
	while (s[i] != '\0') {
		temp[i] = (char)(s[i] - '0');
		i++;
	}
	i--;
	int x = 0;
	int j;
	for (j = 0; j <= i; j++) {
		x = x * 10 + temp[j];
	}
	return x;
}
int main(int argc, char *argv[])
{
	if (argc == 2) {
		if (scmp(argv[1], "-h") == 0 || scmp(argv[1], "--help") == 0) {
			printf("\bhelp menu\n");
			printf("./search-cli -g/--graph FILE_PATH -s/--stats STATS_PARAMS");
			printf("(STATS_PARAMS : edges  vertices  freeman)");
			printf(":Displays statistical information for graph with `FILE_ PATH` as input file\n");
			printf("./search-cli -g/--graph FILE_PATH -sp/--shortestpath SEARCH_PARAMS -u STARTING_POINT -v TARGET_POINT:");
			printf("Displays the shortest path calculated with `SEARCH_ PARAMS` from the start point u to the end point v in the diagram with `SEARCH_ PATH` as the input file");
		} else if (scmp(argv[1], "-j") == 0){
			draw();
		} else {
			printf("Invalid instruction");
		}
	} else if (argc == 5) {
		if ((scmp(argv[1], "-g") || scmp(argv[1], "-graph") == 0) && (scmp(argv[3], "-s") == 0 || scmp(argv[3], "-stats") == 0)) {
			if (scmp(argv[4], "edges") == 0) {
				printf("%d", numberOfEdges(argv[2]));
			} else if (scmp(argv[4], "vertices") == 0) {
				printf("%d", numberOfVertices(argv[2]));
			} else if (scmp(argv[4], "freeman") == 0) {
				printf("%f", freemanNetworkCentrality(argv[2]));
			} else {
				printf("Invalid instruction");
			}
		}
	} else if (argc == 9) {
		if ((scmp(argv[1], "-g") == 0 || scmp(argv[1], "--graph") == 0) && 
		(scmp(argv[3], "-sp") == 0 || scmp(argv[3], "--shortestpath") == 0) && 
		scmp(argv[5], "-u") == 0 && 
		scmp(argv[7], "-v") == 0) {
			shortestPath(str_to_int(argv[5]), str_to_int(argv[7]), argv[4], argv[2]);
		}
	}
	return 0;
}
