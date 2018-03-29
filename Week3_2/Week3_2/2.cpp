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

st shellSort(itemType a[], int n)
{
	int i, j, h; itemType v;
	st result = { 0, 0 };
	h = 1;  do h = 3 * h + 1; while (h < n);	//	간격
	do {
		h = h / 3;	//	줄여가며
		for (i = h; i <= n; i++)
		{
			v = a[i]; j = i;
			result.b++;	//	data move count++
			while (a[j - h] > v)		//	각격별로 삽입 정렬
			{
				result.a++;
				a[j] = a[j - h]; j -= h; result.b++; if (j <= h - 1) break;
			}
			result.a++;	//	compare count
			a[j] = v;
			result.b++;
		}
	} while (h > 1);
	return result;
}


int main(){
	st result_of_A, result_of_B;
	scanf("%d", &N);
	make_data();
	result_of_A = shellSort(A, N);
	result_of_B = shellSort(B, N);
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