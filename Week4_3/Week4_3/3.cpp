#include<stdio.h>
#include<string.h>
#define buffer_size 1000
#define MAX_NOW 10000
typedef struct st {
	char str[20];	//	word string
	int cnt;	//	�󵵼�
}itemType;
itemType word[MAX_NOW];
int NOW;	//	Number Of Words
void insert(char* p) {
	for (int i = 0; i < NOW; i++) {
		if (strcmp(word[i].str, p) == 0) {	//	���� Ž��
			word[i].cnt++;	//	ã���� �󵵼� ����
			return;
		}
	}
	strcpy(word[NOW].str, p);	//	�� �ܾ��� ��� �־��ְ�
	word[NOW].cnt = 1;	//	�󵵼��� 1��
	NOW++;
}
void input() {
	FILE *in = fopen("datafile.txt", "r");
	char buffer[buffer_size];
	char delimeters[30] = { " .,/\r\t\n" };	//	�ܾ ���� ����
	char* pointer;
	while(true) {
		fgets(buffer, sizeof(buffer), in);	//	�� ���� �Է�
		if (feof(in)) {	//	������ ������ �Է�
			break;
		}

		pointer = strtok(buffer, delimeters);	//	�������� �ܾ�
		while (true) {
			if (pointer == NULL) {
				break;	//	NULL�� ��� �ܾ �� ���Դٴ� ��
			}
			insert(pointer);	//	����
			pointer = strtok(NULL, delimeters);	//	�ٽ� ������
		}
	}
	fclose(in);
}
inline void swap(itemType a[], int i, int j)
{
	itemType  t = a[i]; a[i] = a[j]; a[j] = t;
}
bool compare(itemType i, itemType j) {	//	�� ����
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
			while (!compare(a[++i], v));	//	a�� v���� ���ϰ��
			while (compare(a[--j], v));		//	b�� v���� ���ϰ��
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
		printf("%s : %d\n", word[i].str, word[i].cnt);	//	���
	}
}
int main() {
	input();
	process();
	output();
	return 0;
}
