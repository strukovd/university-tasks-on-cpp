#include <iostream>
using namespace std;

struct List
{
	int *mas, size, n;
};

void Init(List &l)
{
	if (l.mas) delete [] l.mas;

	do {
		cout<<"Введите кол-во элементов списка: ";
		cin>>l.size;
	} while(l.size<0);

	l.mas = new int [l.size];
	l.n = 0;
	for(int i=0; i<l.size; i++)
		l.mas[i] = NULL;
}

void Add(List &l)
{
	if(l.n == l.size) cout<<"Список переполнен!"<<endl;
	else {
		int val;
		cout<<"Введите значение элемента: ";
		cin>>val;
		for(int i=l.n; i; i--) l.mas[i] = l.mas[i-1];
		l.mas[0] = val;
		l.n++;
	}
}

void Del(List &l)
{
	if (l.n) {
		for(int i = 0; i < (l.n-1); i++) l.mas[i] = l.mas[i+1];
			l.n--;
		cout<<"Первый элемент удален!"<<endl;
	}
	else cout<<"Список пуст!"<<endl;
}

void Show(List &l)
{
	if (l.n)
		for(int i=0; i<l.n; i++)
			cout<<"["<<i<<"] "<<l.mas[i]<<endl;
	else cout<<"Список пуст!"<<endl;
}

void Search(List &l)
{
	if (l.n)
	{
		int f,c=0;
		cout<<"Искомое значение: ";
		cin>>f;
		for(int i=0; i<l.n; i++)
		if (f == l.mas[i]) {
			cout<<"["<<i<<"] "<<l.mas[i]<<endl;
			c++;
		}
		(c)?cout<<"Найдено результатов: "<<c<<endl:cout<<"Ничего не найдено!"<<endl;
	}
	else cout<<"Список пуст!"<<endl;
}

void Max(List &l)
{
	if (l.n)
	{
		int max = l.mas[0];
		for(int i=0; i<l.n; i++) {
			if (max < l.mas[i]) max = l.mas[i];
		}
		cout<<"Максимальный элемент: "<<max<<endl;
	}
	else cout<<"Список пуст!"<<endl;
}

void ShowPos(List &l)
{
	if (l.n) {
		int pos;
		cout<<"Позиция элемента: ";
		do{
			cin>>pos;
		} while(pos<0||pos>=l.n);
		cout<<"["<<pos<<"] "<<l.mas[pos]<<endl;
	}
	else cout<<"Список пуст!"<<endl;
}

void menu(List l)
{
	int act;
	do{
		cout<<"0. Exit\n1. Add\n2. Delete\n3. Show\n4. Search\n5. Find Max\n6. Find of pos\n7. izm razm mas\n\nChange action: ";
		cin>>act;
		switch (act) {
			case 1: Add(l); break;
			case 2: Del(l); break;
			case 3: Show(l); break;
			case 4: Search(l); break;
			case 5: Max(l); break;
			case 6: ShowPos(l); break;
			case 7: Init(l); break;
		}
		cout<<endl;
	} while(act);
}

int main()
{
	setlocale(0,"");
	List l = {NULL, NULL, NULL};
	Init(l);
	menu(l);
	delete [] l.mas;
	return 0;
}
