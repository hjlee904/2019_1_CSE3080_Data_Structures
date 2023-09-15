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
	stackPointer temp1; //추가하는 stack의 주소값
	temp1 = (stackPointer)malloc(sizeof(stack));
	temp1->data = item; //data에 파일에서 읽어들인 값 저장
	temp1->link = NULL;
	if (!top) {
		top = temp1;
	}
	else {
		temp1->link = top; //link에 제일 끝에 위치해 있던 stack의 주소값(top의 주소값) 저장
		top = temp1; //top은 다시 새로 입력된 stack 가리킴
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
		printf("%d ", (temp1->data).key); //출력 
		temp1 = temp1->link; //다음 stack으로 
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