// ConsoleApplication4.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

using namespace std;
#include <iostream>

int main()
{
    int const size = 10;
    int arr[size][size] = {0};
    int i = 2;// строки
    int j = 1;// столбцы
    int counter = 0;
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            arr[i][j] = rand() % 10;
        }
    }
    //arr[i][j] <=> *(*(arr+i)+j) 2 * size 
    cout << endl << (arr + i*size+j) << endl;
    cout << endl << *arr << endl;
    cout << endl << *arr << endl;
    /*
    cout << endl << "arr: " << arr << endl;
    cout << endl << "*arr: " << *arr << endl;
    cout << endl << "**arr: " << **arr << endl;

    cout << endl;

    cout << endl << "arr + 2: " << arr + 2 << endl;
    cout << endl << "*arr + 2: " << *arr + 2 << endl;
    cout << endl << "**arr + 5: " << **arr + 2 << endl;

    cout << endl;

    cout << endl << "*(arr + 2): " << *(arr + 2) << endl;
    cout << endl << "(*(arr + 2) + 3): " << (*(arr + 2) + 3) << endl;
    cout << endl << "*(*(arr + 2) + 3): " << *(*(arr + 2) + 3) << endl;

    cout << endl;

    cout << endl << "**(arr + 2): " << **(arr + 2) << endl;
    */
    for (int i = 0; i < 10; i++) {
        cout << endl;
        for (int j = 0; j < 10; j++) {
            cout << counter << " [" << i << "][" << j <<"]: " << *arr[i][j] << " | ";
            counter++;
        }
    }
    
}


