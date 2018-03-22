#include <iostream>
using namespace std;

typedef struct treeNode *itemType;	// treeNode를 가리키는 구조체 포인터 재정의

struct treeNode {
	char info;			// node에 들어가는 문자
	struct treeNode *l, *r;	// treeNode의 각각 왼쪽노드와 오른쪽 노드
};
struct treeNode *x, *z;	// 새로 생성되어 삽입, 삭제를 수행할 포인터

class Stack {
public:

	Stack(int max = 100) {
		stack = new itemType[max];	// 크기가 50인 treeNode형 배열을 포인터 stack이 가리킴
		p = 0;	// 원소의 시작주소 0으로 초기화
	}
	// 소멸자
	~Stack() {
		delete stack;
	}

	inline void push(itemType v) {
		stack[p++] = v;	// stack배열의 마지막에 해당 매개변수값 저장
	}
	// stack[]에서 마지막 원소의 값을 반환하고 배열의 주소를 1감소 시킴
	inline itemType pop() {
		return stack[--p];// 배열속 원소의 주소값을 반환
	}

	inline int empty() {
		return !p;
	}

private:
	itemType * stack;	// treeNode *stack;과 같다.
	int p;			// 배열의 위치
};

// 해당 treeNode의 info값을 출력하는 함수
void visit(struct treeNode *t) {
	cout << t->info << " ";
}

// 재귀를 이용한 중위순회 함수
void traverse(struct treeNode *t) {
	if (t != z) {	// 마지막 노드까지 재귀
		traverse(t->l);	// 왼쪽 끝부터 탐색
		visit(t);	// 해당 원소출력
		traverse(t->r);	// 오름쪽 탐색
	}
}


int main() {
	char c;		// 문자를 입력받을 변수
	Stack stack(50);	// class객체 -> 크기가 50인 배열stack을 생성

						// 마지막 노드임을 알아낼 더미노드
	z = new treeNode;
	z->l = z;
	z->r = z;

	// 입력이 끝날때 까지 반복
	while ((c = cin.get()) != '\n') {
		// ' '일 경우 다음 문자를 입력받음
		while (c == ' ')
			cin.get(c);

		// 입력받은 문자를 저장하는 노드생성, 각 노드의 끝을 더미노드에 연결
		x = new treeNode;
		x->info = c;
		x->l = z;
		x->r = z;

		// 입력받은 문자가 연산식인 경우
		if (c == '+' || c == '*' || c == '-') {
			x->r = stack.pop();	// stack[]에서 꺼내어 새 노드의 오른쪽 포인터로 연결
			x->l = stack.pop();	// stack[]에서 꺼내어 새 노드의 왼쪽 포인터로 연결
		}
		stack.push(x);	// 새 노드를 stack에 삽입
	}
	traverse(stack.pop());	// 중위탐색을 수행
	cout << endl;	// 마지막 enter출력
	return 0;
}
