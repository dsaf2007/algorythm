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
itemType C[MAX_N];
int sc;	//	sort한 횟수
struct st {
	int a, b;	//	수 두개를 묶는 구조체
}cnt[3];
int value[MAX_N];
int check[MAX_N];
bool compare(const st i, const st j) {	//	정렬 기준
	return i.a < j.a;
}
void make_data() {
	int r;
	srand((unsigned)time(NULL));
	for (int i = 0; i < N; i++) {
		value[i] = rand() % N + 1;
		while (check[value[i]] == 1)value[i] = rand() % N + 1;
		check[value[i]] = 1;
	}
	//sort(D, D + N, compare);	//	order sort
	for (int i = 0; i < N; i++) {
		A[i] = N - i;
		B[i] = value[i];
		C[i] = rand() % N + 1;
	}
}
class MAKE_HEAP {
private:
	int N;
public:
	MAKE_HEAP() {}
	~MAKE_HEAP() {}
	void swap(itemType a[], int i, int j) {
		int temp;
		cnt[sc].b += 3;
		temp = a[j]; a[j] = a[i]; a[i] = temp;
	}
	void MakeHeap(itemType a[], int Root, int LastNode) {
		int Parent, LeftSon, RightSon, Son; itemType RootValue;
		Parent = Root;
		RootValue = a[Root];
		LeftSon = 2 * Parent + 1;
		RightSon = LeftSon + 1;
		while (LeftSon <= LastNode) {	//	자식이 있을 때
			cnt[sc].a++;
			if (RightSon <= LastNode && a[LeftSon] < a[RightSon]) {	//	오른쪽 자식이 존재하며 오른쪽 자식이 더 클때
																	//cnt[sc].a++;
				Son = RightSon;	//	Son에 오른쪽 자식을 저장하고
			}
			else Son = LeftSon;	//	아닐경우 왼쪽 자식 저장
			cnt[sc].a++;
			if (RootValue < a[Son]) {	//	Son이 부모보다 큰 경우
				cnt[sc].b++;
				a[Parent] = a[Son];	//	부모와 Son을 바꿔 줌
				Parent = Son;	//	그리고 자식노드로 내려가서 반복
				LeftSon = Parent * 2 + 1;
				RightSon = LeftSon + 1;
			}
			else break;
		}
		cnt[sc].b++;
		a[Parent] = RootValue;
	}
	void heapsort(itemType a[], int N) {
		int i;
		for (i = N / 2; i >= 1; i--)  MakeHeap(a, i - 1, N - 1);		//	초기 힙 구성
		for (i = N - 1; i >= 1; i--) { swap(a, 0, i); MakeHeap(a, 0, i - 1); }	//	정렬
	}
};

int main() {
	scanf("%d", &N);
	MAKE_HEAP heap;
	make_data();
	heap.heapsort(A, N);
	sc++;
	heap.heapsort(B, N);
	sc++;
	heap.heapsort(C, N);
	printf("SortedData_A: ");	//	출력
	for (int i = 0; i < 20; i++) {
		printf("%d ", A[i]);
	}
	printf("\n");
	printf("SortedData_B: ");
	for (int i = 0; i < 20; i++) {
		printf("%d ", B[i]);
	}
	printf("\n");
	printf("SortedData_C: ");
	for (int i = 0; i < 20; i++) {
		printf("%d ", C[i]);
	}
	printf("\n");
	printf("Compare_Cnt_A %d, DataMove_Cnt_A %d\n", cnt[0].a, cnt[0].b);
	printf("Compare_Cnt_B %d, DataMove_Cnt_B %d\n", cnt[1].a, cnt[1].b);
	printf("Compare_Cnt_C %d, DataMove_Cnt_B %d\n", cnt[2].a, cnt[2].b);
	return 0;
}