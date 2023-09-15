#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<time.h>

void sort(int*, int);

int main() {
	int i = 0, k = 0, t;
	int j, n;
	int step = 10;
	double duration;

	FILE* fp = fopen("input.txt", "r");
	printf("Input : ");

	while (1) {
		t = fgetc(fp);
		if (feof(fp)) break;
		if (t != 10) {
			i++;
		}
	}

	int* arr = (int*)malloc(sizeof(int) * i);

	FILE* fp2 = fopen("input.txt", "r");
	while (1) {
		fscanf(fp2, "%d", arr + k);
		if (k == i) break;
		printf("%d ", arr[k]);
		k++;
	}

	sort(arr, k);
	printf("\nSorted : ");
	for (j = 0; j < i; j++) {
		printf("%d ", arr[j]);
	}

	printf("\n     n  repetitions       time\n");

	for (n = 0; n <= 100; n += step) {
		long repetitions = 0;
		int* a = (int*)calloc(n, sizeof(int));
		for (int l = 0; l < n; l++) {
			a[l] = n - l;
		}
		clock_t start = clock();
		do {
			repetitions++;
			sort(a, n);
		} while (clock() - start < 1);
		duration = ((double)(clock() - start)) / CLOCKS_PER_SEC;
		duration /= repetitions;
		printf("%6d %12d %.8f\n", n, repetitions, duration);
	}

	fclose(fp);
	free(arr);
	return 0;
}

void sort(int* list, int i) {
	int j, k, min, temp;
	for (j = 0; j < i - 1; j++) {
		min = j;
		for (k = j + 1; k < i; k++) {
			if (list[k] < list[min]) min = k;
		}
		temp = list[min];
		list[min] = list[j];
		list[j] = temp;
	}
}
