#include <iostream>
using namespace std;

typedef struct treeNode *itemType;	// treeNode�� ����Ű�� ����ü ������ ������

struct treeNode {
	char info;			// node�� ���� ����
	struct treeNode *l, *r;	// treeNode�� ���� ���ʳ��� ������ ���
};
struct treeNode *x, *z;	// ���� �����Ǿ� ����, ������ ������ ������

class Stack {
public:

	Stack(int max = 100) {
		stack = new itemType[max];	// ũ�Ⱑ 50�� treeNode�� �迭�� ������ stack�� ����Ŵ
		p = 0;	// ������ �����ּ� 0���� �ʱ�ȭ
	}
	// �Ҹ���
	~Stack() {
		delete stack;
	}

	inline void push(itemType v) {
		stack[p++] = v;	// stack�迭�� �������� �ش� �Ű������� ����
	}
	// stack[]���� ������ ������ ���� ��ȯ�ϰ� �迭�� �ּҸ� 1���� ��Ŵ
	inline itemType pop() {
		return stack[--p];// �迭�� ������ �ּҰ��� ��ȯ
	}

	inline int empty() {
		return !p;
	}

private:
	itemType * stack;	// treeNode *stack;�� ����.
	int p;			// �迭�� ��ġ
};

// �ش� treeNode�� info���� ����ϴ� �Լ�
void visit(struct treeNode *t) {
	cout << t->info << " ";
}

// ��͸� �̿��� ������ȸ �Լ�
void traverse(struct treeNode *t) {
	if (t != z) {	// ������ ������ ���
		traverse(t->l);	// ���� ������ Ž��
		visit(t);	// �ش� �������
		traverse(t->r);	// ������ Ž��
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
	traverse(stack.pop());	// ����Ž���� ����
	cout << endl;	// ������ enter���
	return 0;
}
