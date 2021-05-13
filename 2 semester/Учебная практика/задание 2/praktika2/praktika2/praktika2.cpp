#include <iostream>
#include <fstream>
#include <iomanip>
#include <cmath>
using namespace std;

const char* FILENAME_1 = "src.txt"; //путь к исходным файлам для матрицы с диагональным преобладанием
const char* FILENAME_2 = "src2.txt"; //путь к исходным файлам для исходной матрицы

void IntMatrix(double*** ARRAY, int* SIZE, int* CodeError, const char* FILENAME);
//ввод матрицы проверка на ошибки
void GetCode(int CodeError);
//вывод ошибки по соотвествующему коду
void PrintArray(double** ARRAY, int SIZE);
//печать двумерного массива
void PrintArray(double* ARRAY, int SIZE);
//печать одномерного массива
void PrintArrayFixed(double* ARRAY, int SIZE);
//печать с высокой точностью 
void NewNormMatrix(double** ARRAY, int SIZE);
//преобразование матрицы
void NormMatrix(double** ARRAY, int SIZE, double *A);
//норма матрицы
void NormFreeTerm(double** ARRAY, int SIZE, double *F);
//норма вектора свободных членов
double SumLine(double** ARRAY, int SIZE, int row);
//сумма модулей элементо в строке
void CountIter(double** ARRAY, int SIZE, double A, double F, double Eps, int *k);
//поиск нижней границы количества итераций
void FindSolution(double** ARRAY, double** SOLUTION, int SIZE, int *iter, double Eps);
//поиск решения
double *MultipleMatrix(double** ARRAY_1, double* ARRAY_2, int SIZE);
//умножение матрицы на вектор столбец с добавлением столбца свободных членов
double MaxDelt(double* ARRAY_1, double* ARRAY_2, int SIZE, double *max);
//макисмальная разница между пред. и текущей итерацией
double Delt(double* ARRAY_1, double* ARRAY_2, int i);
//поиск модули разница между модулями пред. и текущей итерации в некотором столбце
void Variance(double** ARRAY, double* SOLUTION, int SIZE, double** VARIANCE);
//поиск невязки

 int main() {
	 system("color F0"); //задаем цвет консоли
	 setlocale(LC_ALL, "Russian"); //задаем язык
	 int SIZE; //размер матрицы
	 int CodeError = 0; //код ошибки
	 double** ARRAY; //объявление матрицы с диаг.преобладанием
	 double** ARRAYOLD; //объявление изначальной матрицы
	 double* SOLUTION; //вектор столбец решений
	 double* VARIANCE; //вектор столбец невязки
	 double A = 0; //значение нормы матрицы
	 double F = 0; //значение нормы вектора свободных членов
	 int iter = 0; //кол-во "реальных" итераций
	 int k = 0; //нижнее грань кол-ва итераций 
	 double Eps = 0.001; //требуемая тончность вычислений
	 IntMatrix(&ARRAY, &SIZE, &CodeError, FILENAME_1);
	 IntMatrix(&ARRAYOLD, &SIZE, &CodeError, FILENAME_2);
	 if (CodeError == 0) {
		 cout << "Исходная матрица A: ";
		 PrintArray(ARRAY, SIZE);
		 NewNormMatrix(ARRAY, SIZE);
		 cout << endl << "---------------------------------------------------------------------------" << endl << endl;
		 cout << "Приведенная матрица A`:" << endl << "для получения решений вида: x = A` * x + b" << endl;
		 PrintArray(ARRAY, SIZE);
		 NormMatrix(ARRAY, SIZE, &A);
		 if (A < 1) {
			 cout << endl << "Норма матрицы A = " << A << " < 1 => сходится";
		 }
		 else {
			 cout << endl << "Норма матрицы A = " << A << " > 1 => не сходится";
			 return 1;
		 }
		 NormFreeTerm(ARRAY, SIZE, &F);
		 cout << endl << "Норма вектора F = " << F;
		 CountIter(ARRAY, SIZE, A, F, Eps, &k);
		 cout << endl << "Нижняя граница количества итераций: k >= " << k << endl;
		 cout << "Необходимая точность Eps: " << Eps << endl;
		 system("pause");
		 FindSolution(ARRAY, &SOLUTION, SIZE, &iter, Eps);
		 cout << "Общее количество итераций: " << iter << endl;
		 cout << endl << "Решение удовлетворяющее условиям необходимой точности: " << endl;
		 PrintArray(SOLUTION, SIZE);
		 cout << endl << endl << "Невязка: r: А - Ax" << endl;
		 Variance(ARRAYOLD, SOLUTION, SIZE, &VARIANCE);
		 PrintArrayFixed(VARIANCE, SIZE);
	 }
	 else {
		 GetCode(CodeError);
	 }
 }

 void IntMatrix(double*** ARRAY, int* SIZE, int* CodeError, const char* FILENAME) {
	 /*
	 функция для ввода матрицы, размеров матрицы и проверки на различные ошибки
	 */
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
	 fin >> *SIZE; //считываем количество строк
	 if (*SIZE < 0) {
		 *CodeError = -6;
	 }
	 *ARRAY = new double* [*SIZE];
	 for (int i = 0; i < *SIZE; i++) {
		 *(*ARRAY + i) = new double[*SIZE+double(1)];
	 }
	 while (!fin.eof()) { //чтение элементов массива, пока элементы не закончатся
		 fin >> buff;
		 CntVec++; //подсчет количества элементов массив
	 }
	 
	 if (CntVec > *SIZE * (*SIZE+1)) { //проверка на выход за границы массива
		*CodeError = -4;
		return;
	 }
	 if (CntVec < *SIZE * (*SIZE + 1)) { //проверка на недостаток элементов 
		 *CodeError = -5;
		 return;
	 }
	 fin.seekg(0); //возврат чтения файла на самое начало

	 fin >> buff; //так как вернулись на самое начало, записываем в буффер размеры
	 while (!fin.eof()) {
		 fin >> *(*(*ARRAY + CntLine) + CntColumn); //чтение массива из файла
		 CntColumn++;
		 if (CntColumn == *SIZE+1) {
			 CntLine++;
			 CntColumn = 0;
		 }
	 }
	 fin.close(); // закрываем файл
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
 void PrintArray(double** ARRAY, int SIZE) { //печать двумерного массива
	 for (int i = 0; i < SIZE; i++) {
		 cout << endl;
		 for (int j = 0; j < SIZE+1; j++) {
				 cout << setw(15) << ARRAY[i][j];
		 }
	 }
	 cout << endl;
 }
 void PrintArray(double* ARRAY, int SIZE) { //печать одномерного массива
	 for (int i = 0; i < SIZE; i++) {
		 cout << ARRAY[i] << " ";
	 }
 }
 void PrintArrayFixed(double* ARRAY, int SIZE) { // печать с фиксированной точностью используемая для печати невязки
	 for (int i = 0; i < SIZE; i++) {
		 cout << fixed << ARRAY[i] << " ";
	 }
 } 
 void NewNormMatrix(double** ARRAY, int SIZE) {
	/*
	для получения решения нам нужно исходную матрицу преобразовать к виду x=A`x + b
	то есть мы делим строчку на коэффиценты стоящие у диагонального x
	после "переносим все в правую часть, то есть умножаем на -1
	если попадется свободный столбик со свободным членом знак оставляем
	после зануляем диагональ, т.к. мы выразили нужный нам x
	*/
	 for (int i = 0; i < SIZE; i++) {
		 for (int j = 0; j < SIZE+1; j++) {
			 if (i == j) { //если попался диагональный элемент - пропускаем, зануление будет позже
				 continue;
			 }
			 ARRAY[i][j] = -1*(ARRAY[i][j] / ARRAY[i][i]); //делим на коэффиценты стоящие у диагонального x и "переносим"
			 if (j == SIZE) {
				 ARRAY[i][j] = ARRAY[i][j] * -1; //возвращаем знак свободного члена обратно
			 }
		 } 
	 }
	 for (int k = 0; k < SIZE; k++) {   //зануляем диагональ
		 ARRAY[k][k] = 0;
	 }
 }
 void NormMatrix(double** ARRAY, int SIZE, double *A) {
	 /*
	 ищем норму матрицы:
	 нормой матрицы является максимум суммы среди всех строчек 
	 сумма ищется как сумма модулей всех элементов
	 A=max{сумма по i;|a1i|...сумма по i;|ani|}
	 используется для определения сходимости
	 */
	 for (int i = 0; i < SIZE; i++) { 
		 if (SumLine(ARRAY, SIZE, i) > *A) {
			 *A = SumLine(ARRAY, SIZE, i);
		 }
	 }
 }
 void NormFreeTerm(double** ARRAY, int SIZE, double *F) {
	 /*
	 ищем норму вектора F
	 нормой вектора является максимальной элемент
	 среди столбца свободных членов
	 F=max{|bi|}
	 */
	 for (int i = 0; i < SIZE; i++) {
		 if (fabs(ARRAY[i][SIZE]) > *F) { 
			 *F = fabs(ARRAY[i][SIZE]);
		 }
	 }
 }
 double SumLine(double** ARRAY, int SIZE, int row) {
	 /*
	 Функция суммирующая модули элементов всей строки, 
	 где row - столбец в котором нужно посчитать сумма
	 прим.(столбец свободных членов пропускается)
	 */
	 double sum = 0;
	 for (int i = 0; i < SIZE; i++) {
		 sum += fabs(ARRAY[row][i]); 
	 }
	 return sum;
 }
 void CountIter(double **ARRAY, int SIZE, double A, double F, double Eps, int *k) {
	 /*
	 функция для подсчета нижней грани количества итераций
	 A^(k+1)*F/(1-A)<=Eps 
	 где k количество итераций
	 */
	 int i = 0;
	 while ((pow(A, i + 1) * F) / (1 - A) >= Eps) {
		 i++;
	 }
	 *k = i;
 }
 void FindSolution(double** ARRAY, double** SOLUTION, int SIZE, int *iter, double Eps) {
	 /*
	 Функция для поиска решения
	 алгоритм следующий:
	 первое приближение - столбик из свободных членов преобразованной матрицы(A`)
	 после высчитываем новое решение, ищем максимальную разницу между 
	 пред. и текущим решением для проверки выхода из цикла
	 после присваем значения пред. итерации нынешней
	 */
	 *SOLUTION = new double [SIZE];
	 double *predSOLUTION = new double[SIZE];
	 double max = 0;
	 for (int i = 0; i < SIZE; i++) {
		 predSOLUTION[i] = ARRAY[i][SIZE];								  //x0 - самое первое приближение это столбик из свободных членов
	 }
	 cout << "Нулевое приближение x0: " << endl;
	 PrintArray(predSOLUTION, SIZE);
	 cout << endl << endl;
	 predSOLUTION = *SOLUTION; //x0=x1
	 do{
		 *iter = *iter + 1;
		 *SOLUTION = MultipleMatrix(ARRAY, predSOLUTION, SIZE);				  //теперь получили x1
		 MaxDelt(*SOLUTION, predSOLUTION, SIZE, &max);
		 cout << "x" << *iter << ":";
		 PrintArray(*SOLUTION, SIZE);
		 predSOLUTION = *SOLUTION; 
		 cout << endl << "maxdelt:" << max << endl << endl;
	 } while (max > Eps);
 }
double *MultipleMatrix(double** ARRAY_1, double* ARRAY_2, int SIZE) {
	 /*
	 функция для умножения матрицы A на столбец решений для
	 перехода на следующую итерацию, x^(k+1) = A' * x^k + F`
	 также добавляется столбец свободных членов по условию
	 перехода на следующую итерацию
	 функция возвращает x^k+1
	 */
	 double *buff = new double [SIZE];					//объявляем матрицу буфер, в которой будет лежать результат
	 for (int i = 0; i < SIZE; i++) {                
			buff[i] = 0;
			 for (int j = 0; j < SIZE; j++) {		    //умножаем исходную матрицу A
				 buff[i] += ARRAY_1[i][j] * ARRAY_2[j]; //на вектор столбец решений прошлых итераций
			 }											//и сохраняем в buff матрицу
	 }													//
	 for (int i = 0; i < SIZE; i++) {
		 buff[i] = buff[i] + ARRAY_1[i][SIZE];
	 }										 
	 return buff; 
 }
double MaxDelt(double* ARRAY_1, double *ARRAY_2, int SIZE, double *max) {
	/*
	функция для поиска максимальной дельты 
	максимальная дельта - это максимальная разница между
	текущим и прошлым решением
	данное число является условием для выхода из цикла
	*/
	*max = Delt(ARRAY_1, ARRAY_2, 0);
	for (int i = 1; i < SIZE; i++) {
		if (Delt(ARRAY_1, ARRAY_2, i) > *max) {
			*max = Delt(ARRAY_1, ARRAY_2, i);       //ищем самую большую дельту
		}
	}
	return *max;
}
double Delt(double* ARRAY_1, double* ARRAY_2, int i) {
	/*модуль разницы модулей между пред. и текущей итерацией */
	return fabs(fabs(ARRAY_1[i]) - fabs(ARRAY_2[i]));
}
void Variance(double** ARRAY, double* SOLUTION, int SIZE, double **VARIANCE) {
	/*
	вычисление невязки - расхождение приближенного равенства
	r = F - Ax, где x - конечный вектор столбец решений,
	F - первоначальный вектор столбец свободных членов
	A - первоначальная матрица
	функция возвращает вектор столбец с невязками по каждому иксу
	*/
	double* buff = new double[SIZE];
	*VARIANCE = new double[SIZE];
	buff = MultipleMatrix(ARRAY, SOLUTION, SIZE);
	for (int i = 0; i < SIZE ; i++) {		//т.к. в умножении матрицы мы добавляем столбец 
		buff[i] = buff[i] - ARRAY[i][SIZE]; //свободных членов вычитаем его для получения
	}										//верного результата
	for (int i = 0; i < SIZE; i++) {
		*(*VARIANCE + i) = ARRAY[i][SIZE] - buff[i];
	}
}