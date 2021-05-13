
/****************************************************************
* Project Type : Win32 Console Application *
* Project Name : lab3*
* File Name : lab3333.CPP *
* Programmer(s) : Кузнецов И.И. *
* Modifyed By : *
* Created : 16/04/20 *
* Last Revision : 28/05/20 *
* Comment(s) : ДИНАМИЧЕСКИЕ МНОГОМЕРНЫЕ МАССИВОВ *
*****************************************************************/
#include <string>
#include <fstream>
#include <iostream>
#include <iomanip>

using namespace std;

const char* FILENAME_1 = "src.txt"; //путь к исходным файлам для 1 матрицы
const char* FILENAME_2 = "../tests_1/src12.txt"; //путь к исходным файлам для 2 матрицы

//	* ----------------------------------------------------------------------------------------- *
//								Н Е К О Р Р Е К Т Н Ы Е  Т Е С Т Ы
//			src0.txt  - тест на отсутствие файла
//			src1.txt  - тест на пустой файл
//			src2.txt  - тест на неккоректные символы при вводе (буквы)
//			src3.txt  - тест на количество входных элементов > размера матрицы
//			src4.txt  - тест на количество входных элементов < размера матрицы
//			src13.txt - тест на отрицательные размеры матрицы (N<0)
//			src14.txt - тест на отрицательные размеры матрицы (M<0)
//
//								    К О Р Р Е К Т Н Ы Е  Т Е С Т Ы 
//			src5.txt  - тест на размер матрицы = количество входных элементов
//
//			src6.txt  - тест без положительных элементов в матрице
//			src7.txt  - тест с одним положительным элементов в матрице
//			src8.txt  - тест с несколькими одинаковыми максимумами
//
//			src9.txt  - тест для проверки перестановок с нечетным количеством столбцов
//			src10.txt - тест для проверки перестановок с четным количеством столбцов
//
//			src11.txt - тест с размерами матрицами: ARRAY1 - 5 8; ARRAY2 - 4 7
//			src12.txt - тест с размерами матрицами: ARRAY1 - 6 9; ARRAY2 - 3 6
//
//	* ----------------------------------------------------------------------------------------- *	

void CleanMemory(double** ARRAY, int N) { //освобождаем память
	for (int i = 0; i < N; i++) {
		delete[] ARRAY[i];
	}

	delete[] ARRAY;
}
void PrintArray(double** ARRAY, int *VecX, int N, int M) { //печать массива
	cout << endl;
	for (int i = 0; i < M-1; i++) {
		cout << setw(6) << "x" << VecX[i];
	}
	cout << setw(6) << "b";
	for (int i = 0; i < N; i++) {
		cout << endl;
		for (int j = 0; j < M; j++) {
			if (j == M-1) {
				cout << "  |" << setw(7) << ARRAY[i][j];
			}
			else {
				cout << setw(7) << ARRAY[i][j];
			}
			
		}
	}
	cout << endl;
}
void GetCode(int CodeError) {
	switch (CodeError)
	{
	case -1:
		cout << "Ошибка! файл не найден" << endl << endl;
		break;
	case -2:
		cout << "Ошибка! файл пуст!" << endl << endl;
		break;
	case -3:
		cout << "Ошибка! Допустим ввод только цифр!" << endl << endl;
		break;
	case -4:
		cout << "Ошибка! Количество входных элементов больше размера массива!" << endl << endl;
		break;
	case -5:
		cout << "Ошибка! Количество входных элементов меньше размера массива!" << endl << endl;
		break;
	}
}
void IntMatrix(double*** ARRAY, int* N, int* M, int* CodeError, const char* FILENAME) {
	ifstream fin; //создаем объект класса ifstream
	fin.open(FILENAME); //открываем файл
	int CntVec = 0; //счетчик реального размера массива
	int CntLine = 0; //счетчик для ввода
	int CntColumn = 0; //счетчик для ввода
	double buff; // буффер для проверки корректности вводимых данных

	if (!fin) // если файл не найден
	{
		*CodeError = -1;
		return;
	}

	if (fin.peek() == EOF)  //если найденный файл пуст
	{
		*CodeError = -2;
		return;
	}

	while (!fin.eof()) { //проверка на ввод цифр
		fin >> buff;
		if (!fin) {
			*CodeError = -3;
			return;
		}
	}
	fin.seekg(0); //возврат чтения файла на самое начало

	fin >> *N; //считываем количество строк
	fin >> *M; //считываем количество столбцов

	*ARRAY = new double* [*N];
	for (int i = 0; i < *N; i++) {
		*(*ARRAY + i) = new double[*M];
	}

	while (!fin.eof()) { //чтение элементов массива, пока элементы не закончатся
		fin >> buff;
		CntVec++; //подсчет количества элементов массив
	}
	if (CntVec > * N * *M) { //проверка на выход за границы массива
		*CodeError = -4;
		return;
	}
	if (CntVec < *N * *M) { //проверка на недостаток элементов 
		*CodeError = -5;
		return;
	}
	fin.seekg(0); //возврат чтения файла на самое начало

	fin >> buff >> buff; //так как вернулись на самое начало, записываем в буффер размеры
	while (!fin.eof()) {
		fin >> *(*(*ARRAY + CntLine) + CntColumn); //чтение массива из файла
		CntColumn++;
		if (CntColumn == *M) {
			CntLine++;
			CntColumn = 0;
		}
	}

	fin.close(); // закрываем файл

}

/*
ФУНКЦИЯ ДЛЯ СУММИРОВАНИЯ СТРОКИ
ВХОДНЫЕ ПАРАМЕТРЫ:
	ARRAY - МАТРИЦА С КОТОРОЙ РАБОТАЕМ
	M - РАЗМЕР СТРОКИ
	row - ИНДЕКС СТРОКИ В КОТОРОЙ ИЩЕМ СУММУ
ВОЗРАЩАЕМЫЕ ПАРАМЕТРЫ:
	СУММА СТРОКИ ПОД НОМЕРОМ row, БЕЗ СВОБОДНЫХ ЧЛЕНОВ 
*/
double SumLine(double** ARRAY, int M, int row) {
	double sum = 0; 
	for (int i = 0; i < M-1; i++) { //идем по строкам матрицы пропуская свободные члены
		sum += fabs(ARRAY[row][i]); //попадаем в row столбец, считаем |сумму| всей строки
	}
	return sum;
}
//++

/*
ФУНКЦИЯ ДЛЯ ПОДСЧЕТА НОРМЫ МАТРИЦЫ
ВХОДНЫЕ ПАРАМЕТРЫ:
	ARRAY - МАТРИЦА С КОТОРОЙ РАБОТАТАЕМ
	N - РАЗМЕР СТОЛБЦОВ 
	M - РАЗМЕР СТРОКИ
ВОЗРАЩАЕМЫЕ ПАРАМЕТРЫ:
	НОРМА МАТРИЦЫ - МАКСИМАЛЬНАЯ СУММА СТРОК СРЕДИ СТОЛБЦОВ ПО МОДУЛЮ
*/
double NormMatrix(double **ARRAY, int N, int M) {
	double max = 0; //т.к. мы считаем модули значений в строке, 
					//то max можно принять за 0, т.к сумма будет >=0
	for (int i = 0; i < N; i++) { //идем по строкам матрицы
		if (SumLine(ARRAY, M, i) > max) {
			max = SumLine(ARRAY, M, i);
		}
	}
	return max;
}
//++

/*
ФУНКЦИЯ НАХОДЯЩАЯ МАКСИМУМ СРЕДИ СТОЛБЦОВ СВОБОДНЫХ ЧЛЕНОВ ПО МОДУЛЮ
ВХОДНЫЕ ПАРАМЕТРЫ:
	ARRAY - МАТРИЦА С КОТОРОЙ РАБОТАЕМ
	N - РАЗМЕР СТОЛБЦОВ
ВОЗВРАЩАЕМЫЕ ПАРАМЕТРЫ:
	МАКСИМУМ СРЕДИ СТОЛБЦОВ СВОБОДНЫХ ЧЛЕНОВ ПО МОДУЛЮ
*/
double MaxFreeTerm(double **ARRAY, int N, int M) {
	double max = 0; //т.к. работаем с модулем элементы будут всегда >=0
	for (int i = 0; i < N; i++) {
		if (fabs(ARRAY[i][M-1]) > max) { //попадаем в i-ую строку и идем на св. член
			max = fabs(ARRAY[i][M-1]);
		}
	}
	return max;
}
//++

/*
template <typename T>
T MatrixB(T** ARRAY) {
	T temp;
	for (int i = 0; i < N - 1; i++) {
		for (int j = 0; j < M; j++) {
			if (i == j) {
				continue;
			}
			*(*(ARRAY + i) + j) -= *(*(ARRAY + i) + j) / temp;
		}
	}
}
*/


void Res(double** ARRAY, double* res, int N, int M) {
	for (int i = 0; i < N; i++) {
		res[i] == ARRAY[i][M-1] / ARRAY[i][i];
		cout << ARRAY[i][M-1] << "  " << ARRAY[i][i];
		cout << endl;
	}
}

 /*
ФУНКЦИЯ ДЛЯ ПЕРЕСТАНОВКИ СТОЛБЦОВ
ВХОДНЫЕ ПАРАМЕТРЫ:
   ARRAY - МАТРИЦА С КОТОРОЙ РАБОТАЕМ
   indexmax - НАЙДЕННЫЙ СТОЛБЕЦ С МАКС. ЭЛЕМЕНТОМ
   num - СТОЛБЕЦ С КОТОРЫМ БУДЕМ МЕНЯТЬ
   N - РАЗМЕР СТОЛБЦОВ
ВЫХОДНЫЕ ПАРАМЕТРЫ:
	НИЧЕГОШЕНЬКИ, ПОМЕНЯЛИ И ХВАТИТ
 */
 void SwapCols(double** ARRAY, int *VecX, int indexmax, int num, int M) {
	 double temp;
	 for (int i = num; i < M; i++) {
		 temp = ARRAY[i][indexmax];
		 ARRAY[i][indexmax] = ARRAY[i][num];
		 ARRAY[i][num] = temp;	

		 temp = VecX[indexmax];
		 VecX[indexmax] = VecX[num];
		 VecX[num] = temp;
	 }
 }
 //++

 /*
ФУНКЦИЯ ДЛЯ ПЕРЕСТАНОВКИ СТРОК
ВХОДНЫЕ ПАРАМЕТРЫ:
   ARRAY - МАТРИЦА С КОТОРОЙ РАБОТАЕМ
   indexmax - НАЙДЕННЫЙ СТОЛБЕЦ С МАКС. ЭЛЕМЕНТОМ
   num - СТОЛБЕЦ С КОТОРЫМ БУДЕМ МЕНЯТЬ
   N - РАЗМЕР СТРОКИ
ВЫХОДНЫЕ ПАРАМЕТРЫ:
	НИЧЕГОШЕНЬКИ, ПОМЕНЯЛИ И ХВАТИТ
 */
 void SwapRows(double** ARRAY, int *VecX, int indexmax, int num, int N) {
	 double temp;
	 for (int i = num; i < N; i++) {
		 temp = ARRAY[indexmax][i];
		 ARRAY[indexmax][i] = ARRAY[num][i];
		 ARRAY[num][i] = temp;

		
		
	 }
 }
 //++

/*
ФУНКЦИЯ ДЛЯ ПОИСКА МАКСИМУМА НА ПЕРЕСЕЧЕНИИ СТРОК И СТОЛБЦОВ (i==j)
ВХОДНЫЕ ПАРАМЕТРЫ:
	ARRAY - МАТРИЦА С КОТОРОЙ РАБОТАЕМ
	NUM - НОМЕР ДИАГОНАЛИ НА КОТОРОЙ РАБОТАЕМ
	N - РАЗМЕР СТОЛБЦОВ
	M - РАЗМЕР СТРОК
ВОЗРАЩАЕМЫЕ ПАРАМЕТРЫ:
	ПУСТОТА - МЕНЯЕМ СТРОКИ/СТОЛБЦЫ
*/
 void SwapMaxRowsCols(double** ARRAY, int *VecX, int num, int N, int M) {
	 double max = 0;
	 int indexmax = 0;
	 for (int i = 0; i < M - 1; i++) {		//-1 т.к. не забываем про свободные члены
		 if (ARRAY[num][i] > max) {		//попадаем в столбец num и идем по строке
			 max = ARRAY[num][i];
			 indexmax = i;
		 }
	 }
		 bool flag = false;						//делаем флаг чтобы знать строка/столбец

	 for (int i = 0; i < N; i++) {
		if (ARRAY[i][num] > max) {		//идем по всем столбцам 
			max = ARRAY[i][num];		//попадай в num строку
			indexmax = i;						//ищем максимум
			flag = true;						//в столбце бОльший элемент
		}
	 }
		 if (flag == false) {					//максимум в строке
			 SwapCols(ARRAY, VecX, indexmax, num, N);	//меняем num столбец с максимальным столбцом 
		 }
		 else {									//максимум в строчке
			 SwapRows(ARRAY, VecX, indexmax, num, M);	//меняем num строку с максимальной строкой 
		 }
	 }
 //++

 /*
ФУНКЦИЯ ДИАГОНАЛЬНОГО ПРЕОБЛАДАНИЯ ЭЛЕМЕНТОВ МАТРИЦЫ
ВХОДНЫЕ ПАРАМЕТРЫ:
	ARRAY - МАССИВ С КОТОРЫМ РАБОТАЕМ
	N - РАЗМЕР СТОЛБЦОВ
	M - РАЗМЕР СТРОК
ВЫХОДНЫЕ ПАРАМЕТРЫ:
	ПУСТОТА - ВЫЗЫВАЕМ ФУНКЦИИ ДАЛЬШЕ
*/
 void DominateDiagonal(double** ARRAY, int *VecX, int N, int M) {
	 for (int i = 0; i < N; i++) {
		 if (fabs(SumLine(ARRAY, M, i) - *(*(ARRAY + i) + i)) > fabs(*(*(ARRAY + i) + i))) {
			 SwapMaxRowsCols(ARRAY, VecX, i, N, M);
		 }
	 }

 }

 //++
 void MinMaxRows(double** ARRAY, int N, int M) {
	 for (int i = 0; i < N; i++) {
		 if (fabs(SumLine(ARRAY, M, i) - *(*(ARRAY + i) + i)) > fabs(*(*(ARRAY + i) + i))) {

		 }
	 }
 }
 void CheckDominate(double** ARRAY, int N, int M) {
	 for (int i = 0; i < N; i++) {
		 if (fabs(SumLine(ARRAY, M, i) - *(*(ARRAY + i) + i)) < fabs(*(*(ARRAY + i) + i))) { //если не преобладание то...
			 cout << "true" << i << " ";
		 }
		 else {
			 cout << "false" << i << " ";
		 }
	 }
 }


 int main() {
	 system("color F0"); //задаем цвет консоли
	 setlocale(LC_ALL, "Russian"); //задаем язык
	 int N; //кол-во столбцов
	 int M = 1; //кол-во строк
	 int CodeError = 0; //код ошибки
	 double** ARRAY_1; //объявление первой матрицы
	 IntMatrix(&ARRAY_1, &N, &M, &CodeError, FILENAME_1);
	 int* VecX = new int[M - 1];
	 for (int i = 0; i < M - 1; i++) {
		 VecX[i] = i;
	 }
	 double* res = new double[N];
	 if (CodeError == 0) {
		 cout << "Исходные данные первого массива: ";
		 PrintArray(ARRAY_1, VecX, N, M);
		 cout << endl << "-------------------------------------------------" << endl << endl;
		 cout << NormMatrix(ARRAY_1, N, M);
		 cout << endl;
		 cout << MaxFreeTerm(ARRAY_1, N, M);
		 DominateDiagonal(ARRAY_1, VecX, N, M);
		 //SwapMaxRowsCols(ARRAY_1, 0, N, M);
		 PrintArray(ARRAY_1, VecX, N, M);
		 Res(ARRAY_1, res, N, M);
		 CheckDominate(ARRAY_1, N, M);
		 CleanMemory(ARRAY_1, N);
		 
	 }
	 else {
		 GetCode(CodeError);
	 }
 }
