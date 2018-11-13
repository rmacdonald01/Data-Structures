//
//  binHeap.cpp
//  HW04
//
//  Created by Bobby Macdonald on 11/12/18.
//  Copyright © 2018 Bobby Macdonald. All rights reserved.
//

#include <iostream>
#include <cstdlib>
#include <queue>
#include <algorithm>    //to get swap function
#include "bintree.h"

using namespace std;
using namespace main_savitch_10;



template <class Item>
void change(binary_tree_node<Item>* &root, binary_tree_node<Item>* &child);

template <class Item>
binary_tree_node<Item>* heap(binary_tree_node<Item>* root_ptr);


int main(){
    cout << "Trees:" << endl;
    
    binary_tree_node<int> *heap_root = new binary_tree_node<int> (10);
    heap_root->set_left(new binary_tree_node<int> (4));
    heap_root->set_right(new binary_tree_node<int> (18));
    heap_root->left()->set_left(new binary_tree_node<int> (2));
    heap_root->right()->set_left(new binary_tree_node<int> (13));
    heap_root->left()->set_right(new binary_tree_node<int> (7));
    heap_root->right()->set_right(new binary_tree_node<int> (25));
    heap_root->left()->left()->set_left(new binary_tree_node<int> (1));
    heap_root->left()->right()->set_left(new binary_tree_node<int> (5));
    heap_root->left()->left()->set_right(new binary_tree_node<int> (3));
    heap_root->left()->right()->set_right(new binary_tree_node<int> (9));
    heap_root->right()->left()->set_left(new binary_tree_node<int> (11));
    heap_root->right()->right()->set_left(new binary_tree_node<int> (20));
    heap_root->right()->left()->set_right(new binary_tree_node<int> (15));
    heap_root->right()->right()->set_right(new binary_tree_node<int> (30));
    
    
    print(heap_root, 0);
    
    heap(heap_root);
    
    print(heap_root, 0);
    
    return 0;
}

template <class Item>
void change(binary_tree_node<Item>* &root, binary_tree_node<Item>* &child){
    Item temp = child->data();
    child->set_data(root->data());
    root->set_data(temp);
}

template <class Item>
binary_tree_node<Item>* heap(binary_tree_node<Item> *root_ptr){  //will make a minimum heap
    
    binary_tree_node<Item> *temp = root_ptr;
    
    if (temp->left() != NULL){
        
        if (temp->data() > temp->left()->data()){
            binary_tree_node<Item>* other = temp->left();
            temp->left()->set_data(root_ptr->data());
            root_ptr->set_data(other->data());
        }
        
        heap(temp->left());
    }
    
    if (temp->right() != NULL){
        if (temp->data() > temp->right()->data()){
            binary_tree_node<Item>* another = temp->right();
            temp->right()->set_data(root_ptr->data());
            root_ptr->set_data(another->data());
        }
        heap(temp->right());
    }
    
    
    return root_ptr;
}

