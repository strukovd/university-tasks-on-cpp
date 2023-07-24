#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;
struct OfficeSuite
{
    char Name[31], Manufacturer[31];
    double Quantity, cost;
};
OfficeSuite *FillingTable(char&, char*);
void Menu(OfficeSuite*, char&, char*);
void ShowTable(OfficeSuite*, char&, char*);
void BubbleSort(OfficeSuite*, char&, char*);
void StringSwap(char*, char*, const int&);
template <class Type> void Swap(Type&, Type&);
void Search(OfficeSuite*);
void EditTable(OfficeSuite*, char&, char*);
void EditNotes(char*, char&);
void SwNotes(char*, char&);
void Export(OfficeSuite*, char&, char*);
OfficeSuite *Import(char&, char*);
int CountLinesAndAdditionNotes(char*, char&, char*);
bool CheckSomeChars(const char*, const char*, const int&);
void Clear(OfficeSuite*);
void LoadStruct(OfficeSuite*, char*, char&);
double InNumber(char*, int&);
int Atoi(char&);
 
int q_packet(0); //Количество пакетов
 
int main()
{
setlocale(0,"");
    OfficeSuite *packet;
    char need_notes, notes[201] = {'\0'};
    int action; //Действие
    cout<<"Выберите действие:\n1 - Создать новую таблицу\n2 - Импортировать таблицу\nДействие №";
    do{ cin>>action; cin.get(); }while(action<1 && action>2);
 
    packet = (action==1)?FillingTable(need_notes, notes):Import(need_notes, notes);     
    
    Menu(packet, need_notes, notes);
delete [] packet;
return 0;
}
 
OfficeSuite *FillingTable(char &need_notes, char *notes)
{
    cout<<"\nВведите количество офисных пакетов: ";
    cin>>q_packet; cin.get(); cout<<endl;
    OfficeSuite *packet = new OfficeSuite [q_packet];
    for (int i(0); i<q_packet; i++)
    {
        cout<<"№"<<i+1<<" наименование пакета: "; cin.getline(packet[i].Name, 30);
        cout<<"№"<<i+1<<" производитель пакета: "; cin.getline(packet[i].Manufacturer, 30);
        cout<<"№"<<i+1<<" кол-во сост. частей пакета: "; cin>>packet[i].Quantity;
        cout<<"№"<<i+1<<" цена пакета: "; cin>>packet[i].cost; cin.get(); cout<<endl;
    }
    cout<<"Добавить примечание? (y/n): "; //Запрос добавления примечания
    do {cin>>need_notes; need_notes=tolower(need_notes);} while(need_notes!='y' && need_notes!='n');
    if (need_notes=='y')
    {
        cout<<"Примечание: ";
        cin.get(); cin.getline(notes, 200); cout<<"\n\n";
    }
    else cout<<"\n\n";
return packet;
}
 
void Menu(OfficeSuite *packet, char &need_notes, char *notes)
{
    char menu;
    do
    {
        cout<<"Выберите действие:"<<endl<<"1 - Вывести таблицу на экран"<<endl<<"2 - Отсортировать таблицу"<<endl;
        cout<<"3 - Поиск в таблице"<<endl<<"4 - Редактировать таблицу"<<endl<<"5 - Заменить примечание"<<endl;
        (need_notes=='y')?cout<<"6 - Отключить примечание\n":cout<<"6 - Включить примечание\n";
        cout<<"7 - Экспортировать таблицу в файл"<<endl<<"8 - Очистить экран"<<endl<<"9 - Выйти"<<endl;
        cout<<"Действие №";   do{cin>>menu;} while(menu < '0' || menu > '9'); cin.get();
        switch(menu)
        {
            case '1': ShowTable(packet, need_notes, notes); break;
            case '2': BubbleSort(packet, need_notes, notes); break;
            case '3': Search(packet); break;
            case '4': EditTable(packet, need_notes, notes); break;
            case '5': EditNotes(notes, need_notes); break;
            case '6': SwNotes(notes, need_notes); break;
            case '7': Export(packet, need_notes, notes); break;
            case '8': system("cls"); break;
            case '9': system("pause");
        }
 
    }while(menu!='9');
}
 
void ShowTable(OfficeSuite *packet, char &need_notes, char *notes)
{
    cout<<"\n"<<left<<setw(17)<<"Наименование"<<setw(17)<<"Производитель"<<setw(24)<<"Кол-во сост. частей"<<"Цена($)\n";
    for (int i(0); i<q_packet; i++)
        cout<<left<<setw(17)<<packet[i].Name<<setw(17)<<packet[i].Manufacturer<<setw(24)<<packet[i].Quantity<<packet[i].cost<<"\n";
    if (need_notes == 'y') cout<<"Примечание: "<<notes<<"\n\n";
    else cout<<"\n";
}
 
void BubbleSort(OfficeSuite *packet, char &need_notes, char *notes)
{
    cout<<"\n№1 - Наименование\n№2 - Производитель\n№3 - Кол-во сост. частей\n№4 - Цена($)\n№0 - Отмена\nСортировать по столбцу №"; 
    int sort_stl; do{cin>>sort_stl;}while( sort_stl<0 || sort_stl>4 );
    cout<<"\n1 - По возрастанию .<...>.\n2 - По убыванию    .>...<.\nСортировать по: ";
    char SortBy; //Сортировать по
    do { cin>>SortBy; }while(SortBy!='1' && SortBy!='2');
    double verifiable_stl[2]; //Проверяемые значения
    for (int i(0); true; i++) //Сортировка пузырьком
    {
        bool perfect = true; //Были ли найдены изъяны
        for (int j(0); j<q_packet-1; j++)
        {
            switch (sort_stl) //Выбор проверяемого столбца
            {
            case 0: return;
            case 1: verifiable_stl[0]=tolower(packet[j].Name[0]); verifiable_stl[1]=tolower(packet[j+1].Name[0]); break;
            case 2: verifiable_stl[0]=tolower(packet[j].Manufacturer[0]); verifiable_stl[1]=tolower(packet[j+1].Manufacturer[0]); break;
            case 3: verifiable_stl[0]=packet[j].Quantity; verifiable_stl[1]=packet[j+1].Quantity; break;
            case 4: verifiable_stl[0]=packet[j].cost; verifiable_stl[1]=packet[j+1].cost; break;
            }
            if ( SortBy=='1' && verifiable_stl[0] > verifiable_stl[1] || SortBy=='2' && verifiable_stl[0] < verifiable_stl[1] ) 
            {//Если проверяемый столбец не соответсвует выбранной сортировке, то меняем местами всю структуру местами
                StringSwap(packet[j].Name, packet[j+1].Name, 31);
                StringSwap(packet[j].Manufacturer, packet[j+1].Manufacturer, 31);
                Swap(packet[j].Quantity, packet[j+1].Quantity);
                Swap(packet[j].cost, packet[j+1].cost);
                perfect = false;
            }
        }
        if(perfect) //Если изъяны не найдены, останавливем цикл
        break;
    }
    ShowTable(packet, need_notes, notes);
}
 
void StringSwap(char *a, char *b, int const &size)
{
    char temp;
    for (int i(0); i<size; i++)
    {
        temp = a[i];
        a[i] = b[i];
        b[i] = temp;
    }
}
 
template <class Type> void Swap(Type &a, Type &b)
{
    Type temp = a;
    a = b;
    b = temp;
}
 
void Search(OfficeSuite *packet)
{
    cout<<"\n№1 - Наименование\n№2 - Производитель\n№3 - Кол-во сост. частей\n№4 - Цена($)\n\nИскать по столбцу №";
    int verifiable_stl, found(0); do{cin>>verifiable_stl; cin.get();}while( verifiable_stl<1 || verifiable_stl>4 );
    switch(verifiable_stl) 
    {
    case 1: //Еслм проверяемый столбец =1
        char s_name[31];
        cout<<"Искомое значение: "; cin.getline(s_name, 30);
        for (int i(0); i<q_packet; i++)
            if ( !strcmp(s_name, packet[i].Name) ) //strcmp проверяет две строки, если равны возвращает ЛОЖЬ
            { //Выводим найденную строку
                cout<<left<<setw(17)<<packet[i].Name<<setw(17)<<packet[i].Manufacturer<<setw(24)<<packet[i].Quantity<<packet[i].cost<<"\n";
                ++found; //Прибавляем к числу найденных
            }
        break;
    case 2: 
        char s_Manufacturer[31];
        cout<<"Искомое значение: "; cin.getline(s_Manufacturer, 30);
        for (int i(0); i<q_packet; i++)
            if ( !strcmp(s_Manufacturer, packet[i].Manufacturer) )
            {
                cout<<left<<setw(17)<<packet[i].Name<<setw(17)<<packet[i].Manufacturer<<setw(24)<<packet[i].Quantity<<packet[i].cost<<"\n";
                ++found;
            }
        break;
    case 3:
        double s_quantity;
        cout<<"Искомое значение: "; cin>>s_quantity;
        for (int i(0); i<q_packet; i++)
            if ( s_quantity == packet[i].Quantity )
            {
                cout<<left<<setw(17)<<packet[i].Name<<setw(17)<<packet[i].Manufacturer<<setw(24)<<packet[i].Quantity<<packet[i].cost<<"\n";
                ++found;
            }
        break;
    case 4:
        double s_cost;
        cout<<"Искомое значение: "; cin>>s_cost;
        for (int i(0); i<q_packet; i++)
            if ( s_cost == packet[i].cost )
            {
                cout<<left<<setw(17)<<packet[i].Name<<setw(17)<<packet[i].Manufacturer<<setw(24)<<packet[i].Quantity<<packet[i].cost<<"\n";
                ++found;
            }
        break;
    }
    if (!found) cout<<"К сожалению, ни чего - не найдено.\n"<<endl; //Если результатов 0
    else cout<<"\nГотово!\nКоличество найденных значений: "<<found<<"\n\n";
}
 
void EditTable(OfficeSuite *packet, char &need_notes, char *notes)
{
    int line, column; //Строка, столбец
    ShowTable(packet, need_notes, notes);
    cout<<"Cтрока №";
    do{ cin>>line; }while(line>q_packet || line<1);
    cout<<"Столбец №";
    do{ cin>>column; cin.get(); }while(column<1 || column>4);
    if (column==1)
    { //Просто удаляем предидущее значение т.к. редактировать в cmd нельзя
        cout<<"Предидущее значение: "<<packet[line-1].Name<<"\nУдалено!\nВведите новое значение: ";
        for (int c(0); c<31; c++) packet[line-1].Name[c] = '\0';
        do{
            cin.getline(packet[line-1].Name, 30);
            if (packet[line-1].Name[0]=='\0')
                cout<<"Не корректное значение!\nВведите еще раз!"<<endl;
        }while(packet[line-1].Name[0]=='\0');
    }
    else if (column==2)
    {
        cout<<"Предидущее значение: "<<packet[line-1].Manufacturer<<"\nУдалено!\nВведите новое значение: ";
        for (int c(0); c<31; c++) packet[line-1].Manufacturer[c] = '\0';
        do{
            cin.getline(packet[line-1].Manufacturer, 30);
            if (packet[line-1].Manufacturer[0]=='\0')
                cout<<"Не корректное значение!\nВведите еще раз!"<<endl;
        }while(packet[line-1].Manufacturer[0]=='\0');
    }
    else if (column==3)
    {
        cout<<"Предидущее значение: "<<packet[line-1].Quantity<<"\nУдалено!\nВведите новое значение: ";
        packet[line-1].Quantity = 0;
        do{
            cin>>packet[line-1].Quantity;
            if (!packet[line-1].Quantity)
                cout<<"Не корректное значение!\nВведите еще раз!"<<endl;
        }while(!packet[line-1].Quantity);
    }
    else
    {
        cout<<"Предидущее значение: "<<packet[line-1].cost<<"\nУдалено!\nВведите новое значение: ";
        packet[line-1].cost = 0;
        do{
            cin>>packet[line-1].cost;
            if (!packet[line-1].cost)
                cout<<"Не корректное значение!\nВведите еще раз!"<<endl;
        }while(!packet[line-1].cost);
    }
    cout<<"Изменение сохранено!\n\n";
}
 
void EditNotes(char *notes, char &need_notes)
{
    if(notes[0]!='\0') cout<<"\nСтарое примечание: "<<notes<<"\nУдалено!\n"; //Если примечание не пустое
    cout<<"\nВведите новое примечание: ";
    for (int c(0); c<201; c++)
        notes[c] = '\0';
    cin.getline(notes, 200);
    if (notes[0] == '\0') {cout<<"Примечание не корректно!\nПримечание отключено!\n\n"; need_notes='n';}
    else cout<<"Новое примечание сохранено!\n\n";
}
 
void SwNotes(char *notes, char &need_notes)
{
    if (need_notes=='y') need_notes='n';
    else if (notes[0]!='\0') need_notes='y'; //Если примечание не пустое, включим его
         else cout<<"\nНельзя включить не корректное примечание!\n";
    cout<<"\n";
}
 
void Export(OfficeSuite *packet, char &need_notes, char *notes)
{
    char namefile[31]; 
    cout<<"\nВведите имя файла: ";
    cin.getline(namefile, 30);
    ofstream fout(namefile);
    fout<<"Наименование\tПроизводитель\tКол-во сост. частей\tЦена($)\n";
    for (int i(0); i<q_packet; i++) //По одной строке, отправляем в файл
        fout<<packet[i].Name<<"\t\t"<<packet[i].Manufacturer<<"\t\t"<<packet[i].Quantity<<"\t\t\t"<<packet[i].cost<<"\n";
    if (need_notes == 'y') fout<<"Примечание: "<<notes; //Если есть примечание, отправляем тоже
    cout<<"Готово!\n\n";
    fout.close();
}
////////Импорт////////
OfficeSuite *Import(char &need_notes, char *notes)
{
    char filename[31], temp[3000] = {'\0'};
    ifstream fin;
    while(true)
    {
        for(int c(0); c<31; c++) filename[c]='\0'; //Очищаем имя файла
        cout<<"Введите имя файла: ";
        cin.getline(filename, 30);
        fin.open(filename);
        if(fin.fail()) cout<<"Файла с таким именем, не существует!\n"; else break;
    }
    for (int c(0); !fin.eof(); c++) {fin>>noskipws>>temp[c];} //Загружаем все во временный массив
    cout<<"Загружено: \n"<<temp<<"\n\n";
    fin.close();
    q_packet = CountLinesAndAdditionNotes(temp, need_notes, notes);
    cout<<"Количество пакетов: "<<q_packet<<endl;
    cout<<"Прмечание: "; if ('y'==need_notes) cout<<"Присутствует\n\n"; else cout<<"Отсутствует\n\n";
    OfficeSuite *packet = new OfficeSuite [q_packet];
    Clear(packet);
    LoadStruct(packet, temp, need_notes);
return packet;
}
 
int CountLinesAndAdditionNotes(char *temp, char &need_notes, char *notes)
{
    int Lines=0, i(54);
    for (; temp[i]!='\0'; i++)
    {
        if (temp[i] == '\n') Lines++;
        else if (temp[i] == 'П' && CheckSomeChars(&temp[i], "Примечание:", 11) )
        { //Если встретили примечание, запишем его
            i+=12; Lines--;
            need_notes = 'y';
            for (int j(0); temp[i]!='\0'; i++, j++) notes[j]=temp[i];
        }
    }//Отматаем, все лишние переносы строки, в конце файла
    while (temp[--i] == '\n') Lines--;
return Lines;
}
 
bool CheckSomeChars(const char *a, const char *b, const int &q_chars)
{
    for (int i(0); i<q_chars; i++)
        if (a[i] == b[i])
            return CheckSomeChars(&a[i+1], &b[i+1], q_chars-1);
        else
            return false;
    return true;
}
 
void Clear(OfficeSuite *packet)
{
    for (int i(0); i<q_packet; i++)
    {
        packet[i].Quantity = 0;
        packet[i].cost = 0;
        for (int j(0); j<31; j++)
        {
            packet[i].Name[j] = '\0';
            packet[i].Manufacturer[j] = '\0';
        }
    }
}
 
void LoadStruct(OfficeSuite *packet, char *temp, char &need_notes)
{
    int line=0, i=55;
    while(temp[i+1]!='\0')
    {
        if (temp[i]=='П' && CheckSomeChars(&temp[i], "Примечание:", 11)) break;
        else
        {
        for (int k(0); temp[i]!='\t'; k++, i++)
            {packet[line].Name[k] = temp[i];}
        while(temp[i]=='\t') i++;
        for (int k(0); temp[i]!='\t'; k++, i++)
            {packet[line].Manufacturer[k] = temp[i];}
        while(temp[i]=='\t') i++;
        packet[line].Quantity = InNumber(temp, i);
        while(temp[i]=='\t') i++;
        packet[line].cost = InNumber(temp, i);
        while(temp[i]=='\n') i++;
        line++;
        if (line >= q_packet) break;
        }
    }
}
 
double InNumber(char *a, int &i)
{
    double number(0), bit(0); //Общее кол-во целых и дроюных чисел
    bool drobnoe(false);
    int q_digits(0), d(1), q_bits(0), b(1);
    for(; a[i]>=48&&a[i]<=57 || a[i]=='.'; i++)
    {//Пока a[i] десятичная цифра или точка, выполнять, и i++
        if (a[i]=='.') {drobnoe=true; continue;}
        if (!drobnoe) q_digits++;
        else q_bits++;
    }
    int copy(i-1);
    while (q_digits)
    {
        if (a[copy]=='.') {--copy; continue;}
        if (q_bits) //Если есть дробные числа
        {
            bit += (Atoi(a[copy])*b);
            b*=10;
            q_bits--; copy--;
        }
        else
        {
            number += (Atoi(a[copy])*d);
            d*=10;
            q_digits--; copy--;
        }
    }
    if (drobnoe)
        number+=(double)bit/b;
 
return number;
}
 
int Atoi(char &A) { return (A>=48 && A<=57)?A-48:A; }
