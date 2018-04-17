#include<stdio.h>
#include <iostream>
#include<time.h>
#include<stdlib.h>

#define infoNIL 0
#define itemMIN -1
#define MAX_N 100010

typedef int itemType;
typedef int infoType;

int result;
int queue[MAX_N], front, rear;   //   inorder 순으로 순회한 결과

class BST {
private:
	struct node {
		itemType key; infoType info;
		struct node *l, *r;
		node(itemType k, infoType i, struct node *l_node, struct node *r_node)  // node 생성시 초기값 부여 가능
		{
			key = k; info = i; l = l_node; r = r_node;
		};
	};
	struct node *head, *z; // z : List의 끝을 대표하는 node pointer – NULL에 해당
public:
	BST(int max) {   //   생성자
		z = new node(0, infoNIL, 0, 0);
		head = new node(itemMIN, infoNIL, z, z);
	}
	~BST() {   //   소멸자
	}
	infoType  BSTsearch(itemType v);
	void BSTinsert(itemType v, infoType info);
	void BSTdelete(itemType v);

	void InorderRecursive(node* p) {   //   재귀
		if (p->l != z) {   //   왼쪽
			InorderRecursive(p->l);
		}
		queue[rear] = p->key; 
		rear++;
		if (p->r != z) {   //   오른쪽
			InorderRecursive(p->r);
		}
	}

	void Inorder() {
		InorderRecursive(head->r);
	}
};

BST T1(MAX_N);
BST T3(MAX_N);

infoType BST::BSTsearch(itemType v) {   //   탐색
	struct node *x = head->r;
	z->key = v;
	while (v != x->key) {
		result++;
		x = (v < x->key) ? x->l : x->r;
	}
	return x->info;
}

void BST::BSTinsert(itemType v, infoType info) {   //   삽입
	struct node *p, *x;
	p = head; x = head->r;
	while (x != z) { p = x; x = (v < x->key) ? x->l : x->r; }
	x = new node(v, info, z, z);
	if (v < p->key) p->l = x; else p->r = x;
}

void BST::BSTdelete(itemType v) {   //   삭제
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
int data[MAX_N];
bool check[MAX_N];



void make_data() {   //   데이터 생성
	int i, j;
	for (i = 0; i < num; i++) {
		while (true) {
			j = rand() % num;
			if (!check[j]) {
				check[j] = true;
				break;
			}
		}
		data[i] = j + 1;
	}
}


int main() {
	srand(time(NULL));
	std::cin >> num;
	make_data();

	for (int i = 0; i < num; i++) {//트리생성
		T1.BSTinsert((itemType)data[i], (infoType)i);
	}
	T1.Inorder();//중위순회 및 재배치
	for (int i = 0; i < num; i++) {   //   결과 삽입
		T3.BSTinsert((itemType)queue[i], (infoType)i);
	}
	for (int i = 0; i < num; i++) {   //   탐색
		T3.BSTsearch((itemType)data[i]);
	}

	std::cout << (double)result / num << std::endl;
	return 0;
}