//
// Created by Gleb on 18.10.2021.
//

#ifndef RBTREEHW_RBNODE_H
#define RBTREEHW_RBNODE_H
#include "List.h"

template<typename T1, typename T2>
class RBNode {
public:
    T1 val;
    List<T2> chain;
    int color;  // 0 - чёрный, 1 - красный
    RBNode<T1, T2> *left;
    RBNode<T1, T2> *right;
    RBNode<T1, T2> *parent;

    RBNode(T1 val, T2 val_2, int color, RBNode<T1, T2> *left, RBNode<T1, T2> *right, RBNode<T1, T2> *parent);

    RBNode();

    bool isNull() const;

    bool isRoot() const;

    void add_to_chain(T2 value);
};


/**
 * Конструктор создания узла КЧ-дерева
 */
template<typename T1, typename T2>
RBNode<T1, T2>::RBNode(T1 val, T2 val_2, int color, RBNode<T1, T2> *left, RBNode<T1, T2> *right, RBNode<T1, T2> *parent) {
    this->val = val;
    this->color = color;
    this->left = left;
    this->right = right;
    this->parent = parent;
    this->chain.insert(val_2);
}


/**
 * Конструктор создания null-узла
 */
template<typename T1, typename T2>
RBNode<T1, T2>::RBNode() {
    this->color = 0;
    this->left = nullptr;
    this->right = nullptr;
    this->parent = nullptr;
}


/**
 * Возвращает true, если узел является null-узлом КЧ-дерева
 */
template<typename T1, typename T2>
bool RBNode<T1, T2>::isNull() const {
    return (this->left == nullptr && this->right == nullptr);
}


/**
 * Возвращает true, если узел является корнем КЧ-дерева
 */
template<typename T1, typename T2>
bool RBNode<T1, T2>::isRoot() const {
    return this->parent->isNull();
}

/**
 * Добавляет значение value в цепочку узла
 */
template<typename T1, typename T2>
void RBNode<T1, T2>::add_to_chain(T2 value) {
    this->chain.insert(value);
}


#endif //RBTREEHW_RBNODE_H
