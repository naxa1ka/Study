#include <iostream>
#include <iomanip> 
#include <math.h>
using namespace std;

double f(double x) {
    //-x^3-2*x^2-4*x+10
    return -pow(x, 3) - 2 * pow(x, 2) - 4 * x + 10;
}

double df(double x) {
    //-3x^2-4x-4
    return -3 * pow(x, 2) - 4 * x - 4;
}

double d2f(double x) {
    //-6x-4
    return -6 * x - 4;
}

void find(double a, double b, double eps) {
    int iteration = 0;
    double x0; // первое приближение
    double xn;
    if (a > b) { //если пользователь перепутал границы местами
        x0 = a;  //x0 используется как временная переменная
        a = b;   //для замены местами концов отрезков
        b = x0;
    }
    
    if ((f(a) * f(b)) > 0) {
        cout << "Ошибка! Нет корней в данном интервале!";
        return;
    }
    if (f(a) * d2f(a) > 0) {
        x0 = a;
    }
    else {
        x0 = b;
    }
    xn = x0 - (f(x0) / df(x0)); //высчитываем первое приближение
    cout << "Первоначальное приближение x0 = " << xn << " " << endl;
    while(fabs(x0-xn)>eps){
        x0 = xn;
        xn = x0 - (f(x0) / df(x0));
        iteration++;
        cout << "iteration: " << iteration;
        cout << " |";
        cout << " x: " << setprecision(15) << xn << endl;
    } 
}

int main()
{
    system("color F0");
    setlocale(LC_ALL, "Russian");
    double a;
    double b;
    double eps;
    cout << "Введите a для отрезка [a,b]: " << endl;
    cin >> a;
    cout << "Введите b для отрезка [a,b]: " << endl;
    cin >> b;
    cout << "Введите необходимую точность: ";
    cin >> eps;
    find(a,b,eps);
    return 1;
}
