#include "Tree.h"
#include <iostream>
#include <iomanip>
#include <queue>

using namespace std;

template<typename T>
Tree<T>::Tree() {
    SIZE = 0;
    ROOT = nullptr;
}

template<typename T>
Tree<T>::~Tree() {
    remove(ROOT);
}

template<typename T>
int Tree<T>::getSize() {
    return SIZE;
}

template<typename T>
int Tree<T>::getHeight() {
    return getHeight(ROOT);
}

template<typename T>
int Tree<T>::getHeight(Node<T> *parent) {
    if (!parent) return 0;

    return 1 + max(getHeight(parent->left), getHeight(parent->right));
}

template<typename T>
void Tree<T>::inorderTraversal() {
    if (!ROOT) {
        cout << "Tree is empty!" << endl;
        return;
    }
    inorderTraversal(ROOT);
}

template<typename T>
void Tree<T>::inorderTraversal(Node<T> *parent) {
    if (parent != nullptr) {
        inorderTraversal(parent->left);
        cout << parent->key << " ";
        inorderTraversal(parent->right);
    }
}

template<typename T>
void Tree<T>::preorderTraversal() {
    if (!ROOT) {
        cout << "Tree is empty!" << endl;
        return;
    }
    preorderTraversal(ROOT);
}

template<typename T>
void Tree<T>::preorderTraversal(Node<T> *parent) {
    if (parent != nullptr) {
        cout << parent->key << " ";
        preorderTraversal(parent->left);
        preorderTraversal(parent->right);
    }
}

template<typename T>
void Tree<T>::postorderTraversal() {
    if (!ROOT) {
        cout << "Tree is empty!" << endl;
        return;
    }
    postorderTraversal(ROOT);
}

template<typename T>
void Tree<T>::postorderTraversal(Node<T> *parent) {
    if (parent != nullptr) {
        preorderTraversal(parent->left);
        preorderTraversal(parent->right);
        cout << parent->key << " ";
    }
}

template<typename T>
void Tree<T>::print() {
    if (!ROOT) {
        cout << "Tree is empty!" << endl;
        return;
    }
    print(ROOT, 0);
}

template<typename T>
void Tree<T>::print(Node<T> *parent, int indent) {
    if (parent != nullptr) {
        if (parent->right) {
            print(parent->right, indent + 4);
        }

        if (indent) {
            cout << setw(indent) << ' ';
        }

        if (parent->right) {
            cout << " /\n" << setw(indent) << ' ';
        }

        cout << parent->key << "\n ";

        if (parent->left) {
            cout << setw(indent) << ' ' << " \\\n";
            print(parent->left, indent + 4);
        }
    }
}

template<typename T>
void Tree<T>::print(Node<T> *node) {
    cout << "key: " << node->key << endl;

    cout << "left: ";
    if (node->left != nullptr) {
        cout << node->left->key << endl;
    } else {
        cout << "nullptr" << endl;
    }

    cout << "right: ";
    if (node->right != nullptr) {
        cout << node->right->key << endl;
    } else {
        cout << "nullptr" << endl;
    }
}

/************************************/

template<typename T>
void Tree<T>::insert(T key) {
    if (!ROOT) { //если дерево пустое
        ROOT = new Node<T>(key, nullptr, nullptr, nullptr);
        SIZE++;
        return;
    }

    Node<T> *parent = ROOT;

    while (parent != nullptr) {
        if (key > parent->key) {
            if (parent->right == nullptr) {
                parent->right = new Node<T>(key, parent, nullptr, nullptr);
                break;
            } else {
                parent = parent->right;
            }
        } else {
            if (parent->left == nullptr) {
                parent->left = new Node<T>(key, parent, nullptr, nullptr);
                break;
            } else {
                parent = parent->left;
            }
        }
    }
    SIZE++;
}

/************************************/

template<typename T>
void Tree<T>::search(T key) {
    Node<T> *res = search(ROOT, key);
    if (!res) {
        cout << "Not found!";
        return;
    }

    print(res);
}


/**
 * Для каждого узла функция сравнивает значение его ключа с искомым ключом.
 * Если ключи одинаковы, то функция возвращает текущий узел,
 * в противном случае функция вызывается рекурсивно для левого или правого поддерева.
 */
template<typename T>
Node<T> *Tree<T>::search(Node<T> *parent, T key) {
    if ((!parent) || (parent->key == key))
        return parent;

    if (key < parent->key)
        return search(parent->left, key);
    else
        return search(parent->right, key);
}

/************************************/

template<typename T>
void Tree<T>::remove(T key) {
    Node<T> *v = search(ROOT, key);
    remove(v);
}

/**
 * Для удаления узла из бинарного дерева поиска нужно рассмотреть три возможные ситуации.
 * 1) Если у узла нет дочерних узлов, то у его родителя нужно просто заменить указатель на null.
 *
 * 2) Если у узла есть только один дочерний узел,
 * то нужно создать новую связь между родителем удаляемого узла и его дочерним узлом.
 *
 * 3) Если у узла два дочерних узла, то нужно найти следующий за ним элемент
 * (у этого элемента не будет левого потомка), его правого потомка подвесить
 * на место найденного элемента, а удаляемый узел заменить найденным узлом.
 * Таким образом, свойство бинарного дерева поиска не будет нарушено.
 */

template<typename T>
void Tree<T>::remove(Node<T> *v) {
    Node<T> *p = v->parent;                                  // предок удаляемого элемента
    if ((v->left == nullptr) && (v->right == nullptr)) {  // первый случай: удаляемый элемент - лист
        if (p->left == v) {
            delete (p->left);
            //p->left = nullptr;
        }
        if (p->right == v) {
            delete (p->right);
            // p->right = nullptr;
        }
    } else if ((v->left == nullptr) || (v->right == nullptr)) { // второй случай: удаляемый элемент имеет одного потомка
        if (v->left == nullptr) {
            if (p->left == v) {
                p->left = v->right;
            } else {
                p->right = v->right;
            }
            v->right->parent = p;
        } else {
            if (p->left == v) {
                p->left = v->left;
            } else {
                p->right = v->left;
            }
            v->left->parent = p;
        }
    } else {                                    // третий случай: удаляемый элемент имеет двух потомков
        Node<T> *successor = next(v->key);
        v->key = successor->key;
        if (successor->parent->left == successor) {
            successor->parent->left = successor->right;
            if (successor->right != nullptr) {
                successor->right->parent = successor->parent;
            }
        } else {
            successor->parent->right = successor->right;
            if (successor->right != nullptr) {
                successor->right->parent = successor->parent;
            }
        }
    }
}

/**
 * Если у узла есть правое поддерево, то следующий за ним элемент будет минимальным элементом в этом поддереве
 * Если у него нет правого поддерева, то нужно следовать вверх, пока не встретим узел,
 */

template<typename T>
Node<T> *Tree<T>::next(T key) {
    Node<T> *current = ROOT;
    Node<T> *successor = nullptr;

    while (current != nullptr) {
        if (current->key > key) {
            successor = current;
            current = current->left;
        } else {
            current = current->right;
        }
    }

    return successor;
}

template<typename T>
int Tree<T>::count() {
    int counter = 0;
    //string soglasnie = "abcdfghklmnprstvwxz";
    queue<Node<T> *> tmp_queue;
    Node<T> *node;

    if (ROOT == NULL)
        return 0;

    tmp_queue.push(ROOT);
    while (!tmp_queue.empty()) {
        int maximum = getHeight(ROOT);
        node = tmp_queue.front();
        tmp_queue.pop();
        int level = maximum - getHeight(node) + 1;
        if(level == 2 || level == 3){
            if (node->key % 2 == 1) counter++;
            //for (int i = 0; i < soglasnie.size()-1; ++i) {
               // if(node->key == soglasnie[i]){
                //    counter++;
              //      break;
              //  }
            //}
        }
        cout << "Level = " << maximum - getHeight(node) + 1 << " Data = " << node->key << endl;

        if (node->left) {
            tmp_queue.push(node->left);
        }
        if (node->right) {
            tmp_queue.push(node->right);
        }

    }
    return counter;
}

/************************************/