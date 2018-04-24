#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#include<iostream>

#define infoNIL 0
#define itemMIN -1
#define MAX_N 100010

#define infoNIL 0
#define itemMIN -1
#define black 0
#define red 1

typedef int itemType;
typedef int infoType;
using namespace std;

int result;
int queue[MAX_N], front, rear;	//	inorder 순으로 순회한 결과

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

class BST {
private:
	struct node {
		itemType key; infoType info;
		struct node *l, *r;
		node(itemType k, infoType i, struct node *ll, struct node *rr)  // node 생성시 초기값 부여 가능 
		{
			key = k; info = i; l = ll; r = rr;
		};
	};
	struct node *head, *z; // z : List의 끝을 대표하는 node pointer – NULL에 해당
public:
	BST(int max) {	//	생성자
		z = new node(0, infoNIL, 0, 0);
		head = new node(itemMIN, infoNIL, z, z);
	}
	~BST() {	//	소멸자
	}
	infoType  BSTsearch(itemType v);
	void BSTinsert(itemType v, infoType info);
	void BSTdelete(itemType v);

	void InorderRecursive(node* p) {	//	재귀 메소드를 이용해 순회
		if (p->l != z) {	//	왼쪽자식부터
			InorderRecursive(p->l);
		}
		queue[rear] = p->key;	//	자신
		rear++;
		if (p->r != z) {	//	오른쪽자식
			InorderRecursive(p->r);
		}
	}

	void Inorder() {
		InorderRecursive(head->r);
	}
};

BST T1(MAX_N);
BST T2(MAX_N);
RBtree T3(MAX_N);

infoType BST::BSTsearch(itemType v) {	//	탐색
	struct node *x = head->r;
	z->key = v;  // 아래 반복문을 간결히 만들기 위함
	while (v != x->key) {
		result++;
		x = (v < x->key) ? x->l : x->r;
	}
	return x->info;
}

void BST::BSTinsert(itemType v, infoType info) {	//	삽입
	struct node *p, *x;
	p = head; x = head->r;
	while (x != z) { p = x; result++; x = (v < x->key) ? x->l : x->r; }
	x = new node(v, info, z, z);
	result++;
	if (v < p->key) p->l = x; else p->r = x;
}

void BST::BSTdelete(itemType v) {	//	삭제
	struct node *x = head->r, *p, *t, *c;
	p = head;
	result++;
	while (x->key != v && x != z) {
		p = x;
		result++;
		x = (v < x->key) ? x->l : x->r;
		result++;
	}
	if (x == z) return;
	else t = x;
	if (t->r == z) x = t->l;
	else if (t->r->l == z) {
		x = t->r; x->l = t->l;
	}
	else {
		c = x->r; while (c->l->l != z) c = c->l;
		x = c->l; c->l = x->r;
		x->l = t->l; x->r = t->r;
	}
	free(t);
	result++;
	if (v<p->key) p->l = x; else p->r = x;
}

int num;
int datas[MAX_N];
bool check[MAX_N];



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
	

	for (int i = 0; i < num; i++) {	//	T1 구축
		T1.BSTinsert((itemType)datas[i], (infoType)i);
	}
	printf("%.2lf ( T1의 구축 시 평균 비교 회수 )\n", result*1.0 / num);

	T1.Inorder();

	result = 0;
	for (int i = 0; i < num; i++) {	//	T2 구축
		T2.BSTinsert((itemType)queue[i], (infoType)i);
	}
	printf("%.2lf ( T2의 구축 시 평균 비교 회수 )\n", result*1.0 / num);

	result = 0;
	for (int i = 0; i < num; i++) {	//	T3 구축
		T3.insert((itemType)queue[i], (infoType)i);
	}
	printf("%.2lf ( T3의 구축 시 평균 비교 회수 )\n", result*1.0 / num);

	printf("\n");

	result = 0;
	for (int i = 0; i < num; i++) {	//	T1 데이터 탐색
		T1.BSTsearch((itemType)datas[i]);
	}
	printf("%.2lf ( T1의 평균 탐색 비교 회수 )\n", result*1.0 / num);

	result = 0;
	for (int i = 0; i < num; i++) {	//	T2 데이터 탐색
		T2.BSTsearch((itemType)datas[i]);
	}
	printf("%.2lf ( T2의 평균 탐색 비교 회수 )\n", result*1.0 / num);


	result = 0;
	for (int i = 0; i < num; i++) {	//	T3 데이터 탐색
		T3.search((itemType)datas[i]);
	}
	printf("%.2lf ( T3의 평균 탐색 비교 회수 )\n", result*1.0 / num);
	/*time_t timer = time(NULL);
	struct tm *t = localtime(&timer);
	cout << t->tm_year + 1900 << "/" << t->tm_mon + 1 << "/" << t->tm_mday << " " << t->tm_hour << ":" << t->tm_min << ":" << t->tm_sec << endl;*/
	return 0;
}