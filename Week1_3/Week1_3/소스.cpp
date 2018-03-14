#include <iostream>

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
		struct node *temp = head->next;
		itemType v = temp->key;
		head->next = temp->next;
		free(temp);
		return v;
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

}