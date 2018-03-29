#include<stdio.h>
#define MAX_N 1000010
typedef int itemType;
int N;
long long int weight;
itemType A[MAX_N];
void make_data(){	//	make data
	int r;
	for (int i = 1; i <= N; i++){
		A[i] = N - i + 1;
	}
}

long long int insertion(itemType a[], int n)	//	insertion sort
{
	int i, j; itemType v;
	long long int result = 0;
	for (i = 2; i <= n; i++)
	{
		v = a[i]; j = i;
		result += (long long int)a[i];
		while (a[j - 1] > v) { 
			a[j] = a[j - 1];
			result += (long long int)a[j - 1];
			j--; 
		}
		a[j] = v;
		result += (long long int)v;
	}
	return result;
}

long long int shellSort(itemType a[], int n)	//	shell sort
{
	int i, j, h; itemType v;
	long long int result = 0;
	h = 1;  do h = 3 * h + 1; while (h < n);
	do {
		h = h / 3;
		for (i = h; i <= n; i++)
		{
			v = a[i]; j = i;
			result += (long long int)a[i];
			while (a[j - h] > v)
			{
				a[j] = a[j - h]; 
				result += (long long int)a[j - h];
				j -= h;
				if (j <= h - 1) break;
			}
			a[j] = v;
			result += (long long int)v;
		}
	} while (h > 1);
	return result;
}
// temp에 크기가 더 작은 것을 저장
bool bubble(bool sorted, itemType *a,int n){
		int temp;
	if (*(a - 1) > *a) {	
		weight += (*(a - 1)) + ((*a) * 2);
		temp = *a;			
		*a = *(a - 1);		
		*(a - 1) = temp;	
		sorted = false;
	}
	return sorted;
}
long long int bubbleSort(itemType a[], int n)	//	bubble sort
{
	//long long int result = 0;
	bool flag = false;
	while(!flag){
		flag = true;
		for(int i=1;i<N;++i)
			flag = bubble(flag,&a[i],n);
	}
	return weight;
}
int main(){
	scanf("%d", &N);
	make_data();
	printf("Insertion Sort : %lld\n", insertion(A, N));	//	출력
	make_data();
	printf("Bubble Sort : %lld\n", bubbleSort(A, N));
	make_data();
	printf("Shell Sort : %lld\n", shellSort(A, N));
	return 0;
}