#pragma once

#include "RBNode.h"
#include <vector>
#include <iostream>

template<typename T>
class RBTree {
public:
    RBNode<T> *root;

    RBTree();

    explicit RBTree(std::vector<T> values);

    bool isEmpty();

    void add(T val);

    RBNode<T> *find(T val) const;

    void remove(T val);

    void clear();

    T max() const;

    T min() const;

    void preOrderTraversal();

    void postOrderTraversal();

    void inOrderTraversal();

    void reverseInOrderTraversal();

    void print(RBNode<T> *q, long n);

    bool has(T val) const;

    std::vector<T> to_vector();

private:
    RBNode<T> *nullNode;

    void rightRotate(RBNode<T> *x);

    void leftRotate(RBNode<T> *x);

    void balanceAdd(RBNode<T> *z);

    RBNode<T> *getMaxLeft(RBNode<T> *node) const;

    RBNode<T> *getMinRight(RBNode<T> *node) const;

    void transplant(RBNode<T> *u, RBNode<T> *v);

    void balanceRemove(RBNode<T> *x);

    void preOrderTraversal(RBNode<T> *curr);

    void postOrderTraversal(RBNode<T> *curr);

    void inOrderTraversal(RBNode<T> *curr);

    void reverseInOrderTraversal(RBNode<T> *curr);

    void to_vector_traversal(RBNode<T> *curr, std::vector<T>& vect);
};


/**
 * Конструктор пустого КЧ-дерева
 */
template<typename T>
RBTree<T>::RBTree() {
    this->nullNode = new RBNode<T>();
    this->root = nullNode;
}


/**
 * Конструктор КЧ-дерева с заданными элементами values
 * @param values  Массив элементов, которые последовательно добавятся в дерево
 */
template<typename T>
RBTree<T>::RBTree(std::vector<T> values) {
    this->nullNode = new RBNode<T>();
    this->root = nullNode;
    for (T val: values) {
        this->add(val);
    }
};


/**
 * Возвращает true, если дерево пустое
 */
template<typename T>
bool RBTree<T>::isEmpty() {
    return this->root == nullNode;
}


/**
 * Делает правый поворот вокруг узла x
 * @param x  Узел, вокруг которого поворачиваем
 */
template<typename T>
void RBTree<T>::rightRotate(RBNode<T> *x) {
    RBNode<T> * y;

    y = x->left;
    x->left = y->right;
    if (!y->right->isNull()) {
        y->right->parent = x;
    }
    y->parent = x->parent;
    if (x->isRoot()) {
        this->root = y;
    }
    else if (x == x->parent->right) {
        x->parent->right = y;
    }
    else {
        x->parent->left = y;
    }
    y->right = x;
    x->parent = y;
}


/**
 * Делает левый поворот вокруг узла x
 * @param x  Узел, вокруг которого поворачиваем
 */
template<typename T>
void RBTree<T>::leftRotate(RBNode<T> *x) {
    RBNode<T> * y;

    y = x->right;
    x->right = y->left;
    if (!y->left->isNull()) {
        y->left->parent = x;
    }
    y->parent = x->parent;
    if (x->isRoot()) {
        this->root = y;
    }
    else if (x == x->parent->left) {
        x->parent->left = y;
    }
    else {
        x->parent->right = y;
    }
    y->left = x;
    x->parent = y;
}


/**
 * Добавляет в дерево узел со значением val
 * @param val  Значение, которое хотим добавить
 */
template<typename T>
void RBTree<T>::add(T val) {
    RBNode<T> * z = new RBNode<T>(val, 1, nullNode, nullNode, nullNode);
    RBNode<T> * y = nullNode;
    RBNode<T> * x = this->root;
    while (x != nullNode) {
        y = x;
        if (z->val < x->val) {
            x = x->left;
        } else if (z->val > x->val) {
            x = x->right;
        } else {
//            x->count += 1;  Убрал увеличение счётчика, чтобы узлы удалялись с первого раза
            return;
        }
    }
    z->parent = y;
    if (y == nullNode) {
        this->root = z;
    } else if (z->val < y->val) {
        y->left = z;
    } else {
        y->right = z;
    }
    balanceAdd(z);
}




/**
 * Балансирует дерево после добавления узла
 * @param node  Узел, вокруг которого балансируем
 */
template<typename T>
void RBTree<T>::balanceAdd(RBNode<T> *z) {
    while (z->parent->color == 1) {
        if (z->parent == z->parent->parent->left) {
            RBNode<T> *y = z->parent->parent->right;
            if (y->color == 1) {
                z->parent->color = 0;
                y->color = 0;
                z->parent->parent->color = 1;
                z = z->parent->parent;
            }
            else {
                if (z == z->parent->right) {
                    z = z->parent;
                    leftRotate(z);
                }
                z->parent->color = 0;
                z->parent->parent->color = 1;
                rightRotate(z->parent->parent);
            }
        }
        else {
            RBNode<T> *y = z->parent->parent->left;
            if (y->color == 1) {
                z->parent->color = 0;
                y->color = 0;
                z->parent->parent->color = 1;
                z = z->parent->parent;
            }
            else {
                if (z == z->parent->left) {
                    z = z->parent;
                    rightRotate(z);
                }
                z->parent->color = 0;
                z->parent->parent->color = 1;
                leftRotate(z->parent->parent);
            }
        }
    }
    this->root->color = 0;
}


/**
 * Ищет узел со значением val. Если такого нет, то возвращает null-узел
 * @param val  Значение, которое ищем
 * @return  Указатель на узел, если такой имеется, и null-узел, если значения val в дереве нет
 */
template<typename T>
RBNode<T> *RBTree<T>::find(T val) const {
    RBNode<T> *curr = this->root;
    while (val != curr->val and !curr->isNull()) {
        if (val < curr->val) {
            curr = curr->left;
        } else {
            curr = curr->right;
        }
    }
    return curr;
}


/**
 * У узла node находит максимальный узел слева
 * @param node  Узел, у которого ищем максимальный слева
 * @return  Указатель на максимальный слева узел
 */
template<typename T>
RBNode<T> *RBTree<T>::getMaxLeft(RBNode<T> *node) const {
    RBNode<T> *curr = node->left;
    while (curr->right != nullNode) {
        curr = curr->right;
    }
    return curr;
}


/**
 * У узла node находит минимальный узел справа
 * @param node  Узел, у которого ищем минимальный справа
 * @return  Указатель на минимальный справа узел
 */
template<typename T>
RBNode<T> *RBTree<T>::getMinRight(RBNode<T> *node) const {
    RBNode<T> *curr = node->right;
    while (curr->left != nullNode) {
        curr = curr->left;
    }
    return curr;
}


/**
 * Заменяет в дереве узел u на узел v
 * @param u  Узел, который заменяем
 * @param v  Узел, на который заменяем
 */
template<typename T>
void RBTree<T>::transplant(RBNode<T> *u, RBNode<T> *v) {
    if (u->isRoot()) {
        this->root = v;
    } else if (u == u->parent->left) {
        u->parent->left = v;
    } else {
        u->parent->right = v;
    }
    v->parent = u->parent;
}


/**
 * Удаляет узел со значением value из дерева
 * Если узлов с таким значением в дереве несколько, то уменьшает счётчик таких узлов
 * @param value  Значение, которое удаляем
 */
template<typename T>
void RBTree<T>::remove(T value) {
    RBNode<T> *z = this->find(value);
    if (z->isNull()) {  // Если такого значения нет в дереве
        std::cout << "Not found" << std::endl;
        return;
    }
    if (z->count > 1) {  // Если у узла есть дубликаты
        z->count -= 1;
        return;
    }
    if (z->isRoot()  && z->left->isNull() && z->right->isNull()) {
        this->root = nullNode;
        return;
    }

    RBNode<T> *y = z;
    RBNode<T> *x;
    int yOriginalColor = y->color;
    if (z->left->isNull()) {
        x = z->right;
        this->transplant(z, z->right);
    } else if (z->right->isNull()) {
        x = z->left;
        this->transplant(z, z->left);
    } else {
        y = this->getMaxLeft(z);
        yOriginalColor = y->color;
        x = y->left;
        if (y->parent == z) {
            x->parent = y;
        } else {
            transplant(y, y->left);
            y->left = z->left;
            y->left->parent = y;
        }
        transplant(z, y);
        y->right = z->right;
        y->right->parent = y;
        y->color = z->color;
    }
    if (yOriginalColor == 0) {
        balanceRemove(x);
    }
}


/**
 * Балансирует дерево после удаления узла
 * @param x  Узел, начиная с которого балансируем дерево
 */
template<typename T>
void RBTree<T>::balanceRemove(RBNode<T> *x) {
    while (!x->isRoot() and x->color == 0) {
        if (x == x->parent->left) {  // Узел слева
            RBNode<T> *w = x->parent->right;
            if (w->color == 1) {
                w->color = 0;
                x->parent->color = 1;
                leftRotate(x->parent);
                w = x->parent->right;
            }
            if (w->left->color == 0 and w->right->color == 0) {
                w->color = 1;
                x = x->parent;
            } else {
                if (w->right->color == 0) {
                    w->left->color = 0;
                    w->color = 1;
                    this->rightRotate(w);
                    w = x->parent->right;
                }

                w->color = x->parent->color;
                x->parent->color = 0;
                w->right->color = 0;
                this->leftRotate(x->parent);
                x = this->root;
            }
        } else {  // Узел справа
            RBNode<T> *w = x->parent->left;
            if (w->color == 1) {
                w->color = 0;
                x->parent->color = 1;
                rightRotate(x->parent);
                w = x->parent->left;
            }
            if (w->left->color == 0 and w->right->color == 0) {
                w->color = 1;
                x = x->parent;
            } else {
                if (w->left->color == 0) {
                    w->right->color = 0;
                    w->color = 1;
                    this->leftRotate(w);
                    w = x->parent->left;
                }

                w->color = x->parent->color;
                x->parent->color = 0;
                w->left->color = 0;
                this->rightRotate(x->parent);
                x = this->root;
            }
        }
    }
    x->color = 0;
}


/**
 * Очищает дерево
 */
template<typename T>
void RBTree<T>::clear() {
    while (!this->isEmpty()) {
        this->remove(this->root->val);
    }
}


/**
 * Находит максимальное значение в дереве
 * @return  Максимальное значение дерева
 */
template<typename T>
T RBTree<T>::max() const {
    RBNode<T> *curr = this->root;
    while (!curr->right->isNull()) {
        curr = curr->right;
    }
    return curr->val;
}


/**
 * Находит минимальное значение в дереве
 * @return  Минимальное значение дерева
 */
template<typename T>
T RBTree<T>::min() const {
    RBNode<T> *curr = this->root;
    while (!curr->left->isNull()) {
        curr = curr->left;
    }
    return curr->val;
}


/**
 * Прямой обход (корень, левый, правый)
 */
template<typename T>
void RBTree<T>::preOrderTraversal(RBNode<T> *curr) {
    if (curr == nullNode) {
        return;
    }
    std::cout << curr->val << " ";
    preOrderTraversal(curr->left);
    preOrderTraversal(curr->right);
}

template<typename T>
void RBTree<T>::preOrderTraversal() {
    this->preOrderTraversal(this->root);
    std::cout << std::endl;
}


/**
 * Обратный обход (левый, правый, корень)
 */
template<typename T>
void RBTree<T>::postOrderTraversal(RBNode<T> *curr) {
    if (curr == nullNode) {
        return;
    }
    postOrderTraversal(curr->left);
    postOrderTraversal(curr->right);
    std::cout << curr->val << " ";
}

template<typename T>
void RBTree<T>::postOrderTraversal() {
    this->postOrderTraversal(this->root);
    std::cout << std::endl;
}


/**
 * Симметричный обход (левый, корень, правый)
 */
template<typename T>
void RBTree<T>::inOrderTraversal(RBNode<T> *curr) {
    if (curr == nullNode) {
        return;
    }
    inOrderTraversal(curr->left);
    std::cout << curr->val << " ";
    inOrderTraversal(curr->right);
}

template<typename T>
void RBTree<T>::inOrderTraversal() {
    this->inOrderTraversal(this->root);
    std::cout << std::endl;
}


/**
 * Обратный симметричный обход (правый, корень, левый)
 */
template<typename T>
void RBTree<T>::reverseInOrderTraversal(RBNode<T> *curr) {
    if (curr == nullNode) {
        return;
    }
    reverseInOrderTraversal(curr->right);
    std::cout << curr->val << " ";
    reverseInOrderTraversal(curr->left);
}

template<typename T>
void RBTree<T>::reverseInOrderTraversal() {
    this->reverseInOrderTraversal(this->root);
    std::cout << std::endl;
}

template<typename T>
void RBTree<T>::print(RBNode<T> *q, long n) {
    long i;
    if (!q->isNull())
    {
        print(q->right, n+5);
        for (i = 0; i < n; i++)
//            printf(" ");
            std::cout << " ";
        char color = 'R';
        if (q->color == 0) {
            color = 'B';
        }
//        printf("%d %c\n", q->val, color);
        std::cout << q->val << " " << color << "\n";
        print(q->left, n+5);
    }
}

/**
 * Возвращает true, если в дереве есть значение val
 * @param val Значение, которое ищем
 * @return Есть ли значение в дереве
 */
template<typename T>
bool RBTree<T>::has(T val) const {
    return !this->find(val)->isNull();
}

/**
 * Возвращает вектор значений данного дерева
 * @return Вектор значений дерева
 */
template<typename T>
std::vector<T> RBTree<T>::to_vector() {
    std::vector<T> result = {};
    this->to_vector_traversal(this->root, result);
    return result;
}

/**
 * Рекурсивно обходит дерево, засовывая значения узлов в вектор vect
 * @param curr Текущий узел обхода
 * @param vect Вектор, куда складываются значения пройденных узлов
 */
template<typename T>
void RBTree<T>::to_vector_traversal(RBNode<T> *curr, std::vector<T>& vect) {
    if (curr == nullNode) {
        return;
    }
    to_vector_traversal(curr->left, vect);
    vect.push_back(curr->val);
    to_vector_traversal(curr->right, vect);
}
