#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>

typedef struct {
	int row;
	int col;
	int value;
}terms;

void fast_transpose(terms a[], terms b[], int m) {
	int temp1, temp2;
	int *row_terms = (int*)malloc(sizeof(int) * m);
	int *starting_pos = (int*)malloc(sizeof(int) * m);
	int i, j, num_cols = a[0].col, num_terms = a[0].value;
	b[0].row = num_cols; b[0].col = a[0].row;
	b[0].value = num_terms;
	if (num_terms > 0) {
		for (i = 0; i < num_cols; i++) row_terms[i] = 0;
		for (i = 1; i <= num_terms; i++) row_terms[a[i].col]++;
		//starting_pos[0] = 1;
		temp1 = row_terms[0]; row_terms[0] = 1;
		for (i = 1; i < num_cols; i++) {
			temp2 = row_terms[i];
			row_terms[i] = row_terms[i - 1] + temp1;
			temp1 = temp2;
			//starting_pos[i] = starting_pos[i - 1] + row_terms[i - 1];
		}
		for (i = 1; i <= num_terms; i++) {
			j = row_terms[a[i].col]++;
			//j = starting_pos[a[i].col]++;
			b[j].row = a[i].col; b[j].col = a[i].row;
			b[j].value = a[i].value;
		}
	}
}

int main() {
	int n, m, i = 1, j = 1;
	int va, ro = 0, co = 0;

	FILE *fp = fopen("A.txt", "r");
	fscanf(fp, "%d", &n);
	fscanf(fp, "%d", &m);

	terms *a = (terms *)malloc(sizeof(terms));
	a[0].row = n;
	a[0].col = m;
	a[0].value = 0;

	a = (terms*)realloc(a, sizeof(terms) * (i + 1));

	for (int l = 1; l <= (n * m); l++) {
		fscanf(fp, "%d", &va);
		if (va != 0) {
			a[i].col = co;
			a[i].row = ro;
			a[i].value = va;
			co++;
			i++;
			a = (terms*)realloc(a, sizeof(terms) * (i + 1));
		}
		else if (va == 0) { co++; }
		if ((j % m) == 0) { co = 0; ro++; }
		j++;
	}
	a[0].value = i - 1;
	
	terms *b = (terms *)malloc(sizeof(terms) * i);

	fast_transpose(a, b, m);

	for (int k = 0; k < i; k++) {
		printf("%d %d %d\n", b[k].row, b[k].col, b[k].value);
	}

	return 0;

}

