#include <iostream>
#include <iomanip>
#include <string>
#include <Windows.h>

using namespace std;
enum Specialty { PC_Science, IT, Math_Economic, Physics_IT, Work_Training };
string SpecialtyStr[] = { "Комп’ютерні науки      ", "Інформатика            ", "Математика та економіка", "Фізика та інформатика  ", "Трудове навчання       " };
union ThirdGrade {
	int Programming;
	int NumericalMethods;
	int Pedagogy;
};
struct Student {
	int Sort_Number;
	string Last_Name;
	int Course;
	Specialty speciality;
	int PhysicsGrade;
	int MathGrade;
	ThirdGrade ThirdSubject;
};
void Create(Student* p, const int N);
void Print(Student* p, const int N);
void DisplayAverageGrade(Student* p, const int N);
double CalculatePercentageWith45PhysicsGrade(Student* p, const int N);
void SortStudents(Student* p, const int N);
void BuildIndexArray(Student* p, const int N, int* indexArray);
void PrintIndexArray(const int* indexArray, const int N);
int BinarySearch(Student* p, const int N);

int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	int N;

	cout << "Введіть кількість Студентів N: "; cin >> N;
	Student* p = new Student[N];	
	int* indexArray = new int[N];
	int menuItem;
	do {
		cout << endl << endl << endl;
		cout << "Виберіть дію:" << endl << endl;
		cout << " [1] - введення даних з клавіатури" << endl;
		cout << " [2] - вивід даних на екран" << endl;
		cout << " [3] - вивід прізвищ і середнього балу" << endl;
		cout << " [4] - обчислення проценту студентів з фізики оцінки “5” або “4”" << endl;
		cout << " [5] - сортування студентів" << endl;  
		cout << " [6] - бінарний пошук студента за прізвищем, спеціальністю та оцінкою з третього предмету" << endl;
		cout << " [0] - вихід та завершення роботи програми" << endl << endl;
		cout << "Введіть значення: "; cin >> menuItem;
		cout << endl << endl << endl;
		switch (menuItem) {
		case 1:
			Create(p, N);
			break;
		case 2:
			Print(p, N);
			break;
		case 3:
			DisplayAverageGrade(p, N);
			break;
		case 4:
			cout << "Процент студентів з фізики оцінки “5” або “4”: " <<
				CalculatePercentageWith45PhysicsGrade(p, N) << "%" << endl;
			break;
		case 5:
			BuildIndexArray(p, N, indexArray);
			cout << "Масив індексів перед сортуванням: ";
			PrintIndexArray(indexArray, N);
			SortStudents(p, N);
			BuildIndexArray(p, N, indexArray);
			cout << "Масив індексів після сортування: ";
			PrintIndexArray(indexArray, N);
			cout << "Студенти відсортовані." << endl;
			break;
		case 6:
		{
			int result = BinarySearch(p, N);
			if (result != -1) {
				cout << "Студент знайдений на позиції: " << result + 1 << endl;
			}
			else {
				cout << "Студента не знайдено." << endl;
			}
			break;
		}
		
		case 0:
			break;
		default:
			cout << "Ви ввели помилкове значення! "
				"Слід ввести число - номер вибраного пункту меню" << endl;
		}
	} while (menuItem != 0);
	return 0;
}
void Create(Student* p, const int N) {
	int speciality;
	for (int i = 0; i < N; i++) {
		cout << "Номер№ " << i + 1 << ":" << endl;
		cin.get();
		cin.sync();
		cout << " Порядковий номер студента у групі: "; cin >> p[i].Sort_Number;
		cout << " Прізвище: "; cin >> p[i].Last_Name;
		cout << " Курс: "; cin >> p[i].Course;
		cout << " Спеціальність: 0 - Комп’ютерні науки, 1 - Інформатика, 2 - Математика та економіка, 3 - Фізика та інформатика, 4 - Трудове навчання: "; 
		cin >> speciality;
		p[i].speciality = static_cast<Specialty>(speciality);
		cout << " Оцінка з фізики: "; cin >> p[i].PhysicsGrade;
		cout << " Оцінка з математики: "; cin >> p[i].MathGrade;
		switch (p[i].speciality) {
		case PC_Science:
			cout << " Оцінка з програмування: "; cin >> p[i].ThirdSubject.Programming;
			break;
		case IT:
			cout << " Оцінка з чисельних методів: "; cin >>
				p[i].ThirdSubject.NumericalMethods;
			break;
		default:
			cout << " Оцінка з педагогіки: "; cin >> p[i].ThirdSubject.Pedagogy;
			break;
		}
		cout << endl;
	}
}
void Print(Student* p, const int N) {
	cout <<
		"============================================================================================================================================ = "
		<< endl;
	cout << "| № | Номер в групі | Прізвище | Курс | Спеціальність          | Фізика   | Математика | Програмування | Чисельних методи | Педагогіки      |"
		<< endl;
	cout << "-------------------------------------------------------------------------------------------------------------------------------------------- - "
		<< endl;
	for (int i = 0; i < N; i++) {
		cout << "| " << setw(0) << right << i + 1 << " ";
		cout << "| " << setw(14) << left << p[i].Sort_Number
			<< "| " << setw(9) << left << p[i].Last_Name
			<< "| " << setw(12) << left << SpecialtyStr[p[i].speciality]
			<< "| " << setw(9) << right << p[i].PhysicsGrade
			<< "| " << setw(9) << right << p[i].MathGrade << " | ";
		switch (p[i].speciality) {
		case PC_Science:
			cout << setw(15) << right << p[i].ThirdSubject.Programming << " |";
			cout << setw(17) << right << "|";
			cout << setw(17) << right << "|";
			break;
		case IT:
			cout << setw(17) << right << "|";
			cout << setw(15) << right << p[i].ThirdSubject.NumericalMethods << " |";
			cout << setw(17) << right << "|";
			break;
		default:
			cout << setw(17) << right << "|";
			cout << setw(17) << right << "|";
			cout << setw(15) << right << p[i].ThirdSubject.Pedagogy << " |";
			break;
		}
		cout << endl;

	}
	cout <<
		"============================================================================================================================================ = "
		<< endl;
	cout << endl;
}
void DisplayAverageGrade(Student* p, const int N) {
	cout <<
		"============================================================================================================================================ = "
		<< endl;
	cout << "| № | Прізвище | Середній бал |"
		<< endl;
	cout << "-------------------------------------------------------------------------------------------------------------------------------------------- - "
		<< endl;
	for (int i = 0; i < N; i++) {
		int sum = 0;
		switch (p[i].speciality) {
		case PC_Science:
			sum = p[i].PhysicsGrade + p[i].MathGrade + p[i].ThirdSubject.Programming;
			break;
		case IT:
			sum = p[i].PhysicsGrade + p[i].MathGrade +
				p[i].ThirdSubject.NumericalMethods;
			break;
		default:
			sum = p[i].PhysicsGrade + p[i].MathGrade + p[i].ThirdSubject.Pedagogy;
			break;
		}

		double average = static_cast<double>(sum) / 3.0;
		cout << "| " << setw(0) << right << i + 1 << " ";
		cout << "| " << setw(13) << left << p[i].Last_Name
			<< "| " << setw(12) << right << setprecision(2) << fixed << average << " |"
			<< endl;
	}
	cout <<
		"============================================================================================================================================ = "
		<< endl;
	cout << endl;
}
double CalculatePercentageWith45PhysicsGrade(Student* p, const int N) {
	int count45 = 0;
	for (int i = 0; i < N; i++) {
		if (p[i].PhysicsGrade == 4 || p[i].PhysicsGrade == 5) {
			count45++;
		}
	}
	return (static_cast<double>(count45) / N) * 100.0;
}
void SortStudents(Student* p, const int N) {
	Student tmp;
	for (int i0 = 0; i0 < N - 1; i0++) {
		for (int i1 = 0; i1 < N - i0 - 1; i1++) {
			if ((p[i1].speciality > p[i1 + 1].speciality) ||
				(p[i1].speciality == p[i1 + 1].speciality && p[i1].ThirdSubject.Programming > p[i1 + 1].ThirdSubject.Programming) ||
				(p[i1].speciality == p[i1 + 1].speciality && p[i1].ThirdSubject.Programming == p[i1 + 1].ThirdSubject.Programming && p[i1].Last_Name > p[i1 + 1].Last_Name)) {
				tmp = p[i1];
				p[i1] = p[i1 + 1];
				p[i1 + 1] = tmp;
			}
		}
	}
}
void BuildIndexArray(Student* p, const int N, int* indexArray) {
	for (int i = 0; i < N; ++i) {
		indexArray[i] = i;
	}

	for (int i0 = 0; i0 < N - 1; i0++) {
		for (int i1 = 0; i1 < N - i0 - 1; i1++) {
			if ((p[indexArray[i1]].speciality > p[indexArray[i1 + 1]].speciality) ||
				(p[indexArray[i1]].speciality == p[indexArray[i1 + 1]].speciality && p[indexArray[i1]].ThirdSubject.Programming > p[indexArray[i1 + 1]].ThirdSubject.Programming) ||
				(p[indexArray[i1]].speciality == p[indexArray[i1 + 1]].speciality && p[indexArray[i1]].ThirdSubject.Programming == p[indexArray[i1 + 1]].ThirdSubject.Programming && p[indexArray[i1]].Last_Name > p[indexArray[i1 + 1]].Last_Name)) {
				swap(indexArray[i1], indexArray[i1 + 1]);
			}
		}
	}
}
void PrintIndexArray(const int* indexArray, const int N) {
	cout << "Масив індексів: ";
	for (int i = 0; i < N; ++i) {
		cout << indexArray[i] << " ";
	}
	cout << endl;
}

int BinarySearch(Student* p, const int N) {
	string searchLastName;
	int searchSpecialty;
	int searchGrade;

	cout << "Введіть прізвище студента: ";
	cin >> searchLastName;
	cout << "Введіть спеціальність студента (0 - Комп’ютерні науки, 1 - Інформатика, 2 - Математика та економіка, 3 - Фізика та інформатика, 4 - Трудове навчання): ";
	cin >> searchSpecialty;
	cout << "Введіть оцінку з третього предмету студента: ";
	cin >> searchGrade;

	Specialty searchSpecialtyEnum = static_cast<Specialty>(searchSpecialty);

	int left = 0;
	int right = N - 1;

	while (left <= right) {
		int mid = left + (right - left) / 2;

		if (p[mid].Last_Name == searchLastName && p[mid].speciality == searchSpecialtyEnum && p[mid].ThirdSubject.Programming == searchGrade) {
			return mid;
		}

		if (p[mid].Last_Name < searchLastName ||
			(p[mid].Last_Name == searchLastName && p[mid].speciality < searchSpecialtyEnum) ||
			(p[mid].Last_Name == searchLastName && p[mid].speciality == searchSpecialtyEnum && p[mid].ThirdSubject.Programming < searchGrade)) {
			left = mid + 1;
		}
		else {
			right = mid - 1;
		}
	}

	return -1; 
}
