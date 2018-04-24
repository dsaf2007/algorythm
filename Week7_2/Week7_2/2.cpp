#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#include<iostream>

#define infoNIL 0
#define itemMIN -1
#define MAX_N 10010

#define infoNIL 0
#define itemMIN -1
#define black 0
#define red 1

typedef int itemType;
typedef int infoType;
using namespace std;


int result;

class RBtree {
private:
	struct node {
		itemType key, tag;
		infoType Info;
		struct node *l, *r;
		node(itemType k, infoType i, itemType t, struct node *ll, struct node *rr) {
			key = k; Info = i; tag = t; l = ll; r = rr;
		}
	};
	struct node *head, *tail, *x, *p, *g, *gg, *z;
public:
	RBtree(int max) {	//	red-black tree 생성
		z = new node(0, infoNIL, black, 0, 0);	//	NULL
		z->l = z; z->r = z;
		head = new node(itemMIN, infoNIL, black, z, z);	//	빈 노드
	}
	void insert(itemType k, infoType info) {	//	삽입
		x = head; p = head; g = head;
		while (x != z) {	//	위치 찾기
			gg = g; g = p; p = x;
			result++;
			x = (k < x->key) ? x->l : x->r;
			if (x->l->tag && x->r->tag) split(k);	//	둘다 red면
		}
		x = new node(k, info, red, z, z);
		result++;
		if (k < p->key) p->l = x; else p->r = x;
		split(k); head->r->tag = black;
	}

	struct node *rotate(itemType k, struct node *y) {	//	회전
		struct node *high, *low;
		result++;
		high = (k< y->key) ? y->l : y->r;	//	위로 올릴 노드
		result++;
		if (k < high->key) { low = high->l; high->l = low->r; low->r = high; }	//	k 배치
		else { low = high->r; high->r = low->l; low->l = high; }
		result++;
		if (k < y->key) y->l = low; else y->r = low;
		return low;
	}
	void split(itemType k) {	//	색 부여 후 회전하여 조정
		x->tag = red; x->l->tag = black; x->r->tag = black;
		if (p->tag) {	//	p->tag가 red면
			g->tag = red;
			result += 2;
			if (k<g->key != k<p->key) p = rotate(k, g);
			x = rotate(k, gg);
			x->tag = black;
		}
	}
	infoType search(itemType k) {
		struct node *temp = head->r;
		z->key = k;  // 아래 반복문을 간결히 만들기 위함
		while (k != temp->key) {
			result++;
			temp = (k < temp->key) ? temp->l : temp->r;
		}
		return temp->Info;
	}
};

RBtree T3(MAX_N);

typedef int element;
typedef struct list *list_ptr;
typedef struct list {
	element item;
	list_ptr link;
};
list_ptr ht1[11];
list_ptr ht2[101];
list_ptr ht3[1009];

int num;
int datas[MAX_N];
bool check[MAX_N];




void chain_insert(element item, int h, list_ptr* bucket) {	//	삽입
	list_ptr temp, trail = NULL;
	list_ptr lead;

	for (lead = *bucket; lead; trail = lead, lead = lead->link);	//	NULL을 만날 때까지

	temp = (list_ptr)malloc(sizeof(list));
	temp->item = item;
	temp->link = NULL;
	if (trail) {	//	bucket이 비어있지 않을 때
		trail->link = temp;
	}
	else {
		*bucket = temp;
	}
}

bool chain_search(element item, int h, list_ptr* bucket) {
	list_ptr lead;
	for (lead = *bucket; lead; lead = lead->link) {
		result++;
		if (lead->item == item) {	//	item을 찾은 경우
			return true;
		}
	}
	return false;	//	못 찾은 경우
}



int main() {
	srand(time(NULL));
	cin >> num;
	
	int i, j;
	for (i = 0; i < num; i++) {
		while (true) {
			j = rand() % num;
			if (!check[j]) {
				check[j] = true;
				break;
			}
		}
		datas[i] = j + 1;
	}

	for (int i = 0; i < num; i++) {	//	T3 구축
		T3.insert((itemType)datas[i], (infoType)i);
	}
	printf("%.2lf ( T3의 구축 시 평균 비교 회수 )\n", result*1.0 / num);

	for (int i = 0; i < num; i++) {	//	Hash Table 크기가 11인 경우의 구축
		chain_insert(datas[i], datas[i] % 11, &ht1[datas[i] % 11]);
	}
	printf("0.00 ( Hash Table 크기가 11인 경우의 구축 시 평균 비교 회수 )\n");

	for (int i = 0; i < num; i++) {	//	Hash Table 크기가 101인 경우의 구축
		chain_insert(datas[i], datas[i] % 101, &ht2[datas[i] % 101]);
	}
	printf("0.00 ( Hash Table 크기가 101인 경우의 구축 시 평균 비교 회수 )\n");

	for (int i = 0; i < num; i++) {	//	Hash Table 크기가 1009인 경우의 구축
		chain_insert(datas[i], datas[i] % 1009, &ht3[datas[i] % 1009]);
	}
	printf("0.00 ( Hash Table 크기가 1009인 경우의 구축 시 평균 비교 회수 )\n");

	printf("\n");

	result = 0;
	for (int i = 0; i < num; i++) {	//	T3 데이터 탐색
		T3.search((itemType)datas[i]);
	}
	printf("%.2lf ( T3의 평균 비교 회수 )\n", result*1.0 / num);	//	T3 평균 탐색 비교 횟수

	result = 0;
	for (int i = 0; i < num; i++) {	//	Hash Table 크기가 11인 경우 데이터 탐색
		chain_search(datas[i], datas[i] % 11, &ht1[datas[i] % 11]);
	}
	printf("%.2lf ( Hash Table 크기가 11인 경우 평균 비교 회수 )\n", result*1.0 / num);

	result = 0;
	for (int i = 0; i < num; i++) {	//	Hash Table 크기가 101인 경우 데이터 탐색
		chain_search(datas[i], datas[i] % 101, &ht2[datas[i] % 101]);
	}
	printf("%.2lf ( Hash Table 크기가 101인 경우 평균 비교 회수 )\n", result*1.0 / num);

	result = 0;
	for (int i = 0; i < num; i++) {	//	Hash Table 크기가 1009인 경우 데이터 탐색
		chain_search(datas[i], datas[i] % 1009, &ht3[datas[i] % 1009]);
	}
	printf("%.2lf( Hash Table 크기가 1009인 경우 평균 비교 회수 )\n", result*1.0 / num);

	return 0;
}
