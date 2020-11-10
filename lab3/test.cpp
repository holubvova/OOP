// references.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "List.h"
#include "Refernces.h"
//#include "References.cpp"

using namespace std;



/*word;56,54,6,5,8,9,6;302;
find;4,58,98,6,42;100;
rain;158,32,5,6,54,69,87,2;160;
apple;1,15,3,2,70,80,32,5,45;291;
puchirchyk;3,8,15,23,67,85;115;*/
void _change(const char* last, const char* new_name, List<References>& _data);
void DELL(List<References>& _where, List<References>& to_dell);
void RE_DELL(List<References>& _where, List<References>& to_re_dell);
void DELL_if(List<References>& _where, List<References>& to_dell, int size);
void add_references(const char* new_list, List<References>& _where);
int main()
{
    
    List<References> data;
    List<References> dell;
    data.load("test.csv");
    data.Print();
    cout << "dell when _size < 150:" << endl;
    DELL_if(data, dell,150);
    cout << "data: " << endl;
    data.Print();
    cout << "dell: " << endl;
    dell.Print();
    _change("test", "_change", data);
    cout << "after _change:" << endl;
    data.Print();
  //  _change("apple", "APPLE", dell);
    cout << "after _change DELL list:" << endl;
  //  dell.Print();
    cout << "RE_DELL:" << endl;
    RE_DELL(dell, data);
    cout << "data :" << endl;
    data.Print();
    cout << "dell:" << endl;
    dell.Print();
    add_references("testADD;32,32,1,5,65,5,3,5;152;", dell);
    cout << "after ADD:" << endl;
    dell.Print();
    cout << "dell:" << endl;
    dell.Print();
    cout << "data:" << endl;
    data.Print();
    DELL(data, dell);
    cout << "after DELL:" << endl;
    cout << "data" << endl;
    data.Print();
    cout << "dell:" << endl;
    dell.Print();
    
    return 0;
}
void _change(const char* last_word, const char* new_word, List<References> & _data ) {
    List<References>::iterator it;
    for (it = _data.begin(); it != _data.end(); it++) {
        if (strcmp((*it).data.getword(), last_word) == 0) {
            (*it).data.change(new_word);
        }
    }
}
void DELL_if(List<References>& _where, List<References>& to_dell,int size ) {
    List<References>::iterator it;
    for (it = _where.begin(); it != _where.end(); ++it) {
        if ((*it).data.getsize() < size) {
            _where.splice(it, to_dell);
            it = _where.begin();
        }
      //  it = _where.begin();
    }
}

void DELL(List<References>& _where, List<References>& to_dell) {
    List<References>::iterator it = _where.begin();
    _where.splice(it, to_dell);
}

void add_references(const char* new_list, List<References> & _where) {
    _where.push_front(References(new_list));

}
void RE_DELL(List<References>& _where, List<References>& to_re_dell) {
    List<References>::iterator it = _where.begin();
    _where.splice(it, to_re_dell);
}


// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
