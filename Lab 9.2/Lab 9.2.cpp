#include <iostream>
#include <iomanip>
#include <string>
#include <Windows.h>

using namespace std;
enum Specialty { PC_Science, IT, Math_Economic, Physics_IT, Work_Training };
string SpecialtyStr[] = { "��������� �����      ", "�����������            ", "���������� �� ��������", "Գ���� �� �����������  ", "������� ��������       " };
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

	cout << "������ ������� �������� N: "; cin >> N;
	Student* p = new Student[N];	
	int* indexArray = new int[N];
	int menuItem;
	do {
		cout << endl << endl << endl;
		cout << "������� ��:" << endl << endl;
		cout << " [1] - �������� ����� � ���������" << endl;
		cout << " [2] - ���� ����� �� �����" << endl;
		cout << " [3] - ���� ������ � ���������� ����" << endl;
		cout << " [4] - ���������� �������� �������� � ������ ������ �5� ��� �4�" << endl;
		cout << " [5] - ���������� ��������" << endl;  
		cout << " [6] - ������� ����� �������� �� ��������, ������������ �� ������� � �������� ��������" << endl;
		cout << " [0] - ����� �� ���������� ������ ��������" << endl << endl;
		cout << "������ ��������: "; cin >> menuItem;
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
			cout << "������� �������� � ������ ������ �5� ��� �4�: " <<
				CalculatePercentageWith45PhysicsGrade(p, N) << "%" << endl;
			break;
		case 5:
			BuildIndexArray(p, N, indexArray);
			cout << "����� ������� ����� �����������: ";
			PrintIndexArray(indexArray, N);
			SortStudents(p, N);
			BuildIndexArray(p, N, indexArray);
			cout << "����� ������� ���� ����������: ";
			PrintIndexArray(indexArray, N);
			cout << "�������� ����������." << endl;
			break;
		case 6:
		{
			int result = BinarySearch(p, N);
			if (result != -1) {
				cout << "������� ��������� �� �������: " << result + 1 << endl;
			}
			else {
				cout << "�������� �� ��������." << endl;
			}
			break;
		}
		
		case 0:
			break;
		default:
			cout << "�� ����� ��������� ��������! "
				"��� ������ ����� - ����� ��������� ������ ����" << endl;
		}
	} while (menuItem != 0);
	return 0;
}
void Create(Student* p, const int N) {
	int speciality;
	for (int i = 0; i < N; i++) {
		cout << "����� " << i + 1 << ":" << endl;
		cin.get();
		cin.sync();
		cout << " ���������� ����� �������� � ����: "; cin >> p[i].Sort_Number;
		cout << " �������: "; cin >> p[i].Last_Name;
		cout << " ����: "; cin >> p[i].Course;
		cout << " ������������: 0 - ��������� �����, 1 - �����������, 2 - ���������� �� ��������, 3 - Գ���� �� �����������, 4 - ������� ��������: "; 
		cin >> speciality;
		p[i].speciality = static_cast<Specialty>(speciality);
		cout << " ������ � ������: "; cin >> p[i].PhysicsGrade;
		cout << " ������ � ����������: "; cin >> p[i].MathGrade;
		switch (p[i].speciality) {
		case PC_Science:
			cout << " ������ � �������������: "; cin >> p[i].ThirdSubject.Programming;
			break;
		case IT:
			cout << " ������ � ��������� ������: "; cin >>
				p[i].ThirdSubject.NumericalMethods;
			break;
		default:
			cout << " ������ � ���������: "; cin >> p[i].ThirdSubject.Pedagogy;
			break;
		}
		cout << endl;
	}
}
void Print(Student* p, const int N) {
	cout <<
		"============================================================================================================================================ = "
		<< endl;
	cout << "| � | ����� � ���� | ������� | ���� | ������������          | Գ����   | ���������� | ������������� | ��������� ������ | ���������      |"
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
	cout << "| � | ������� | ������� ��� |"
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
	cout << "����� �������: ";
	for (int i = 0; i < N; ++i) {
		cout << indexArray[i] << " ";
	}
	cout << endl;
}

int BinarySearch(Student* p, const int N) {
	string searchLastName;
	int searchSpecialty;
	int searchGrade;

	cout << "������ ������� ��������: ";
	cin >> searchLastName;
	cout << "������ ������������ �������� (0 - ��������� �����, 1 - �����������, 2 - ���������� �� ��������, 3 - Գ���� �� �����������, 4 - ������� ��������): ";
	cin >> searchSpecialty;
	cout << "������ ������ � �������� �������� ��������: ";
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
