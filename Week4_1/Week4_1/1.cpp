#include<stdio.h>	//	input, output
#include<stdlib.h>	//	rand()
#include<time.h>	//	srand()
#include<algorithm>	//	sort()
#define MAX_N 100000
using namespace std;
typedef int itemType;
int N;
itemType A[MAX_N];
itemType B[MAX_N];
int sc;	//	sort한 횟수
struct st{
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
inline void swap(itemType a[], int i, int j)
{
	itemType  t = a[i]; a[i] = a[j]; a[j] = t;
}


int partition(itemType a[], int l, int r)
{
	int i, j; itemType v;
	if (r > l) {
		cnt[sc].b++;
		v = a[l]; i = l; j = r + 1;
		for (;;) {
			//cnt[sc].a++;
			while (a[++i] < v) cnt[sc].a++;	//	기준보다 작은 수가 나올때까지
			//cnt[sc].a++;
			while (a[--j] > v) cnt[sc].a++;	//	기준보다 큰 수가 나올때까지
			if (i >= j) break;
			swap(a, i, j);	//	바꿔주고
		}
		swap(a, j, l);	//	기준을 가운데로
	}
	return j;
}

void quicksort(itemType a[], int l, int r) {
	int  j;
	if (r > l) {
		j = partition(a, l, r);
		quicksort(a, l, j - 1);	//	기준점을 기준으로 좌 정렬
		quicksort(a, j + 1, r);	//	우 정렬
	}
}

int main(){
	scanf("%d", &N);
	make_data();
	quicksort(A, 1, N);
	sc++;
	quicksort(B, 1, N);
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
