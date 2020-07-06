#include <stdio.h>
#include <stdlib.h>
#include "search.h"

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

void CreateAdj(char name[])		//建立邻接表 
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
		if (flag[m] == 0) {				//用来计算点的数量 
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
	int S[500000] = {0};				//S用来记录点是否被找过的记录
	int MINdis, i, j, u;
	for (i = 0; i < 500000; i++) {
		if (flag[i] == 1) {
			path[i] = -1;
			dist[i] = INF;
		}
	}
	ArcNode *p = G.adjlist[v].firstarc;	//用来指向v邻接表的第一个结点 
	while (p != NULL) {
		dist[p->adjvex] = p->weight;				//因为存在路径，所以直接修改dist的值 
		path[p->adjvex] = v;
		p = p->nextarc;
	}
	S[v] = 1;										//修改的结点v的记录 
	path[v] = -1;
	for (i = 0; i < G.n - 1; i++) {
		MINdis = INF;
		int count = 0;
		for (j = 0; count != G.n; j++) {			//优先队列优化找最小路径 
			if (flag[j] == 1) {
				if (S[j] == 0 && dist[j] < MINdis) {
					u = j;
					MINdis = dist[j];
				}
				count++;
			}
		}
		S[u] = 1;
		p = G.adjlist[u].firstarc;		//指向该点邻接表的第一个结点 
		while (p != NULL) {
			if (S[p->adjvex] == 0) {
				if (dist[u] + p->weight < dist[p->adjvex]) {	//比较点的距离并进行修改 
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
