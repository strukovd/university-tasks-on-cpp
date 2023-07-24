#include <iostream>
using namespace std;

struct Queue
{
	int val;
	Queue *next;
};

void Add(Queue *&beg, Queue *&end, int &c, bool toend)
{
	Queue *pv = new Queue;
	cout << "Значение: ";
	cin >> pv->val;
	pv->next = NULL;

	if (!toend)
		pv->next = beg, beg = pv;
	else if (beg)
		end->next = pv, end = pv;
	else
		beg = pv, end = pv;
	c++;
}

void Del(Queue *&beg, Queue *&end, int &c)
{
	if (beg) {
		Queue *pv = beg;
		beg = beg->next;
		if (beg == NULL)
			end = NULL;
		delete pv;
		c--;
	}
	else cout << "Очередь пуста!\n\n";
}

void Show(Queue *&beg)
{
	if(beg) {
		Queue *pv = beg;
		for(int i(0); pv; pv = pv->next)
			cout << ++i << ". " << pv->val << endl;
		cout << endl;
	}
	else cout << "Очередь пуста!\n\n";
}

void Glue(Queue *&beg, Queue *&end, int &c)
{
	if (beg == NULL) {
		cout << "Очередь пуста!\n\n";
		return;
	}

	int elem;
	Queue *beg2(NULL), *end2(NULL);
	cout << "Из скольки элементов будет состоять другая очередь?\n";
	do
		cin >> elem;
	while(elem < 1);
	cout << endl;

	for(int i(0); i<elem; i++)
		Add(beg2, end2, c, true);

	cout << "Результат: " << endl;
	Show(beg2);
	cout << "Относительно основной, куда будем клеить?" << endl << "1. К конец\n*. В начало" << endl;
	cin >> elem;

	if (elem == 1)
		end->next = beg2, end = end2;
	else
		end2->next = beg, beg = beg2;
	cout << "Готово!" << endl;
}

void Search(Queue *&beg, int &c)
{
	if (beg) {
		int method, find(0);
		Queue *pv = beg;
		cout << "1. Посик по ключу\n*. Поиск по значению\n";
		cin >> method;
		if (method==1) {
			cout << "Ключ ячейки: ";
			while(find<1 || find>c) cin >> find;
			for(int i=1; i<find; pv = pv->next, i++);
			cout << find << ". " << pv->val << endl;
		}
		else {
			cout << "Искомое значение: ";
			cin >> find;
			for(int i=1; pv; pv=pv->next, i++)
				if(pv->val == find)
					cout << i << ". " << find << endl;
		}
	}
	else cout << "Очередь пуста!\n\n";
}

void MinMax(Queue *&beg)
{
	if(beg) {
		int min(beg->val), max(min);
		Queue *pv = beg->next;
		for(; pv; pv = pv->next)
			if(max < pv->val)
				max = pv->val;
			else if(min > pv->val)
				min = pv->val;
		cout << "Минимальное значение: " << min << endl;
		cout << "Максимальное значение: " << max << endl;
	}
	else cout << "Очередь пуста!\n\n";
}

void DelQueue(Queue *&beg, Queue *&end, int &c)
{
	if(beg) {
		Queue *pv;
		while(beg)
			pv = beg, beg = beg->next, delete pv;
		end = NULL, c = 0;
		cout << "Очередь очищена!\n\n";
	}
	else cout << "Очередь пуста!\n\n";
}

int main()
{
	setlocale(0,"");
	Queue *beg(NULL), *end(NULL);
	int c=0, act;
	do {
		cout << "0. Выход\n1. Добавить\n2. Удалить\n3. Отобразить\n4. В начало\n5. Конкатенация\n6. Поиск\n7. MinMax\n8. Счетчик\n9. Очистить" << endl;
		cout << "Выберите действие: ", cin >> act, cout<<endl;

		switch (act)
		{
			case 1: Add(beg, end, c, true); break;
			case 2: Del(beg, end, c); break;
			case 3: Show(beg); break;
			case 4: Add(beg, end, c, false); break;
			case 5: Glue(beg, end, c); break;
			case 6: Search(beg, c); break;
			case 7: MinMax(beg); break;
			case 8: cout << "Кол-во элем. в очереди: " << c << endl; break;
			case 9: DelQueue(beg, end, c);
		}
	} while(act);

	DelQueue(beg, end, c);
	system("pause");
	return 0;
}