#include<stdio.h>	//	input, output
#include<stdlib.h>	//	rand()
#include<time.h>	//	srand()
#include<algorithm>	//	sort()
#define MAX_N 30010
using namespace std;
typedef int itemType;
int N;
itemType A[MAX_N];
itemType B[MAX_N];
itemType C[MAX_N];
int counting[MAX_N];
int answer[MAX_N];
int sc;	//	sort한 횟수
struct st {
	int a, b;	//	수 두개를 묶는 구조체
}D[MAX_N], cnt[3];
bool compare(const st i, const st j) {	//	정렬 기준
	return i.a < j.a;
}
void make_data() {
	int r;
	srand((unsigned)time(NULL));
	for (int i = 1; i <= N; i++) {
		D[i].a = rand() % N + 1;	//	random number
		D[i].b = i;
	}
	sort(D + 1, D + N + 1, compare);	//	order sort
	for (int i = 1; i <= N; i++) {
		A[i] = N - i + 1;
		B[i] = D[i].b;
		C[i] = rand() % N + 1;
	}
}
void CountSort(int a[], int n, int b[], int k) {
	int i, j;
	for (i = 1; i <= k; i++) counting[i] = 0;	//	초기화
	for (i = 1; i <= n; i++) {
		//cnt[sc].b++;
		counting[a[i]] = counting[a[i]] + 1;	//	각 키의 갯수
	}
	for (i = 2; i <= k; i++) {
		//cnt[sc].b++;
		counting[i] = counting[i] + counting[i - 1];		//	누적 합
	}
	for (j = n; j >= 1; j--) {
		//cnt[sc].b++;
		b[counting[a[j]]] = a[j];
		//cnt[sc].b++;
		counting[a[j]] = counting[a[j]] - 1;
	}
	for (int i = 1; i <= n; i++) {
		a[i] = b[i];	//	원래 배열로 이동
		cnt[sc].b++;
	}
}


int main() {
	scanf("%d", &N);
	make_data();
	CountSort(A, N, answer, N);
	sc++;
	CountSort(B, N, answer, N);
	sc++;
	CountSort(C, N, answer, N);
	printf("SortedData_A: ");	//	출력
	for (int i = 1; i <= 30; i++) {
		printf("%d ", A[i]);
	}
	printf("\n");
	printf("SortedData_B: ");
	for (int i = 1; i <= 30; i++) {
		printf("%d ", B[i]);
	}
	printf("\n");
	printf("SortedData_C: ");
	for (int i = 1; i <= 30; i++) {
		printf("%d ", C[i]);
	}
	printf("\n");
	printf("Compare_Cnt_A %d, DataMove_Cnt_A %d\n", cnt[0].a, cnt[sc].b);
	printf("Compare_Cnt_B %d, DataMove_Cnt_B %d\n", cnt[1].a, cnt[sc].b);
	printf("Compare_Cnt_C %d, DataMove_Cnt_B %d\n", cnt[2].a, cnt[sc].b);
	return 0;
}
