#include <iostream>
using namespace std;
typedef double itemType;

class Stack2
{
public:
	Stack2()
	{
		head = new node;
		head->next = NULL;
	}
	~Stack2()
	{

	}
	void push(itemType v)
	{
		struct node *temp = new node;
		temp->key = v;
		temp->next = head->next;
		head->next = temp;
	}
	itemType pop()
	{
		if (empty() != 1)
		{
			struct node *temp = head->next;
			itemType v = temp->key;
			head->next = temp->next;
			free(temp);
			return v;
		}
	}
	int empty()
	{
		if (head->next == NULL)
			return 1;
	}

private:
	struct node
	{
		itemType key; struct node *next;
	};
	struct node *head, *z;
};


void main()
{
	char c;
	Stack2 acc;
	itemType x;
	while ((c = cin.get()) != '\n')
	{
		x = 0;
		while (c == ' ')cin.get(c);
		if (c == '+') x = acc.pop() + acc.pop();
		if (c == '-')
		{
			itemType a, b;
			b = acc.pop();
			a = acc.pop();
			x = a - b;
		}
		if (c == '*')
		{
			x = acc.pop()*acc.pop();
		}
		if (c == '/')
		{
			itemType a, b;
			b = acc.pop();
			a = acc.pop();
			x = a / b;
		}
		while (c >= '0' && c <= '9')
		{
			x = 10 * x + (c - '0');  cin.get(c);
		}
		acc.push(x);

	}
	x = acc.pop();
	if ((int)(x * 10) % 10 == 0)
		cout << x << endl;
	else
	{
		cout << fixed;
		cout.precision(2);
		cout << x << endl;
	}
}