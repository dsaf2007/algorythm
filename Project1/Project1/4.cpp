#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <algorithm>
using namespace std;


class Set
{
private:
	
public:
	int *set; int setSize;
	Set(int size)
	{
		setSize = size;
		set = new int[size];
		for (int i = 0; i < size; i++)
		{
			set[i] = NULL;
		}
	}
	~Set()
	{
		//delete [] set;
	}
	int check(int element)
	{
		for (int i = 0; i < setSize; i++)
		{
			if (set[i] == element)
				return 1;
		}
		
	}

	void print()
	{
		for (int i = 0; i < setSize; i++)
		{
			if (set[i] != NULL)
			{
				cout << set[i] << " ";
			}
		}

	}
};
Set temp(100);
int intersection(Set set1, Set set2)
{
	int count = 0;

	int tempSize = max(set1.setSize, set2.setSize);
	
	if (tempSize == set1.setSize)
	{
		for (int i = 0; i < set2.setSize; i++)
		{
			if (set1.check(set2.set[i]) == 1)
			{
				temp.set[count++] = set2.set[i];
				
			}
		}
	}
	else
	{
		for (int i = 0; i < set2.setSize; i++)
		{
			if (set2.check(set1.set[i]) == 1)
			{
				temp.set[count++] = set1.set[i];
			}
		}
	}
	//Set inter(count);
	//for (int i = 0; i < count; i++)
	//{
	//	inter.set[i] = temp.set[i];
	//}
	return count;
}
Set temp2(100);
void Union(int unionsize, Set interSet,Set set1,Set set2)
{
	//cout << unionsize << endl;
	Set unionSet(unionsize);
	int i = 0,j=0,tempSize=0;
	while(i<set1.setSize)
	{
			if (interSet.check(set1.set[i]) != 1)
			{
				temp2.set[tempSize] = set1.set[i];
				tempSize ++;
			}
			i++;
	}
	while (j < set2.setSize)
	{
		if (interSet.check(set2.set[j]) != 1)
		{
			temp2.set[tempSize] = set2.set[j];
			tempSize++;
		}
		j++;
	}
	for (int k = 0; k <= interSet.setSize; k++)
	{
		temp2.set[tempSize]= interSet.set[k];
		tempSize++;
	}

	for (int i = 0; i < unionsize; i++)
	{
			unionSet.set[i] = temp2.set[i];
	}
	sort(unionSet.set, unionSet.set + unionsize);
	unionSet.print();
	cout << endl;

}
void main()
{

	srand(time(NULL));
	int a = 0; int b = 0;
	
	cin >> a >> b;
	Set set1(a), set2(b);
	
	
	for (int i = 0; i < set1.setSize; i++)//initialize set1
	{
		
		unsigned int element = (rand() % 60)+1;
		if (set1.check(element) != 1)
		{
			set1.set[i] = element;
			
		}
		else
			i--;
		sort(set1.set, set1.set + i+1);
	}
	for (int i = 0; i < set2.setSize; i++)//initialize set2
	{
		unsigned int element = (rand() % 60) + 1;
		if (set2.check(element) != 1)
		{
			set2.set[i] = element;
		
		}
		else
			i--;
		sort(set2.set, set2.set + i+1);
	}

	int interSize=intersection(set1, set2);
	Set inter(interSize);
	for (int i = 0; i < interSize; i++)
	{
		inter.set[i] = temp.set[i];
	}
	cout << "집합A - " ; set1.print(); cout << endl;
	cout << "집합B - "; set2.print(); cout << endl;
	cout << "합집합 - ";
	Union(set1.setSize + set2.setSize - inter.setSize,inter, set1, set2);
	cout << "교집합 - "; inter.print(); cout << endl;
	
}