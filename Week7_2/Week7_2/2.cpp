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
	RBtree(int max) {	//	red-black tree ����
		z = new node(0, infoNIL, black, 0, 0);	//	NULL
		z->l = z; z->r = z;
		head = new node(itemMIN, infoNIL, black, z, z);	//	�� ���
	}
	void insert(itemType k, infoType info) {	//	����
		x = head; p = head; g = head;
		while (x != z) {	//	��ġ ã��
			gg = g; g = p; p = x;
			result++;
			x = (k < x->key) ? x->l : x->r;
			if (x->l->tag && x->r->tag) split(k);	//	�Ѵ� red��
		}
		x = new node(k, info, red, z, z);
		result++;
		if (k < p->key) p->l = x; else p->r = x;
		split(k); head->r->tag = black;
	}

	struct node *rotate(itemType k, struct node *y) {	//	ȸ��
		struct node *high, *low;
		result++;
		high = (k< y->key) ? y->l : y->r;	//	���� �ø� ���
		result++;
		if (k < high->key) { low = high->l; high->l = low->r; low->r = high; }	//	k ��ġ
		else { low = high->r; high->r = low->l; low->l = high; }
		result++;
		if (k < y->key) y->l = low; else y->r = low;
		return low;
	}
	void split(itemType k) {	//	�� �ο� �� ȸ���Ͽ� ����
		x->tag = red; x->l->tag = black; x->r->tag = black;
		if (p->tag) {	//	p->tag�� red��
			g->tag = red;
			result += 2;
			if (k<g->key != k<p->key) p = rotate(k, g);
			x = rotate(k, gg);
			x->tag = black;
		}
	}
	infoType search(itemType k) {
		struct node *temp = head->r;
		z->key = k;  // �Ʒ� �ݺ����� ������ ����� ����
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




void chain_insert(element item, int h, list_ptr* bucket) {	//	����
	list_ptr temp, trail = NULL;
	list_ptr lead;

	for (lead = *bucket; lead; trail = lead, lead = lead->link);	//	NULL�� ���� ������

	temp = (list_ptr)malloc(sizeof(list));
	temp->item = item;
	temp->link = NULL;
	if (trail) {	//	bucket�� ������� ���� ��
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
		if (lead->item == item) {	//	item�� ã�� ���
			return true;
		}
	}
	return false;	//	�� ã�� ���
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

	for (int i = 0; i < num; i++) {	//	T3 ����
		T3.insert((itemType)datas[i], (infoType)i);
	}
	printf("%.2lf ( T3�� ���� �� ��� �� ȸ�� )\n", result*1.0 / num);

	for (int i = 0; i < num; i++) {	//	Hash Table ũ�Ⱑ 11�� ����� ����
		chain_insert(datas[i], datas[i] % 11, &ht1[datas[i] % 11]);
	}
	printf("0.00 ( Hash Table ũ�Ⱑ 11�� ����� ���� �� ��� �� ȸ�� )\n");

	for (int i = 0; i < num; i++) {	//	Hash Table ũ�Ⱑ 101�� ����� ����
		chain_insert(datas[i], datas[i] % 101, &ht2[datas[i] % 101]);
	}
	printf("0.00 ( Hash Table ũ�Ⱑ 101�� ����� ���� �� ��� �� ȸ�� )\n");

	for (int i = 0; i < num; i++) {	//	Hash Table ũ�Ⱑ 1009�� ����� ����
		chain_insert(datas[i], datas[i] % 1009, &ht3[datas[i] % 1009]);
	}
	printf("0.00 ( Hash Table ũ�Ⱑ 1009�� ����� ���� �� ��� �� ȸ�� )\n");

	printf("\n");

	result = 0;
	for (int i = 0; i < num; i++) {	//	T3 ������ Ž��
		T3.search((itemType)datas[i]);
	}
	printf("%.2lf ( T3�� ��� �� ȸ�� )\n", result*1.0 / num);	//	T3 ��� Ž�� �� Ƚ��

	result = 0;
	for (int i = 0; i < num; i++) {	//	Hash Table ũ�Ⱑ 11�� ��� ������ Ž��
		chain_search(datas[i], datas[i] % 11, &ht1[datas[i] % 11]);
	}
	printf("%.2lf ( Hash Table ũ�Ⱑ 11�� ��� ��� �� ȸ�� )\n", result*1.0 / num);

	result = 0;
	for (int i = 0; i < num; i++) {	//	Hash Table ũ�Ⱑ 101�� ��� ������ Ž��
		chain_search(datas[i], datas[i] % 101, &ht2[datas[i] % 101]);
	}
	printf("%.2lf ( Hash Table ũ�Ⱑ 101�� ��� ��� �� ȸ�� )\n", result*1.0 / num);

	result = 0;
	for (int i = 0; i < num; i++) {	//	Hash Table ũ�Ⱑ 1009�� ��� ������ Ž��
		chain_search(datas[i], datas[i] % 1009, &ht3[datas[i] % 1009]);
	}
	printf("%.2lf( Hash Table ũ�Ⱑ 1009�� ��� ��� �� ȸ�� )\n", result*1.0 / num);

	return 0;
}
