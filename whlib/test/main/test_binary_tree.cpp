#include <iostream>
#include <vector>
#include "../../include/basic/abstract_data_type/binary_tree.h"
using namespace std;
using namespace wh::basic::adt;
int main()
{
    Binary_tree<int> bt;
    vector<int> vec ={0,1,2,3,4,5,6,7,8};
    bt.create_tree(vec);
    Node<int>*& root = bt.get_root();
    // cout << bt.get_size() << endl;
    // cout << root->data << endl;
    // cout << root->left_child->data << endl; 
    // cout << root->right_child->data << endl; 
    // cout << root->left_child->left_child->data << endl; 
    // cout << root->left_child->right_child->data << endl; 
    // cout << root->right_child->left_child->data << endl; 

    //测试遍历
    // vector< Node<int>* > res;
    // bt.pre_order_traverse(bt.get_root(),res);
    // for(auto it : res)
    // {
    //     cout << it->data << endl;
    // }
    // cout << "--------------" <<endl;
    // res.clear();
    // bt.in_order_traverse(bt.get_root(),res);
    // for(auto it : res)
    // {
    //     cout << it->data << endl;
    // }
    // cout << "--------------" <<endl;
    // res.clear();
    // bt.post_order_traverse(bt.get_root(),res);
    // for(auto it : res)
    // {
    //     cout << it->data << endl;
    // }


    //测试析构
    cout << bt.get_size() << endl;
    bt.delete_tree(root);
    cout << bt.get_size() << endl;
    //cout << (root == nullptr) << endl;
    cout << (bt.get_root()==nullptr) << endl;
    //cout << root->data << endl;
}