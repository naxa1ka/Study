#include<iostream>
#include <cstring>

using namespace std;

enum ACTIONS {
    NOTHING,
    PLUS,
    DOUBLE_PLUS,
    MINUS,
    DOUBLE_MINUS
};


class Boolean {
private:
    int _size;
    bool *_number;

public:
    short sizeOfNumber(int number);

    bool *decToBin(int number);

    void normalizeNumber(int newSize);

    void additionalCode();

    void Show();

    Boolean operator+(Boolean b2);

    Boolean(int number);

    Boolean(const Boolean &src);

    Boolean(int size, bool *number);

    ~Boolean();

    ACTIONS getAction(const Boolean &B, bool bi_minus1);

    //void shift(Boolean &number);

    int multiply(Boolean &firstNumber, Boolean &secondNumber);

    void reverseCode();

    bool fullShift(Boolean &B, Boolean &schp);

    int Show(Boolean &b1, Boolean &b2, bool znak);

    void shift();

    void SimpleShow();


    void showTroika(Boolean &B, bool bi_minus1);
};

Boolean::Boolean(int number) {
    bool isMinus = number < 0;
    number = abs(number);
    _size = sizeOfNumber(number);
    _number = decToBin(number);
    if (isMinus) {
        additionalCode();
    }
}

Boolean::Boolean(int size, bool *number) {
    _size = size;
    _number = number;
}


Boolean::Boolean(const Boolean &src) {
    _size = src._size;
    _number = new bool[_size];
    memcpy(_number, src._number, _size);
}

/**
 * Функция, подсчитывающая необходимое количество
 * бит, в которое поместится входное слово
 * @param number - входное слово
 * @return количество бит
 */
short Boolean::sizeOfNumber(int number) {
    unsigned int currentNumber = 1; //2^0 = 1; 2 4 16 32
    short counterBits = 0; //количество бит

    do {
        currentNumber <<= 1u;
        counterBits++;
    } while (number >= currentNumber);

    return counterBits;
}

/**
 * Перевод десятичного числа в
 * двоичное число
 * @param number - входное слово
 * @return массив результата перевода
 */
bool *Boolean::decToBin(int number) {
    const int size = _size;
    bool *bin = new bool[size + 1];

    bin[0] = number < 0;

    for (int i = size; i > 0; i--) {
        bin[i] = number % 2;
        number /= 2;
    }
    _size++;
    delete [] _number;
    return bin;
}

void Boolean::SimpleShow() {
    for (int i = 0; i < _size; ++i) {
        cout << _number[i];
    }
    cout << " ";
}

void Boolean::Show() {
    for (int i = 0; i < _size; ++i) {
        cout << _number[i];
    }
    cout << endl;
}

Boolean::~Boolean() {
    //delete[] _number;
}

void Boolean::normalizeNumber(int newSize) {
    bool znak = false;

    if (_number[0] == 1) {
        znak = true;
        additionalCode();
    }

    bool *dest = new bool[newSize];

    for (int i = 0; i < newSize; ++i) {
        dest[i] = false;
    }

    memmove(dest + sizeof(bool) * (newSize - _size),
            _number,
            sizeof(bool) * _size
    );
    //delete[] _number;
    _number = dest;
    _size = newSize;

    if (znak)
        additionalCode();
}

Boolean Boolean::operator+(Boolean b2) {
    Boolean b1 = *this;

    if (b2._size > b1._size) {
        b1.normalizeNumber(b2._size);
    } else if (b1._size > b2._size) {
        b2.normalizeNumber(b1._size);
    }

    int maxSize = max(b1._size, b2._size);

    bool *fn = b1._number;
    bool *sn = b2._number;

    bool *res = new bool[maxSize];
    bool carry = false;

    for (int i = maxSize - 1; i >= 0; i--) {
        if (fn[i] == 0 && sn[i] == 0) {
            res[i] = false | carry;
            carry = false;
        } else if ((fn[i] == 1 && sn[i] == 0) || (fn[i] == 0 && sn[i] == 1)) {
            res[i] = !carry;
        } else if (sn[i] == 1 && fn[i] == 1) {
            res[i] = carry;
            carry = true;
        }
    }

    return Boolean(maxSize, res);
}

void Boolean::reverseCode() {
    for (int i = 0; i < _size; ++i) {
        _number[i] = !_number[i];
    }
}

void Boolean::additionalCode() {
    reverseCode();
    *this = *this + Boolean(1);
}

ACTIONS action(const bool input[3]) {
    if (input[0] == 0) { //0__
        if (input[1] == 0) { //00_
            if (input[2] == 0) { //000
                return NOTHING;
            } else { //001
                return PLUS;
            }
        } else { // 01_
            if (input[2] == 0) { //010
                return PLUS;
            } else { //011
                return DOUBLE_PLUS;
            }
        }
    } else { //1__
        if (input[1] == 0) { //10_
            if (input[2] == 0) { //100
                return DOUBLE_MINUS;
            } else { //101
                return MINUS;
            }
        } else { //11_
            if (input[2] == 0) { //110
                return MINUS;
            } else { //111
                return NOTHING;
            }
        }
    }

}

ACTIONS Boolean::getAction(const Boolean &B, bool bi_minus1) {
    int size = B._size;
    bool currAction[3];
    currAction[0] = B._number[size - 2];
    currAction[1] = B._number[size - 1];
    currAction[2] = bi_minus1;
    return action(currAction);
}

void Boolean::shift() {
    memmove(_number + sizeof(bool), _number, sizeof(bool) * _size);
}

void Boolean::showTroika(Boolean &B, bool bi_minus1){
    cout << B._number[_size-2] << B._number[_size-1] << bi_minus1;
    cout << endl;
}

//++
bool Boolean::fullShift(Boolean &B, Boolean &schp) {
    int size = B._size;
    bool bi_minus1 = B._number[size - 1];
    B.shift();
    B._number[0] = schp._number[size - 1]; //берем правый бит из СЧП
    schp.shift();
    return bi_minus1;
}

int Boolean::multiply(Boolean &firstNumber, Boolean &secondNumber) {
    //знак по старшим битам двух чисел
    bool znak = firstNumber._number[0] ^secondNumber._number[0];
    //максимальный размер разрядной сетки из двух чисел
    int maxSize = max(firstNumber._size, secondNumber._size);

    //количество циклов которое потребуется для получения результата
    int counterAction = 1;
    //новый размер разрядной сетки, при котором будут образовываться нужные нам тройки операций
    int newSize = 2;
    while (newSize < maxSize) {
        newSize += 2;
        counterAction++;
    }
    //ровняем оба числа по новому размеру разрядной сетки
    secondNumber.normalizeNumber(newSize);
    secondNumber.Show();
    firstNumber.normalizeNumber(newSize);
    firstNumber.Show();

    cout << endl;

    //сумма частичных произведний равная изначально нулю
    Boolean schp(0);
    schp.normalizeNumber(newSize);

    //копируем в регистр множимое
    Boolean B(secondNumber);
    Boolean additionalNumber(firstNumber);
    additionalNumber.additionalCode();

    //действие которое будет выполняться в текущей итерации
    ACTIONS currentAction;

    //бит, который требуется для выяснения операции
    //получается путем сдвига второго регистра
    bool bi_minus1 = false;
    //счетчик проведенных операций
    int counter = 0;

    while (counter < counterAction) {
        currentAction = getAction(B, bi_minus1);
        cout << "Current action: ";
        switch (currentAction) {
            case MINUS:
                cout << "Minus\n";
                break;
            case PLUS:
                cout << "Plus\n";
                break;
            case DOUBLE_MINUS:
                cout << "DoubleMinus\n";
                break;
            case DOUBLE_PLUS:
                cout << "DoublePlus\n";
                break;
            case NOTHING:
                cout << "Nothing\n";
                break;
        }

        if (currentAction == NOTHING) {
            cout << endl;
            cout << "Before shift: \n";
            schp.SimpleShow();
            B.SimpleShow();
            B.showTroika(B, bi_minus1);

            cout << "After first shift: \n";
            bi_minus1 = fullShift(B, schp);
            schp.SimpleShow();
            B.SimpleShow();
            B.showTroika(B, bi_minus1);

            cout << "After second shift: \n";
            bi_minus1 = fullShift(B, schp);
            schp.SimpleShow();
            B.SimpleShow();
            B.showTroika(B, bi_minus1);
            cout << endl;
        } else if (currentAction == DOUBLE_PLUS || currentAction == DOUBLE_MINUS) {
            cout << endl;
            cout << "Before shift: \n";
            schp.SimpleShow();
            B.SimpleShow();
            B.showTroika(B, bi_minus1);

            cout << "After first shift: \n";
            bi_minus1 = fullShift(B, schp);
            schp.SimpleShow();
            B.SimpleShow();
            B.showTroika(B, bi_minus1);

            cout << "Summ with: \n";

            if (currentAction == DOUBLE_MINUS) {
                //firstNumber.additionalCode(); //второе число представляем в доп коде
                additionalNumber.Show();
                schp = schp + additionalNumber;
                //firstNumber.additionalCode();
            } else {
                firstNumber.Show();
                schp = schp + firstNumber;
            }
            cout << "After sum: \n";
            schp.SimpleShow();
            B.SimpleShow();
            B.showTroika(B, bi_minus1);

            cout << "After second shift: \n";
            bi_minus1 = fullShift(B, schp);
            schp.SimpleShow();
            B.SimpleShow();
            B.showTroika(B, bi_minus1);
            cout << endl;
        } else if (currentAction == PLUS || currentAction == MINUS) {
            cout << endl;
            cout << "Before sum: \n";
            schp.SimpleShow();
            B.SimpleShow();
            B.showTroika(B, bi_minus1);

            cout << "Summ with: \n";

            if (currentAction == MINUS) {
                //firstNumber.additionalCode();
                additionalNumber.Show();
                schp = schp + additionalNumber;
                //firstNumber.additionalCode();
            } else {
                firstNumber.Show();
                schp = schp + firstNumber;
            }
            cout << "After sum: \n";
            schp.SimpleShow();
            B.SimpleShow();
            B.showTroika(B, bi_minus1);

            cout << "After first shift: \n";
            bi_minus1 = fullShift(B, schp);
            schp.SimpleShow();
            B.SimpleShow();
            B.showTroika(B, bi_minus1);

            cout << "After second shift: \n";
            bi_minus1 = fullShift(B, schp);
            schp.SimpleShow();
            B.SimpleShow();
            B.showTroika(B, bi_minus1);
            cout << endl;
        }
        counter++;

    }

    if (znak) {
        B.additionalCode();
        schp.reverseCode();
    }

    return Show(schp, B, znak);
}

int Boolean::Show(Boolean &b1, Boolean &b2, bool znak) {
    int result = 0;
    int pow = 1;

    for (int i = b2._size - 1; i >= 0; i--) {
        if (b2._number[i] == 1) {
            result += pow;
        }
        pow *= 2;
    }

    for (int i = b1._size - 1; i >= 0; i--) {
        if (b1._number[i] == 1) {
            result += pow;
        }
        pow *= 2;
    }

    if (znak)
        result *= -1;

    return result;
}


int main() {
    int firstNumber;
    int secondNumber;
    cout << "Enter first number:" << endl;
    cin >> firstNumber;

    cout << "Enter second number:" << endl;
    cin >> secondNumber;

    Boolean result(0);
    Boolean fn(firstNumber);
    Boolean sn(secondNumber);

    cout << "Our result: " << endl << result.multiply(fn, sn) << endl;
    cout << firstNumber << " * " << secondNumber << " = " << endl << firstNumber * secondNumber << endl;
}