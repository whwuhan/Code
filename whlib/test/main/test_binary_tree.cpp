#include <iostream>
#include <vector>
#include "../../include/basic/abstract_data_type/binary_tree.h"
using namespace std;
using namespace wh::basic::adt;
int main()
{
    Binary_tree<int> bt;
    vector<int> vec ={0,1,2,3,4,5};
    bt.create_binary_tree(vec);
    auto root = bt.get_root();
    cout << bt.get_size() << endl;
    cout << root->data << endl;
    cout << root->left_child->data << endl; 
    cout << root->right_child->data << endl; 
    cout << root->left_child->left_child->data << endl; 
    cout << root->left_child->right_child->data << endl; 
    cout << root->right_child->left_child->data << endl; 
    cout << (root->right_child->right_child == nullptr) << endl;
}