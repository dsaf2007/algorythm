#include<stdio.h>
#include<string.h>
#define buffer_size 1000
#define MAX_NOW 10000
typedef struct st {
	char str[20];	//	word string
	int cnt;	//	빈도수
}itemType;
itemType word[MAX_NOW];
int NOW;	//	Number Of Words
void insert(char* p) {
	for (int i = 0; i < NOW; i++) {
		if (strcmp(word[i].str, p) == 0) {	//	순차 탐색
			word[i].cnt++;	//	찾으면 빈도수 증가
			return;
		}
	}
	strcpy(word[NOW].str, p);	//	새 단어일 경우 넣어주고
	word[NOW].cnt = 1;	//	빈도수를 1로
	NOW++;
}
void input() {
	FILE *in = fopen("datafile.txt", "r");
	char buffer[buffer_size];
	char delimeters[30] = { " .,/\r\t\n" };	//	단어를 나눌 기준
	char* pointer;
	while(true) {
		fgets(buffer, sizeof(buffer), in);	//	줄 단위 입력
		if (feof(in)) {	//	파일의 끝까지 입력
			break;
		}

		pointer = strtok(buffer, delimeters);	//	나뉘어진 단어
		while (true) {
			if (pointer == NULL) {
				break;	//	NULL일 경우 단어가 다 나왔다는 뜻
			}
			insert(pointer);	//	삽입
			pointer = strtok(NULL, delimeters);	//	다시 나누기
		}
	}
	fclose(in);
}
inline void swap(itemType a[], int i, int j)
{
	itemType  t = a[i]; a[i] = a[j]; a[j] = t;
}
bool compare(itemType i, itemType j) {	//	비교 기준
	if (i.cnt<j.cnt) {
		return true;
	}
	else if (i.cnt == j.cnt) {
		return strcmp(i.str, j.str) > 0;
	}
	return false;
}
int partition(itemType a[], int l, int r) {
	int i, j; itemType v;
	if (r > l) {
		v = a[l]; i = l; j = r + 1;
		for (;;) {
			while (!compare(a[++i], v));	//	a가 v보다 뒤일경우
			while (compare(a[--j], v));		//	b가 v보다 앞일경우
			if (i >= j) break;
			swap(a, i, j);
		}
		swap(a, j, l);
	}
	return j;
}

void quicksort(itemType a[], int l, int r) {
	int  j;
	if (r > l) {
		j = partition(a, l, r);
		quicksort(a, l, j - 1);
		quicksort(a, j + 1, r);
	}
}
void process() {
	quicksort(word, 0, NOW - 1);
}
void output() {
	for (int i = 0; i < NOW; i++) {
		printf("%s : %d\n", word[i].str, word[i].cnt);	//	출력
	}
}
int main() {
	input();
	process();
	output();
	return 0;
}
