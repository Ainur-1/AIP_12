#include <conio.h> //для _getch()
#include <iostream>
#include <string>
#include <stdlib.h>
#include <fstream>
#include <iomanip>

using namespace std;

// описание структур
struct g_list //структура книги
{
	char name[15];
	char room[15];
	char group[15];
	int area;
};

struct o_list //структура автор
{
	char faculty[15];
	int kolvo;
};

// прототипы функций, работающих с динамическими массивами структур
g_list* input_file(int& k);//прототип функции с возвратом значения типа g_list - ввод массива структур из файла
o_list* perech(g_list x[], int k, int& k2);//прототип функции типа o_list - формирование списка авторов с количеством их книг
void outputperech(o_list y[], int k2);//прототип функции - вывод полученного списка на консоль 
void outputperechfile(o_list y[], int k2);//прототип функции - вывод полученного списка в файл

// коды функций
g_list* input_file(int& k)//ф-ция с возвращением значения структуры типа g_list и переменной k из функции
//k - размер массива структур - считываем атрибуты массива структур из файла
{
	int i;
	g_list t;//переменная типа g_list
	g_list* ps;// указатель на тип g_list
	ifstream fin;// поток для ввода из файла

	fin.open("L12.txt");// открыть файл
	if (!fin) { cout << "L12.txt" << " " << "Can’t open file\n"; _getch(); exit(1); }//Функция getch() возвращает очередной символ, считанный с консоли, но не выводит этот сим­вол на экран.

	k = 0;
	do {
		fin >> t.name >> t.room >> t.group >> t.area;// ввод атрибутов g_list из файла
		k++;
	} while (fin.good());//предиктная функця good() возвращает true, если чтение из файла прошло успешно.
	k--;// определили число записей k в файле
	fin.close();
	fin.open("L12.txt");
	ps = new g_list[k];// создаем массив структур g_list из k элементов
	if (ps == NULL) { cout << "No memory\n"; _getch(); exit(1); }
	for (i = 0; i < k; i++)//считывание атрибутов структуры боок из файла
		fin >> ps[i].name >> ps[i].room >> ps[i].group >> ps[i].area;
	fin.close();
	return ps;// возврат массива структур
}

o_list* perech(g_list x[], int k, int& k2)//в функцию передается массив структур типа g_list x размера k
 //из функции возвращается массив структур типа o_list и его размер k2
{
	int i, j, fl;
	o_list* t; //указатель на тип o_list
	t = new o_list[k];//массив структур типа o_list размером k(это максим. размер - для случая, если ВСЕ книги ОДНОГО автора 
	if (t == NULL) { cout << "No memory"; _getch(); exit(1); }
	k2 = 0;
	for (i = 0; i < k; i++)
	{
		fl = 0;
		for (j = 0; j < k2; j++)
			if (strcmp(x[i].group, t[j].faculty) == 0) { fl = 1; t[j].kolvo++; }// если в массиве структур g_list атрибут .faculty = соотвествующему
			// атрибуту структуры o_list, то увеличивается атрибут .kolvo в 
		   //массиве структур t типа o_list, флаг f1 включен
			if (fl == 0) {
				strcpy_s(t[k2].faculty, x[i].group);// копируем автора в массив t из списк книг, если автор встретился впервые
				t[k2].kolvo = 1;
				k2++;
			}
	}
	return t;
}

void outputperech(o_list y[], int k2)// функция вывода полученного списка авторов на консоль
{
	int i;
	cout << "Группа	К-во\n";
	for (i = 0; i < k2; i++)
		cout << y[i].faculty << "	" << y[i].kolvo << endl;
	return;
}

void outputperechfile(o_list y[], int k2)// функция вывода полученного списка авторов в файл
{
	ofstream fout;// поток для вывода
	int i;
	char file[10];// имя файла для вывода
	cout << "Name of output file:\n";
	cin >> file;
	fout.open(file);
	if (!fout.good()) { cout << file << "Not created\n"; _getch(); exit(1); }// если что-то не в порядке
	 //с файлом, то сообщение и выход из программы
	for (i = 0; i < k2; i++)
		fout << setw(15) << y[i].faculty << setw(10) << y[i].kolvo << endl;
	fout.close();
	return;
}

void main()
{
	setlocale(0, ""); // русский язык на консоли
	g_list* ps;// указатель типа g_list
	int n;
	o_list* pp;// указатель типа o_list
	int l;
	ps = input_file(n);// Читаем список книг из файла
	pp = perech(ps, n, l);// Составляем перечень авторов
	outputperech(pp, l);// выводим полученный перечень на консоль и в файл
	outputperechfile(pp, l);
	delete[] ps;// освобождаем память, занятую массивами структур
	delete[] pp;
	system("pause");
}
