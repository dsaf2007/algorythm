#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<algorithm>
#define MAX_N 1000010
using namespace std;
typedef int itemType;
int N;
itemType A[MAX_N];
itemType B[MAX_N];
struct st{
	int a, b;
}C[MAX_N];
bool compare(const st i, const st j){	//	정렬 기준
	return i.a < j.a;
}
void make_data(){	//	make data
	int r;
	srand((unsigned)time(NULL));
	for (int i = 1; i <= N; i++){
		C[i].a = rand() % N + 1;
		C[i].b = i;
	}
	sort(C + 1, C + N, compare);
	for (int i = 1; i <= N; i++){
		A[i] = N - i + 1;
		B[i] = C[i].b;
	}
}

st Bubble(int sorted, itemType *a, int n)
{
	int temp;
	st s;
	s.b = 0;
	if (*(a - 1) > *a) {	//	비교
		temp = *(a - 1);	//	swap
		*(a - 1) = *a;
		*a = temp;
		s.b += 3;	//	data move count
		sorted = false;
	}
	s.a = sorted;	//	is sorted
	return s;
}

st bubbleSort(itemType a[], int n)
{
	int i;
	st Sorted;
	st result = { 0, 0 };
	Sorted.a = false;
	while (!Sorted.a) {	//	바뀌지 않았다면 종료
		Sorted.a = true;
		for (i = 1; i <= n; i++){
			Sorted = Bubble(Sorted.a, &a[i], n);
			result.a++;	//	compare count++
			result.b += Sorted.b;	//	data move count
		}
	}
	return result;
}

int main(){
	st result_of_A, result_of_B;
	scanf("%d", &N);
	make_data();
	result_of_A = bubbleSort(A, N);
	result_of_B = bubbleSort(B, N);
	printf("SortedData_A: ");	//	print
	for (int i = 1; i <= 20; i++){
		printf("%d ", A[i]);
	}
	printf("\n");
	printf("SortedData_B: ");
	for (int i = 1; i <= 20; i++){
		printf("%d ", B[i]);
	}
	printf("\n");
	printf("Compare_Cnt_A %d, DataMove_Cnt_A %d\n", result_of_A.a, result_of_A.b);
	printf("Compare_Cnt_B %d, DataMove_Cnt_B %d\n", result_of_B.a, result_of_B.b);
	return 0;
}