#include "stdio.h"
#include "stdlib.h"
#pragma warning(disable:4996) 
#define MAX_TERMS 100

typedef struct treeNode *treePtr;
typedef struct treeNode {
	treePtr lchild;
	int data;
	treePtr rchild;
} Node;

void inorder(treePtr);
void preorder(treePtr);
void insert(treePtr*, int);
treePtr modifiedSearch(treePtr, int);

void main() {
	int i, n, A[MAX_TERMS];
	treePtr tree = NULL;
	FILE* fp = fopen("input.txt", "r");
	fscanf(fp, "%d", &n);
	for (i = 0; i < n; i++) {
		fscanf(fp, "%d", &A[i]);
	}

	for (i = 0; i < n; i++) {
		insert(&tree, A[i]);
	}

	inorder(tree);
	printf("\n");
	preorder(tree);
	printf("\n");

	fclose(fp);
}

void inorder(treePtr ptr) {
	if (ptr) {
		inorder(ptr->lchild);
		printf("%d ", ptr->data);
		inorder(ptr->rchild);
	}
}
void preorder(treePtr ptr) {
	if (ptr) {
		printf("%d ", ptr->data);
		preorder(ptr->lchild);
		preorder(ptr->rchild);
	}
}
void insert(treePtr* node, int num) {
	treePtr ptr, temp = modifiedSearch(*node, num);
	if (temp || !(*node)) { // node�� NULL�̰ų� 
		ptr = (treePtr)malloc(sizeof(Node));
		/*if () {
		printf("error");
		exit(1);
		}*/
		ptr->data = num;
		ptr->lchild = ptr->rchild = NULL;
		if (*node) {
			if (num < temp->data) {
				temp->lchild = ptr;
			}
			else temp->rchild = ptr;
		}
		else *node = ptr;
	}
}
treePtr modifiedSearch(treePtr ptr, int num) {
	if (!ptr) { // node�� NULL�̸� NULL ����, 
		return NULL;
	}
	while (ptr) { // node�� NULL�� �ƴ� ���
		if (num == ptr->data) { // num�� ���� ���� �̹� �����ϸ� �� ��ġ ����
			return ptr;
		}
		if (num < ptr->data) { // �ƴ� ��� ��� search
			if (ptr->lchild) {
				ptr = ptr->lchild;
			}
			else return ptr;
		}
		else {
			if (ptr->rchild) {
				ptr = ptr->rchild;
			}
			else return ptr;
		}
	}
}

