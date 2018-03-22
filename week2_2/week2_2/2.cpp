#include <iostream>
using namespace std;
typedef struct treeNode *itemType;

struct treeNode {
	char info;			// node에 들어가는 문자를 저장할 변수
	struct treeNode *l, *r;	// treeNode의 각각 왼쪽노드와 오른쪽 노드를 가리키는 포인터
};
struct treeNode *x, *z;	// 새로 생성되어 삽입, 삭제를 수행할 포인터

						// 트리 노드를 완성하기 위한 class
class Stack {
public:
	// 디폴트 매개변수를 사용한 생성자
	Stack(int max = 100) {
		stack = new itemType[max];	// 크기가 50인 treeNode형 배열을 포인터 stack이 가리킴
		p = 0;	// 원소의 시작주소 0으로 초기화
	}
	// 소멸자
	~Stack() {
		delete stack;	// stack포인터가 가리키는 배열과 주소의 메모리를 해제
	}
	// stack[]에 해당 매개변수값 저장
	inline void push(itemType v) {
		stack[p++] = v;	// stack배열의 마지막에 해당 매개변수값 저장
	}
	// stack[]에서 마지막 원소의 값을 반환하고 배열의 주소를 1감소 시킴
	inline itemType pop() {
		return stack[--p];
	}
	// 배열속 원소의 주소값을 반환
	inline int empty() {
		return !p;
	}

private:
	itemType * stack;	// treeNode *stack;과 같다.
	int p;			// 배열의 위치를 가리키는 정수형 변수
};

// stack의 트리를 Queue로 레벨순회가 가능하도록 만들기 위한 class
class Queue {
public:
	// 생성자
	Queue(int max = 100) {
		queue = new itemType[max];	// Queue배열 생성
		size = max;	// 크기값 저장
					// 초기 원소의 위치는 모두 0
		head = 0;
		tail = head;
	}
	// 소멸자 queue[]을 제거
	~Queue() {
		delete queue;
	}

	// 외부에서 정의한 멤버 함수
	void put(itemType v);	// queue[]에 삽입하기 위한 함수
	itemType get();		// queue[]에서 해당 노드를 제거하기 위한 함수
	int empty();	// queue[]이 비었는지 확인하기 위한 함수

private:
	itemType * queue;	// queue배열을 동적할당 하기 위한 포인터변수
	int head, tail;		// queue[]내의 원소들의 처음과 끝을 파악하기 위한 변수
	int size;	// 원형queue[]의 크기
};

// queue[]에 삽입하기 위한 함수
void Queue::put(itemType v) {
	queue[tail++] = v;	// 마지막 원소 자리에 해당 노드 추가
	if (tail > size)		// 큐에 들어왔던 원소의 갯수가 size보다 많아진 경우 원형큐로 삽입
		tail = 0;
};

// queue[]에서 해당 노드를 제거하기 위한 함수
itemType Queue::get() {
	itemType t = queue[head++];	// 해당자리의 노드를 t에 저장, 첫 자리를 가리키는 head를 다음칸으로 넘김
	if (head > size)		// 원형큐에 한바퀴이상 돈 경우 처음 시작을 다시 0으로 설정, 원형으로 만듦
		head = 0;
	return t;	// 삭제한 노드를 반환
};

// queue[]이 비었는지 확인하기 위한 함수
int Queue::empty() {
	return head == tail;	// 처음과 끝이 같다면 큐가 모두 빈경우
};

// 방문한 노드의 info를 출력
void visit(struct treeNode *t) {
	cout << t->info << " ";
}

// 레벨순회를 수행하는 함수
void traverse(struct treeNode *t) {
	Queue queue(50);	// 새로운 원형큐생성
	queue.put(t);	// 새로운 원형큐에 삽입, 순회하며 출력
	while (!queue.empty()) {
		t = queue.get();
		visit(t);
		if (t->l != z)
			queue.put(t->l);
		if (t->r != z)
			queue.put(t->r);
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
	traverse(stack.pop());	// 해당 tree를 queue에 삽입하여 레벨탐색을 수행
	cout << endl;	// 마지막 enter출력
	return 0;
}
