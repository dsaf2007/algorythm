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
int sc;	//	sort�� Ƚ��
struct st{
    int a, b;	//	�� �ΰ��� ���� ����ü
}D[MAX_N], cnt2[3];
bool compare(const st i, const st j){	//	���� ����
    return i.a < j.a;
}
void make_data(){
    int r;
    srand((unsigned)time(NULL));
    for (int i = 1; i <= N; i++){
        D[i].a = rand() % N + 1;	//	random number
        D[i].b = i;
    }
    sort(D + 1, D + N + 1, compare);	//	order sort
    for (int i = 1; i <= N; i++){
        A[i] = N - i + 1;
        B[i] = D[i].b;
        C[i] = rand() % N + 1;
    }
}
typedef struct node *node_pointer;
typedef struct node {
    itemType value;
    node_pointer next;
};
node_pointer TABLE[10], x, z, temp;
void radixSort(itemType *a, int n) {
    int i, j, cnt, radix, radix_mod = 10, cipher = 0;
    i = n;
    while (i>0) { i = i / 10; cipher++; } // cipher : �Է� �������� �ڸ��� (ex. 450 -> 3)
    for (i = 0; i<cipher; i++) {
        for (j = 0; j<n; j++) {
            cnt = 0; radix = (a[j] % radix_mod) / (radix_mod / 10);
            /* radix_mod = 10 �̸� radix�� a[j]�� ���� �ڸ���
             radix_mod = 100 �̸� radix�� a[j]�� ���� �ڸ��� */
            //Cnt[sc].b++;
            temp = new node; temp->value = a[j]; temp->next = z;
            if (TABLE[radix] == z) {
                // z�� list�� ���� Ȯ���ϱ� ���� ��� ������ (NULL�� �ش�)
                cnt2[sc].b++;
                TABLE[radix] = temp;
            }
            else {
                cnt2[sc].b++;
                x = TABLE[radix];	//	Table[radix]�� �������������� ���ܳ����� ã�ư��� ����
                while (x->next != z) {
                    x = x->next;
                }
                //Cnt[sc].b++;
                x->next = temp;
            }
        }
        
        for (j = 0; j<10; j++) {	//	�����ڸ� �Ʒ��� ���ĵ� ������ �������� �۾�
            if (TABLE[j] != z) {
                cnt2[sc].b++;
                x = TABLE[j];
                while (x != z) {
                    cnt2[sc].b++;
                    a[cnt++] = x->value;
                    temp = x; // �޸𸮿��� ��带 �����ϱ� ���� �ӽ� ����
                    x = x->next;
                    delete temp; // �迭�� �̹� ���� ��带 �޸𸮿��� ����
                }
            }
            cnt2[sc].b++;
            TABLE[j] = z;
        }
        radix_mod *= 10;
    }
}



int main(){
    scanf("%d", &N);
    make_data();
    radixSort(A, N);
    sc++;
    radixSort(B, N);
    sc++;
    radixSort(C, N);
    printf("SortedData_A: ");	//	���
    for (int i = 1; i <= 30; i++){
        printf("%d ", A[i]);
    }
    printf("\n");
    printf("SortedData_B: ");
    for (int i = 1; i <= 30; i++){
        printf("%d ", B[i]);
    }
    printf("\n");
    printf("SortedData_C: ");
    for (int i = 1; i <= 30; i++){
        printf("%d ", C[i]);
    }
    printf("\n");
    printf("Compare_Cnt_A %d, DataMove_Cnt_A %d\n", cnt2[0].a, cnt2[0].b);
    printf("Compare_Cnt_B %d, DataMove_Cnt_B %d\n", cnt2[1].a, cnt2[1].b);
    printf("Compare_Cnt_C %d, DataMove_Cnt_B %d\n", cnt2[2].a, cnt2[2].b);
    return 0;
}