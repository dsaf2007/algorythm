#include <iostream>
using namespace std;
typedef struct treeNode *itemType;

struct treeNode {
	char info;			// node�� ���� ���ڸ� ������ ����
	struct treeNode *l, *r;	// treeNode�� ���� ���ʳ��� ������ ��带 ����Ű�� ������
};
struct treeNode *x, *z;	// ���� �����Ǿ� ����, ������ ������ ������

						// Ʈ�� ��带 �ϼ��ϱ� ���� class
class Stack {
public:
	// ����Ʈ �Ű������� ����� ������
	Stack(int max = 100) {
		stack = new itemType[max];	// ũ�Ⱑ 50�� treeNode�� �迭�� ������ stack�� ����Ŵ
		p = 0;	// ������ �����ּ� 0���� �ʱ�ȭ
	}
	// �Ҹ���
	~Stack() {
		delete stack;	// stack�����Ͱ� ����Ű�� �迭�� �ּ��� �޸𸮸� ����
	}
	// stack[]�� �ش� �Ű������� ����
	inline void push(itemType v) {
		stack[p++] = v;	// stack�迭�� �������� �ش� �Ű������� ����
	}
	// stack[]���� ������ ������ ���� ��ȯ�ϰ� �迭�� �ּҸ� 1���� ��Ŵ
	inline itemType pop() {
		return stack[--p];
	}
	// �迭�� ������ �ּҰ��� ��ȯ
	inline int empty() {
		return !p;
	}

private:
	itemType * stack;	// treeNode *stack;�� ����.
	int p;			// �迭�� ��ġ�� ����Ű�� ������ ����
};

// stack�� Ʈ���� Queue�� ������ȸ�� �����ϵ��� ����� ���� class
class Queue {
public:
	// ������
	Queue(int max = 100) {
		queue = new itemType[max];	// Queue�迭 ����
		size = max;	// ũ�Ⱚ ����
					// �ʱ� ������ ��ġ�� ��� 0
		head = 0;
		tail = head;
	}
	// �Ҹ��� queue[]�� ����
	~Queue() {
		delete queue;
	}

	// �ܺο��� ������ ��� �Լ�
	void put(itemType v);	// queue[]�� �����ϱ� ���� �Լ�
	itemType get();		// queue[]���� �ش� ��带 �����ϱ� ���� �Լ�
	int empty();	// queue[]�� ������� Ȯ���ϱ� ���� �Լ�

private:
	itemType * queue;	// queue�迭�� �����Ҵ� �ϱ� ���� �����ͺ���
	int head, tail;		// queue[]���� ���ҵ��� ó���� ���� �ľ��ϱ� ���� ����
	int size;	// ����queue[]�� ũ��
};

// queue[]�� �����ϱ� ���� �Լ�
void Queue::put(itemType v) {
	queue[tail++] = v;	// ������ ���� �ڸ��� �ش� ��� �߰�
	if (tail > size)		// ť�� ���Դ� ������ ������ size���� ������ ��� ����ť�� ����
		tail = 0;
};

// queue[]���� �ش� ��带 �����ϱ� ���� �Լ�
itemType Queue::get() {
	itemType t = queue[head++];	// �ش��ڸ��� ��带 t�� ����, ù �ڸ��� ����Ű�� head�� ����ĭ���� �ѱ�
	if (head > size)		// ����ť�� �ѹ����̻� �� ��� ó�� ������ �ٽ� 0���� ����, �������� ����
		head = 0;
	return t;	// ������ ��带 ��ȯ
};

// queue[]�� ������� Ȯ���ϱ� ���� �Լ�
int Queue::empty() {
	return head == tail;	// ó���� ���� ���ٸ� ť�� ��� ����
};

// �湮�� ����� info�� ���
void visit(struct treeNode *t) {
	cout << t->info << " ";
}

// ������ȸ�� �����ϴ� �Լ�
void traverse(struct treeNode *t) {
	Queue queue(50);	// ���ο� ����ť����
	queue.put(t);	// ���ο� ����ť�� ����, ��ȸ�ϸ� ���
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
	char c;		// ���ڸ� �Է¹��� ����
	Stack stack(50);	// class��ü -> ũ�Ⱑ 50�� �迭stack�� ����

						// ������ ������� �˾Ƴ� ���̳��
	z = new treeNode;
	z->l = z;
	z->r = z;

	// �Է��� ������ ���� �ݺ�
	while ((c = cin.get()) != '\n') {
		// ' '�� ��� ���� ���ڸ� �Է¹���
		while (c == ' ')
			cin.get(c);

		// �Է¹��� ���ڸ� �����ϴ� ������, �� ����� ���� ���̳�忡 ����
		x = new treeNode;
		x->info = c;
		x->l = z;
		x->r = z;

		// �Է¹��� ���ڰ� ������� ���
		if (c == '+' || c == '*' || c == '-') {
			x->r = stack.pop();	// stack[]���� ������ �� ����� ������ �����ͷ� ����
			x->l = stack.pop();	// stack[]���� ������ �� ����� ���� �����ͷ� ����
		}
		stack.push(x);	// �� ��带 stack�� ����
	}
	traverse(stack.pop());	// �ش� tree�� queue�� �����Ͽ� ����Ž���� ����
	cout << endl;	// ������ enter���
	return 0;
}
