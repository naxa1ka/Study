#ifndef LABA_2_SIAOD_NODE_H
#define LABA_2_SIAOD_NODE_H

template<typename T>
class Node {
public:
    T key;
    Node *parent;
    Node *left;
    Node *right;

    explicit Node(
            T key = T(),
            Node *parent = nullptr,
            Node *left = nullptr,
            Node *right = nullptr
    ) {
        this->key = key;
        this->parent = parent;
        this->left = left;
        this->right = right;
    }
};

#endif //LABA_2_SIAOD_NODE_H
