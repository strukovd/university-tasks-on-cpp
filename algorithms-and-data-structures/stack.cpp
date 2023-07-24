#include <iostream>
using namespace std;

struct Stack
{
	int val;
	Stack *next;
};

void Push(Stack *&Top, int &size)
{
	Stack *pv = new Stack;
	cout<<"Значение: ";
	cin >> pv->val;
	pv->next = Top;
	Top = pv;
	size++;
	cout<<endl;
}

void Pop(Stack *&Top, int &size)
{
	if (Top) {
		Stack *pv = Top;
		Top = Top->next;
		delete pv;
		size--;
	}
	else cout<<"Стек пуст!"<<endl;
}

void Show(Stack *&Top)
{
	if (Top) {
		Stack *pv = Top;
		for(int i=1; pv; i++, pv = pv->next)
			cout<<i<<". "<<pv->val<<endl;
	}
	else cout<<"В стеке нет ни одного элемента!\n";
	cout<<endl;
}

void Max(Stack *&Top)
{
	if (Top) {
		Stack *pv = Top;
		int Max = pv->val;

		while(pv) {
			if (Max < pv->val)
				Max = pv->val;
			pv = pv->next;
		}

		cout<<"Максимальный элемент в стеке: "<<Max<<"\n\n";
	}
	else cout<<"В стеке нет ни одного элемента!\n\n";
}

void Search(Stack *&Top)
{
	if (Top) {
		Stack *pv = Top;
		int find, c=0;
		cout<<"Введите искомое значение: ", cin>>find;

		for(int i=1; pv; i++, pv = pv->next)
			if (find==pv->val)
				cout<<i<<". "<<pv->val<<endl, c++;

		if (c)
			cout<<"Найдено "<<c<<" элементов.\n\n";
		else
			cout<<"Ничего не найдено!\n\n";
	}
	else cout<<"В стеке нет ни одного элемента!\n";
}

void FindPos(Stack *&Top, int &size)
{
	if (Top) {
		Stack *pv = Top;
		int pos;
		cout<<"Введите номер искомого элемента: ", cin >> pos;
		if (pos > size || pos < 1) cout<<"Такого элемента не существует!\n\n";
		else {
			for(int i=1; i<pos; i++, pv = pv->next);
			cout<<"Значение элемента: "<<pv->val<<endl;
		}
	}
	else cout<<"В стеке нет ни одного элемента!\n\n";
}

int main()
{
	setlocale(0,"");
	Stack *Top = NULL;
	int act, size = 0;

	do {
		cout<<"Выберите действие:\n0. Выход\n1. Добавить элемент\n2. Удалить элемент\n3. Отобразить список\n4. Поиск элемента\n5. Найти максимальный элемент\n6. Найти по № позиции\n7. Кол-во эл. в стеке\n\n";
		cin>>act;
		switch(act) {
			case 1:
				Push(Top, size); break;
			case 2:
				Pop(Top, size); break;
			case 3:
				Show(Top); break;
			case 4:
				Search(Top); break;
			case 5:
				Max(Top); break;
			case 6:
				FindPos(Top, size);
			case 7:
				cout << size << endl;
		}
	} while(act);

	while(Top)
		Pop(Top, size);

	system("pause");
	return 0;
}
