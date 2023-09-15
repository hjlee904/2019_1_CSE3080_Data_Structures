#include "stdio.h"
#include "stdlib.h"
#pragma warning(disable:4996) 

typedef struct {
	int num;
} element;

typedef struct node_* nodePointer;
typedef struct node_ {
	element data;
	nodePointer link;
} Node;

nodePointer insert(element item, nodePointer tail) {
	nodePointer temp;
	temp = (nodePointer)malloc(sizeof(Node));
	temp->data = item;
	temp->link = NULL;

	if (tail == NULL) {
		tail = temp;
		temp->link = tail;
	}
	else {
		temp->link = tail->link;
		tail->link = temp;
		tail = tail->link;
	}
	return tail;
}

nodePointer add(nodePointer tail1, nodePointer tail2) {
	nodePointer temp;
	temp = tail2->link;
	tail2->link = tail1->link;
	tail1->link = temp;
	tail1 = tail2;
	return tail1;
}

nodePointer del(element item, nodePointer tail) {
	nodePointer temp, temp2;
	temp = tail->link;
	while (1) {
		temp2 = temp->link;
		if ((temp2->data).num == item.num) {
			if ((temp2->data).num == (tail->data).num) {
				tail = temp;
			}
			temp->link = temp2->link;
		}
		if (temp == tail) {
			break;
		}
		if (!((temp2->data).num == item.num)){
			temp = temp->link;
		}
	}
	return tail;
}

void print(nodePointer tail) {
	nodePointer temp = tail->link;
	while (1) {
		printf("%d ", (temp->data).num);
		if (temp == tail) {
			break;
		}
		temp = temp->link;
	}
	printf("\n");
}


int main() {
	element a, b, c;
	nodePointer tail1 = NULL, tail2 = NULL;
	FILE *fp1 = fopen("A.txt", "r");
	FILE *fp2 = fopen("B.txt", "r");
	FILE *fp3 = fopen("C.txt", "r");
	while(1) {
		fscanf(fp1, "%d", &a.num);
		if (feof(fp1)) break;
		tail1 = insert(a, tail1);
	}
	while (1) {
		fscanf(fp2, "%d", &b.num);
		if (feof(fp2)) break;
		tail2 = insert(b, tail2);
	}
	tail1 = add(tail1, tail2);
	print(tail1);

	while (1) {
		fscanf(fp3, "%d", &c.num);
		if (feof(fp3)) break;
		tail1 = del(c, tail1);
	}
	print(tail1);
	
	fclose(fp1);
	fclose(fp2);
	fclose(fp3);
	return 0;
}