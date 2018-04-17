#include<stdio.h>
#include<iostream>
#include<time.h>
#include<stdlib.h>

#define infoNIL 0
#define itemMIN -1
#define MAX_N 10010

typedef int itemType;
typedef int infoType;

int result;

void make();

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
	BST(int max) {
		z = new node(0, infoNIL, 0, 0);
		head = new node(itemMIN, infoNIL, z, z);
	}
	~BST() {
	}
	infoType  BSTsearch(itemType v);
	void BSTinsert(itemType v, infoType info);
	void BSTdelete(itemType v);
};

BST tree(MAX_N);

infoType BST::BSTsearch(itemType v) {   //   탐색
	struct node *x = head->r;
	z->key = v;  // 아래 반복문을 간결히 만들기 위함
	while (v != x->key) {
		//result++;
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

void BST::BSTdelete(itemType v) {
	struct node *x = head->r, *p, *t, *c;
	p = head;
	//result++;
	while (x->key != v && x != z) {   //   찾는 과정
		p = x;
		result++;
		x = (v < x->key) ? x->l : x->r;
		//result++;
	}
	if (x == z) return;   //   찾지 못한 경우
	else t = x;
	if (t->r == z) x = t->l;   //   오른쪽 자식이 없을 경우
	else if (t->r->l == z) {   //   오른쪽 자식의 왼쪽 자식이 없을 경우
		x = t->r; x->l = t->l;
	}
	else {   //   그 외의 경우
		c = x->r; while (c->l->l != z) c = c->l;
		x = c->l; c->l = x->r;
		x->l = t->l; x->r = t->r;
	}
	free(t);   //   메모리 해제
			   //result++;
	if (v<p->key) p->l = x; else p->r = x;
}

int num;
int data[MAX_N];
bool check[MAX_N];

int main() {
	srand(time(NULL));
	std::cin >> num;
	make();


	for (int i = 0; i < num; i++) {
		tree.BSTinsert((itemType)data[i], (infoType)i);
	}
	for (int i = 0; i < num / 10; i++) {   //   10개마다 데이터 한개 삭제
		tree.BSTdelete((itemType)data[i * 10 + rand() % 10]);
	}

	std::cout.setf(_IOSfixed);//결과 소수점고정
	std::cout.precision(2);
	std::cout << (double)result * 10.0 / (double)num << std::endl;


	return 0;
}

void make() {   //   데이터 생성
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



