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
struct st{
	int a, b;	//	compare count, data move count
}C[MAX_N];
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
st insertion(itemType a[], int n)
{
	int i, j; itemType v;
	st result = { 0, 0 };
	for (i = 2; i <= n; i++)
	{
		v = a[i]; j = i;	//	삽입할 수
		result.b++;	//	data move count++
		while (a[j - 1] > v) { a[j] = a[j - 1]; j--; result.a++; result.b++; }	//	당겨오는 작업
		a[j] = v;	//	삽입
		
	}
	return result;	//	결과 반환
}
int main(){
	st result_of_A, result_of_B;
	scanf("%d", &N);
	make_data();
	result_of_A = insertion(A, N);
	result_of_B = insertion(B, N);
	printf("SortedData_A: ");	//	출력
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