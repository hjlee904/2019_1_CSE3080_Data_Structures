#include "stdio.h"
#include "stdlib.h"
#pragma warning(disable:4996) 

typedef struct threadedTree *threadedPointer;
typedef struct threadedTree {
	short int leftThread;
	threadedPointer leftChild;
	char data;
	threadedPointer rightChild;
	short int rightThread;
} threadedTree;
threadedPointer insucc(threadedPointer tree) {
	threadedPointer temp;
	temp = tree->rightChild;
	if (!tree->rightThread) {
		while (!temp->leftThread) {
			temp = temp->leftChild;
		}
	}
	return temp;
}
void tinorder(threadedPointer tree) {
	threadedPointer temp = tree;
	for (;;) {
		temp = insucc(temp);
		if (temp == tree) {
			break;
		}
		printf("%3c", temp->data);
	}
	printf("\n");
}
void insertRight(threadedPointer s, threadedPointer r) {
	threadedPointer temp;
	r->rightChild = s->rightChild;
	r->rightThread = s->rightThread;
	r->leftChild = s;
	r->leftThread = true;
	s->rightChild = r;
	s->rightThread = false;
	if (!r->rightChild) {
		temp = insucc(r);
		temp->leftChild = r;
	}
}
void insertLeft(threadedPointer s, threadedPointer l) {
	threadedPointer temp;
	l->rightChild = s;
	l->rightThread = true;
	l->leftChild = s->leftChild;
	l->leftThread = l->leftThread;
	s->leftChild = l;
	s->leftThread = false;
	if (!l->rightChild) {
		temp = insucc(l);
		temp = insucc(temp);
		temp = insucc(temp);
		temp->rightChild = l;
	}
}
threadedPointer getNewNode(char data) {
	threadedPointer temp = NULL;
	temp = (threadedPointer)malloc(sizeof(threadedTree));
	temp->data = data;
	temp->leftThread = true;
	temp->rightThread = false;
	temp->rightChild = temp;
	temp->leftChild = temp;
	return temp;
}

int main() {
	threadedPointer root = getNewNode('-');
	insertLeft(root, getNewNode('A'));
	insertLeft(root->leftChild, getNewNode('B'));
	insertLeft(root->leftChild->leftChild, getNewNode('D'));
	insertLeft(root->leftChild->leftChild->leftChild, getNewNode('H'));
	insertRight(root->leftChild->leftChild->leftChild, getNewNode('I'));
	insertRight(root->leftChild->leftChild, getNewNode('E'));
	insertRight(root->leftChild, getNewNode('C'));
	insertLeft(root->leftChild->rightChild, getNewNode('F'));
	insertRight(root->leftChild->rightChild, getNewNode('G'));
	
	tinorder(root);
	return 0;
}