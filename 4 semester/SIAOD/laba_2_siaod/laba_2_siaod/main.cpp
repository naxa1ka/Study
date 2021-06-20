#include <iostream>
#include <windows.h>
#include "Tree.cpp"
/*
 * Реализовать функции
 * вставки insert()
 * поиска search()
 * удаления узла remove()
 * обхода дерева inorderTraversal()   - обход узлов в отсортированном порядке
 *               preorderTraversal()  - обход узлов в порядке: вершина, левое поддерево, правое поддерево,
 *               postorderTraversal() - обход узлов в порядке: левое поддерево, правое поддерево, вершина
 * вывода дерева на экран print()
 * нахождения высоты дерева getHeight()
 *            количества узлов getSize()
 * подсчитать количество согласных на 2-3 уровнях - count()
 */
using namespace std;

int main() {
    SetConsoleOutputCP(CP_UTF8);
    setlocale(LC_ALL, "ru");
    Tree<char> tree;
    tree.insert('а');
    /*
    Tree<int> tree;
    tree.insert(8);
    tree.insert(3);
    tree.insert(6);
    tree.insert(17);
    tree.insert(10);
    tree.insert(14);
    tree.insert(13);
    tree.insert(4);
    tree.insert(7);
    tree.insert(15);
    tree.insert(1);

    tree.print();
    tree.inorderTraversal();
    cout << endl;
    tree.preorderTraversal();
    cout << endl;
    tree.postorderTraversal();
    cout << endl;
    tree.search(10);
    tree.remove(17);
    tree.print();

    cout << "Even numbers on 2||3 level: " << tree.count() << endl;
    cout << "Height: " << tree.getHeight() << endl;
    cout << "Size: " << tree.getSize() << endl;
    */
    return 0;
}
