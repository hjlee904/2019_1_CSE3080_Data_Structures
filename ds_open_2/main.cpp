#include<stdio.h>
#include<stdlib.h>

typedef struct _entry {
	int coef;
	int expon;
} entry;

int readPoly(FILE* fp, entry* poly, int i) {
	int a;
	while (!feof(fp)) {
		fscanf(fp, "%d", &poly[i].coef);
		fscanf(fp, "%d", &poly[i].expon);
		/*printf("%d ", (i + 1) * sizeof(entry));
		printf("%d ", i);
		printf("%d %d\n", poly[i].coef, poly[i].expon);*/
		i++;
		realloc(poly, (i + 1) * sizeof(entry));
	}
	a = i;
	return a;
}

void printPoly(entry* poly, int j) {
	int i = 0;
	while (i < j - 1) {
		printf("(%d, %d)", poly[i].coef, poly[i].expon);
		i++;
		if (i == j - 2) break;
		printf(", ");
	}
}

/*void attach(entry *poly, int coefficient, int exponent, int avail) {
	poly[avail].coef = coefficient;
	poly[avail].expon = exponent;
}*/

entry* padd(entry* poly, int sa, int fa, int sb, int fb, int* sd, int* fd) {
	entry* poly2 = (entry*)malloc(sizeof(entry));
	int j = 0;
	int coefficient;
	*sd = j;
	while (sa <= fa && sb <= fb) {
		if (poly[sa].expon < poly[sb].expon) {
			//attach(poly2, poly[sb].coef, poly[sb].expon, j);
			poly2[j].coef = poly[sb].coef;
			poly2[j].expon = poly[sb].expon;
			j++;
			realloc(poly2, (j + 1) * sizeof(entry));
			sb++;
		}
		else if (poly[sa].expon == poly[sb].expon) {
			coefficient = poly[sa].coef + poly[sb].coef;
			if (coefficient) {
				//attach(poly2, coefficient, poly[sa].expon, j);
				poly2[j].coef = coefficient;
				poly2[j].expon = poly[sa].expon;
				j++;
				realloc(poly2, (j + 1) * sizeof(entry));
				sa++; sb++;
			}
		}
		else if (poly[sa].expon > poly[sb].expon) {
			//attach(poly2, poly[sa].coef, poly[sa].expon, j);
			poly2[j].coef = poly[sa].coef;
			poly2[j].expon = poly[sa].expon;
			j++;
			realloc(poly2, (j + 1) * sizeof(entry));
			sa++;
		}
	}
	for (; sa <= fa; sa++) {
		//attach(poly2, poly[sa].coef, poly[sa].expon, j);
		poly2[j].coef = poly[sa].coef;
		poly2[j].expon = poly[sa].expon;
		j++;
		realloc(poly2, (j + 1) * sizeof(entry));
	}
	for (; sb <= fb; sb++) {
		//attach(poly2, poly[sb].coef, poly[sb].expon, j);
		poly2[j].coef = poly[sb].coef;
		poly2[j].expon = poly[sb].expon;
		j++;
		realloc(poly2, (j + 1) * sizeof(entry));
	}
	*fd = j - 1;
	return poly2;
}

int main() {
	int a = 1, b, c;
	int* sd = NULL;
	int* fd = NULL;

	FILE* fp1 = fopen("A.txt", "r");
	FILE* fp2 = fopen("B.txt", "r");
	FILE* fp3 = fopen("C.txt", "r");

	entry* poly1 = (entry*)malloc(sizeof(entry));

	a = readPoly(fp1, poly1, a - 1);
	printf("%d ", a);
	b = readPoly(fp2, poly1, a - 1);
	printf("%d ", b);
	c = readPoly(fp3, poly1, b - 1);
	printf("%d ", c);
	/*for (int k = 0; k < c-1; k++) {
		printf("%d %d %d\n", k, poly1[k].coef, poly1[k].expon);
	}*/
	entry* poly2 = padd(poly1, 0, a - 2, a - 1, b - 2, sd, fd);
	entry* poly3 = padd(poly2, *sd, *fd, b - 1, c - 2, sd, fd);
	printPoly(poly3, *fd);
	return 0;

}

