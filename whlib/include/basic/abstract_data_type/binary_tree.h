#ifndef BINARY_TREE_H
#define BINARY_TREE_H
//二叉树节点
template <typename T>
struct Node
{
    T data;
    Node<T> *left_child;
    Node<T> *right_child;

    Node();
    Node(const T data);
};

//构造函数
template <typename T>
Node<T>::Node():data(),left_child(nullptr),right_child(nullptr)
{}

template <typename T>
Node<T>::Node(const T data):data(data),left_child(nullptr),right_child(nullptr)
{}


//二叉树
template <typename T>
class Binary_tree
{
protected:
    Node<T>* root;//根节点
    unsigned int size;//二叉树的节点个数
public:
    Binary_tree();
    
};


#endif