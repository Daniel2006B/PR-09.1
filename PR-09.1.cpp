#include <iostream>
#include <iomanip>
#include <string>
#include <Windows.h> // забезпечення відображення кирилиці
using namespace std;
enum Speciality { COMPUTER_SCIENCE, INFORMATION, MATHEMATICS_AND_ECONOMICS, HANDICRAFT, PHYSICS_AND_INFORMATICS};
string specialityStr[] = { "Комп’ютерні науки", "Інформатика", "Математика та економіка", "Трудове навчання", "Фізика та інформатика"};
struct Student
{
	string prizv;
	unsigned kurs;
	Speciality speciality;
	
	    int mark1;
		int mark2;
		//int mark3;
		union  {
			int mark3;
			int ped;
			int prog;
			int chys;
		};
	
};
void Create(Student* p, const int N);
void Print(Student* p, const int N);
int LineSearchPhysics5(Student* p, const int N); 
int LineSearchGoodMarks(Student* p, const int N);
void Sort(Student* p, const int N);
int BinSearch(Student* p, const int N, const string prizv, const Speciality speciality);
int* IndexSort(Student* p, const int N);
void PrintIndexSorted(Student* p, int* I, const int N);
int main()
{ // забезпечення відображення кирилиці:
	SetConsoleCP(1251); // встановлення сторінки win-cp1251 в потік вводу
	SetConsoleOutputCP(1251); // встановлення сторінки win-cp1251 в потік виводу

	int N;
	cout << "Введіть кількість студентів N: "; cin >> N;

	Student* p = new Student[N];
	double proc;
	int ispeciality;
	Speciality speciality;
	string prizv;
	int found;
	int menuItem;
	do {
		cout << endl << endl << endl;
		cout << "Виберіть дію:" << endl << endl;
		cout << " [1] - введення даних з клавіатури" << endl;
		cout << " [2] - вивід даних на екран" << endl;
		cout << " [3] - вивід прізвищ та кількість студентів," << endl;
		cout << " хто з цих отримав з фізики оцінку 5" << endl;
		cout << " [4] - вивід прізвищ та кількість студентів," << endl;
		cout << " хто з них вчиться на відмінно" << endl;
		cout << " [5] - фізичне впорядкування даних" << endl;
		cout << " [6] - бінарний пошук студента за курсом та прізвищем" << endl;
		cout << " [7] - індексне впорядкування та вивід даних"
			<< endl << endl;
		cout << " [0] - вихід та завершення роботи програми" << endl << endl;
		cout << "Введіть значення: "; cin >> menuItem;
		cout << endl << endl << endl;
		switch (menuItem)
		{
		case 1:
			Create(p, N);
			break;
		case 2:
			Print(p, N);
			break;
		case 3:
			proc = LineSearchPhysics5(p, N);
			cout << "Кількість студентів, хто з цих отримав з фізики оцінку 5.: " ;
			cout << proc  << endl;
			break;
		case 4:
			proc = LineSearchGoodMarks(p, N);
			cout << "Кількість студентів, хто вчиться на добре або відмінно: ";
			cout << proc << endl;
			break;
		case 5:
			Sort(p, N);
			break;
		case 6:
				cout << "Введіть ключі пошуку:" << endl;
			cout << "спеціальність (0 - Комп’ютерні науки, 1 - Інформатика, 2 - Математика та економіка, 3 - Трудове навчання, 4 - Фізика та інформатика): ";
			cin >> ispeciality;
			speciality = (Speciality)ispeciality;
			cin.get(); // очищуємо буфер клавіатури – бо залишаються символи
			cin.sync(); // "кінець рядка", які не дають ввести наступний літерний рядок

			cout << " прізвище: "; getline(cin, prizv);
			cout << endl;
			if ((found = BinSearch(p, N, prizv, speciality)) != -1)
				cout << "Знайдено студента в позиції " << found + 1 << endl;
			else
				cout << "Шуканого студента не знайдено" << endl;
			break;
		case 7:
			PrintIndexSorted(p, IndexSort(p, N), N);
			break;
		case 0:
			break;
		default:
			cout << "Ви ввели помилкове значення! "
				"Слід ввести число - номер вибраного пункту меню" << endl;
		}
	} while (menuItem != 0);
	return 0;
}
void Create(Student* p, const int N)
{
	int speciality;
	for (int i = 0; i < N; i++)
	{
		cout << "Студент № " << i + 1 << ":" << endl;
		cin.get(); // очищуємо буфер клавіатури – бо залишаються символи
		cin.sync(); // "кінець рядка", які не дають ввести наступний літерний рядок

		cout << " прізвище: ";
		getline(cin, p[i].prizv);
		cout << " курс: "; 
		cin >> p[i].kurs;
		cout << " спеціальність (0 - Комп’ютерні науки, 1 - Інформатика, 2 - Математика та економіка, 3 - Трудове навчання, 4 - Фізика та інформатика): ";
		cin >> speciality;
		p[i].speciality = (Speciality)speciality;

		cout << "оцінка з фізики : ";
		cin >> p[i].mark1;
		cout << "оцінка з математики : ";
		cin >> p[i].mark2;
		switch (p[i].speciality)
		{
		case COMPUTER_SCIENCE:
			cout << " оцінка програмування : "; 
			cin >> p[i].prog;
			break;
		case INFORMATION :
			cout << " оцінка чисельних методів : "; 
			cin >> p[i].chys;
			break;
		default:
			cout << " оцінка з педагогіки : ";
			cin >> p[i].ped;
			break;
		}
		
		cout << endl;
	}
}
void Print(Student* p, const int N)
{
	cout << "=================================================================================="
		<< endl;
		cout << "|  №  |   Прізвище   | курс |     спеціальність      | оцінка1 | оцінка2 | оцінка3 |"
		<< endl;
	cout << "----------------------------------------------------------------------------------"
		<< endl;
	for (int i = 0; i < N; i++)
	{
		cout << "| " << setw(3) << right << i + 1 << " ";
		cout << "| " << setw(13) << left << p[i].prizv
			<< "| " << setw(4) << right << p[i].kurs << " "
			<< "| " << setw(14) << left << specialityStr[p[i].speciality] << " ";
		cout << " | " << setw(7) << right << p[i].mark1 << " "
			<< " | " << setw(7) << left << p[i].mark2 << " "
			<< " | " << setw(7) << right << p[i].mark3 << " |";
		cout << endl<< "=================================================================================="
			<< endl;
	}
	cout << endl;
}
int LineSearchPhysics5(Student* p, const int N)
{
	cout << "Прізвища студентів які вчаться з фізики мають 5:" << endl;
	int n = 0;
	for (int i = 0; i < N; i++)
	{
		if (p[i]. mark1 ==5)
		{
			n++;
			
				cout << setw(3) << right << n
					<< " " << p[i].prizv << endl;
		}
	}
	return n;
}
int LineSearchGoodMarks(Student* p, const int N)
{
	cout << "Прізвища студентів які вчаться на добре або відмінно: " << endl;
	int n = 0;
	for (int i = 0; i < N; i++)
	{
		if (p[i].mark1 >3  && p[i].mark2 > 3 && p[i].mark3 > 3)
		{
			n++;

			cout << setw(3) << right << n
				<< " " << p[i].prizv << endl;
		}
	}
	return n;
}


void Sort(Student* p, const int N)
{
	Student tmp;
	for (int i0 = 0; i0 < N - 1; i0++) // метод "бульбашки"
		for (int i1 = 0; i1 < N - i0 - 1; i1++)
			if ((p[i1].prizv > p[i1 + 1].prizv)
				||
				(p[i1].prizv == p[i1 + 1].prizv &&
					p[i1].speciality > p[i1 + 1].speciality))
			{
				tmp = p[i1];
				p[i1] = p[i1 + 1];
				p[i1 + 1] = tmp;
			}
	
}
int BinSearch(Student* p, const int N, const string prizv, const Speciality speciality)
{ // повертає індекс знайденого елемента або -1, якщо шуканий елемент відсутній
	int L = 0, R = N - 1, m;
	do {
		m = (L + R) / 2;
		if (p[m].prizv == prizv && p[m].speciality == speciality)
			return m;
		if ((p[m].speciality < speciality)
			||
			(p[m].speciality == speciality &&
				p[m].prizv < prizv))
		{
			L = m + 1;
		}
		else
		{
			R = m - 1;
		}
	} while (L <= R);
	return -1;
}
int* IndexSort(Student* p, const int N)
{ // використовуємо метод вставки для формування індексного масиву
 //
 // int i, j, value;
 // for (i = 1; i < length; i++) {
 // value = a[i];
 // for (j = i - 1; j >= 0 && a[j] > value; j--) {
 // a[j + 1] = a[j];
 // }
 // a[j + 1] = value;
 // }
	int* I = new int[N]; // створили індексний масив
	for (int i = 0; i < N; i++)
		I[i] = i; // заповнили його початковими даними
	int i, j, value; // починаємо сортувати масив індексів
	for (i = 1; i < N; i++)
	{
		value = I[i];
		for (j = i - 1;
			j >= 0 && ((p[I[j]].speciality > p[value].speciality) ||
				(p[I[j]].speciality == p[value].speciality &&
					p[I[j]].prizv > p[value].prizv));
			j--)
		{
			I[j + 1] = I[j];
		}
		I[j + 1] = value;
	}
	return I;
}
void PrintIndexSorted(Student* p, int* I, const int N)
{ // аналогічно функції Print(), але замість звертання p[i]...
 // використовуємо доступ за допомогою індексного масиву І: p[I[i]]...
	cout << "========================================================================="
		<< endl;
	cout << "| № | Прізвище | курс | спеціальність | оцінка1 | оцінка2 | оцінка3 |"
		<< endl;
	cout << "-------------------------------------------------------------------------"
		<< endl;
	for (int i = 0; i < N; i++)
	{
		cout << "| " << setw(3) << right << i + 1 << " ";
		cout << "| " << setw(13) << left << p[I[i]].prizv
			<< "| " << setw(4) << right << p[I[i]].kurs << " "
			<< "| " << setw(11) << left << specialityStr[p[I[i]].speciality] << " ";
		cout << " | " << setw(4) << right << p[i].mark1 << " "
			<< " | " << setw(4) << left << p[i].mark2 << " "
			<< " | " << setw(4) << right << p[i].mark3 << " |";
		cout << endl<< "========================================================================="
			<< endl;
		cout << endl;
	}
}

