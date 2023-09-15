#include "stdafx.h"
#include "stdio.h"
#include "stdlib.h"
#pragma warning(disable:4996) 

typedef struct {
	int key;
} element;

typedef struct stack* stackPointer;
typedef struct stack {
	element data;
	stackPointer link;
} stack;

typedef struct queue* queuePointer;
typedef struct queue {
	element data;
	queuePointer link;
} queue;

stackPointer top;
queuePointer front, rear;

void push(element item) {
	stackPointer temp1; //�߰��ϴ� stack�� �ּҰ�
	temp1 = (stackPointer)malloc(sizeof(stack));
	temp1->data = item; //data�� ���Ͽ��� �о���� �� ����
	temp1->link = NULL;
	if (!top) {
		top = temp1;
	}
	else {
		temp1->link = top; //link�� ���� ���� ��ġ�� �ִ� stack�� �ּҰ�(top�� �ּҰ�) ����
		top = temp1; //top�� �ٽ� ���� �Էµ� stack ����Ŵ
	}

	queuePointer temp2;
	temp2 = (queuePointer)malloc(sizeof(stack));
	temp2->data = item;
	temp2->link = NULL;
	if (!rear) {
		rear = temp2;
		front = temp2;
	}
	else {
		rear->link = temp2;
		rear = temp2;
	}

};

void pop(void) {
	stackPointer temp1 = top;
	if (top) {
		top = temp1->link;
	}
	

	queuePointer temp2 = front;
	if (front) {
		front = temp2->link;
	}
	
};

void printlink(void) {
	stackPointer temp1 = top;
	while (temp1) {
		printf("%d ", (temp1->data).key); //��� 
		temp1 = temp1->link; //���� stack���� 
	}
	free(temp1);
	printf("\n");

	queuePointer temp2 = front;
	while (temp2) {
		printf("%d ", (temp2->data).key);
		temp2 = temp2->link;
	}
	free(temp2);
	printf("\n");

};

int main() {
	int a;
	element b;
	FILE *fp = fopen("input.txt", "r");
	while (1) {
		fscanf(fp, "%d", &a);
		if (feof(fp)) break;
		if (a == 0) {
			fscanf(fp, "%d", &b.key);
			push(b);
		}
		else if (a == 1) {
			pop();
		}
	}
	printlink();

	fclose(fp);
	return 0;
}