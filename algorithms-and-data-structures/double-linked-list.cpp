#include <iostream>
#define $ cout<<
using namespace std;

struct list
{
	int val;
	list *next, *pred;
};

bool empty(list *&beg)
{
	if(!beg) {
		$"Список пуст!\n";
		return true;
	}
	else
		return false;
}

//Добавление
void ToBeg(list *&beg, list *&pv)
{
	pv->next = beg;
	beg->pred = pv;
	pv->pred = 0;
	beg = pv;
}

void ToEnd(list *&end, list *&pv)
{
	pv->pred = end;
	pv->next = 0;
	end->next = pv;
	end = pv;
}

void AddByIdx(list *&beg, list*&end, list*&pv, int&size, bool Before)
{
	int pos; list*p = beg;
	(Before)?$"Перед позицией № ":$"После позиции № ";
	do{
		cin>>pos;
		if(pos>size || pos<1)
			$"Такого элемента нет! Введите еще раз!\n";
		else
			break;
	} while(true);

	if(Before)
		pos--;
	else if(pos==size) {
		ToEnd(end, pv);
		return;
	}

	for(int i=1; i<pos; i++)
		p = p->next;

	if(p==beg)
		ToBeg(beg, pv);
	else {
		pv->pred = p;
		pv->next = p->next;
		p->next->pred = pv;
		p->next = pv;
	}
}

void AddByVal(list *&beg, list *&end, list*&pv, int&size, bool Before)
{
	int val; list*p = beg;
	$"Перед значением: ";
	cin>>val;

	for(int i=1; p; i++) {
		if(p->val==val)
			break;
		p = p->next;
	}

	if(!p) {
		$"Элемент с таким значением - не найден!\nНовый элемент удален!";
		delete pv;
		size--;
	}
	else if(p==beg)
		ToBeg(beg, pv);
	else if(p==end)
		ToEnd(end, pv);
	else {
		if(Before)
			p = p->pred;
		pv->pred = p;
		pv->next = p->next;
		p->next->pred = pv;
		p->next = pv;
	}
}

void Add(list *&beg, list *&end, int &size)
{
	list *pv = new list;
	int act;
	$"Значение: "; cin>>pv->val;
	if(!beg) {
		beg = pv;
		beg->next = 0;
		beg->pred = 0;
		end = beg;
		$"Добавлен первый элемент!\n";
	}
	else {
		$"1. В начало 2. В конец 3. Перед индексом\n4. После индекса 5. Перед значения 6. После значения\n";
		do {
			cin>>act;
			switch (act) {
				case 1: ToBeg(beg, pv); break;
				case 2: ToEnd(end, pv); break;
				case 3: AddByIdx(beg, end, pv, size, 1); break;
				case 4: AddByIdx(beg, end, pv, size, 0); break;
				case 5: AddByVal(beg, end, pv, size, 1); break;
				case 6: AddByVal(beg, end, pv, size, 0); break;
				default: $"Неверный ввод, введите еще раз!\n";
			}
		} while(act<1 || act>6);
	}
	size++;
}

void DESTROY(list *&beg, list *&end, list *&pv) //УДАЛЕНИЕ
{
	if(beg==end) { //Если единственный
		delete beg;
		beg=0, end=0;
	}
	else if(beg==pv) { //Если первый
		beg = beg->next;
		beg->pred = 0;
		delete pv;
	}
	else if(end==pv) { //Если последний
		end = end->pred;
		end->next = 0;
		delete pv;
	}
	else {
		pv->pred->next = pv->next;
		pv->next->pred = pv->pred;
		delete pv;
	}
}

void DelEdge(list *&beg, list *&end, bool FromBeg)
{
	list *pv;
	if(FromBeg)
		pv = beg;
	else
		pv = end;
	DESTROY(beg, end, pv);
}

void DelIdx(list *&beg, list *&end, int &size, bool Before)
{
	list *p = beg;
	int index;
	if(beg==end) {
		$"Элемент единсвенный! 0. Отмена *. Удалить\n";
		cin>>index;
		if(index)
			DESTROY(beg, end, p);
		return;
	}

	$"Индекс: ";
	do {
		cin>>index;

		if( (Before)?(index>size || index<=1):(index>=size || index<1) )
			$"Неверный ввод!\n";
		else
			break;
	} while(true);

	for(int i=1; i<index; i++, p=p->next);
	if(Before)
		p=p->pred;
	else
		p=p->next;
	DESTROY(beg, end, p);
}

void DelVal(list *&beg, list *&end, int &size, bool Before)
{
	list*p=beg;
	int val;
	$"Занчение: ";
	cin>>val;

	for(int i=1; p; i++) {
		if(p->val==val)
			break;
		p=p->next;
	}

	if(!p) {
		$"Значение не найдено!\n";
		size++;
		return;
	}
	else if(Before)
		p=p->pred;
	else
		p=p->next;

	if(!p)
		$"Элемента не существует!\n";
	else
		DESTROY(beg, end, p);
}

void Del(list *&beg, list *&end, int &size)
{
	if(empty(beg))
		return;

	int act;
	$"1. Первый 2. Последний 3. Перед индексом\n4. После индекса 5. Перед значением 6. После значения\n";

	do {
		cin>>act;
		switch (act)
		{
			case 1: DelEdge(beg, end, 1); break;
			case 2: DelEdge(beg, end, 0); break;
			case 3: DelIdx(beg, end, size, 1); break;
			case 4: DelIdx(beg, end, size, 0); break;
			case 5: DelVal(beg, end, size, 1); break;
			case 6: DelVal(beg, end, size, 0); break;
			default: $"Неверный ввод, введите еще раз!\n";
		}
	} while(act<1 || act>6);
	size--;
}

void SrchByIdx(list *CBeg, int&size, bool Before)
{
	int index, find, found(0);
	$"Указанный индекс: ";

	do{
		cin>>index;
		if(index>size || index<1)
			$"Такого элемента нет! Введите еще раз!\n";
		else
			break;
	} while(true);

	$"Искомое значение: ";
	cin>>find;

	if(Before) // ПЕРЕД ИНДЕКСОМ
		for(int i=1; i<index; i++,CBeg=CBeg->next) {
			if(CBeg->val==find) {
				$ i<<". "<<CBeg->val<<endl;
				found++;
			}
		}
	else { // ПОСЛЕ ИНДЕКСА
		int i=1;
		for(;i<=index;i++, CBeg=CBeg->next);
		for(;i<=size;i++, CBeg=CBeg->next)
			if(CBeg->val==find) {
				$ i<<". "<<CBeg->val<<endl;
				found++;
			}
	}
	if(found)
		$"Найдено "<<found<<" элементов!\n";
	else
		$"Ничего не найдено!\n";
}

void SrchByVal(list*CBeg, bool Before)
{
	int val, find, found(0);
	$"Указанное значение: ";
	cin>>val;
	$"Искомое значение: ";
	cin>>find;

	if(Before) //ДО ЗНАЧЕНИЯ
		for(int i=1; CBeg && CBeg->val!=val; i++, CBeg=CBeg->next) {
			if(CBeg->val==find) {
				$ i<<". "<<CBeg->val<<endl;
				found++;
			}
		}
	else {
		int i=1;
		for(;CBeg && CBeg->val!=val;i++,CBeg=CBeg->next);

		if(CBeg) {
			CBeg=CBeg->next;
			i++;
		}

		for(;CBeg;i++, CBeg=CBeg->next)
			if(CBeg->val==val) {
				$ i<<". "<<CBeg->val<<endl;
				found++;
			}
	}

	if(found)
		$"Найдено "<<found<<" элементов!\n";
	else
		$"Ничего не найдено!\n";
}

void Search(list *&beg, list *&end, int&size)
{
	if(empty(beg))
		return;

	int act;
	$"1. До индекса 2. После индекса 3. До значения 4. После значения\n";

	do {
		cin>>act;
		switch (act)
		{
			case 1: SrchByIdx(beg, size, 1); break;
			case 2: SrchByIdx(beg, size, 0); break;
			case 3: SrchByVal(beg, 1); break;
			case 4: SrchByVal(beg, 0); break;
			default: $"Неверный ввод, введите еще раз!\n";
		}
	} while(act<1 || act>4);
}

void Swap(list*&beg, list*&end, list*&a, list*&b)
{
	list *tmp=a;
	if(b->next)b->next->pred=a;else end=a;
	if(a->pred)a->pred->next=b;else beg=b;
	//if(a->next)a->next->pred = a;
	//if(b->pred)b->pred->next = b;
	a->next = b->next;
	b->next = a;
	b->pred = a->pred;
	a->pred = b;
}

void Sort(list *&beg, list *&end)
{
	if(empty(beg))
		return;

	list*pv[2];
	bool perfect(false);

	while(true) {
		pv[0]=beg, pv[1]=beg->next;
		perfect=true;

		while(pv[1]) {
			if(pv[0]->val > pv[1]->val) {
				Swap(beg, end, pv[0], pv[1]);
				perfect = false;
			}

			pv[0] = pv[1];
			pv[1] = pv[1]->next;
		}

		if(perfect)
			break;
	}
}

void Show(list*&beg)
{
	if(empty(beg))
		return;

	list*pv=beg;

	for(int i=1; pv; i++, pv=pv->next)
		$ i<<". "<<pv->val<<endl;
}

void DelAll(list*&beg, list*&end, int&size)
{
	if(empty(beg))
		return;

	list*pv;
	while(beg) {
		pv=beg;
		beg=beg->next;
		delete pv;
	}

	beg=0, end=0, size=0;
	$"Список очищен!\n";
}

void ShowAdress(list*CBeg, int&size)
{
	if(empty(CBeg))
		return;

	int num;
	$"Номер: ";
	do{
		cin>>num;
		if(num>size || num<1)
			$"Такого элемента нет! Введите еще раз!\n";
		else
			break;
	} while(true);

	for(int i=1; i<num; i++)
		CBeg=CBeg->next;
	$"next: "<<CBeg->next<<"\npred: "<<CBeg->pred<<endl;
}

int main()
{
	setlocale(0,"");
	list *beg=0, *end=0;
	int act, size=0;

	do {
		$ "1. Добавить 2. Удалить 3. Поиск 4. Сортировка 5. Отобразить 6. Удалить все\nВыберите действие: ";
		cin>>act;
		switch (act)
		{
			case 0: break;
			case 1: Add(beg, end, size); break;
			case 2: Del(beg, end, size); break;
			case 3: Search(beg, end, size); break;
			case 4: Sort(beg, end); break;
			case 5: Show(beg); break;
			case 6: DelAll(beg, end, size); break;
			case 7: ShowAdress(beg, size); break;
			case 100: $"beg->pred: "<<beg->pred<<endl<<"end->next: "<<end->next<<endl; break;
			default: $"Неверный ввод, введите еще раз!\n";
		}
	} while(act);

	DelAll(beg, end, size);
	return 0;
}
