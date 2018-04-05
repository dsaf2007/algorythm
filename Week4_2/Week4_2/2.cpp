#include<stdio.h>	//	input, output
#include<stdlib.h>	//	rand()
#include<time.h>	//	srand()
#include<algorithm>	//	sort()
#define MAX_N 1000010
using namespace std;
typedef int itemType;
int N;
itemType A[MAX_N];
itemType B[MAX_N];
int sc;	//	sort한 횟수
itemType sorted[MAX_N];
struct st {
	int a, b;	//	수 두개를 묶는 구조체
}C[MAX_N], cnt[2];
bool compare(const st i, const st j){	//	정렬 기준
	return i.a < j.a;
}
void make_data(){
	int r;
	srand((unsigned)time(NULL));
	for (int i = 1; i <= N; i++){
		C[i].a = rand() % N + 1;	//	random number
		C[i].b = i;
	}
	sort(C + 1, C + N, compare);	//	order sort
	for (int i = 1; i <= N; i++){
		A[i] = N - i + 1;
		B[i] = C[i].b;
	}
}

void merge(itemType a[], int l, int mid, int r) {
	int i, j, k, n;
	i = l; j = mid + 1; k = l;
	while (i <= mid && j <= r) {
		cnt[sc].a++;
		cnt[sc].b++;
		if (a[i] <= a[j]) {	//	두 집합의 맨 앞중 작은것을 정렬된배열에 넣어준다.
			sorted[k++] = a[i++];
		}
		else {
			sorted[k++] = a[j++];
		}
	}
	if (i > mid){
		for (n = j; n <= r; n++){
			cnt[sc].b++;
			sorted[k++] = a[n];	//	남은 데이터 처리
		}
	}
	else{
		for (n = i; n <= mid; n++){
			cnt[sc].b++;
			sorted[k++] = a[n];
		}
	}
	for (n = l; n <= r; n++){	//	정렬된 데이터를 다시 배열로
		cnt[sc].b++;
		a[n] = sorted[n];
	}
}
void mergesort(itemType a[], int l, int r) {
	int mid;
	if (l < r) {
		mid = (l + r) / 2;
		mergesort(a, l, mid);	//	재귀적으로
		mergesort(a, mid + 1, r);
		merge(a, l, mid, r);	//	정렬
	}
}


int main(){
	scanf("%d", &N);
	make_data();
	mergesort(A, 1, N);
	sc++;
	mergesort(B, 1, N);
	printf("SortedData_A: ");	//	출력
	for (int i = 1; i <= 30; i++){
		printf("%d ", A[i]);
	}
	printf("\n");
	printf("SortedData_B: ");
	for (int i = 1; i <= 30; i++){
		printf("%d ", B[i]);
	}
	printf("\n");
	printf("Compare_Cnt_A %d, DataMove_Cnt_A %d\n", cnt[0].a, cnt[0].b);
	printf("Compare_Cnt_B %d, DataMove_Cnt_B %d\n", cnt[1].a, cnt[1].b);
	return 0;
}
