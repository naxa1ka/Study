#include <string>
#include <fstream>
#include <iostream>

using namespace std;

const char* FILENAME_1 = "tests_1/src11.txt"; //путь к исходным файлам для 1 матрицы
const char* FILENAME_2 = "tests_1/src11.txt"; //путь к исходным файлам для 2 матрицы

//	* -------------------------------------------------------------------------------------------------------- *
//								Н Е К О Р Р Е К Т Н Ы Е  Т Е С Т Ы
//						  src0.txt  - тест на отсутствие файла
//						  src1.txt  - тест на пустой файл
//						  src2.txt  - тест на неккоректные символы при вводе (буквы)
//						  src3.txt  - тест на количество входных элементов > размера матрицы
//						  src4.txt  - тест на количество входных элементов < размера матрицы
//						  src13.txt - тест на отрицательные размеры матрицы (N<0)
//						  src14.txt - тест на отрицательные размеры матрицы (M<0)
//
//								  К О Р Р Е К Т Н Ы Е  Т Е С Т Ы 
//						  src5.txt  - тест на размер матрицы = количество входных элементов
//
//						  src6.txt  - тест без положительных элементов в матрице
//						  src7.txt  - тест с одним положительным элементов в матрице
//						  src8.txt  - тест с несколькими одинаковыми максимумами
//
//						  src9.txt  - тест для проверки перестановок с нечетным количеством столбцов
//						  src10.txt - тест для проверки перестановок с четным количеством столбцов
//
//						  src11.txt - тест с размерами матрицами: ARRAY1 - 5 8; ARRAY2 - 4 7
//						  src12.txt - тест с размерами матрицами: ARRAY1 - 6 9; ARRAY2 - 3 6
//
//	* -------------------------------------------------------------------------------------------------------- *	

void PrintArray(int** ARRAY, int N, int M); //печать массива
void MaxArray(int** ARRAY, int N, int M);  //поиск максимума среди строк в которых есть хотя бы один положительный элемент
void SwapArray(int** ARRAY, int N, int M); //замена строк четных и нечетных номеров
void GetCode(int code);
void CleanMemory(int** ARRAY, int N);
void IntMatrix(int*** ARRAY, int* N, int* M, int* CodeError, const char* FILENAME); //проверка на ошибки и ввод

int main() {
	system("color F0"); //задаем цвет консоли
	setlocale(LC_ALL, "Russian"); //задаем язык
	int N; //размеры матрицы
	int M; //размеры матрицы
	int CodeError = 0; //код ошибки
	int** ARRAY_1; //объявление первой матрицы
	int** ARRAY_2; //объявление второй матрицы

	IntMatrix(&ARRAY_1, &N, &M, &CodeError, FILENAME_1);
	if (CodeError == 0) {
		cout << "Исходные данные первого массива: ";
		PrintArray(ARRAY_1, N, M);
		SwapArray(ARRAY_1, N, M);
		cout << endl << "Массив после перестановки столбцов(первый - последний, второй - предпоследний и тп): ";
		PrintArray(ARRAY_1, N, M);
		MaxArray(ARRAY_1, N, M);
		cout << endl << "-------------------------------------------------" << endl << endl;
		CleanMemory(ARRAY_1, N);
	}
	else {
		GetCode(CodeError);
	}

	CodeError = 0;

	IntMatrix(&ARRAY_2, &N, &M, &CodeError, FILENAME_2);
	if (CodeError == 0) {
		cout << "Исходные данные первого массива: ";
		PrintArray(ARRAY_2, N, M);
		SwapArray(ARRAY_2, N, M);
		cout << endl << "Массив после перестановки столбцов(первый - последний, второй - предпоследний и тп): ";
		PrintArray(ARRAY_2, N, M);
		MaxArray(ARRAY_2, N, M);
		cout << endl << "-------------------------------------------------" << endl << endl;
		CleanMemory(ARRAY_2, N);
	}
	else {
		GetCode(CodeError);
	}

}


void CleanMemory(int** ARRAY, int N) { //освобождаем память
	for (int i = 0; i < N; i++) {
		delete[] ARRAY[i];
	}

	delete[] ARRAY;
}

void PrintArray(int** ARRAY, int N, int M) { //печать массива
	for (int i = 0; i < N; i++) {
		cout << endl;
		for (int j = 0; j < M; j++) {
			cout << *(*(ARRAY + i) + j) << " ";
		}
	}
	cout << endl;
}
void MaxArray(int** ARRAY, int N, int M) {
	cout << endl;
	int max = 0; //т.к. просят найти максимум среди положительных чисел ставим изначальное значение максимума = 0 
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) { //если некоторый элемент больше изначального максимума, то его сохраняем
			if (*(*(ARRAY + i) + j) > max) {  //и после нам не обязательно проверять положительный ли след. элемент,
				max = *(*(ARRAY + i) + j);    //так как новый записанный максимум уже больше нуля
			}
		}
	}
	if (max == 0) {
		cout << "Все элементы отрицательны! Максимума нет!";
	}
	else {
		cout << "Максимум среди положительных элементов в строке: " << max;
	}
	cout << endl;
}
void SwapArray(int** ARRAY, int N, int M) {
	int buff; //временная переменная
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M / 2; j++) {
			buff = *(*(ARRAY + i) + j);
			*(*(ARRAY + i) + j) = *(*(ARRAY + i) + M - 1 - j);
			*(*(ARRAY + i) + M - 1 - j) = buff;
		}
	}
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
	case -6:
		cout << "Ошибка! Входные данные должны быть положительными!" << endl << endl;
		break;
	}
}
void IntMatrix(int*** ARRAY, int* N, int* M, int* CodeError, const char* FILENAME) {
	ifstream fin; //создаем объект класса ifstream
	fin.open(FILENAME); //открываем файл
	int CntVec = 0; //счетчик реального размера массива
	int CntLine = 0; //счетчик для ввода
	int CntColumn = 0; //счетчик для ввода
	int buff; // буффер для проверки корректности вводимых данных

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

	fin >> *N; //считываем размеры
	fin >> *M; //считываем размеры

	if ((*N < 0) || (*M < 0)) {
		*CodeError = -6;
		return;
	}

	*ARRAY = new int* [*N];
	for (int i = 0; i < *N; i++) {
		*(*ARRAY + i) = new int[*M];
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

