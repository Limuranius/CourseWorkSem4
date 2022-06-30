//
// Created by Gleb on 18.10.2021.
//

#ifndef RBTREEHW_RBNODE_H
#define RBTREEHW_RBNODE_H


template<typename T>
class RBNode {
public:
    T val;
    int color;  // 0 - чёрный, 1 - красный
    int count;  // счётчик количества узлов с одинаковым значением
    RBNode<T> *left;
    RBNode<T> *right;
    RBNode<T> *parent;

    RBNode(T val, int color, RBNode<T> *left, RBNode<T> *right, RBNode<T> *parent);

    RBNode();

    bool isNull() const;

    bool isRoot() const;
};


/**
 * Конструктор создания узла КЧ-дерева
 */
template<typename T>
RBNode<T>::RBNode(T val, int color, RBNode<T> *left, RBNode<T> *right, RBNode<T> *parent) {
    this->val = val;
    this->color = color;
    this->left = left;
    this->right = right;
    this->parent = parent;
    this->count = 1;
}


/**
 * Конструктор создания null-узла
 */
template<typename T>
RBNode<T>::RBNode() {
    this->color = 0;
    this->left = nullptr;
    this->right = nullptr;
    this->parent = nullptr;
    this->count = -1;
}


/**
 * Возвращает true, если узел является null-узлом КЧ-дерева
 */
template<typename T>
bool RBNode<T>::isNull() const {
    return (this->count == -1);
}


/**
 * Возвращает true, если узел является корнем КЧ-дерева
 */
template<typename T>
bool RBNode<T>::isRoot() const {
    return this->parent->isNull();
}


#endif //RBTREEHW_RBNODE_H
