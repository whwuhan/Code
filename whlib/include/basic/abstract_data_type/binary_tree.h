/**
 * 完全二叉树
 * wuhan
 * 2020.08.17
 * 
*/
#ifndef BINARY_TREE_H
#define BINARY_TREE_H
#include <vector>
namespace wh{
    namespace basic{
        namespace adt{
            //=================二叉树节点=================
            /**
             * 只能指定具体类型的typedef
             * 例如typedef vector<int> v
            */
            template <typename T>
            struct Node{
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


            //===================二叉树==================
            template <typename T>
            class Binary_tree{
            protected:
                Node<T>* root;//根节点
                unsigned int size;//二叉树的节点个数
            public:
                Binary_tree();
                unsigned int get_size();
                Node<T>*& get_root();//注意这里返回的是原有指针的引用，目的是为了能够改变对象中root的指向
                //创建完全的二叉树（不是二叉排序树）
                void create_tree(std::vector<T>& vector_t);
                void create_tree(std::vector< Node<T> >& vector_node_t);
                //按顺序插入
                void insert(T& t);
                void insert(Node<T>& t);
                //三种遍历递归实现
                void pre_order_traverse(Node<T>* node_ptr,std::vector< Node<T>* >& res);//先序遍历，结果存放在res中，存放的是节点的指针
                void in_order_traverse(Node<T>* node_ptr,std::vector< Node<T>* >& res);//中序遍历，结果存放在res中
                void post_order_traverse(Node<T>* node_ptr,std::vector< Node<T>* >& res);//后序遍历，结果存放在res中
                //释放所有空间(析构函数调用)
                void delete_tree(Node<T>*& node_ptr);//注意这里参数传递的是指针的引用，不是指针的副本
                virtual ~Binary_tree();
            };

            //无参构造函数
            template <typename T>
            Binary_tree<T>::Binary_tree():root(nullptr),size(0)
            {}

            //获取节点个数
            template <typename T>
            unsigned int Binary_tree<T>::get_size(){
                return size;
            }

            //获取根节点
            template <typename T>
            Node<T>*& Binary_tree<T>::get_root(){
                return root;
            }

            //创建链式结构存储的完全二叉树
            template <typename T>
            void Binary_tree<T>::create_tree(std::vector<T>& vector_t){
                size = vector_t.size();//获取节点个数
                std::vector< Node<T>* > vector_node_t_ptr(size);//存放所有节点的指针

                if(size != 0){
                    //构造所有节点的指针
                    for(int i = 0; i < size; i++){
                        vector_node_t_ptr[i] = new Node<T>(vector_t[i]);
                    }
                    root = vector_node_t_ptr[0];//初始化根节点指针
                    //开始构造完全二叉树
                    for(int i = 0; i < size; i++){
                        //添加左孩子
                        if((2 * i + 1) < size){
                            vector_node_t_ptr[i]->left_child = vector_node_t_ptr[2 * i + 1];
                        }
                        else{
                            //Node<T>的构造函数已经将左右孩子初始化为空指针了
                            return;
                        }
                        
                        //添加右孩子
                        if( (2 * (i + 1)) < size ){
                            vector_node_t_ptr[i]->right_child = vector_node_t_ptr[2 * (i + 1)];
                        }
                        else{
                            //Node<T>的构造函数已经将左右孩子初始化为空指针了
                            return;
                        }
                    }
                }
                else{
                    return;
                }
            }

            template <typename T>
            void Binary_tree<T>::create_tree(std::vector< Node<T> >& vector_node_t){

            }

            //插入
            template <typename T>
            void Binary_tree<T>::insert(T& t){

            }

            template <typename T>
            void Binary_tree<T>::insert(Node<T>& t){
                
            }

            //三种遍历递归实现
            //先序
            template <typename T>
            void Binary_tree<T>::pre_order_traverse(Node<T>* node_ptr,std::vector< Node<T>* >& res){
                if(node_ptr){
                    res.push_back(node_ptr);
                    pre_order_traverse(node_ptr->left_child,res);
                    pre_order_traverse(node_ptr->right_child,res);
                }
                return ;
            }

            //中序
            template <typename T>
            void Binary_tree<T>::in_order_traverse(Node<T>* node_ptr,std::vector< Node<T>* >& res){
                if(node_ptr){
                    in_order_traverse(node_ptr->left_child,res);
                    res.push_back(node_ptr);
                    in_order_traverse(node_ptr->right_child,res);
                }
                return ;
            }

            //后序
            template <typename T>
            void Binary_tree<T>::post_order_traverse(Node<T>* node_ptr,std::vector< Node<T>* >& res){
                if(node_ptr){
                    post_order_traverse(node_ptr->left_child,res);
                    post_order_traverse(node_ptr->right_child,res);
                    res.push_back(node_ptr);
                }
                return ;
            }
            
            //释放树内存
            template <typename T>
            void Binary_tree<T>::delete_tree(Node<T>*& node_ptr){
                if(node_ptr){
                    delete_tree(node_ptr->left_child);
                    delete_tree(node_ptr->right_child);
                    delete node_ptr;
                    node_ptr = nullptr;
                }
                return ;
            }

            //析构
            template <typename T>
            Binary_tree<T>::~Binary_tree(){
                delete_tree(root);
            }
        }
    }
}

#endif