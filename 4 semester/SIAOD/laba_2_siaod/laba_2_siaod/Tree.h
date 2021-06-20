#include "Node.h"
#ifndef LABA_2_SIAOD_TREE_H
#define LABA_2_SIAOD_TREE_H

template<typename T>
class Tree {
public:
    Tree();

    ~Tree();

    int getSize();
    int getHeight();

    void inorderTraversal();

    void preorderTraversal();

    void postorderTraversal();

    void print();

    void insert(T key);

    void search(T key);

    void remove(T key);

    int count();
private:
    Node<T> *ROOT; //корень

    int SIZE;

    int getHeight(Node<T> *parent);

    void inorderTraversal(Node<T> *parent);

    void preorderTraversal(Node<T> *parent);

    void postorderTraversal(Node<T> *parent);

    void print(Node<T> *node);

    void print(Node<T> *parent, int indent);

    Node<T> *search(Node<T> *parent, T key);

    void remove(Node<T> *v);

    Node<T> *next(T key);
};

#endif //LABA_2_SIAOD_TREE_H

