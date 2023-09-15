#pragma warning(disable:4996) 
#include "stdio.h"
#include "stdlib.h"
#define MAX_NUM 10000

typedef struct treeNode *treePtr;
typedef struct treeNode {
	int caseNum;
	int n;
	int m;
	int c_landfill;
	int c_road;
	int u[10000];
	int v[10000];
} Node;
treePtr A; // �� ���̽��� ���� ����

typedef struct VERTEX {
	int key;
	int component;
} vertex;
vertex** forest; // connected components

typedef struct EDGE *edgePtr;
typedef struct EDGE {
	int Num;
	int v1, v2;
	int cost;
	edgePtr next;
} edge;
edgePtr selE; // ����� edge ��
edge* heap[MAX_NUM]; // �� ���̽��� �ּ� ���
edge* item = NULL; // �ּ� ��� heap

int N_case;
int s = 0; // ����� edge ��

// �� ���̽��� �ּ� ��� ���
void Kruskal(int, int);

// ���̽� ���� vertex �ʱ�ȭ
void init_vertex(int);

// ���̽� ���� ����� �ּ� ����� min heap�� ����
void insC(edge*, int);

// min heap���� min ���� ������ ���
void delh(int);



void main() {

	FILE *fp = fopen("input.txt", "r");

	fscanf(fp, "%d", &N_case);
	A = (treePtr)malloc(sizeof(Node)*N_case);
	
	for (int i = 0; i < N_case; i++) {
		A[i].caseNum = i + 1;
		fscanf(fp, "%d", &A[i].n); // ���� ����
		fscanf(fp, "%d", &A[i].m); // �ٸ��� ����
		fscanf(fp, "%d", &A[i].c_landfill); // �Ÿ��� �Ǽ� ���
		fscanf(fp, "%d", &A[i].c_road); // �ٸ� �Ǽ� ���
		
		for (int j = 0; j < A[i].m; j++) {
			fscanf(fp, "%d", &A[i].u[j]); // ���� ������ �ٸ� ��
			fscanf(fp, "%d", &A[i].v[j]);
		}
		Kruskal(A[i].n, i); 
	}
	
	if (s > 0) {
		delh(N_case);
		while (1) {
			if (heap[1]->cost > item->cost) break;
			delh(--N_case);
		}
	}
	printf("%d\n", selE->cost);

	fclose(fp);
}

void Kruskal(int n, int i) {
	s = 0;
	selE = (edgePtr)malloc(sizeof(edge));
	edge* newE = NULL;
	// edge* temp = NULL;
	init_vertex(n);

	// ��� ���� �Ÿ����� �Ǽ��ϴ� ���� �ּ� ����� ���
	if (A[i].c_landfill < A[i].c_road) {
		//selE = (edgePtr)malloc(sizeof(edge));
		selE->cost = n * (A[i].c_landfill);
		printf("%d\n", A[i].caseNum);
	}
	
	else {
		{
			selE->next = selE;
			for (int j = 0; j < A[i].m; j++) {
				newE = (edge*)malloc(sizeof(edge));
				newE->Num = A[i].caseNum;
				newE->v1 = A[i].u[j];
				newE->v2 = A[i].v[j];

				// �� ���� �̹� ����Ǿ� �ִ� ���
				if (forest[newE->v1]->component == forest[newE->v2]->component) {
					continue;
				}

				// �� ���� ���� ����Ǿ� ���� ���� ���
				else {
					s++;
					newE->next = selE->next;
					selE->next = newE;
					selE = selE->next;
					forest[newE->v1]->component = forest[newE->v2]->component;
				}
			}
			selE = selE->next;
			s -= 1;
			selE->cost = s*(A[i].c_road) + (n - s)*(A[i].c_landfill);
		}
		insC(selE, i);
	}
}

void init_vertex(int n) {
	forest = (vertex**)malloc(sizeof(vertex*)*(n + 1));
	for (int i = 1; i <= n; i++) {
		vertex* v0 = (vertex*)malloc(sizeof(vertex));
		v0->key = i;
		v0->component = i;
		forest[i] = v0;
	}
}

// �� ���̽��� �ּ� ����� min heap���� �����Ѵ�.
void insC(edge* e, int n) {
	int i;
	edge* temp;
	i = ++n;
	while ((i != 1) && e[0].cost < heap[i / 2]->cost) {
		temp = heap[i];
		heap[i] = heap[i / 2];
		heap[i / 2] = temp;
		i /= 2;
	}
	heap[i] = e;
}

void delh(int n) {
	int s1 = s;
	int parent, child;
	edge* temp;
	edge* temp2;
	
	item = heap[1];
	temp = heap[n--];
	parent = 1; child = 2;
	while (child <= n) {
		if ((child < n) && (heap[child]->cost > heap[child + 1]->cost)) child++;
		if (temp->cost <= heap[child]->cost) break;
		heap[parent] = heap[child];
		parent = child; child *= 2;
	}
	heap[parent] = temp;
	
	temp2 = item;
	
	printf("%d\n", temp2->next->Num);
	while (1) {
		if (s1 < 1) break;
		printf("%d %d\n", temp2->next->v1, temp2->next->v2);
		temp2 = temp2->next;
		s1--;
	}
}