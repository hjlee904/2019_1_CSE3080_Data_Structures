#include<stdio.h>
#include<string.h>
#include<stdlib.h>

int nfind(char*, char*);
int kmp(char*, char*);
void fail(char*);
char failure[100];
int m1 = 0;

int main() {
	
	char str[100];
	char pat[100];

	scanf("%s", str);
	scanf("%s", pat);

	nfind(str, pat);
	fail(pat);
	kmp(str, pat);
	
	return 0;
}

int nfind(char *string, char *pat) {
	int i, j, start = 0;
	int k = 0, m = 0;
	int lasts = strlen(string) - 1;
	int lastp = strlen(pat) - 1;
	int endmatch = lastp;
	
	for (i = 0; endmatch <= lasts; endmatch++, start++) {
		if (string[endmatch] == pat[lastp]) {
			for (j = 0, i = start; (j < lastp) && (string[i] == pat[j]); i++, j++)
				m++;
			if (j == lastp) {
				k = 1;
			}
		}
		m++;
	}
	if (k == 0) {
		printf("nfind: NO\n");
	}
	else if (k == 1) {
		printf("nfind: YES ");
		printf("%d\n", m);
	}

	return -1;
}

int kmp(char *string, char *pat) {
	int i = 0, j = 0;
	int k = 0;
	int lens = strlen(string);
	int lenp = strlen(pat);
	while (i < lens && j < lenp) {
		if (string[i] == pat[j]) {
			i++; j++;
		}
		else if (j == 0) i++;
		else j = failure[j - 1] + 1;
		m1++;
	}
	
	if (j == lenp) {
		k = 1;
	}

	if (k == 0) {
		printf("kmp: NO\n");
	}
	else if (k == 1) {
		printf("kmp: YES ");
		printf("%d\n", m1);
	}
	return -1;
}

void fail(char *pat) {
	int i;
	int n = strlen(pat);
	failure[0] = -1;
	for (int j = 1; j < n; j++) {
		i = failure[j - 1];
		while ((pat[j] != pat[i + 1]) && (i >= 0)) {
			i = failure[i];
			m1++;
		}
		if (pat[j] == pat[i + 1]) {
			failure[j] = i + 1;
		}
		else { failure[j] = -1; }
		m1++;
	}
}