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
	BST(int max) {   //   생성자
		z = new node(0, infoNIL, 0, 0);
		head = new node(itemMIN, infoNIL, z, z);
	}
	~BST() {   //   소멸자
	}
	infoType  BSTsearch(itemType v);
	void BSTinsert(itemType v, infoType info);
	void BSTdelete(itemType v);
};

BST tree(MAX_N);

infoType BST::BSTsearch(itemType v) {
	struct node *x = head->r;
	z->key = v;  // 아래 반복문을 간결히 만들기 위함
	while (v != x->key) {      //   찾으면 종료
		result++;
		x = (v < x->key) ? x->l : x->r;   //   v의 값에 따라 이동
	}
	return x->info;
}

void BST::BSTinsert(itemType v, infoType info) {   //   BST에 item을 삽입하는 메소드
	struct node *p, *x;
	p = head; x = head->r;
	while (x != z) { p = x; x = (v < x->key) ? x->l : x->r; }   //   null인 위치까지 이동
	x = new node(v, info, z, z);   //   노드 생성
	if (v < p->key) p->l = x; else p->r = x;      //   삽입
}

int num;
int data[MAX_N];
bool check[MAX_N];


int main() {
	srand(time(NULL));
	std::cin >> num;
	make();


	for (int i = 0; i < num; i++) { 
		tree.BSTinsert((itemType)data[i], (infoType)i);//삽입
	}
	for (int i = 0; i < num; i++) {   
		tree.BSTsearch((itemType)data[i]);//탐색
	}

	std::cout.precision(3);
	std::cout << (double)result / (double)num << std::endl;//결과
	return 0;
}

void make() {   //   데이터를 만드는 작업
	int i, j;
	for (i = 0; i < num; i++) {
		while (true) {
			j = rand() % num;   //   무작위
			if (!check[j]) {   //   중복 체크
				check[j] = true;
				break;
			}
		}
		data[i] = j + 1;
	}
}