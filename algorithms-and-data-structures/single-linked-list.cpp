#include <iostream>
using namespace std;

struct list
{
	int val;
	list *next;
};

bool empty(list *&head)
{
	if (!head) {
		cout<<"Список пуст!\n";
		return true;
	}
	else
		return false;
}

void ToBeg(list *&head, list *&pv)
{
	pv->next = head;
	head = pv;
}

void ToEnd(list *&head, list *&pv)
{
	pv->next = NULL;
	list *end = head;
	while(end->next)
		end = end->next;
	end->next = pv;
}

void Arbitrarily(list *&head, list *&pv, int &size)
{
	int key;
	cout << "Номер элемента: " << endl;
	cin >> key;

	if(key > size){
		cout << key << " вне диапазона списка! Элемент добавлен в конец!" << endl;
		ToEnd(head, pv);
	}
	else if(key < 2) {
		cout << key << " вне диапазона списка! Элемент добавлен в начало!" << endl;
		ToBeg(head, pv);
	}
	else {
		list *pred = head;
		for(int i=2; i<key; i++)
			pred = pred->next;
		pv->next = pred->next;
		pred->next = pv;
	}
}

void Add(list *&head, int &size)
{
	list *pv = new list;
	cout << "Введите занчение: "; cin >> pv->val;

	if (head==NULL) { //Если первый элемент
		pv->next = NULL;
		head = pv;
		cout << "added firstst element!" << endl;
	}
	else {
		cout << "\n1. To beg\n2. To end\n*. Произвольно\n";
		int act; cin >> act;
		switch (act)
		{
			case 1:
				ToBeg(head, pv);
				break;
			case 2:
				ToEnd(head, pv);
				break;
			default:
				Arbitrarily(head, pv, size);
		}
	}
	size++;
}

void Del(list *&head, int &size)
{
	if(empty(head)) return;

	int key;
	cout << "Номер удаляемого элемента: ";

	do{
		cin >> key;
		if(key < 1 || key > size)
			cout << "Такого элемента не существует!" << endl;
		else
			break;
	} while(true);

	if(key==1) {
		list *pv = head;
		head = head->next;
		delete pv;
	}
	else {
		list *pv[2];
		pv[0] = head;

		for(int i=2; i<key; i++)
			pv[0] = pv[0]->next;

		pv[1] = pv[0]->next;
		pv[0]->next = pv[0]->next->next;
		delete pv[1];
	}
	size--;
}

void Show(list *head)
{
	if(empty(head))
		return;

	for(int i=1; head; i++) {
		cout << i << ". " << head->val << endl;
		head = head->next;
	}
}

void DelAll(list *&head, int &size)
{
	if(empty(head))
		return;
	list *pv;
	while(head) {
		pv = head;
		head = head->next;
		delete pv;
	}
	size = 0;
}

void MinMax(list *head)
{
	if (empty(head))
		return;

	int min = head->val, max = min;

	while(head) {
		if (head->val > max) max = head->val;
		else if (head->val < min) min = head->val;
		head = head->next;
	}
	cout<<"Min: "<<min<<endl;
	cout<<"Max: "<<max<<endl;
}

void SK(list *&head, int &size)
{
	cout<<"Номер элемента: ";
	int key, i=1;
	do {
		cin>>key;
		if(key>size || key<1)
			cout<<"Такого элемента нет!"<<endl;
		else
			break;
	} while(true);

	list *pv = head;
	for(;i<key; i++, pv = pv->next);
	cout<<i<<". "<<pv->val<<endl;
}

void SV(list *&head)
{
	int val, found(0);
	list *pv = head;
	cout<<"value: ";
	cin>>val;

	for(int i=1; pv; i++) {
		if (pv->val == val)
		{
			cout<<i<<". "<<pv->val<<endl;
			found++;
		}
		pv = pv->next;
	}

	if (!found)
		cout<<"Ничего не найдено!"<<endl;
}

void Search(list *&head, int &size)
{
	if(empty(head))
		return;

	cout<<"1. По ключу\n*. По значению\n"<<endl;
	int act;
	cin>>act;
	if(act==1)
		SK(head, size);
	else
		SV(head);
}

void Swap(int &a, int &b)
{
	int tmp;
	tmp = a;
	a = b;
	b = tmp;
}

void Sort(list *&head)
{
	if (empty(head))
		return;

	list *pv[2];
	bool perfect(false);

	while(!perfect) {
		pv[0] = head, pv[1] = pv[0]->next;
		perfect = true;

		while(pv[1])
		{
			if (pv[0]->val > pv[1]->val) {
				Swap(pv[0]->val, pv[1]->val);
				perfect = false;
			}

			pv[0] = pv[1];
			pv[1] = pv[1]->next;
		}
	}
	cout<<"Список отсортирован!"<<endl;
}

void Glue(list *&head, int &size)
{
	if(empty(head))
		return;

	int act ,size2(0);
	list *head2(0), *end2(0), *end(head);
	while(end->next)
		end = end->next;

	cout << "Создайте второй лист.\n0. Готово\n1. Добавить\n2. Отобразить\n";
	do {
		cin>>act;
		switch(act)
		{
			case 0: break;
			case 1: Add(head2, size2); break;
			case 2: Show(head2); break;
			default: cout<<"Неверный ввод!\n";
		}
	} while(act);

	end2 = head2;
	while(end2->next)
		end2 = end2->next;
	cout<<"Способ конкатенации:\n1. Первая ко второй\n2. Вторая к певрой\n";

	do {
		cin>>act;
	} while(act!=1 && act!=2);

	switch(act) {
		case 1: end2->next = head; head = head2; break;
		case 2: end->next = head2; break;
	}

	size+=size2;
	cout<<"Готово!\n";
}

int main()
{
	setlocale(0,"");
	list *head = NULL;

	int act, size(0);
	do {
		cout << "1. Добавить 2. Удалить 3. Показать 4. МинМакс 5. Поиск\n6. Сортировка 7. Конкатенация 8. Удлаить все 9. Кол-во\n" << "Выберите действие: ";
		cin >> act;

		switch(act)
		{
			case 1: Add(head, size); break;
			case 2: Del(head, size); break;
			case 3: Show(head); break;
			case 4: MinMax(head); break;
			case 5: Search(head, size); break;
			case 6: Sort(head); break;
			case 7: Glue(head, size); break;
			case 8: DelAll(head, size); break;
			case 9: cout<<"Кол-во эл.: "<<size<<endl;
		}
	} while(act);

	DelAll(head, size);
	return 0;
}
